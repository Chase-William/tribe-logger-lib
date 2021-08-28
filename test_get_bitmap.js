const { WindowImgetter, WinImgGetError } = require('./dist/index');
const fs = require('fs');

const bitmapResult = WindowImgetter.GetWindowBitmap("ARK: Survival Evolved", true);

switch (bitmapResult.ErrorCode) {
  case WinImgGetError.Success:
    const view = new Uint8Array(bitmapResult.BitmapBuffer);
    // console.log(view);

    fs.writeFileSync('bitmapResult.bmp', view, (err) => {
      if (err) return console.log(err);
      console.log("Saved");
    });
    break;
  case WinImgGetError.FailedToFindWindow:
    console.log("FailedToFindWindow");
    break;
  case WinImgGetError.BitBlockTransferFailed:
    console.log("BitBlockTransferFailed");
    break;
  case WinImgGetError.FailedToGetClientRect:
    console.log("FailedToGetClientRect");
    break;
  case WinImgGetError.TesseractInitializationFailure:
    console.log("TesseractInitializationFailure");
    break;
}