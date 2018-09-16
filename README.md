# VSLC
A Very Simple Language Compiler.

## Build
```bash
mkdir VSLC/
cd VSLC/
git clone git@github.com:EnderQIU/vslc.git vslc/
mkdir build/
cd build/
cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" ../vslc
```

## Usage
usage: vslc [options] ... filename
options:
  -v, --verbose    Enable verbose mode, display the output of scanner and parser.
  -o, --output     Specify output file name. Default is a.out. (string [=a.out])
  -?, --help       print this message

## Acknowledgement
Portion of this software may utilize the following copyrighted materail, the use of which is hereby acknowledged.

- [cmdline: A simple command line parser for C++](https://github.com/tanakh/cmdline) Copyright (c) 2009, Hideyuki Tanaka

## LICENSE
WTFPL – Do What the F*** You Want to Public License
