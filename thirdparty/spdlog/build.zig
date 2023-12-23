const std = @import("std");

const spdlog_sources_dir = "thirdparty/spdlog/src/";

const spdlog_source_files: []const []const u8 = &.{
    spdlog_sources_dir ++ "async.cpp",
    spdlog_sources_dir ++ "bundled_fmtlib_format.cpp",
    spdlog_sources_dir ++ "cfg.cpp",
    spdlog_sources_dir ++ "color_sinks.cpp",
    spdlog_sources_dir ++ "file_sinks.cpp",
    spdlog_sources_dir ++ "spdlog.cpp",
    spdlog_sources_dir ++ "stdout_sinks.cpp",
};

pub fn package(
    allocator: std.mem.Allocator,
    compiler_args_global: []const []const u8,
    b: *std.Build,
    target: std.zig.CrossTarget,
    optimize: std.builtin.Mode,
) !*std.Build.CompileStep {
    const spdlog = b.addStaticLibrary(.{
        .name = "spdlog",
        .target = target,
        .optimize = optimize,
    });

    var compiler_args = std.ArrayList([]const u8).init(allocator);
    try compiler_args.appendSlice(compiler_args_global);
    try compiler_args.appendSlice(&.{
        "-DSPDLOG_NO_EXCEPTIONS",
    });

    spdlog.addCSourceFiles(spdlog_source_files, compiler_args.items);
    spdlog.addIncludePath(std.Build.LazyPath{ .path = "thirdparty/spdlog/include" });
    spdlog.linkLibCpp();

    return spdlog;
}
