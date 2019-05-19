# About
libc template.

## Build
```
mkdir build
cd build
cmake ..
make
```

## Install (*nix)
```
mkdir install
cd install
cmake ..
make
sudo make install
```
Only installs to:
> /usr/local/*

so, may need to set and export LD_LIBRARY_PATH accordingly, or:
> export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

Alternatively, see `exports.sh`, run with `source` command for set-up.

## Use
Link with e.g.:
> -l\<libname\>

## Dependencies
1. libcheck for unit testing
2. pkg-config
3. cmake

## Tests
After build:
> ctest --output-on-failure . -V
