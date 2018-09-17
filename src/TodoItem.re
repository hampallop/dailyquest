module Styles = {
  open Css;
  let wrapperBox =
    style([
      padding(px(15)),
      backgroundColor(hex("6699CC")),
      width(px(300)),
      borderRadius(px(5)),
      textAlign(`left),
      display(`flex),
      margin(px(10)),
    ]);
  let showInputBox = isCompleted =>
    style([
      width(px(40)),
      height(px(40)),
      borderRadius(px(20)),
      border(px(1), solid, white),
      display(inlineBlock),
      cursor(`pointer),
      backgroundColor(isCompleted ? white : transparent),
    ]);
  let label =
    style([
      marginLeft(px(20)),
      color(white),
      fontFamily("menlo"),
      marginTop(px(12)),
    ]);
};

let component = ReasonReact.statelessComponent("TodoItem");
let make = (~title, ~onClick, ~identity=?, ~isCompleted=false, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.wrapperBox>
      <div
        className={Styles.showInputBox(isCompleted)}
        id={
          switch (identity) {
          | None => title
          | Some(identity) => identity
          }
        }
        onClick
        readOnly=true
      />
      <label
        className=Styles.label
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
