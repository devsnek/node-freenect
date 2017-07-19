{
  "targets": [
    {
      "target_name": "freenect",
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "include_dirs": [
        "/usr/local/include/libfreenect",
        "<!@(node -p \"require('node-addon-api').include\")",
      ],
      "link_settings": {
        "ldflags": ["-L/usr/local/lib", "-lfreenect", "-lfreenect_sync"]
      },
      "ldlibs": ["-L/usr/lib", "-L/usr/lib64", "-L/usr/local/lib"],
      "sources": [
        "src/freenect.cc",
        "src/binding.cc"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ]
    }
  ]
}
