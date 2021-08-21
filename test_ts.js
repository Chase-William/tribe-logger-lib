const getter = require('./dist/window-imagetter/index');
const fs = require('fs');

const bitmapResult = getter.WindowImgetter.GetWindowBitmap("ARK: Survival Evolved");

//const bitmapResult = getter.WindowImgetter.CreateNewBitmapReturn(10);
//console.log("Buffer returned: " + bitmapResult.BitmapBuffer);

const view = new Uint8Array(bitmapResult.BitmapBuffer);
console.log(view);

fs.writeFileSync('bitmapResult.bmp', view, (err) => {
  if (err) return console.log(err);
  console.log("Saved");
});