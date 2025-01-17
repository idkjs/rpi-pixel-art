open State;

let selector = (model: state) =>
  switch (model.activeTool) {
  | Color(color) => Some(color)
  | _ => None
  };

let isEqualColor = (selectedColor, currentColor) =>
  selectedColor->Belt.Option.mapWithDefault(false, color =>
    color == currentColor
  );

let getColorPickerMaxWidth = colorWidth => {
  let numberOfColors = Settings.availableColors |> Belt.Array.length;

  let numberOfRows = 2;
  // add some more space to account for border around and space inbetween
  (numberOfColors + 2) * colorWidth / numberOfRows;
};

[@react.component]
let make = (~className="") => {
  let selectedColor = Store.useSelector(selector);
  let dispatch = Store.useDispatch();

  let pickerWidth =
    Css.(
      style([
        maxWidth(px(getColorPickerMaxWidth(Styles.colorSquareSize))),
        media(
          Styles.Breakpoint.down(`sm),
          [
            maxWidth(
              px(getColorPickerMaxWidth(Styles.mobileColorSquareSize)),
            ),
          ],
        ),
      ])
    );

  <div
    className={Cn.fromList([
      "flex flex-wrap max-w-xs self-start",
      pickerWidth,
      className,
    ])}>
    {Settings.availableColors
     ->Belt.Array.mapWithIndex((ind, rgbColor) =>
         <div
           key={ind |> string_of_int}
           className={Cn.fromList([
             Css.(
               style([
                 width(px(Styles.colorSquareSize)),
                 height(px(Styles.colorSquareSize)),
                 backgroundColor(rgbColor |> ColorUtils.colorToCss),
                 media(
                   Styles.Breakpoint.down(`sm),
                   [
                     width(px(Styles.mobileColorSquareSize)),
                     height(px(Styles.mobileColorSquareSize)),
                   ],
                 ),
               ])
             ),
             "border-2 mr-1 mb-1",
             Cn.on(
               "border-gray-500 ",
               !isEqualColor(selectedColor, rgbColor),
             ),
             Cn.on(
               "shadow-outline",
               isEqualColor(selectedColor, rgbColor),
             ),
           ])}
           onClick={_ => dispatch(ColorSelected(rgbColor))}
         />
       )
     ->React.array}
  </div>;
};
