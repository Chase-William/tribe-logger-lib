const { WindowImgetter, WinImgGetError } = require('./dist/index');

process.env.TESSDATA_PREFIX = "C:\\Users\\Chase Roth\\Desktop\\tessdata";

//WindowImgetter.SetupTesseractTESSDATA_PREFIX(__dirname + "../static/tessdata");

const logs = WindowImgetter.TryGetTribeLogText("ARK: Survival Evolved", __dirname + "\\static\\tessdata", 0, 0, 640, 480);

// if (logs.ErrorCode != WinImgGetError.Success) {
//   console.log("Unable to get the tribe log at this time...");
//   return;
// }

switch (logs.ErrorCode) {
  case WinImgGetError.Success:
    console.log(logs.TribeLogText);
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

//console.log(logs.TribeLogText);