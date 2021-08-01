var myModule = require("bindings")("addon");

exports.GetWindowBitmap = function GetWindowBitmap(windowName: string): ArrayBuffer {
  return myModule.getWindowBitmap(windowName);
}