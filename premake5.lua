outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "Genesis"
  architecture "x86_64"
  startproject "Genesis"

  configurations { "Debug", "Release" }

  filter "configurations:Debug"
    defines { "GEN_DEBUG" }
    symbols "On"

  filter "configurations:Release"
    defines { "GEN_RELEASE" }
    optimize "On"

  filter {}

include "Genesis"
include "Sandbox"
