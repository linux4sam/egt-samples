# EGT Sample Applications

Sample applications using EGT.

# Compiling

First compile and install libegt to a directory.

```sh
./autogen.sh
./configure --prefix=/home/jhenderson/ui_install
make && make install
```

Then, configure and build this sampls project.

```sh
./autogen.sh
CXXFLAGS="-I/home/jhenderson/ui_install/include/" \
LDFLAGS="-L/home/jhenderson/ui_install/lib/" \
PKG_CONFIG_PATH=/home/jhenderson/ui_install/lib/pkgconfig \
./configure
make
```

To run an example, set the LD_LIBRARY_PATH environment variable to the library.

```sh
LD_LIBRARY_PATH=/home/jhenderson/ui_install/lib ./example
```

## License

Released under the terms of the `Apache 2` license. See the [COPYING](COPYING)
file for more information.
