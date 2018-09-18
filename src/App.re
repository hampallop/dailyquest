[%bs.raw {|require('./App.css')|}];

type item = {
  title: string,
  completed: bool,
};

type state = {
  items: list(item),
  task: string,
};

type action =
  | Toggle(int)
  | HandleTaskInput(string)
  | AddToDo(item);

let component = ReasonReact.reducerComponent("App");

let initialItems: list(item) = [
  {title: "first task", completed: true},
  {title: "second task", completed: false},
];

module Styles = {
  open Css;
  let inputFocus = Css.focus([outlineStyle(none)]);
  let input =
    style([
      focus([inputFocus]),
      paddingLeft(px(20)),
      padding(px(10)),
      fontSize(px(15)),
      width(px(300)),
      borderRadius(px(20)),
      border(px(2), solid, hex("6699CC")),
      marginTop(px(10)),
      fontFamily("menlo"),
    ]);
  let form =
    style([display(`flex), flexDirection(`column), alignItems(`center)]);
};

let make = _children => {
  let renderItems = (items, send) =>
    items
    |> List.mapi((index, item) =>
         <TodoItem
           key={item.title}
           onClick={_ => send(Toggle(index))}
           title={item.title}
           isCompleted={item.completed}
         />
       )
    |> Array.of_list
    |> ReasonReact.array;
  {
    ...component,
    initialState: () => {items: initialItems, task: ""},
    reducer: (action, state) =>
      switch (action) {
      | Toggle(index) =>
        ReasonReact.Update({
          ...state,
          items:
            state.items
            |> List.mapi((itemIndex, item) =>
                 itemIndex == index ?
                   {...item, completed: !item.completed} : item
               ),
        })
      | HandleTaskInput(input) => ReasonReact.Update({...state, task: input})
      | AddToDo(task) =>
        ReasonReact.Update({items: [task, ...state.items], task: ""})
      },
    render: ({state, send}) =>
      <div className="App">
        <form
          className=Styles.form
          onSubmit={
            event => {
              ReactEvent.Form.preventDefault(event);
              let value = ReactEvent.Form.target(event)##task##value;
              let payload = {title: value, completed: false};
              switch (value) {
              | "" => Js.log("Empty")
              | _ => send(AddToDo(payload))
              };
            }
          }>
          {renderItems(state.items, send)}
          <input
            className=Styles.input
            name="task"
            type_="text"
            autoComplete="off"
            placeholder="input here ..."
            value={state.task}
            onChange={
              event =>
                send(HandleTaskInput(ReactEvent.Form.target(event)##value))
            }
          />
        </form>
      </div>,
  };
};
