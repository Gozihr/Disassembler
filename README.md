# Disassembler

This is hopefully the start of a really awesome custom tool for my own personal RE work.

## Build Instructions
```bash
cmake -B build
make
```
### Build with Ninja
```bash
cmake -G Ninja -B build
ninja -C./build
# or if you just want to build the tests
ninja XED_TEST Disassembler_TEST
```
### Building on Windows (Experimental)
Windows is still experimental and for now you can just build release
- Using Ninja
```powershell
cmake -GNinja -Bbuild -DCMAKE_BUILD_TYPE=Release
ninja -C./build
```
- Using MSBUILD
```powershell
cmake -B build
msbuild build\Disassembler.sln -t:Build -p:Configuration=Release
```

## Dependencies 
- Catch2
- CmdParser
- Capstone
- XED (optional)
- LIEF

## Usage
- `echo 0x55488b05b8130000 | xargs ./disasm --raw -a x86_64 -i`
- `./disasm --raw -a x86_64 -i 0x55488b05b8130000`
- `./disasm --raw -a x86_64 -i 55488b05b8130000`
- `./disasm --raw -a x86_64 -i "0x 55 48 8b 05 b8 13 00 00"`
- `./disasm --raw -a x86_64 -i "55 48 8b 05 b8 13 00 00"`
- `./disasm --binary -f /bin/ls`

## Docker Build & Run
- build: `docker build -t disassembler:latest .`
- run: `docker run  --name test_vm -it disassembler:latest`


## Debuging 
- Switch compiler
    - in the process of building this project i've found differences between clang and gcc. First step I try is to swap the compilers
    - `cmake -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ ..`
- Build with Debug symbols
    - If you need unoptimized replace -O3 with -O0 whereever you find CMAKE_CXX_FLAGS. If you don'y just run below
    - `cmake -DCMAKE_BUILD_TYPE=Debug ..`
- Check for Dwarf Version
    - `readelf --debug-dump=info src/cli/disasm | grep "Version" | uniq`

## Supported Platform(s)
- OS X
- Linux
- Windows (Experimental) (Release Only Builds)

## Coming Soon
- [x] flags
- [ ] input/output files
    - [x] input
    - [ ] output
- [ ] elf/pe/mach-O
    - [x] mach-O
    - [x] elf
- add support for more disassemblers (compare output)
    - [x] XED
- [ ] Allow for dynamic loading of disassemblers (plugin model)