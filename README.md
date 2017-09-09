# lctoxy

Program for converting Ultimate 3000 RSCL ASCII chromatograms to XY data.

## Licensing

This software is released under the [MIT](LICENSE) license.

## Quick Start 

### Requirements

* [CMake](https://cmake.org) 3.4.3
* [Boost](http://www.boost.org/) 1.65.0
* [GSL](https://github.com/Microsoft/GSL)

### Supported Platforms

This software has been built successfully on the following platforms:
* GNU/Linux using GCC 5.4.0
* GNU/Linux using Clang 3.8.0
* OS X El Capitan (10.12) using Apple LLVM 8.1.0
* Windows using Visual Studio 2017

### Obtaining the Source Code

The source code can be obtained from

        git clone git@github.com:stigrs/lctoxy.git

### Building the Software

These steps assumes that the source code of this repository has been cloned
into a directory called `lctoxy`.

1. Create a directory to contain the build outputs:

        cd lctoxy
        mkdir build
        cd build

2. Configure CMake to use the compiler of your choice (you can see a list by
   running `cmake --help`):

        cmake -G "Visual Studio 15 2017" ..

3. Build the software (in this case in the Release configuration):

        cmake --build . --config Release

4. Install the software:

        cmake --build . --config Release --target install

## Usage

Command to run the software:

        lctoxy -m mass_file -c chromatogram_file
        
