FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
    && apt install -y --no-install-recommends \
    build-essential cmake vim openssl curl ca-certificates \
    libcapstone-dev pkg-config

# Set the working directory to root (ie $HOME)
WORKDIR root

COPY src src
COPY CMakeLists.txt CMakeLists.txt

RUN mkdir build && cd build \
    && cmake .. && make

RUN ./build/src/Disassembler_TEST
