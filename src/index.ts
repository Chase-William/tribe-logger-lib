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
  
  export function TryGetTribeLogText(windowName: string, left: Number, top: Number, right: Number, bottom: Number): TribeLog {
    return myModule.TryGetTribeLogText(windowName, left, top, right, bottom);
  }

  export function TestMethod(): string {
    return myModule.TestMethod();
  }

  export class BitmapResult {
    ErrorCode: WinImgGetError;
    BitmapBuffer: ArrayBuffer;
  }
  
  export class TribeLog {
    ErrorCode: WinImgGetError;
    TribeLogText: string;
  }
}