const { WindowImagetter } = require('./dist/index');
const fs = require('fs');

console.log("Calling native node addon api for a bitmap from the specified window...");
const bitmapResult = WindowImagetter.GetWindowBitmap("ARK: Survival Evolved", true);

// console.log(bitmapResult)

switch (bitmapResult.ErrorCode) {
  case WindowImagetter.WinImgGetError.Success:
    const view = new Uint8Array(bitmapResult.BitmapBuffer);
    // console.log(view);

    fs.writeFileSync('bitmapResult.bmp', view, (err) => {
      if (err) return console.log(err);
      console.log("Saved");
    });
    break;
  case WindowImagetter.WinImgGetError.FailedToFindWindow:
    console.log("FailedToFindWindow");
    break;
  case WindowImagetter.WinImgGetError.BitBlockTransferFailed:
    console.log("BitBlockTransferFailed");
    break;
  case WindowImagetter.WinImgGetError.FailedToGetClientRect:
    console.log("FailedToGetClientRect");
    break;
  case WindowImagetter.WinImgGetError.TesseractInitializationFailure:
    console.log("TesseractInitializationFailure");
    break;
  default:
    console.log("Something went wrong, the default switch should never be triggered...");
    break;
}