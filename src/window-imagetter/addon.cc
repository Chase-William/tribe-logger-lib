/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2018 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/
#pragma once
#include <nan.h>
#include "sync.h"   // NOLINT(build/include)

class BitmapReturn : public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init) {
      v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
      tpl->InstanceTemplate()->SetInternalFieldCount(1);
      Nan::SetPrototypeMethod(tpl, "GetValue", GetValue);
      constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    }

    static NAN_METHOD(NewInstance) {
      v8::Local<v8::Function> cons = Nan::New(constructor());
      double value = info[0]->IsNumber() ? Nan::To<double>(info[0]).FromJust() : 0;
      const int argc = 1;
      v8::Local<v8::Value> argv[1] = {Nan::New(value)};
      info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    }

  private:
    // Constructor
    explicit BitmapReturn(double value = 0) : value_(value) { }
    // Deconstructor
    ~BitmapReturn() { }
    
    static NAN_METHOD(New) {
      if (info.IsConstructCall()) {
        double value = info[0]->IsNumber() ? Nan::To<double>(info[0]).FromJust() : 0;
        BitmapReturn* obj = new BitmapReturn(value);
        obj->Wrap(info.This()); // Wrap this object
        info.GetReturnValue().Set(info.This()); // Set the return value of this function to *this*
      } else {
        const int argc = 1;
        v8::Local<v8::Value> argv[argc] = {info[0]}; // what the heck is this
        v8::Local<v8::Function> cons = Nan::New(constructor());
        info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
      }
    }

    static NAN_METHOD(GetValue) {
      BitmapReturn* obj = ObjectWrap::Unwrap<BitmapReturn>(info.Holder());
      info.GetReturnValue().Set(obj->value_);
    }

    /*
      Constructor to create instances of this type.
    */
    static inline Nan::Persistent<v8::Function> & constructor() {
      static Nan::Persistent<v8::Function> my_constructor;
      return my_constructor;
    }

    // Field for this wrapper
    double value_;
};

NAN_MODULE_INIT(InitAll) {
  BitmapReturn::Init(target);
  Nan::Set(target,
    Nan::New<v8::String>("NewBitmapReturn").ToLocalChecked(),
    Nan::GetFunction(
      Nan::New<v8::FunctionTemplate>(BitmapReturn::NewInstance)).ToLocalChecked());
  Nan::Set(target, Nan::New<v8::String>("GetWindowBitmap").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(GetWindowBitmap)).ToLocalChecked());
  Nan::Set(target, Nan::New<v8::String>("TryGetTribeLogText").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(TryGetTribeLogText)).ToLocalChecked());
}

NODE_MODULE(addon, InitAll);
//NAN_MODULE_WORKER_ENABLED(addon, InitAll)