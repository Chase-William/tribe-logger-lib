#pragma once
#include <nan.h>
#include "sync.h"
#include "bitmap_result.h"

// Send status to Javascript
// void sendStatus() {
//     // Create callback parameters
//     const int argc = 1;
//     v8::Local<v8::Value> args[argc];

//     // Create generic JS object for status
//     v8::Local<v8::Object> jsObject = Nan::New<v8::Object>();

//     // Create property names & values for each field
//     v8::Local<v8::String> propName = Nan::New("statusCode").ToLocalChecked();
//     v8::Local<v8::Value> propValue = Nan::New(status->statusCode);

//     // Add field to JS object
//     Nan::Set(jsObject, propName, propValue);

//     // And again...
//     propName = Nan::New("statusMessage").ToLocalChecked();
//     propValue = Nan::New(status->statusMessage).ToLocalChecked();
//     Nan::Set(jsObject, propName, propValue);

//     // .... Etc., etc. for all the other fields ....

//     // Set parameter to JS object
//     args[0] = jsObject;

//     // Pass status to Javascript
//     v8::Local<v8::Value> jsReturnValue = jsStatusDelegate.Call(argc, args);
// }

NAN_MODULE_INIT(InitAll) {
  BitmapResult::Init(target);
  // Nan::Set(target,
  //   Nan::New<v8::String>("NewBitmapResult").ToLocalChecked(),
  //   Nan::GetFunction(Nan::New<v8::FunctionTemplate>(BitmapResult::NewInstance)).ToLocalChecked());
  Nan::Set(target, Nan::New<v8::String>("GetWindowBitmap").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(GetWindowBitmap)).ToLocalChecked());
  Nan::Set(target, Nan::New<v8::String>("TryGetTribeLogText").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(TryGetTribeLogText)).ToLocalChecked());
}

NODE_MODULE(addon, InitAll);
//NAN_MODULE_WORKER_ENABLED(addon, InitAll)