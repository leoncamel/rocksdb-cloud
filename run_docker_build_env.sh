#!/bin/bash

# echo "Checking AWS access keys"
# if [[ -z ${AWS_ACCESS_KEY_ID+x} ]]; then
#   AWS_ACCESS_KEY_ID=$(aws configure get aws_access_key_id) || die_error "AWS access key ID not found"
# fi
# if [[ -z ${AWS_SECRET_ACCESS_KEY+x} ]]; then
#   AWS_SECRET_ACCESS_KEY=$(aws configure get aws_secret_access_key) || die_error "AWS secret access key not found"
# fi

export AWS_ACCESS_KEY_ID
export AWS_SECRET_ACCESS_KEY

export SRC_ROOT=$(git rev-parse --show-toplevel)

echo $UID

# -u $UID -e V=1 -e USE_AWS=1 -e USE_KAFKA=1 \

echo "Run docker env..."
docker run -it -v $SRC_ROOT:/opt/rocksdb-cloud/src -w /opt/rocksdb-cloud/src \
    -e V=1 -e USE_AWS=1 -e USE_KAFKA=1 \
    -e AWS_ACCESS_KEY_ID -e AWS_SECRET_ACCESS_KEY \
    --rm rocksdb-cloud-xiaolin \
    /bin/bash

