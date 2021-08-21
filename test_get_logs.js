const { WindowImgetter, WinImgGetError } = require('./dist/index');

const logs = WindowImgetter.TryGetTribeLogText("ARK: Survival Evolved", 0, 0, 640, 480);

if (logs.ErrorCode != WinImgGetError.Success) {
  console.log("Unable to get the tribe log at this time...");
  return;
}
console.log(logs.TribeLogText);