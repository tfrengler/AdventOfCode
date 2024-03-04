const std = @import("std");

pub fn build(b: *std.Build) void {
    const optimize = b.standardOptimizeOption(.{});
    const exe = b.addExecutable(.{
        .name = "main",
        .root_source_file = .{ .path = "./src/Day01Part01.zig" },
        .optimize = optimize,
    });

    b.default_step.dependOn(&exe.step);
}
