const std = @import("std");
const nvrhi = @import("thirdparty/nvrhi/build.zig");
const jolt = @import("thirdparty/JoltPhysics/build.zig");
const spdlog = @import("thirdparty/spdlog/build.zig");

pub fn build(b: *std.Build) !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "daydream",
        .target = target,
        .optimize = optimize,
    });

    exe.pie = true;
    exe.link_z_relro = true;

    const mode_debug: bool = optimize == std.builtin.OptimizeMode.Debug;
    const mode_safe: bool = optimize == std.builtin.OptimizeMode.ReleaseSafe or mode_debug;
    const compiler_args_global: []const []const u8 = &.{
        "-fno-exceptions",
        "-Wa,--noexecstack",
        "-fstrict-flex-arrays=3",
        "-fPIE",
        "-DSPDLOG_COMPILED_LIB",
        if (mode_safe) "-ftrivial-auto-var-init=zero" else "",
        if (mode_safe) "-fcf-protection=full" else "",
        if (mode_safe) "-D_LIBCPP_ENABLE_ASSERTIONS" else "",
        if (mode_debug) "-D_LIBCPP_ENABLE_DEBUG_MODE" else "",
        // if (mode_safe) "-fstack-clash-protection" else "",
    };

    {
        const system_include_paths: []const []const u8 = &.{
            "thirdparty/SDL2/x86_64-w64-mingw32/include/",
            "thirdparty/spdlog/include/",
            "thirdparty/nvrhi/include/",
            "thirdparty/JoltPhysics/",
            "thirdparty/glm/",
            "thirdparty/entt/src/",
            "thirdparty/GSL/include/",
            "thirdparty/expected/include/",
            "thirdparty/cgltf/",
            "toolchain-out/",
        };

        for (system_include_paths) |include_path| {
            exe.addSystemIncludePath(std.Build.LazyPath{ .path = include_path });
        }
    }

    {
        const source_files: []const []const u8 = &.{
            "src/main.cpp",
            "src/fatal.cpp",
            "src/impl.cpp",
            "src/app.cpp",
            "src/window.cpp",
            "src/device.cpp",
            "src/loader.cpp",
            "src/systems/renderer.cpp",
            "src/systems/player.cpp",
        };

        var compiler_args = std.ArrayList([]const u8).init(allocator);
        try compiler_args.appendSlice(compiler_args_global);
        try compiler_args.appendSlice(&.{
            "-std=c++20",
            "-Werror",
            "-Weverything",
            "-Wno-missing-prototypes",
            "-Wno-c++98-compat-pedantic",
            "-Wno-c++98-compat",
            "-Wno-padded",
        });

        exe.addCSourceFiles(
            source_files,
            compiler_args.items,
        );
    }

    {
        const system_libs: []const []const u8 =
            &.{
            // "gdi32",
            // "ole32",
            // "setupapi",
            // "winmm",
            // "imm32",
            // "oleaut32",
            // "version",
            "d3d11",
        };

        for (system_libs) |lib| {
            exe.linkSystemLibrary(lib);
        }
    }

    // SDL
    exe.addObjectFile(std.Build.LazyPath{ .path = "thirdparty/SDL2/x86_64-w64-mingw32/lib/libSDL2.dll.a" });
    exe.addObjectFile(std.Build.LazyPath{ .path = "thirdparty/SDL2/x86_64-w64-mingw32/lib/libSDL2main.a" });
    b.installBinFile("thirdparty/SDL2/x86_64-w64-mingw32/bin/SDL2.dll", "SDL2.dll");

    // JoltPhysics
    exe.linkLibrary(try jolt.package(allocator, compiler_args_global, b, target, optimize));

    // spdlog
    exe.linkLibrary(try spdlog.package(allocator, compiler_args_global, b, target, optimize));

    // NVRHI
    exe.linkLibrary(try nvrhi.package(allocator, compiler_args_global, b, target, optimize));
    exe.step.dependOn(&b.addSystemCommand(&.{ "toolchain/ShaderMake/ShaderMake.exe", "-p", "DXBC", "--header", "-c", "shader/shadermake.cfg", "--compiler", "toolchain/ShaderMake/fxc.exe", "-o", "toolchain-out/shader/" }).step);

    b.installArtifact(exe);
}
