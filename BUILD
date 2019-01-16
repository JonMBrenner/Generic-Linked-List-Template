flags = ["-fdiagnostics-color=always", "-std=c++17", "-Wall", "-Wextra", "-pedantic-errors",]

cc_test(
    name = "test_linked_list",
    srcs = [
        "test_linked_list.cpp",
        "test_main.cpp",
    ],
    deps = [
        ":linked_list",
        ":catch",
    ],
    copts = flags,
    size = "small",

)

cc_library(
    name = "linked_list",
    srcs = ["linked_list.cpp",],
    hdrs = ["linked_list.h",],
    copts = flags,
)

cc_library(
    name = "catch",
    hdrs = ["catch.hpp"],
)
