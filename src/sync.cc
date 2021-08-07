/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2018 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/
#pragma once
#include <nan.h>
#include "sync.h"  // NOLINT(build/include)
#include "window_img_getter.h"
#include <iostream>

// Fetch a single bitmap
NAN_METHOD(GetWindowBitmap) {
  Nan::MaybeLocal<v8::String> windowName = Nan::To<v8::String>(info[0]);
  // Get non-null string, otherwise crash
  v8::Local<v8::String> str = windowName.ToLocalChecked();
  // Start conversion to C++ types
  Nan::Utf8String value(str);
  // Get underlying char* from Nan string
  const char* ptr =  value.operator*();
  unsigned long size;
  // Call our custom API for polling a bitmap from a target window
  char* buffer = GetNativeWindowBitmap(ptr, size);
  // Create JS object Buffer from returned char* buffer (BITMAP w/ header, headerinfo, pixel payload)
  Nan::MaybeLocal<v8::Object> buff = Nan::NewBuffer(
    buffer,
    size,
    DisposeNativeBitmap,
    nullptr
  );
  // Set return
  info.GetReturnValue().Set(buff.ToLocalChecked());
}