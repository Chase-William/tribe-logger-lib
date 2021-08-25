const { WindowImgetter, WinImgGetError } = require('./dist/index');

process.env.TESSDATA_PREFIX = "C:\\Users\\Chase Roth\\Desktop\\tessdata";

WindowImgetter.SetupTesseractTESSDATA_PREFIX(__dirname + "../static/tessdata");

const logs = WindowImgetter.TryGetTribeLogText("ARK: Survival Evolved", 0, 0, 640, 480);

if (logs.ErrorCode != WinImgGetError.Success) {
  console.log("Unable to get the tribe log at this time...");
  return;
}
console.log(logs.TribeLogText);