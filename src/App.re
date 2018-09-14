[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo: string = "./logo.svg";

type item = {
  title: string,
  completed: bool,
};

type state = {
  foo: string,
  items: list(item),
};

type action =
  | Click
  | Submit(item);

let component = ReasonReact.reducerComponent("App");

let initialItems: list(item) = [
  {title: "first task", completed: true},
  {title: "second task", completed: false},
];

let make = _children => {
  ...component,
  initialState: () => {foo: "hello", items: initialItems},
  reducer: (action, state) =>
    switch (action) {
    | Click => ReasonReact.Update({...state, foo: "world"})
    | Submit(task) =>
      ReasonReact.Update({...state, items: [task, ...state.items]})
    },
  render: ({state, send}) =>
    <div className="App">
      {ReasonReact.string(state.foo)}
      <form
        onSubmit={
          e => {
            ReactEvent.Form.preventDefault(e);
            Js.log(ReactEvent.Form.target(e)##task##value);
            let value = ReactEvent.Form.target(e)##task##value;
            let payload = {title: value, completed: false};
            send(Submit(payload));
          }
        }>
        {
          ReasonReact.array(
            Array.of_list(
              List.map(
                item =>
                  <div>
                    <input type_="checkbox" id={item.title} />
                    <label htmlFor={item.title}>
                      {ReasonReact.string(item.title)}
                    </label>
                  </div>,
                state.items,
              ),
            ),
          )
        }
        <input name="task" type_="text" />
        <button onClick={_event => send(Click)}>
          {ReasonReact.string("click me")}
        </button>
      </form>
    </div>,
};