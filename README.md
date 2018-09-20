# VSLC
A Very Simple Language Compiler.

## Build
```bash
mkdir VSLC/
cd VSLC/
git clone git@github.com:EnderQIU/vslc.git vslc/
mkdir build/
cd build/

# For macOS (required llvm 6.0.1, tested on macOS High Sierra)
brew install llvm
cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" ../vslc

# For Windows (required llvm 6.0.1, tested on Windows 10 build 1803)
cd where-you-want-llvm-to-live
svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm
setx LLVM_PATH ...where-you-want-llvm-to-live/llvm/  # For present user
setx LLVM_PATH ...where-you-want-llvm-to-live/llvm/ -m  # For system-wide
# start a new cmd
cd ...VSLC/build/
cmake -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 15" ../vslc
```

## Usage
```bash
> vslc --help
usage: vslc [options] ... filename
options:
  -v, --verbose    Enable verbose mode, display the output of scanner and parser.
  -o, --output     Specify output file name. Default is a.out. (string [=a.out])
  -?, --help       print this message
```

## Acknowledgement
Portion of this software may utilize the following copyrighted materail, the use of which is hereby acknowledged.

- [cmdline: A simple command line parser for C++](https://github.com/tanakh/cmdline) Copyright (c) 2009, Hideyuki Tanaka
- [first-follow: Calculator for finding first, follow and predict sets for a grammar.](https://github.com/MikeDevice/first-follow) MIT License 
- [pytablewriter: A Python library to write a table in various formats](https://pytablewriter.rtfd.io/) MIT License

## LICENSE
WTFPL – Do What the F*** You Want to Public License
