package(default_visibility = ["//visibility:public"])

load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")
load("@mxebzl//tools/windows:rules.bzl", "pkg_winzip")

config_setting(
    name = "windows",
    values = {
        "crosstool_top": "@mxebzl//tools/windows:toolchain",
    }
)

cc_binary(
    name = "eeprom",
    data = ["//content"],
    linkopts = select({
        ":windows": ["-mwindows", "-lSDL2main" ],
        "//conditions:default": [],
    }) + [
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

pkg_winzip(
    name = "eeprom-windows",
    files = [
        ":eeprom",
        "//content",
    ]
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
        ":game_state",
        ":level",
    ],
)

cc_library(
    name = "game_state",
    srcs = ["game_state.cc"],
    hdrs = ["game_state.h"],
)

cc_library(
    name = "map",
    srcs = ["map.cc"],
    hdrs = ["map.h"],
    deps = [
        "@libgam//:spritemap",
        "@libgam//:util",
    ],
)

cc_library(
    name = "level",
    srcs = ["level.cc"],
    hdrs = ["level.h"],
    deps = [
        ":map",
    ],
)

