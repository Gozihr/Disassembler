FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
    && apt install -y --no-install-recommends \
    build-essential cmake vim openssl curl ca-certificates \
    libcapstone-dev pkg-config wget

# Set the working directory to root (ie $HOME)
WORKDIR root

COPY . .

RUN mkdir build && cd build \
    && cmake .. && make

RUN ./build/src/test/Disassembler_TEST
