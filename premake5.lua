workspace "FryWork"
    architecture "x86_64"
    cppdialect "C++17"
    configurations
    {
        "Debug",
        "Release"
    }
include "FryEngine"
include "FryBox"
include "FryTest"