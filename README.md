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

## Documentation
We'll attempt to use `doxygen` to generate templates. 

1. Try this [container](https://hub.docker.com/r/nxpleuvenjenkins/doxygen) `docker run -it --rm --name doxygen -v ~/Source/libc-template:/src nxpleuvenjenkins/doxygen /bin/bash`.
2. Create `doxygen` config file, or use the included `doxyconf`.
3. Run the `doxygen` command on the config file.
4. [Serve](https://dev.to/nicolasmesa/serve-your-current-directory-with-python-and-http-2m3p) the pages in the `html` folder.
5. Or [set up](https://goseeky.wordpress.com/2017/07/22/documentation-101-doxygen-with-github-pages/) on GitHub Pages.

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

## Vagrantfile
Just map the folders you want and `vagrant up && vagrant ssh`.

# References
1. [Starting and stopping containers](https://stackoverflow.com/questions/26153686/how-do-i-run-a-command-on-an-already-existing-docker-container)
