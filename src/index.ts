/*
  Authored by Chase Roth 7/30/2021
  See repository root directory for more information.
  Type-Script front end for using this API.
*/

/*
  This path must be a valid relative path from the calling main.js executing dir to the binding native addon
*/
const myModule = require("../build/Release/binding");

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
  
  export function TryGetTribeLogText(windowName: string, tessDataPath: string, left: Number, top: Number, right: Number, bottom: Number): TribeLog {
    return myModule.TryGetTribeLogText(windowName, tessDataPath, left, top, right, bottom);
  }

  export function TestMethod(): string {
    return myModule.TestMethod();
  }

  export function SetupTesseractTESSDATA_PREFIX(path: string) {
    myModule.SetTESSDATA_PREFIX(path);
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