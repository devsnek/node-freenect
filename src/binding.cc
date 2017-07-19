#include "freenect.h"

void Init(napi_env env, napi_value exports, napi_value module, void* priv) {
  Freenect::Init(env, exports);
}

NAPI_MODULE(addon, Init)
