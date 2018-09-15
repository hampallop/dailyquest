[%bs.raw {|require('./App.css')|}];

type item = {
  title: string,
  completed: bool,
};

type state = {
  foo: string,
  items: list(item),
  task: string,
};

type action =
  | Click(int)
  | Submit(item)
  | HandleTaskInput(string);

let component = ReasonReact.reducerComponent("App");

module Item = {
  let component = ReasonReact.statelessComponent("Item");
  let make = (~title, ~onClick, ~identity=?, ~isCompleted=false, _children) => {
    ...component,
    render: _self =>
      <div>
        <input
          type_="checkbox"
          id={
            switch (identity) {
            | None => title
            | Some(identity) => identity
            }
          }
          onChange=onClick
          checked=isCompleted
          readOnly=true
        />
        <label
          htmlFor={
            switch (identity) {
            | None => title
            | Some(identity) => identity
            }
          }>
          {ReasonReact.string(title)}
        </label>
      </div>,
  };
};

let initialItems: list(item) = [
  {title: "first task", completed: true},
  {title: "second task", completed: false},
];

let make = _children => {
  let renderItems = (items, send) =>
    ReasonReact.array(
      Array.of_list(
        List.mapi(
          (index, item) =>
            <Item
              key={item.title}
              onClick={_ => send(Click(index))}
              title={item.title}
              isCompleted={item.completed}
            />,
          items,
        ),
      ),
    );

  {
    ...component,
    initialState: () => {foo: "hello", items: initialItems, task: ""},
    reducer: (action, state) =>
      switch (action) {
      | Click(index) =>
        ReasonReact.Update({
          ...state,
          items:
            List.mapi(
              (itemIndex, item) =>
                itemIndex == index ?
                  {...item, completed: !item.completed} : item,
              state.items,
            ),
        })
      | HandleTaskInput(input) => ReasonReact.Update({...state, task: input})
      | Submit(task) =>
        ReasonReact.Update({
          ...state,
          items: [task, ...state.items],
          task: "",
        })
      },
    render: ({state, send}) =>
      <div className="App">
        {ReasonReact.string(state.foo)}
        <form
          onSubmit={
            event => {
              ReactEvent.Form.preventDefault(event);
              let value = ReactEvent.Form.target(event)##task##value;
              let payload = {title: value, completed: false};
              switch (value) {
              | "" => Js.log("Empty")
              | _ => send(Submit(payload))
              };
            }
          }>
          {renderItems(state.items, send)}
          <input
            name="task"
            type_="text"
            value={state.task}
            onChange={
              event =>
                send(HandleTaskInput(ReactEvent.Form.target(event)##value))
            }
          />
          <button> {ReasonReact.string("click me")} </button>
        </form>
      </div>,
  };
};
