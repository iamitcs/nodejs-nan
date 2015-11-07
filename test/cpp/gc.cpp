/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2015 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include <nan.h>

using namespace Nan;  // NOLINT(build/namespaces)

static bool prologue_called = false;
static bool epilogue_called = false;

NAN_GC_CALLBACK(gcPrologueCallback) {
  prologue_called = true;
}

NAN_GC_CALLBACK(gcEpilogueCallback) {
  epilogue_called = true;
}

NAN_METHOD(Hook) {
  AddGCPrologueCallback<gcPrologueCallback>();
  AddGCEpilogueCallback<gcEpilogueCallback>();
  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(Check) {
  HandleScope scope;
  info.GetReturnValue().Set(
      New(prologue_called && epilogue_called));
  RemoveGCPrologueCallback<gcPrologueCallback>();
  RemoveGCEpilogueCallback<gcEpilogueCallback>();
}

void Init(v8::Local<v8::Object> target) {
  Set(target
    , New<v8::String>("hook").ToLocalChecked()
    , GetFunction(New<v8::FunctionTemplate>(Hook)).ToLocalChecked()
  );
  Set(target
    , New<v8::String>("check").ToLocalChecked()
    , GetFunction(New<v8::FunctionTemplate>(Check)).ToLocalChecked()
  );
}

NAN_MODULE(gc, Init)
