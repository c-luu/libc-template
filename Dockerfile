FROM udacity/project-assistant-base:3.0

ARG develop
ARG gpgkeyfile

ENV DEBIAN_FRONTEND=noninteractive

RUN wget -O - https://ppa.bitanical.com/pward8@gatech.edu.gpg.key|apt-key add - && \
    echo "deb https://ppa.bitanical.com/apt/debian bionic main" >> /etc/apt/sources.list.d/ppa.bitanical.list

RUN apt-get update && apt-get install -y \
    libgmp-dev \
    gcc-multilib \
    valgrind \
    portmap \
    rpcbind \
    libcurl4-openssl-dev \
    bzip2 \
    imagemagick \
    libmagickcore-dev \
    libssl-dev \
    llvm \
    net-tools \
    libtool \
    pkg-config \
    check \
    tmux \
    vim
