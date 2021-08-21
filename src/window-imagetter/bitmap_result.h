#pragma once
#include <nan.h>

class BitmapResult : public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init) {
      v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
      tpl->InstanceTemplate()->SetInternalFieldCount(1);
      // Setting the prototypes to be used from the front-end JavaScript
      Nan::SetPrototypeMethod(tpl, "GetErrorCode", GetErrorCode);
      Nan::SetPrototypeMethod(tpl, "GetBitmapBuffer", GetBitmapBuffer);      
      constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());      
    }

    // static NAN_METHOD(NewInstance) {
    //   v8::Local<v8::Function> cons = Nan::New(constructor());
    //   double value = info[0]->IsNumber() ? Nan::To<double>(info[0]).FromJust() : 0;
    //   const int argc = 1;
    //   v8::Local<v8::Value> argv[1] = {Nan::New(value)};
    //   info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    // }

  private:
    // Constructor
    explicit BitmapResult(int errorCode, char* buffer, uint32_t size) : m_errorCode(errorCode), m_buffer(buffer), m_size(size) { }
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

    static NAN_METHOD(GetErrorCode) {
      BitmapResult* obj = ObjectWrap::Unwrap<BitmapResult>(info.Holder());
      info.GetReturnValue().Set(obj->m_errorCode);
    }

    /*
      Constructor to create instances of this type.
    */
    static inline Nan::Persistent<v8::Function> & constructor() {
      static Nan::Persistent<v8::Function> my_constructor;
      return my_constructor;
    }

    char* m_buffer;
    uint32_t m_size;
    int m_errorCode;
};