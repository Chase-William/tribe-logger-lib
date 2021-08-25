#pragma once
#include <nan.h>
#include "sync.h" // Contains our functions
#include "env.h"
#include <iostream>

NAN_METHOD(SetTESSDATA_PREFIX) {
  std::cout << "Setting TESSDATA_PREFIX 1\n";
  Nan::Utf8String value(Nan::To<v8::String>(info[0]).ToLocalChecked());
  // malloc(value.length() * sizeof(char));
  std::cout << "Setting TESSDATA_PREFIX 2\n";
  TESSDATA_PREFIX = (char*)malloc(value.length() * sizeof(int));
  std::cout << "Setting TESSDATA_PREFIX 3\n";
  std::memcpy(&TESSDATA_PREFIX, value.operator*(), value.length() * sizeof(int));
  std::cout << "Setting TESSDATA_PREFIX 4\n";
  std::cout << &TESSDATA_PREFIX << std::endl;
  
  /*
    We need our TESS api to load in the correct path for the tessdata/eng.eng.traineddata file.
    Using enviroment variables or by calling a initialize function giving a path or something....
  */
}

void Initialize(v8::Local<v8::Object> exports) {
  Nan::Set(exports, Nan::New<v8::String>("GetWindowBitmap").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(GetWindowBitmap)).ToLocalChecked());
  Nan::Set(exports, Nan::New<v8::String>("TryGetTribeLogText").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(TryGetTribeLogText)).ToLocalChecked());
  Nan::Set(exports, Nan::New<v8::String>("TestMethod").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(TestMethod)).ToLocalChecked());

  Nan::Set(exports, Nan::New<v8::String>("SetTESSDATA_PREFIX").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(SetTESSDATA_PREFIX)).ToLocalChecked());
}

extern "C" NODE_MODULE_EXPORT void
NODE_MODULE_INITIALIZER(v8::Local<v8::Object> exports,
                        v8::Local<v8::Value> module,
                        v8::Local<v8::Context> context) {
  /* Perform addon initialization steps here. */  

  Initialize(exports);
}