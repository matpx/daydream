const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "daydream",
        .target = target,
        .optimize = optimize,
    });

    exe.linkLibC();
    exe.linkLibCpp();

    var shaderc: []const u8 = ".\\toolchain\\sokol-tools-bin\\bin\\linux\\sokol-shdc";

    if (exe.target.isWindows()) {
        shaderc = ".\\toolchain\\sokol-tools-bin\\bin\\win32\\sokol-shdc.exe";

        exe.linkSystemLibraryName("kernel32");
        exe.linkSystemLibraryName("user32");
        exe.linkSystemLibraryName("gdi32");
        exe.linkSystemLibraryName("ole32");
    } else if (exe.target.getOsTag() == .wasi) {
        exe.defineCMacro("__EMSCRIPTEN__", "1");
    } else {
        exe.linkSystemLibraryName("X11");
        exe.linkSystemLibraryName("Xi");
        exe.linkSystemLibraryName("Xcursor");
        // exe.addSystemIncludePath(std.Build.LazyPath{ .path = "/usr/include" });
        // exe.addLibraryPath(std.Build.LazyPath{ .path = "/usr/lib64" });
    }

    const common_options: []const []const u8 = &.{
        "-Werror",
        "-Wall",
        "-Wextra",
        // "-Wtrampolines",
        "-Wformat=2",
        "-Wconversion",
        "-Wimplicit-fallthrough",
        "-Wfloat-equal",
        "-Wconversion",
        "-Wshift-overflow",
        "-Wcast-qual",
        "-Wcast-align",
        "-Wnewline-eof",
        "-fstrict-flex-arrays=3",
        // "-fstack-clash-protection",
        "-fstack-protector-strong",
        // "-Wl,-z,nodlopen",
        // "-Wl,-z,noexecstack",
        // "-Wl,-z,relro",
        // "-Wl,-z,now",
        "-Wa,--noexecstack",
    };

    const debug_options: []const []const u8 = common_options ++ .{
        // "-O1",
        "-D_LIBCPP_ENABLE_DEBUG_MODE",
    };

    const release_options: []const []const u8 = common_options ++ .{
        "-D_LIBCPP_ENABLE_ASSERTIONS",
        "-U_FORTIFY_SOURCE",
        "-D_FORTIFY_SOURCE=3",
    };

    exe.addSystemIncludePath(std.Build.LazyPath{ .path = "thirdparty/sokol/" });
    exe.addSystemIncludePath(std.Build.LazyPath{ .path = "thirdparty/glm/" });
    exe.addSystemIncludePath(std.Build.LazyPath{ .path = "thirdparty/entt/single_include/" });
    exe.addSystemIncludePath(std.Build.LazyPath{ .path = "thirdparty/fmt/include/" });
    exe.addSystemIncludePath(std.Build.LazyPath{ .path = "thirdparty/GSL/include/" });
    exe.addSystemIncludePath(std.Build.LazyPath{ .path = "thirdparty/expected/include/" });
    exe.addCSourceFiles(
        &.{
            "src/main.cpp",
            "src/impl.c",
            "src/app.cpp",
            "src/renderer.cpp",
        },
        if (optimize == std.builtin.OptimizeMode.Debug) debug_options else release_options,
    );

    exe.step.dependOn(&b.addSystemCommand(&.{ ".\\toolchain\\sokol-tools-bin\\bin\\win32\\sokol-shdc.exe", "--input=shader\\unlit.glsl", "--output=shader\\include\\shader\\unlit.h", "--slang=glsl330" }).step);

    b.installArtifact(exe);
}
