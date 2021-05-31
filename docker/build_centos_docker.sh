#!/bin/bash

export http_proxy=http://172.20.3.242:1087;export https_proxy=http://172.20.3.242:1087;

yum install -y centos-release-scl git make wget which python3 libcurl-devel zlib-devel bzip2-devel lz4-devel libzstd-devel openssl-devel gflags-devel snappy-devel jemalloc-devel && \
    yum install -y devtoolset-8-gcc devtoolset-8-gcc-c++ && \
    source /opt/rh/devtoolset-8/enable

mkdir -p /ax-install/cmake
mkdir -p /ax-install/aws-install

cd /ax-install && \
    curl -JLO https://cmake.org/files/v3.12/cmake-3.12.0-Linux-x86_64.tar.gz && \
    tar xfz /ax-install/cmake-3.12.0-Linux-x86_64.tar.gz --strip-components=1 -C /usr/local && \
    rm -f /ax-install/cmake-3.12.0-Linux-x86_64.tar.gz

cd /ax-install && \
    git clone -q --single-branch --depth 1 --branch 1.8.8 https://github.com/aws/aws-sdk-cpp.git && \
    cd /ax-install/aws-install && \
    cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTING=OFF '-DBUILD_ONLY=kinesis;core;s3;transfer' ../aws-sdk-cpp/ && \
    make -j 8 && make install && \
    rm -rf /ax-install/aws-install/

cd /ax-install && \
    export LIBRDKAFKA_VERSION=0.11.3 && \
    wget https://github.com/edenhill/librdkafka/archive/v${LIBRDKAFKA_VERSION}.tar.gz && \
    tar -zxvf v${LIBRDKAFKA_VERSION}.tar.gz && \
    cd /ax-install/librdkafka-${LIBRDKAFKA_VERSION} && \
    ./configure && make && make install && \
    rm -rf v${LIBRDKAFKA_VERSION}.tar.gz /ax-install/librdkafka-${LIBRDKAFKA_VERSION}

echo "/usr/local/lib/" >> /etc/ld.so.conf.d/usr_local.conf
echo "/usr/local/lib64/" >> /etc/ld.so.conf.d/usr_local.conf
ldconfig -v

