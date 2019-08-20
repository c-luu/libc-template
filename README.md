# About
libc template. `docker build .` to generate an image to compile and run tests.

## Build
```
mkdir build
cd build
cmake ..
make
```

or:

`docker run --rm -v ~/src/path:/src -w /src/build <included built image> cmake ..`

`docker run --rm -v ~/src/path:/src -w /src/build <included built image> make`

## Tests
After build:
> ctest --output-on-failure . -V

or:

`docker run --rm -v ${PWD}/src -w /src/build <included built image> ctest --output-on-failure=true . -V`

## Documentation
We'll attempt to use `doxygen` to generate templates. 

1. Try this [container](https://hub.docker.com/r/nxpleuvenjenkins/doxygen) `docker run --rm -w /src -v ~/Source/libc-template:/src nxpleuvenjenkins/doxygen doxygen doxyconf`.
2. Create `doxygen` config file, or use the included `doxyconf`.
3. Run the `doxygen` command on the config file.
4. [Serve](https://dev.to/nicolasmesa/serve-your-current-directory-with-python-and-http-2m3p) the pages in the `html` folder.
5. Or [set up](https://goseeky.wordpress.com/2017/07/22/documentation-101-doxygen-with-github-pages/) on GitHub Pages.

or:

`docker run --rm -v ~/Source/src/path:/src -w /src nxpleuvenjenkins/doxygen doxygen doxyconf`

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
4. Docker

## Docker
### Hyperv
If using `docker-toolbox` on Windows:

1. [Setup a hyperv driver docker-machine and external network switch.](https://docs.docker.com/machine/drivers/hyper-v/)
2. Run `docker-machine env <your machine name here>` and follow the instructions.
3. Stuck here since `docker-toolbox` only allows you to map your users directory.

### MacOS
1. `docker build --rm .`
2. `docker run -it --rm -v ~/path/to/src:/src <image_id> /bin/bash`
3. `docker run --cap-add SYS_PTRACE -it -v ~/path/to/src:/src <image_id> /bin/bash` (optional for TSan).

# References
1. [Starting and stopping containers](https://stackoverflow.com/questions/26153686/how-do-i-run-a-command-on-an-already-existing-docker-container)
