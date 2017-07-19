{
  "targets": [
    {
      "target_name": "freenect",
      "include_dirs": ["/usr/local/include/libfreenect"],
      "ldflags": ["-L/usr/local/lib", "-l:libfreenect.a"],
      "ldlibs": [],
      "libraries": [],
      "sources": [
        "src/freenect.cc",
        "src/binding.cc"
      ],
    }
  ]
}
