const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    //const optimize = b.standardOptimizeOption(.{});
    const exe = b.addExecutable(.{
        .name = "Day01",
        .root_source_file = b.path("./src/Day01Part01.zig"),
        .target = target,
        .optimize = .Debug,
    });

    b.installArtifact(exe);
}
