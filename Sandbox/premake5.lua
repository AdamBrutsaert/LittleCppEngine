project "Sandbox"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"

  targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
  objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
  includedirs { "%{wks.location}/Genesis/include" }

  links { "Genesis" }
  files { "include/**.h", "src/**.cpp"}

  filter "configurations:Debug"
    symbols "On"

  filter "configurations:Release"
    optimize "On"
