const getter = require('./dist/window-imagetter/index');
const fs = require('fs');

let result = getter.WindowImgetter.GetWindowBitmap("ARK: Survival Evolved");
console.log("error: " + result.ErrorCode);
console.log("Js-Buffer: ");
console.log(result);

const view = new Uint8Array(result.BitmapBuffer);
console.log(view);

fs.writeFileSync('test.bmp', view, (err) => {
  if (err) return console.log(err);
  console.log("Saved");
});