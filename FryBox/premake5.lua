project "FryBox"
   kind "ConsoleApp"
   language "C++"
   targetdir "../Build/bin/%{prj.name}"
   objdir "../Build/bin-int/%{prj.name}"
   includedirs{"../FryEngine/src"}
   links{"FryEngine"}

   files { "src/**.h", "src/**.cpp" }
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"