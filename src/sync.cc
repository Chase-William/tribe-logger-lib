/*
  Need to update both functions below to return a key/value pair like:
  Object:
    ErrorCode: NULL,
    BitmapData: 0x0239F439

  Checkout: https://github.com/nodejs/nan/blob/master/doc/maybe_types.md#api_nan_define_own_property
*/
#pragma once
#include <nan.h>
#include <iostream>
#include "sync.h"
#include "window_img_getter.h"
#include "tribe_logger.h"

NAN_METHOD(TestMethod) {
  info.GetReturnValue().Set(Nan::New("Was able to retrieve a value (string) from the C++ back-end.").ToLocalChecked());
}

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
  WinImgRtrn result = GetNativeWindowBitmap(ptr, size);
  std::cout << "GetNativeWindowBitmap return\n"; 
  int* err = std::get<0>(result);
  char* buffer = std::get<1>(result);

  // Create generic JS object to append to
  v8::Local<v8::Object> jsObj = Nan::New<v8::Object>();

  std::cout << "Buffer: " << &buffer << std::endl;

  // Create propNames and values
  v8::Local<v8::String> errorName = Nan::New("ErrorCode").ToLocalChecked();
  v8::Local<v8::Number> errorValue = Nan::New(err == NULL ? 0 : *err);
  delete err; // cleanup bc we are passing by value to v8 so this can be deleted
  v8::Local<v8::String> bufferName = Nan::New("BitmapBuffer").ToLocalChecked();
  v8::Local<v8::Object> bufferValue = Nan::NewBuffer(buffer, (uint32_t)size).ToLocalChecked();
  
  // Apply properties
  Nan::Set(jsObj, errorName, errorValue);
  Nan::Set(jsObj, bufferName, bufferValue);

  // Set object as return type
  info.GetReturnValue().Set(jsObj);
}

NAN_METHOD(TryGetTribeLogText) {
  Nan::MaybeLocal<v8::String> v8WindowName = Nan::To<v8::String>(info[0]);
  Nan::MaybeLocal<v8::String> v8tessData = Nan::To<v8::String>(info[1]);
  Nan::MaybeLocal<v8::Integer> v8left = Nan::To<v8::Integer>(info[2]);
  Nan::MaybeLocal<v8::Integer> v8top = Nan::To<v8::Integer>(info[3]);
  Nan::MaybeLocal<v8::Integer> v8right = Nan::To<v8::Integer>(info[4]);
  Nan::MaybeLocal<v8::Integer> v8bottom = Nan::To<v8::Integer>(info[5]);

  std::string windowName = std::string(Nan::Utf8String(v8WindowName.ToLocalChecked()).operator*());
  std::string tessDataPath = std::string(Nan::Utf8String(v8tessData.ToLocalChecked()).operator*());

  int left = (int)v8left.ToLocalChecked().operator*()->Value();
  int top = (int)v8top.ToLocalChecked().operator*()->Value();
  int right = (int)v8right.ToLocalChecked().operator*()->Value();
  int bottom = (int)v8bottom.ToLocalChecked().operator*()->Value();
  // Get tuple from native function contianing a possible errCode & the data
  WinImgTextRtrn result = InternalTryGetTribeLogText(windowName, tessDataPath, left, top, right, bottom);
  int* err = std::get<0>(result);
  const char* logText = std::get<1>(result);
 
  v8::Local<v8::Object> jsObj = Nan::New<v8::Object>();
  v8::Local<v8::String> errorName = Nan::New("ErrorCode").ToLocalChecked();
  v8::Local<v8::Number> errorValue = Nan::New(err == NULL ? 0 : *err);
  delete err;
  v8::Local<v8::String> logTextName = Nan::New("TribeLogText").ToLocalChecked();
  v8::Local<v8::String> logTextValue = Nan::New(logText).ToLocalChecked();  
  Nan::Set(jsObj, errorName, errorValue);
  Nan::Set(jsObj, logTextName, logTextValue);

  // Set object as return type
  info.GetReturnValue().Set(jsObj);
}