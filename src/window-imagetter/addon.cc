#pragma once
#include <nan.h>
#include "sync.h"

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New<v8::String>("GetWindowBitmap").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(GetWindowBitmap)).ToLocalChecked());
  Nan::Set(target, Nan::New<v8::String>("TryGetTribeLogText").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(TryGetTribeLogText)).ToLocalChecked());
}

NODE_MODULE(addon, InitAll);
//NAN_MODULE_WORKER_ENABLED(addon, InitAll)