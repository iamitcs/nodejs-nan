/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2015 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include <nan.h>

using namespace Nan;  // NOLINT(build/namespaces)

class ErrorWorker : public NanAsyncWorker {
 public:
  explicit ErrorWorker(NanCallback *callback) : NanAsyncWorker(callback) {}
  ~ErrorWorker() {}

  void Execute () {
    SetErrorMessage("Error");
  }
};

NAN_METHOD(Work) {
  NanCallback *callback = new NanCallback(info[0].As<v8::Function>());
  NanAsyncQueueWorker(new ErrorWorker(callback));
  info.GetReturnValue().SetUndefined();
}

void Init (v8::Handle<v8::Object> exports) {
  NanSet(exports
    , NanNew("a").ToLocalChecked()
    , NanNew<v8::FunctionTemplate>(Work)->GetFunction());
}

NODE_MODULE(asyncworkererror, Init)
