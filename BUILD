package(default_visibility = ["//visibility:public"])

load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")

cc_binary(
    name = "eeprom",
    data = ["//content"],
    linkopts = [
        "-lSDL2",
        "-lSDL2_image",
        "-lSDL2_mixer",
        "-static-libstdc++",
        "-static-libgcc",
    ],
    srcs = ["main.cc"],
    deps = [
        "@libgam//:game",
        ":screens",
    ],
)

pkg_tar(
    name = "eeprom-linux",
    extension = "tar.gz",
    strip_prefix = "/",
    package_dir = "eeprom/",
    srcs = [
        ":eeprom",
        "//content",
    ],
)

cc_library(
    name = "screens",
    srcs = [
        "title_screen.cc",
        "level_screen.cc",
    ],
    hdrs = [
        "title_screen.h",
        "level_screen.h",
    ],
    deps = [
        "@libgam//:backdrop",
        "@libgam//:screen",
        "@libgam//:text",
        ":box",
        ":game_state",
        ":level",
    ],
)

cc_library(
    name = "game_state",
    srcs = ["game_state.cc"],
    hdrs = ["game_state.h"],
    deps = [
        ":player",
    ]
)

cc_library(
    name = "map",
    srcs = ["map.cc"],
    hdrs = ["map.h"],
    deps = [
        "@libgam//:graphics",
        "@libgam//:spritemap",
        "@libgam//:util",
    ],
)

cc_library(
    name = "level",
    srcs = ["level.cc"],
    hdrs = ["level.h"],
    deps = [
        "@libgam//:graphics",
        ":crate",
        ":map",
        ":player",
        ":piston",
    ],
)

cc_library(
    name = "player",
    srcs = ["player.cc"],
    hdrs = ["player.h"],
    deps = [
        "@libgam//:graphics",
        "@libgam//:spritemap",
        ":map",
    ],
)

cc_library(
    name = "box",
    srcs = ["box.cc"],
    hdrs = ["box.h"],
    deps = [
        "@libgam//:graphics",
    ],
)

cc_library(
    name = "piston",
    srcs = ["piston.cc"],
    hdrs = ["piston.h"],
    deps = [
        "@libgam//:graphics",
        "@libgam//:spritemap",
    ],
)

cc_library(
    name = "crate",
    srcs = ["crate.cc"],
    hdrs = ["crate.h"],
    deps = [
        "@libgam//:graphics",
        "@libgam//:spritemap",
    ],
)

