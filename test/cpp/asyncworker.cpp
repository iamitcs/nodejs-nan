/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2015 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#ifndef _WIN32
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif
#include <nan.h>

using namespace Nan;  // NOLINT(build/namespaces)

class SleepWorker : public AsyncWorker {
 public:
  SleepWorker(Callback *callback, int milliseconds)
    : AsyncWorker(callback), milliseconds(milliseconds) {}
  ~SleepWorker() {}

  void Execute () {
    Sleep(milliseconds);
  }

 private:
  int milliseconds;
};

NAN_METHOD(DoSleep) {
  Callback *callback = new Callback(info[1].As<v8::Function>());
  AsyncQueueWorker(
      new SleepWorker(callback, To<uint32_t>(info[0]).FromJust()));
}

void Init(v8::Handle<v8::Object> exports) {
  Set(exports
    , New<v8::String>("a").ToLocalChecked()
    , New<v8::FunctionTemplate>(DoSleep)->GetFunction());
}

NODE_MODULE(asyncworker, Init)
