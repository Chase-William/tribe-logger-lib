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


std::tuple<int*, const char*>InternalGetTribeLogText(std::string windowName, int left, int top, int right, int bottom) {
  unsigned long size;

  std::tuple<int*, char*> r = GetNativeWindowBitmap(windowName, size);

  int *err = std::get<0>(r);
  if (err != nullptr) {
    return std::make_tuple<int*, const char*>(&(*err), NULL);
  }
  const l_uint8 *buf = (l_uint8*)std::get<1>(r);
  //const std::shared_ptr<l_uint8*> buf = std::make_shared<l_uint8*>(GetNativeWindowBitmap(windowName, size));
  //const l_uint8* buf = (l_uint8*)GetNativeWindowBitmap(windowName, size);
  //const l_uint8 *bmpBuf = std::static_pointer_cast<l_uint8 *>(bmpBuf);
  const char *text;

  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
  // Init with English, without lang specification
  if (api->Init(NULL, "eng")) {
    fprintf(stderr, "Could not initialize tesseract.\n");
    return std::make_tuple<int*, const char*>(new int(5), NULL);
  }

  api->SetRectangle(left, top, right - left, bottom - top);
  Pix *img = pixReadMemBmp(buf, size);
  api->SetImage(img);
  text = api->GetUTF8Text();

  api->End();
  delete api; // Cleanup tesseract api
  pixDestroy(&img); // Cleanup leptonic bitmap type for tesseract
  delete buf; // Cleanup bitmap

  return std::make_tuple<int*, const char*>(NULL, &(*text)); // Return text found
}