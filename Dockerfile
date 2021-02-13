FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
    && apt install -y --no-install-recommends \
    git build-essential cmake vim openssl curl ca-certificates \
    libglib2.0-dev nasm python3 libcapstone-dev pkg-config wget

# Set the working directory to root (ie $HOME)
WORKDIR root

COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Debug
RUN make -C./build

RUN ./build/src/test/Disassembler_TEST

ENV XED_LIB_PATH /root/packages/xed/lib

RUN export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$XED_LIB_PATH \
    && ./build/plugins/xedPlugin/test/XED_TEST \
    && ./build/src/cli/disasm --raw -a x86_64 -i 0x55488b05b8130000 -d build/plugins/xedPlugin/libxedPlugin.so

RUN scripts/elfLinuxBuildAndRun.sh src/test/hello.linux.asm \
    && ./build/src/cli/disasm --binary -f src/test/hello.linux.out

RUN export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$XED_LIB_PATH \
    && ./build/src/cli/disasm --binary -f src/test/hello.linux.out -d build/plugins/xedPlugin/libxedPlugin.so