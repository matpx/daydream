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

    if (exe.target.isWindows()) {
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
        "-Wformat=2",
        "-Wconversion",
        // "-Wtrampolines",
        "-Wimplicit-fallthrough",
        "-Wfloat-equal",
        "-Wconversion",
        // "-Wlogical-op",
        "-Wshift-overflow",
        // "-Wduplicated-cond",
        "-Wcast-qual",
        "-Wcast-align",
        "-U_FORTIFY_SOURCE",
        "-D_FORTIFY_SOURCE=3",
        "-fstrict-flex-arrays=3",
        // "-fstack-clash-protection",
        "-fstack-protector-strong",
        // "-Wl,-z,nodlopen",
        // "-Wl,-z,noexecstack",
        // "-Wl,-z,relro",
        // "-Wl,-z,now",
    };

    const debug_options: []const []const u8 = common_options ++ .{
        "-O1",
        // "-D_GLIBCXX_DEBUG",
        // "-D_GLIBCXX_DEBUG_PEDANTIC",
    };

    const release_options: []const []const u8 = common_options ++ .{
        // "-D_GLIBCXX_ASSERTIONS",
    };

    exe.addSystemIncludePath(std.Build.LazyPath{ .path = "thirdparty/" });
    exe.addCSourceFile(.{
        .file = .{ .path = "src/main.cpp" },
        .flags = if (optimize == std.builtin.OptimizeMode.Debug) debug_options else release_options,
    });

    b.installArtifact(exe);
}
