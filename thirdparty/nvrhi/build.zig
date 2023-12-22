const std = @import("std");

const nvrhi_source_files: []const []const u8 = &.{
    "thirdparty/nvrhi/src/common/dxgi-format.cpp",
    "thirdparty/nvrhi/src/common/format-info.cpp",
    "thirdparty/nvrhi/src/common/misc.cpp",
    "thirdparty/nvrhi/src/common/sparse-bitset.cpp",
    "thirdparty/nvrhi/src/common/state-tracking.cpp",
    "thirdparty/nvrhi/src/common/utils.cpp",
    "thirdparty/nvrhi/src/d3d11/d3d11-buffer.cpp",
    "thirdparty/nvrhi/src/d3d11/d3d11-commandlist.cpp",
    "thirdparty/nvrhi/src/d3d11/d3d11-compute.cpp",
    "thirdparty/nvrhi/src/d3d11/d3d11-constants.cpp",
    "thirdparty/nvrhi/src/d3d11/d3d11-device.cpp",
    "thirdparty/nvrhi/src/d3d11/d3d11-graphics.cpp",
    "thirdparty/nvrhi/src/d3d11/d3d11-queries.cpp",
    "thirdparty/nvrhi/src/d3d11/d3d11-resource-bindings.cpp",
    "thirdparty/nvrhi/src/d3d11/d3d11-shader.cpp",
    "thirdparty/nvrhi/src/d3d11/d3d11-texture.cpp",
    "thirdparty/nvrhi/src/validation/validation-commandlist.cpp",
    "thirdparty/nvrhi/src/validation/validation-device.cpp",
};

pub fn package(
    b: *std.Build,
    target: std.zig.CrossTarget,
    optimize: std.builtin.Mode,
) *std.Build.CompileStep {
    const nvrhi = b.addStaticLibrary(.{
        .name = "nvrhi",
        .target = target,
        .optimize = optimize,
    });

    const compiler_args: []const []const u8 = &.{};

    nvrhi.addCSourceFiles(nvrhi_source_files, compiler_args);
    nvrhi.addIncludePath(std.Build.LazyPath{ .path = "thirdparty/nvrhi/include" });
    nvrhi.linkLibCpp();

    return nvrhi;
}
