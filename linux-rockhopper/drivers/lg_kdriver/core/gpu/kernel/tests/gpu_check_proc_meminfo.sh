#!/bin/bash

source $(dirname $0)/../common.bash

# http://clm.lge.com/issue/browse/SCDCR-6659
grep ^GPUTotal: /proc/meminfo
grep ^GPUCached: /proc/meminfo
grep ^GPUReclaimable: /proc/meminfo

test -d /proc/gpu
test -d /proc/um

