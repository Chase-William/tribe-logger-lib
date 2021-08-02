/*
  Authored by Chase Roth 7/30/2021
  See repository root directory for more information.

  Type-Script front end for using this API.
*/

var myModule = require("bindings")("addon");

exports.GetWindowBitmap = function GetWindowBitmap(windowName: string): ArrayBuffer {
  return myModule.GetWindowBitmap(windowName);
}