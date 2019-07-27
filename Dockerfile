FROM rikorose/gcc-cmake

ARG develop
ARG gpgkeyfile

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    libgmp-dev \
    gcc-multilib \
    valgrind \
    portmap \
    rpcbind \
    libcurl4-openssl-dev \
    bzip2 \
    libssl-dev \
    llvm \
    net-tools \
    libtool \
    pkg-config \
    check \
    tmux \
    vim
