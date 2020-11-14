FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
    && apt install -y --no-install-recommends \
    git build-essential cmake vim openssl curl ca-certificates \
    python3 libcapstone-dev pkg-config wget

# Set the working directory to root (ie $HOME)
WORKDIR root

COPY . .

RUN mkdir build && cd build \
    && cmake .. \
    && make

RUN ./build/src/test/Disassembler_TEST

ENV XED_LIB_PATH /root/packages/xed/lib

RUN export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$XED_LIB_PATH \
    && ./build/plugins/xedPlugin/test/XED_TEST
