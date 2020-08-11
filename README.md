# Disassembler

This is hopefully the start of a really awesome custom tool for my own personal RE work.

## Build Instructions
```bash
mkdir build
cd build
cmake ../
make
```
## Dependencies 
- Catch2
- CmdParser

## Usage
- `echo 0x55488b05b8130000 | xargs ./Disassemble`
- `./Disassemble 0x55488b05b8130000`
- `./Disassemble 55488b05b8130000`
- `./Disassembler "0x 55 48 8b 05 b8 13 00 00"`
- `./Disassembler "55 48 8b 05 b8 13 00 00"`

## Coming Soon
- flags
- input/output files
- elf/pe/mach-O
- add support for more disassemblers (compare output)
- Allow for dynamic loading of disassemblers (plugin model)