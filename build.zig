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
    exe.want_lto = false; // TODO: https://github.com/ziglang/zig/issues/15958

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
        exe.linkSystemLibraryName("GL");
    }

    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator = gpa.allocator();

    var compiler_args = std.ArrayList([]const u8).init(allocator);
    defer compiler_args.deinit();

    try compiler_args.appendSlice(&.{
        "-std=c++20",
        "-Werror",
        "-Weverything",
        "-Wno-missing-prototypes",
        "-Wno-c++98-compat-pedantic",
        "-Wno-c++98-compat",
        "-fstrict-flex-arrays=3",
    });

    if (optimize == std.builtin.OptimizeMode.Debug) {
        try compiler_args.append("-D_LIBCPP_ENABLE_DEBUG_MODE");
    } else {
        try compiler_args.append("-D_LIBCPP_ENABLE_ASSERTIONS");
    }

    const system_include_paths: []const []const u8 = &.{
        "thirdparty/sokol/",
        "thirdparty/glm/",
        "thirdparty/entt/src/",
        "thirdparty/fmt/include/",
        "thirdparty/GSL/include/",
        "thirdparty/expected/include/",
    };

    for (system_include_paths) |include_path| {
        exe.addSystemIncludePath(std.Build.LazyPath{ .path = include_path });
    }

    const source_files: []const []const u8 = &.{
        "src/main.cpp",
        "src/impl.cpp",
        "src/app.cpp",
        "src/renderer.cpp",
    };

    exe.addCSourceFiles(
        source_files,
        compiler_args.items,
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
