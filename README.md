# Disassembler

This is hopefully the start of a really awesome custom tool for my own personal RE work.

## Build Instructions
```bash
mkdir build
cd build
cmake ../
make
```
### Build with Ninja
```bash
mkdir build
cd build
cmake -G Ninja ..
Ninja XED_TEST Disassembler_TEST
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

## Supported Platform(s)
- OS X
- Linux

## Coming Soon
- [x] flags
- [ ] input/output files
    - [x] input
    - [ ] output
- [ ] elf/pe/mach-O
    - [x] mach-O
- add support for more disassemblers (compare output)
    - [x] XED
- [ ] Allow for dynamic loading of disassemblers (plugin model)