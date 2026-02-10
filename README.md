# Mumble Link C

A library to interact with the [Mumble Link Plugin](https://www.mumble.info/documentation/developer/positional-audio/link-plugin/) in C.

You can enable this plugin by going to `Settings -> Plugins -> Link -> Enable`.

## Minimal Example / Usage

A minimal example can be found in [`test/test.c`](test/test.c) and compiled with the sibling Makefile

```sh
cd test
make
./mumblelinktest
```

To use this in your project simply add [`mumble.c`](mumble.c) and [`mumble.h`](mumble.h) to your project

