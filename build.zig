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
            "vector.c",
            "matrix.c",
            "vector_transform_layer.c",
            "vector_transform_block.c",
            "vector_transform_block_creator.c",
            "file_interface.c",
            "test.c",
        },
        .flags = &.{"-std=c99"},
    });

    b.installArtifact(test_executable);
}
