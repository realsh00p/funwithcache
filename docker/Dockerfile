# syntax=docker/dockerfile:1.4

FROM debian:bullseye-slim

SHELL [ "/bin/bash", "-c" ]

RUN apt-get update && apt-get \
      install -y \
        wget \
        gnupg

RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - >/dev/null && \
    echo "deb http://apt.llvm.org/bullseye/ llvm-toolchain-bullseye-14 main" | tee -a /etc/apt/sources.list >/dev/null && \
    echo "deb-src http://apt.llvm.org/bullseye/ llvm-toolchain-bullseye-14 main" | tee -a /etc/apt/sources.list >/dev/null && \
    apt-get update && apt-get \
      install -y \
        autoconf \
        automake \
        build-essential \
        clang-14 \
        clang-format-14 \
        clangd-14 \
        cmake \
        curl \
        gdb \
        git \
        libboost-program-options-dev \
        libtool \
        python3 \
        python3-pip \
        python3-venv \
        valgrind && \
    rm -rf /var/lib/apt/lists*

RUN pushd /opt && \
      git clone https://github.com/protocolbuffers/protobuf.git --branch v21.1 --depth 1 --recurse-submodules && \
      pushd protobuf && \
        ./autogen.sh && \
        ./configure --prefix=/usr && \
        make -j $(nproc) && \
        make install && \
      popd && \
    popd
