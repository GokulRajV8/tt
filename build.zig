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
            "src/vector.c",
            "src/matrix.c",
            "src/vector_transform_layer.c",
            "src/vector_transform_block.c",
            "src/vector_transform_block_creator.c",
            "src/file_interface.c",
            "src/test.c",
        },
        .flags = &.{"-std=c99"},
    });

    b.installArtifact(test_executable);
}
