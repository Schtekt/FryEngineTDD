project "gTest"
  kind "StaticLib"
  targetdir "../Build/bin/%{prj.name}"
  objdir "../Build/bin-int/%{prj.name}"
  files { "../googletest/googletest/src/gtest-all.cc" }
  includedirs { "../googletest/googletest/include", "../googletest/googletest" }
  filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

  filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

project "FryTest"
    kind "ConsoleApp"
    language "C++"
    targetdir "../Build/bin/%{prj.name}"
    objdir "../Build/bin-int/%{prj.name}"
    files {"src/**.cpp", "src/**.h"}
    includedirs{"src/", "../googletest/googletest/include"}
    links{"FryEngine", "gTest"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"