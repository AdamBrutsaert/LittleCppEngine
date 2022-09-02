project "Genesis"
  kind "StaticLib"
  language "C++"
  cppdialect "C++20"

  targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
  objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
  includedirs { "include", "thirdparties/glfw/include" }

  files { "include/**.h", "src/**.cpp"}

  filter "configurations:Debug"
    defines { "GEN_DEBUG" }
    symbols "On"

  filter "configurations:Release"
    defines { "GEN_RELEASE" }
    optimize "On"

  filter {}

include "thirdparties/glfw"
