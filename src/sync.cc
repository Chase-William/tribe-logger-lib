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

// Fetch a single bitmap
NAN_METHOD(GetWindowBitmap) {
  Nan::Utf8String windowName(Nan::To<v8::String>(info[0]).ToLocalChecked());
  v8::Local<v8::Boolean> v8IncludeFileHeader = Nan::To<v8::Boolean>(info[1]).ToLocalChecked();

  // Get underlying char* from Nan string
  const char* ptr =  windowName.operator*();
  bool includeFileHeader = v8IncludeFileHeader.operator*()->Value();

  // Call our custom API for polling a bitmap from a target window
  WindowBitmapResult r = GetNativeWindowBitmap(ptr, includeFileHeader);

#if _DEBUG
  std::cout << "ErrorCode: " << r.ErrorCode << std::endl;
  std::cout << "BitmapBuffer Address: " << &(r.BitmapBuffer) << std::endl;
  std::cout << "Size: " << r.Size << std::endl;
  std::cout << "Width: " << r.Width << std::endl;
  std::cout << "Height: " << r.Height << std::endl;
#endif

  int* err = r.ErrorCode;

  // Create generic JS object to append to
  v8::Local<v8::Object> jsObj = Nan::New<v8::Object>();

  // Create propNames and values
  v8::Local<v8::String> errorName = Nan::New("ErrorCode").ToLocalChecked();
  v8::Local<v8::Number> errorValue = Nan::New(err == NULL ? 0 : *err);
  delete err; // cleanup bc we are passing by value to v8 so this can be deleted
  v8::Local<v8::String> bufferName = Nan::New("BitmapBuffer").ToLocalChecked();
  v8::Local<v8::Object> bufferValue = Nan::NewBuffer(r.BitmapBuffer, (uint32_t)r.Size, DisposeNativeBitmap, NULL).ToLocalChecked();
  // Creat width js prop
  v8::Local<v8::String> widthName = Nan::New("Width").ToLocalChecked();
  v8::Local<v8::Number> widthValue = Nan::New(r.Width);
  // Create height js prop
  v8::Local<v8::String> heightName = Nan::New("Height").ToLocalChecked();
  v8::Local<v8::Number> heightValue = Nan::New(r.Height);

  // Apply props to js obj
  Nan::Set(jsObj, errorName, errorValue);
  Nan::Set(jsObj, bufferName, bufferValue);
  Nan::Set(jsObj, widthName, widthValue);
  Nan::Set(jsObj, heightName, heightValue);

  // Set obj as return
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
  TribeLogResult r = InternalTryGetTribeLogText(windowName, tessDataPath, left, top, right, bottom);

  int* err = r.ErrorCode;
 
  // Create js obj
  v8::Local<v8::Object> jsObj = Nan::New<v8::Object>();
  // Create error prop
  v8::Local<v8::String> errorName = Nan::New("ErrorCode").ToLocalChecked();
  v8::Local<v8::Number> errorValue = Nan::New(*err);
  delete err;
  // Create tribeLogText prop
  v8::Local<v8::String> logTextName = Nan::New("TribeLogText").ToLocalChecked();
  v8::Local<v8::String> logTextValue = Nan::New(r.TribeLogText).ToLocalChecked();  

  // Apply props to js obj
  Nan::Set(jsObj, errorName, errorValue);
  Nan::Set(jsObj, logTextName, logTextValue);

  // Set object as return
  info.GetReturnValue().Set(jsObj);
}