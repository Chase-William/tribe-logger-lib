/*
  Authored by Chase Roth 8/7/2021
  See repository root directory for more information.
*/

#pragma once
#include <iostream>
#include "tribe_logger.h"
#include "window_img_getter.h"
// Tesseract OCR headers
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

TribeLogResult InternalTryGetTribeLogText(std::string windowName, std::string tessData, int left, int top, int width, int height) {

  WindowBitmapResult r = GetNativeWindowBitmap(windowName, true);
  
  int* err = r.ErrorCode;
  const l_uint8 *buf = (l_uint8*)r.BitmapBuffer;
  const char *text = NULL;
  if (*err != WinImgGetError::Success) {
    text = (new std::string())->c_str();
  } else {
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Init with English, without lang specification
    //std::cout << "TESSDATA: " << tessData << std::endl;
    if (api->Init(tessData.c_str(), "eng")) {
      fprintf(stderr, "Could not initialize tesseract.\n");
      *err = WinImgGetError::TesseractInitializationFailure;
      return TribeLogResult(err, text);
    }
    
    std::cout << "Width: " << width;

    Pix *img = pixReadMemBmp(buf, r.Size);
    api->SetImage(img);
    api->SetRectangle(left, top, width, height);
    text = api->GetUTF8Text();

    api->End();
    delete api; // Cleanup tesseract api
    pixDestroy(&img); // Cleanup leptonic bitmap type for tesseract
  }
  delete buf; // Cleanup bitmap

  return TribeLogResult(err, text); // Return text found
}