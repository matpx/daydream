#!/bin/sh

set -e

./toolchain/zig-linux-x86_64/zig build
./zig-out/bin/daydream
