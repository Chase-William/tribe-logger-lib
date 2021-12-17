const { WindowImagetter } = require('./dist/index');

process.env.TESSDATA_PREFIX = "C:\\Users\\Chase Roth\\Desktop\\tessdata";

//WindowImgetter.SetupTesseractTESSDATA_PREFIX(__dirname + "../static/tessdata");

const area = {
  left: 0,
  top: 0,
  width: 640,
  height: 480
};

const logs = WindowImagetter.TryGetTribeLogText("ARK: Survival Evolved", __dirname + "\\static\\tessdata", area);

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
  default:
    console.log("Something went wrong, the default switch should never be triggered...");
    break;
}
