#pragma once
#include <nan.h>
#include "sync.h" // Contains our functions

void Initialize(v8::Local<v8::Object> exports) {
  Nan::Set(exports, Nan::New<v8::String>("GetWindowBitmap").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(GetWindowBitmap)).ToLocalChecked());
  Nan::Set(exports, Nan::New<v8::String>("TryGetTribeLogText").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(TryGetTribeLogText)).ToLocalChecked());
  Nan::Set(exports, Nan::New<v8::String>("TestMethod").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(TestMethod)).ToLocalChecked());
}

extern "C" NODE_MODULE_EXPORT void
NODE_MODULE_INITIALIZER(v8::Local<v8::Object> exports,
                        v8::Local<v8::Value> module,
                        v8::Local<v8::Context> context) {
  /* Perform addon initialization steps here. */
  Initialize(exports);
}