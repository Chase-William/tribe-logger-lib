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


const char* InternalGetTribeLogText(std::string windowName, int left, int top, int right, int bottom) {
  unsigned long size;

  //const std::shared_ptr<l_uint8*> buf = std::make_shared<l_uint8*>(GetNativeWindowBitmap(windowName, size));
  const l_uint8* buf = (l_uint8*)GetNativeWindowBitmap(windowName, size);
  //const l_uint8 *bmpBuf = std::static_pointer_cast<l_uint8 *>(bmpBuf);
  const char *text;

  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
  // Init with English, without lang specification
  if (api->Init(NULL, "eng")) {
    fprintf(stderr, "Could not initialize tesseract.\n");
    return nullptr;
  }

  api->SetRectangle(left, top, right - left, bottom - top);
  Pix *img = pixReadMemBmp(buf, size);
  text = api->GetUTF8Text();

  api->End();
  delete api;
  pixDestroy(&img);

  return text;
}