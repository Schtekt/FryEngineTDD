project "FryEngine"
    kind "StaticLib"
    language "C++"
    targetdir "../Build/bin/%{prj.name}"
    objdir "../Build/bin-int/%{prj.name}"
    files { "src/**.h", "src/**.cpp" }
    filter "system:windows"
        links {"d3d11"}
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"