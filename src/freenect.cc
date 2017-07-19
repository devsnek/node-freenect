#include <cstdlib>
#include <assert.h>

#include <libfreenect_sync.h>

#include "freenect.h"

#define MAX_TILT_ANGLE (31.0)
#define MIN_TILT_ANGLE (-31.0)
#define INVALID_TILT_ANGLE (-99.0)

#define DECLARE_NAPI_METHOD(name, func) { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_ref Freenect::constructor;

Freenect::Freenect()
: env_(nullptr), wrapper_(nullptr), deviceIndex(0), videoFormat(FREENECT_VIDEO_RGB), depthFormat(FREENECT_DEPTH_11BIT)
{
  videoBuffer = malloc(freenect_find_video_mode(FREENECT_RESOLUTION_LOW, FREENECT_VIDEO_RGB).bytes);
  depthBuffer = malloc(freenect_find_depth_mode(FREENECT_RESOLUTION_LOW, FREENECT_DEPTH_11BIT).bytes);
  tiltState = new freenect_raw_tilt_state();
  tiltAngle = INVALID_TILT_ANGLE; // GetTiltAngle();
}

Freenect::~Freenect() {
  napi_delete_reference(env_, wrapper_);
  free(videoBuffer);
  free(depthBuffer);
  freenect_sync_stop();
}

void Freenect::Destructor(napi_env env, void* nativeObject, void* /*finalize_hint*/) {
  reinterpret_cast<Freenect*>(nativeObject)->~Freenect();
}

void Freenect::Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value cons;
  napi_property_descriptor properties[] = {
    DECLARE_NAPI_METHOD("setLed", SetLed),
    // DECLARE_NAPI_METHOD("setTiltAngle", SetTiltAngle),
    // DECLARE_NAPI_METHOD("getVideo", GetVideo),
    // DECLARE_NAPI_METHOD("getDepth", GetDepth),
    // DECLARE_NAPI_METHOD("getTiltAngle", GetTiltAngle),
  };
  napi_define_class(env, "Freenect", New, nullptr, 1, properties, &cons);
  assert(status == napi_ok);

  status = napi_create_reference(env, cons, 1, &constructor);
  assert(status == napi_ok);

  status = napi_set_named_property(env, exports, "Freenect", cons);
  assert(status == napi_ok);
}

napi_value Freenect::New(napi_env env, napi_callback_info info) {
  napi_status status;

  bool is_constructor;
  status = napi_is_construct_call(env, info, &is_constructor);
  assert(status == napi_ok);

  if (is_constructor) {
    size_t argc = 0;
    napi_value args[0];
    napi_value jsthis;
    status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
    assert(status == napi_ok);

    Freenect* f = new Freenect();

    f->env_ = env;
    status = napi_wrap(env,
                       jsthis,
                       reinterpret_cast<void*>(f),
                       Freenect::Destructor,
                       nullptr,  // finalize_hint
                       &f->wrapper_);

    return jsthis;
  } else {
    // plzno
  }
}

Freenect* Freenect::GetThis(napi_env env, napi_callback_info info, size_t argc, napi_value* args) {
  napi_status status;

  napi_value jsthis;
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  Freenect* f;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&f));
  assert(status == napi_ok);

  return f;
}

napi_value Freenect::SetLed(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  /*napi_value jsthis;
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  Freenect* f;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&f));
  assert(status == napi_ok);*/
  Freenect* f = GetThis(env, info, argc, args);

  napi_valuetype valuetype;
  status = napi_typeof(env, args[0], &valuetype);
  assert(status == napi_ok);

  double option = 1;
  if (valuetype != napi_undefined) {
    status = napi_get_value_double(env, args[0], &option);
    assert(status == napi_ok);
  }

  freenect_led_options fOption = (freenect_led_options)option;
  bool success = freenect_sync_set_led(fOption, f->deviceIndex);
  if (success) f->ledOption = fOption;

  napi_value num;
  status = napi_create_number(env, option, &num);
  assert(status == napi_ok);

  return num;
}
