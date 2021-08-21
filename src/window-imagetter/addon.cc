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

class BitmapResult : public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init) {
      v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
      tpl->InstanceTemplate()->SetInternalFieldCount(1);
      Nan::SetPrototypeMethod(tpl, "GetBitmapBuffer", GetBitmapBuffer);
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
    explicit BitmapResult(char* buffer, uint32_t size) : m_buffer(), m_size(size) { }
    // Deconstructor
    ~BitmapResult() { }
    
    static NAN_METHOD(New) {
      if (info.IsConstructCall()) {
        // double value = info[0]->IsNumber() ? Nan::To<double>(info[0]).FromJust() : 0;
        // BitmapResult* obj = new BitmapResult(value);
        // obj->Wrap(info.This()); // Wrap this object
        // info.GetResultValue().Set(info.This()); // Set the Result value of this function to *this*
      } else {
        const int argc = 1;
        v8::Local<v8::Value> argv[argc] = {info[0]}; // what the heck is this
        v8::Local<v8::Function> cons = Nan::New(constructor());
        info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
      }
    }

    // static NAN_METHOD(GetValue) {
    //   BitmapResult* obj = ObjectWrap::Unwrap<BitmapResult>(info.Holder());
    //   info.GetResultValue().Set(obj->value_);
    // }

    static NAN_METHOD(GetBitmapBuffer) {
      BitmapResult* obj = ObjectWrap::Unwrap<BitmapResult>(info.Holder());
      info.GetReturnValue().Set(Nan::NewBuffer(obj->m_buffer, obj->m_size).ToLocalChecked());
    }

    /*
      Constructor to create instances of this type.
    */
    static inline Nan::Persistent<v8::Function> & constructor() {
      static Nan::Persistent<v8::Function> my_constructor;
      return my_constructor;
    }

    // Field for this wrapper
    char* m_buffer;
    uint32_t m_size;
    //double value_;
};

NAN_MODULE_INIT(InitAll) {
  BitmapResult::Init(target);
  Nan::Set(target,
    Nan::New<v8::String>("NewBitmapResult").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(BitmapResult::NewInstance)).ToLocalChecked());
  Nan::Set(target, Nan::New<v8::String>("GetWindowBitmap").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(GetWindowBitmap)).ToLocalChecked());
  Nan::Set(target, Nan::New<v8::String>("TryGetTribeLogText").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(TryGetTribeLogText)).ToLocalChecked());
}

NODE_MODULE(addon, InitAll);
//NAN_MODULE_WORKER_ENABLED(addon, InitAll)