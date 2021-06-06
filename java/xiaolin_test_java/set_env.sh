#!/usr/bin/env bash
set -euo pipefail

export JAVA_HOME=$HOME/local/jdk8u282-b08/
export PATH=$JAVA_HOME/bin:$PATH
export LD_LIBRARY_PATH=$HOME/work/cpp/install/lib:$HOME/work/cpp/install/lib64:$LD_LIBRARY_PATH

export AWS_ACCESS_KEY_ID=minioadmin
export AWS_SECRET_ACCESS_KEY=minioadmin

export ROCKSDB_AWS_DEBUG_LEVEL=Debug
