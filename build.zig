const std = @import("std");

const shaders: []const []const u8 = &.{
    "unlit",
};

const indir = "shader/";
const outdir = "shader/include/shader/";

fn shader_needs_update(shader: []const u8) !bool {
    var infile_buffer = [_]u8{undefined} ** 100;
    const infile_path = try std.fmt.bufPrint(&infile_buffer, indir ++ "{s}.glsl", .{shader});

    var outfile_buffer = [_]u8{undefined} ** 100;
    const outfile_path = try std.fmt.bufPrint(&outfile_buffer, outdir ++ "{s}.h", .{shader});

    const infile = try std.fs.cwd().openFile(infile_path, .{});
    const outfile = std.fs.cwd().openFile(outfile_path, .{}) catch return true;

    return (try infile.metadata()).accessed() > (try outfile.metadata()).accessed();
}

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "daydream",
        .target = target,
        .optimize = optimize,
    });

    exe.linkLibC();
    exe.linkLibCpp();

    const shaderc: []const u8 = if (exe.target.isWindows())
        "./toolchain/sokol-tools-bin/bin/win32/sokol-shdc.exe"
    else
        "./toolchain/sokol-tools-bin/bin/linux/sokol-shdc";

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
        "-std=c++20",
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
            "src/impl.cpp",
            "src/app.cpp",
            "src/renderer.cpp",
        },
        if (optimize == std.builtin.OptimizeMode.Debug) debug_options else release_options,
    );

    for (shaders) |shader| {
        if (try shader_needs_update(shader)) {
            var infile_buffer = [_]u8{undefined} ** 100;
            const infile_arg = try std.fmt.bufPrint(&infile_buffer, "--input=" ++ indir ++ "{s}.glsl", .{shader});

            var outfile_buffer = [_]u8{undefined} ** 100;
            const outfile_arg = try std.fmt.bufPrint(&outfile_buffer, "--output=" ++ outdir ++ "{s}.h", .{shader});

            exe.step.dependOn(&b.addSystemCommand(&.{ shaderc, infile_arg, outfile_arg, "--slang=glsl330" }).step);
        }
    }

    b.installArtifact(exe);
}
