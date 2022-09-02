outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "Genesis"
  architecture "x86_64"
  startproject "Sandbox"

  configurations { "Debug", "Release" }

include "Genesis"
include "Sandbox"
