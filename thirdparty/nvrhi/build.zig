const std = @import("std");

const nvrhi_sources_dir = "thirdparty/nvrhi/src/";

const nvrhi_source_files: []const []const u8 = &.{
    nvrhi_sources_dir ++ "common/dxgi-format.cpp",
    nvrhi_sources_dir ++ "common/format-info.cpp",
    nvrhi_sources_dir ++ "common/misc.cpp",
    nvrhi_sources_dir ++ "common/sparse-bitset.cpp",
    nvrhi_sources_dir ++ "common/state-tracking.cpp",
    nvrhi_sources_dir ++ "common/utils.cpp",
    nvrhi_sources_dir ++ "d3d11/d3d11-buffer.cpp",
    nvrhi_sources_dir ++ "d3d11/d3d11-commandlist.cpp",
    nvrhi_sources_dir ++ "d3d11/d3d11-compute.cpp",
    nvrhi_sources_dir ++ "d3d11/d3d11-constants.cpp",
    nvrhi_sources_dir ++ "d3d11/d3d11-device.cpp",
    nvrhi_sources_dir ++ "d3d11/d3d11-graphics.cpp",
    nvrhi_sources_dir ++ "d3d11/d3d11-queries.cpp",
    nvrhi_sources_dir ++ "d3d11/d3d11-resource-bindings.cpp",
    nvrhi_sources_dir ++ "d3d11/d3d11-shader.cpp",
    nvrhi_sources_dir ++ "d3d11/d3d11-texture.cpp",
    nvrhi_sources_dir ++ "validation/validation-commandlist.cpp",
    nvrhi_sources_dir ++ "validation/validation-device.cpp",
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
