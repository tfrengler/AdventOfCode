const std = @import("std");

pub fn gnargle() void {
    std.debug.print("Hello, World!\n", .{});
}

pub fn main() !void {
    gnargle();
}
