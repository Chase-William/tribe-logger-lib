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
#include "tribe_logger.h"
#include <iostream>

// Fetch a single bitmap
NAN_METHOD(GetWindowBitmap) {
  Nan::MaybeLocal<v8::String> v8WindowName = Nan::To<v8::String>(info[0]);
  // Get non-null string, otherwise crash
  v8::Local<v8::String> str = v8WindowName.ToLocalChecked();
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

NAN_METHOD(GetTribeLogText) {
  Nan::MaybeLocal<v8::String> v8WindowName = Nan::To<v8::String>(info[0]);
  Nan::MaybeLocal<v8::Integer> v8left = Nan::To<v8::Integer>(info[1]);
  Nan::MaybeLocal<v8::Integer> v8top = Nan::To<v8::Integer>(info[2]);
  Nan::MaybeLocal<v8::Integer> v8right = Nan::To<v8::Integer>(info[3]);
  Nan::MaybeLocal<v8::Integer> v8bottom = Nan::To<v8::Integer>(info[4]);

  v8::Local<v8::String> str = v8WindowName.ToLocalChecked(); // Nan::MaybeLocal<v8:String> to std::string conversion
  std::string windowName = std::string(Nan::Utf8String(str).operator*());

  int left = (int)v8left.ToLocalChecked().operator*()->Value();
  int top = (int)v8top.ToLocalChecked().operator*()->Value();
  int right = (int)v8right.ToLocalChecked().operator*()->Value();
  int bottom = (int)v8bottom.ToLocalChecked().operator*()->Value();

  const char* logText = InternalGetTribeLogText(windowName, left, top, right, bottom);

  if (!logText) {
    std::cout << "LogText was empty when returned from func InternalGetTribeLogText" << std::endl;
  }

  info.GetReturnValue().Set(Nan::New<v8::String>(logText).ToLocalChecked());
}