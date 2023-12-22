const std = @import("std");
const nvrhi = @import("thirdparty/nvrhi/build.zig");
const jolt = @import("thirdparty/JoltPhysics/build.zig");
const spdlog = @import("thirdparty/spdlog/build.zig");

// fn source_pair_needs_update(infile_path: []const u8, outfile_path: []const u8) !bool {
//     const infile = try std.fs.cwd().openFile(infile_path, .{});
//     const outfile = std.fs.cwd().openFile(outfile_path, .{}) catch return true;

//     return (try infile.metadata()).accessed() > (try outfile.metadata()).accessed();
// }

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "daydream",
        .target = target,
        .optimize = optimize,
    });

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
        const compiler_args_common: []const []const u8 = &.{
            "-std=c++20",
            // "-fno-exceptions",
            // "-fno-rtti",
            "-Werror",
            "-Weverything",
            "-Wno-missing-prototypes",
            "-Wno-c++98-compat-pedantic",
            "-Wno-c++98-compat",
            "-Wno-padded",
            "-fstrict-flex-arrays=3",
            "-fPIE",
            "-DSPDLOG_COMPILED_LIB",
        };

        const compiler_args: []const []const u8 =
            if (optimize == std.builtin.OptimizeMode.Debug)
            compiler_args_common ++ .{ "-D_LIBCPP_ENABLE_DEBUG_MODE", "-D_GLIBCXX_DEBUG" }
        else if (optimize == std.builtin.OptimizeMode.ReleaseSafe)
            compiler_args_common ++ .{
                "-D_LIBCPP_ENABLE_ASSERTIONS",
                "-D_GLIBCXX_ASSERTIONS",
                "-fcf-protection=full",
                "-Wa,--noexecstack",
                "-ftrivial-auto-var-init=zero",
                // "-fstack-clash-protection",
            }
        else
            compiler_args_common;

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

        exe.addCSourceFiles(
            source_files,
            compiler_args,
        );
    }

    {
        const system_libs: []const []const u8 = if (exe.target.isWindows())
            &.{
                "gdi32",
                "ole32",
                "setupapi",
                "winmm",
                "imm32",
                "oleaut32",
                "version",
                "d3d11",
            }
        else
            &.{};

        for (system_libs) |lib| {
            exe.linkSystemLibrary(lib);
        }
    }

    {
        exe.addObjectFile(std.Build.LazyPath{ .path = "thirdparty/SDL2/x86_64-w64-mingw32/lib/libSDL2.a" });
        // exe.addObjectFile(std.Build.LazyPath{ .path = "thirdparty/SDL2/x86_64-w64-mingw32/lib/libSDL2.dll.a" });
        exe.addObjectFile(std.Build.LazyPath{ .path = "thirdparty/SDL2/x86_64-w64-mingw32/lib/libSDL2main.a" });
        // b.installBinFile("thirdparty/SDL2/x86_64-w64-mingw32/bin/SDL2.dll", "SDL2.dll");
    }

    exe.linkLibrary(spdlog.package(b, target, optimize));

    exe.linkLibrary(nvrhi.package(b, target, optimize));
    exe.step.dependOn(&b.addSystemCommand(&.{ "toolchain/ShaderMake/ShaderMake.exe", "-p", "DXBC", "--header", "-c", "shader/shadermake.cfg", "--compiler", "toolchain/ShaderMake/fxc.exe", "-o", "toolchain-out/shader/" }).step);

    // exe.linkLibrary(jolt.package(b, target, optimize));

    // {
    //     const shaderc: []const u8 = if (exe.target.isWindows())
    //         "toolchain/sokol-tools-bin/bin/win32/sokol-shdc.exe"
    //     else
    //         "toolchain/sokol-tools-bin/bin/linux/sokol-shdc";

    //     const shaders: []const []const u8 = &.{
    //         "unlit",
    //     };

    //     const shader_indir = "shader/";
    //     const shader_outdir = "shader/include/shader/";

    //     for (shaders) |shader| {
    //         var infile_buffer = [_]u8{undefined} ** 256;
    //         var outfile_buffer = [_]u8{undefined} ** 256;

    //         const infile_path = try std.fmt.bufPrint(&infile_buffer, shader_indir ++ "{s}.glsl", .{shader});
    //         const outfile_path = try std.fmt.bufPrint(&outfile_buffer, shader_outdir ++ "{s}.h", .{shader});

    //         if (try source_pair_needs_update(infile_path, outfile_path)) {
    //             const infile_arg = try std.fmt.bufPrint(&infile_buffer, "--input=" ++ shader_indir ++ "{s}.glsl", .{shader});
    //             const outfile_arg = try std.fmt.bufPrint(&outfile_buffer, "--output=" ++ shader_outdir ++ "{s}.h", .{shader});

    //             exe.step.dependOn(&b.addSystemCommand(&.{ shaderc, infile_arg, outfile_arg, "--slang=glsl330" }).step);
    //         }
    //     }
    // }

    exe.pie = true;
    exe.link_z_relro = true;
    // exe.want_lto = false; // https://github.com/ziglang/zig/issues/15958

    b.installArtifact(exe);
}
