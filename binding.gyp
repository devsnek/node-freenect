{
  "targets": [
    {
      "target_name": "freenect",
      "include_dirs": ["/usr/local/include/libfreenect"],
      "link_settings": {
        "ldflags": ["-l:libfreenect.a", "-l:libfreenect_sync.a"]
      },
      "ldlibs": ['/usr/local/lib'],
      "libraries": [],
      "sources": [
        "src/freenect.cc",
        "src/binding.cc"
      ],
    }
  ]
}
