/**********************************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2014 NAN contributors
 *
 * MIT +no-false-attribs License <https://github.com/rvagg/nan/blob/master/LICENSE>
 **********************************************************************************/

#include <unistd.h>
#include <node.h>
#include <nan.h>

class SleepWorker : public NanAsyncWorker {
 public:
  SleepWorker(NanCallback *callback, int milliseconds)
    : NanAsyncWorker(callback), milliseconds(milliseconds) {}
  ~SleepWorker() {}

  void Execute () {
    usleep(milliseconds * 1000);
  }

 private:
  int milliseconds;
};

NAN_METHOD(Sleep) {
  NanScope();
  NanCallback *callback = new NanCallback(args[1].As<v8::Function>());
  NanAsyncQueueWorker(new SleepWorker(callback, args[0]->Uint32Value()));
  NanReturnUndefined();
}

void Init(v8::Handle<v8::Object> exports) {
  exports->Set(NanSymbol("a"), v8::FunctionTemplate::New(Sleep)->GetFunction());
}

NODE_MODULE(asyncworker, Init)
