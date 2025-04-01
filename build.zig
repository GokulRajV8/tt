const std = @import("std");

pub fn build(b: *std.Build) void {
    const test_executable = b.addExecutable(.{
        .name = "test",
        .target = b.standardTargetOptions(.{}),
        .optimize = b.standardOptimizeOption(.{}),
    });
    test_executable.linkLibC();
    test_executable.addCSourceFiles(.{
        .files = &.{
            "src/tt/vector.c",
            "src/tt/matrix.c",
            "src/tt/layer.c",
            "src/tt/block.c",
            "src/tt/file_interface.c",
            "src/tt/simple_bp.c",
            "src/test.c",
        },
        .flags = &.{"-std=c99"},
    });

    b.installArtifact(test_executable);
}
