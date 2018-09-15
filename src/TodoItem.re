let component = ReasonReact.statelessComponent("TodoItem");
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