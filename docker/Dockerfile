# syntax=docker/dockerfile:1.4

FROM debian:bullseye-slim

RUN apt-get update && apt-get \
      install -y \
        build-essential \
        cmake \
        gdb \
        valgrind \
        libboost-program-options-dev \
        libprotobuf-dev \
        protobuf-compiler \
        wget && \
    rm -rf /var/lib/apt/lists*

RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - >/dev/null && \
    echo "deb http://apt.llvm.org/bullseye/ llvm-toolchain-bullseye-14 main" | tee -a /etc/apt/sources.list >/dev/null && \
    echo "deb-src http://apt.llvm.org/bullseye/ llvm-toolchain-bullseye-14 main" | tee -a /etc/apt/sources.list >/dev/null && \
    apt-get update && apt-get \
      install -y \
        clangd-14 \
        clang-14 \
        clang-format-14 && \
    rm -rf /var/lib/apt/lists*
