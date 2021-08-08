/*
  Authored by Chase Roth 7/30/2021
  See repository root directory for more information.

  Type-Script front end for using this API.
*/

var myModule = require("bindings")("addon");

exports.GetWindowBitmap = function GetWindowBitmap(windowName: string): ArrayBuffer {
  return myModule.GetWindowBitmap(windowName);
}

exports.GetTribeLogText = function GetTribeLogText(windowName: string, left: Number, top: Number, right: Number, bottom: Number) {
  return myModule.GetTribeLogText(windowName, left, top, right, bottom);
}