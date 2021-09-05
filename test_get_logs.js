const { WindowImagetter } = require('./dist/index');

process.env.TESSDATA_PREFIX = "C:\\Users\\Chase Roth\\Desktop\\tessdata";

//WindowImgetter.SetupTesseractTESSDATA_PREFIX(__dirname + "../static/tessdata");

const logs = WindowImagetter.TryGetTribeLogText("ARK: Survival Evolved", __dirname + "\\static\\tessdata", 0, 0, 640, 480);

switch (logs.ErrorCode) {
  case WindowImagetter.WinImgGetError.Success:
    console.log(logs.TribeLogText);
    break;
  case WindowImagetter. WinImgGetError.FailedToFindWindow:
    console.log("FailedToFindWindow");
    break;
  case WindowImagetter. WinImgGetError.BitBlockTransferFailed:
    console.log("BitBlockTransferFailed");
    break;
  case WindowImagetter. WinImgGetError.FailedToGetClientRect:
    console.log("FailedToGetClientRect");
    break;
  case WindowImagetter. WinImgGetError.TesseractInitializationFailure:
    console.log("TesseractInitializationFailure");
    break;
}
