/*
  Need to update both functions below to return a key/value pair like:
  Object:
    ErrorCode: NULL,
    BitmapData: 0x0239F439

  Checkout: https://github.com/nodejs/nan/blob/master/doc/maybe_types.md#api_nan_define_own_property
*/
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

NAN_METHOD(TryGetTribeLogText) {
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
  // Get tuple from native function contianing a possible errCode & the data
  std::tuple<int*, const char*> r = InternalTryGetTribeLogText(windowName, left, top, right, bottom);
  // Create a blank object that we will append properties to (errCode & data)
  v8::Local<v8::Object> b = Nan::Nothing<v8::Local<v8::Object>>().ToChecked();  

  v8::MaybeLocal<v8::Number> nanErr;
  int* err = std::get<0>(r);

  // Nan::Maybe<bool> test = Nan::DefineOwnProperty(b, Nan::New<v8::String>("ErrorCode").ToLocalChecked(), Nan::New<v8::Number>(err));
  // If failure to define own property
  if (!Nan::DefineOwnProperty(b, Nan::New<v8::String>("ErrorCode").ToLocalChecked(), Nan::New<v8::Number>(err)).ToChecked()) {

  }

  if (err != nullptr) { // Return error
    nanErr = Nan::New<v8::Number>(err);

  }
  const char* logText = std::get<1>(r);
  // if (!logText) {
  //   std::cout << "LogText was empty when returned from func InternalGetTribeLogText" << std::endl;
  // }
  v8::Local<v8::String> rText = Nan::New<v8::String>(logText).ToLocalChecked(); // fix -> to not crash process upon checked
  

  info.GetReturnValue().Set(rText);
}