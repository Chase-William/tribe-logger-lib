const { WindowImgetter, WinImgGetError } = require('./dist/index');
const fs = require('fs');

const bitmapResult = WindowImgetter.GetWindowBitmap("ARK: Survival Evolved");

console.log("ErrorCode: " + bitmapResult.ErrorCode);

if (!bitmapResult.ErrorCode == WinImgGetError.Success) {
  console.log("An issue occured and therefore the bitmap cannot be saved...");
  return;
}
const view = new Uint8Array(bitmapResult.BitmapBuffer);
console.log(view);

fs.writeFileSync('bitmapResult.bmp', view, (err) => {
  if (err) return console.log(err);
  console.log("Saved");
});