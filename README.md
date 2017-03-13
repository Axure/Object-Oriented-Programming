# Object Oriented Programming Projects

## Build

This project should be built with make.

Better not build in the source directory. It is recommended to make a separate `build` directory (which is afore-ignored in this repo) like this:

```bash
mkdir build
cd build
```

The following commands are all relative to this path.

### Debug mode

Logs are enabled in debug mode

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Release mode

```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Disclaimer

I *am not* attending, and *never attended* this course. This project is just for personal practice and learning.

## License

MIT