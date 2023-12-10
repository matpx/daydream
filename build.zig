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

    if (exe.target.isWindows()) {
        exe.linkSystemLibraryName("kernel32");
        exe.linkSystemLibraryName("user32");
        exe.linkSystemLibraryName("gdi32");
        exe.linkSystemLibraryName("ole32");
    } else if (exe.target.isLinux()) {
        exe.linkSystemLibraryName("X11");
        exe.linkSystemLibraryName("Xi");
        exe.linkSystemLibraryName("Xcursor");
    } else if (exe.target.getOsTag() == .wasi) {
        exe.defineCMacro("__EMSCRIPTEN__", "1");
    }

    // exe.addIncludePath(std.Build.LazyPath{ .path = "subprojects/sokol" });
    exe.addCSourceFile(.{ .file = .{ .path = "src/main.cpp" }, .flags = &.{} });

    b.installArtifact(exe);
}
