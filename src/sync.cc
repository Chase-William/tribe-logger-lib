/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2018 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include <nan.h>
#include "pi_est.h"  // NOLINT(build/include)
#include "sync.h"  // NOLINT(build/include)
#include "window_img_getter.h"
#include <iostream>

// Simple synchronous access to the `Estimate()` function
NAN_METHOD(CalculateSync) {
  // expect a number as the first argument
  int points = Nan::To<int>(info[0]).FromJust();
  double est = Estimate(points);

  info.GetReturnValue().Set(est);
}

NAN_METHOD(GetMyNumber) {
  double retval = GetNumber();
  info.GetReturnValue().Set(retval);
}

NAN_METHOD(GetWindowBitmap) {
  Nan::MaybeLocal<v8::String> windowName = Nan::To<v8::String>(info[0]);
  v8::Local<v8::String> str;
  str = windowName.ToLocalChecked();

  //v8::String *v8str = str.operator*();
  Nan::Utf8String value(str);  // Error here

  //Nan::Utf8String almostStr = Nan::Utf8String(str);
  const char* ptr =  value.operator*();

  std::cout << "WindowName given after Nan to C++ type conversion: " << *ptr << std::endl;

  unsigned long size;
  char* buffer = GetNativeWindowBitmap(ptr, size);
  std::cout << "Buffer Address: " << &buffer << " Buffer Length: " << size << std::endl;
  Nan::MaybeLocal<v8::Object> buff = Nan::NewBuffer(
    buffer,
    size,
    DisposeNativeBitmap,
    nullptr
  );

  info.GetReturnValue().Set(buff.ToLocalChecked());
}