# Turtle

Turtle is a simple implementation of LOGO.

Take a walk down the memory lane ...

## Demo

## Installing

### Dependencies

Turtle requires the following to be built:
- CMake (>= 3.10)
- make or ninja  
- gcc or clang
- gtkmm-3.0
- Boost (>= 1.70)

On Ubuntu, the following command will install them:
```shell
sudo apt install git cmake make gcc libgtkmm-3.0-dev libboost-all-dev
```

### Steps to build

Clone this repo and run the `build.sh` script.
```shell
git clone https://github.com/RedDocMD/turtle
cd turtle
./build.sh
```
Note that `build.sh` requires `sudo` to copy the binary and desktop files
to their correct destinations.

## Features

### Commands

### Others