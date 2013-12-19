#include <nan.h>

static NanUnsafePersistent<v8::String> unsafePersistentTest1;

NAN_METHOD(Save1) {
  NanScope();

  NanAssignUnsafePersistent(
      v8::String, unsafePersistentTest1, args[0].As<v8::String>());

  NanReturnUndefined();
}

NAN_METHOD(Get1) {
  NanScope();

  NanReturnValue(NanPersistentToLocal<v8::String>(unsafePersistentTest1));
}

NAN_METHOD(Dispose1) {
  NanScope();

  NanDispose(unsafePersistentTest1);

  NanReturnUndefined();
}

void Init (v8::Handle<v8::Object> target) {
  target->Set(
      NanSymbol("save1")
    , v8::FunctionTemplate::New(Save1)->GetFunction()
  );
  target->Set(
      NanSymbol("get1")
    , v8::FunctionTemplate::New(Get1)->GetFunction()
  );
  target->Set(
      NanSymbol("dispose1")
    , v8::FunctionTemplate::New(Dispose1)->GetFunction()
  );
}

NODE_MODULE(unsafepersistent, Init)

