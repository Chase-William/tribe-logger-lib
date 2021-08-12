// Tribe Logging API here
//const tribe_api = require("./window-imagetter/index");
import { WindowImgetter } from "./window-imagetter/index";

export module TribeLogger {
  export function GetTribeLogText(windowName: string, left: Number, top: Number, right: Number, bottom: Number): void {
    const text_logs: string = WindowImgetter.GetTribeLogText(windowName, left, top, right, bottom);
    console.log(text_logs);
  }
}
/*
  TODO:

  - Create Get TribeLogInfo() that returns the string of text containing the tribe log text from the bitmap
    - Add correct params
    - Call internal GetWindowBitmap()
    - Use Tesseract to get text
    - Return text in v8 string to ts/js sender

*/