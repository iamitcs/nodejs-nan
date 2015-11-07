/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2015 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include <nan.h>

using namespace Nan;  // NOLINT(build/namespaces)

void Init(v8::Local<v8::Object> target) {
  Set(target
    , New<v8::String>("key").ToLocalChecked()
    , New<v8::String>("a property").ToLocalChecked()
  );
}

NAN_MODULE(symbols, Init)
