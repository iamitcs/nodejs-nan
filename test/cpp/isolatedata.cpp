/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2015 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include <nan.h>

using namespace Nan;  // NOLINT(build/namespaces)

struct Dummy {
  int value;
};

NAN_METHOD(SetAndGet) {
  Dummy *d0 = new Dummy;
  Dummy *d1 = NULL;

  v8::Isolate *isolate = v8::Isolate::GetCurrent();

  SetIsolateData<Dummy>(isolate, d0);
  d1 = GetIsolateData<Dummy>(isolate);

  delete d1;

  info.GetReturnValue().Set(New<v8::Boolean>(d0 == d1));
}

void Init (v8::Handle<v8::Object> target) {
  Set(target
    , New<v8::String>("setAndGet").ToLocalChecked()
    , New<v8::FunctionTemplate>(SetAndGet)->GetFunction()
  );
}

NODE_MODULE(isolatedata, Init)
