const std = @import("std");

pub fn build(b: *std.Build) void {
    const exe = b.addExecutable(.{
        .name = "daydream",
    });

    exe.linkLibC();

    if (exe.target.isWindows()) {
        exe.linkSystemLibraryName("kernel32");
        exe.linkSystemLibraryName("user32");
        exe.linkSystemLibraryName("gdi32");
        exe.linkSystemLibraryName("ole32");
    } else {
        exe.linkSystemLibraryName("X11");
        exe.linkSystemLibraryName("Xi");
        exe.linkSystemLibraryName("Xcursor");
    }

    exe.addIncludePath(std.Build.LazyPath { .path = "subprojects/sokol" });
    exe.addCSourceFile(.{ .file = .{ .path = "src/main.cpp" }, .flags = &.{}});

    b.installArtifact(exe);
}