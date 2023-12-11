#!/bin/sh

set -e

./toolchain/zig/zig build
./zig-out/bin/daydream
