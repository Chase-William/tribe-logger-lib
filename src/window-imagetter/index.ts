/*
  Authored by Chase Roth 7/30/2021
  See repository root directory for more information.

  Type-Script front end for using this API.
*/

var myModule = require("bindings")("addon");

export enum WinImgGetError {
  Success = 0,
  FailedToFindWindow = 1,
  FailedToGetClientRect = 2,
  BitBlockTransferFailed = 3,
  TesseractInitializationFailure = 4
};

export module WindowImgetter {
  export function GetWindowBitmap(windowName: string): BitmapResult {
    return myModule.GetWindowBitmap(windowName);
  }
  
  export function TryGetTribeLogText(windowName: string, left: Number, top: Number, right: Number, bottom: Number): string {
    return myModule.TryGetTribeLogText(windowName, left, top, right, bottom);
  }

  export function CreateNewBitmapReturn(value: number): BitmapResult {
    return myModule.NewBitmapReturn(value);
  }

  export class BitmapResult {
    ErrorCode: WinImgGetError;
    BitmapBuffer: ArrayBuffer;
  }
}