/*
  Authored by Chase Roth 7/30/2021
  See repository root directory for more information.

  Type-Script front end for using this API.
*/

var myModule = require("bindings")("addon");

export module WindowImgetter {
  export function GetWindowBitmap(windowName: string): ArrayBuffer {
    return myModule.GetWindowBitmap(windowName);
  }
  
  export function GetTribeLogText(windowName: string, left: Number, top: Number, right: Number, bottom: Number): string {
    return myModule.GetTribeLogText(windowName, left, top, right, bottom);
  }
}