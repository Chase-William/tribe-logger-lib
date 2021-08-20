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
  
  export function TryGetTribeLogText(windowName: string, left: Number, top: Number, right: Number, bottom: Number): string {
    return myModule.TryGetTribeLogText(windowName, left, top, right, bottom);
  }
}