type pixel = {
  coords: Coords.t,
  color: Color.t,
};

type t = array(pixel);

let getPixel = (coords, matrix) => {
  matrix
  ->Belt.Array.keep(pixel => Coords.areEqual(coords, pixel.coords))
  ->Belt.Array.get(0);
};

let getPixelColor = (coords, matrix) =>
  (matrix |> getPixel(coords))->Belt.Option.map(pixel => pixel.color);

let unsetPixel = (pixel, matrix) =>
  switch (matrix |> getPixel(pixel.coords)) {
  | None => matrix
  | Some(pixel) =>
    matrix->Belt.Array.keep(p => !Coords.areEqual(p.coords, pixel.coords))
  };

let setPixel = (pixel, matrix) => {
  switch (matrix |> getPixel(pixel.coords)) {
  | None => matrix->Belt.Array.concat([|pixel|])
  | Some(p) =>
    Js.log(p);
    if (p.color === pixel.color) {
      matrix;
    } else {
      matrix
      ->Belt.Array.keep(p => !Coords.areEqual(p.coords, pixel.coords))
      ->Belt.Array.concat([|pixel|]);
    };
  };
};
