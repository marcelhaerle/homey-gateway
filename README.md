# Homey Gateway

## Developer Setup

Download: https://github.com/labapart/gattlib/archive/refs/tags/dev.tar.gz

```shell
sudo apt install -y doxygen libglib2.0-dev libbluetooth-dev libreadline-dev python3-dev
tar xf gattlib-dev.tar.gz && cd gattlib-dev
mkdir build && cd build && cmake .. && make
sudo make install
```

## Build Project

Prepare cmake:

```shell
mkdir -p build
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=DEBUG
cmake -S . -B build/release -DCMAKE_BUILD_TYPE=RELEASE
```

Run debug build:

```shell
cmake --build build/debug
```

Run release build:

```shell
cmake --build build/release
```
