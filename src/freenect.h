#include <node_api.h>

#include <libfreenect_sync.h>

class Freenect {
public:
  static void Init(napi_env env, napi_value exports);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);

private:
  explicit Freenect();
  ~Freenect();

  static napi_value New(napi_env env, napi_callback_info info);
  static napi_ref constructor;

  static Freenect* GetThis(napi_env env, napi_callback_info info, size_t argc, napi_value* args);

  static napi_value SetLed(napi_env env, napi_callback_info info);

  int deviceIndex;
  double tiltAngle;
  freenect_led_options ledOption;
  freenect_raw_tilt_state* tiltState;
  freenect_video_format videoFormat;
  freenect_depth_format depthFormat;
  void* videoBuffer;
  void* depthBuffer;

  napi_env env_;
  napi_ref wrapper_;
};
