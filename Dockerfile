FROM udacity/project-assistant-base:3.0

ARG develop
ARG gpgkeyfile

ENV DEBIAN_FRONTEND=noninteractive

RUN wget -O - https://ppa.bitanical.com/pward8@gatech.edu.gpg.key|apt-key add - && \
    echo "deb https://ppa.bitanical.com/apt/debian bionic main" >> /etc/apt/sources.list.d/ppa.bitanical.list

ENV PATH="/src/cmake-3.14.0-Linux-x86_64/bin:${PATH}"

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
