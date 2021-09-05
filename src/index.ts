/*
  Authored by Chase Roth 7/30/2021
  See repository root directory for more information.
  Type-Script front end for using this API.
*/

/*
  This path must be a valid relative path from the calling main.js executing dir to the binding native addon
  -- First Line for Node
  -- Second for Electron
*/
const myModule = require("../build/Release/binding");
// const myModule = require("./binding");

export module WindowImagetter {

  export enum WinImgGetError {
    Success = 0,
    FailedToFindWindow = 1,
    FailedToGetClientRect = 2,
    BitBlockTransferFailed = 3,
    TesseractInitializationFailure = 4
  };
  

  export interface Area {
    left: number;
    top: number;
    width: number;
    height: number;
  }

  export function GetWindowBitmap(windowName: string, includeFileHeader: boolean): BitmapResult {
    return myModule.GetWindowBitmap(windowName, includeFileHeader);
  }  

  export function TryGetTribeLogText(windowName: string, tessDataPath: string, area: Area): TribeLogResult {   
    return myModule.TryGetTribeLogText(windowName, tessDataPath, area.left, area.top, area.width, area.height);
  }

  export function TestMethod(): string {
    return myModule.TestMethod();
  }

  export class BitmapResult {
    ErrorCode: WinImgGetError;
    BitmapBuffer: ArrayBuffer;
    Width: Number;
    Height: Number;
  }
  
  export class TribeLogResult {
    ErrorCode: WinImgGetError;
    TribeLogText: string;
  }
}