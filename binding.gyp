{
  "targets": [
    {
      "target_name": "freenect",
      "include_dirs": ["/usr/local/include/libfreenect"],
      "link_settings": {
        "ldflags": ["-L/usr/local/lib", "-lfreenect", "-lfreenect_sync"]
      },
      "ldlibs": ["-L/usr/lib", "-L/usr/lib64", "-L/usr/local/lib"],
      "sources": [
        "src/freenect.cc",
        "src/binding.cc"
      ],
    }
  ]
}
