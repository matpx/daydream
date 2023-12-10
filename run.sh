#!/bin/sh

set -e

./toolchain/zig-linux-x86_64/zig-upx build
./zig-out/bin/daydream
