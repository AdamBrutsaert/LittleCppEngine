project "Genesis"
  files {
    "include/GLFW/glfw3.h",
    "include/GLFW/glfw3native.h",
    "src/internal.h",
    "src/platform.h",
    "src/mappings.h",
    "src/context.c",
    "src/init.c",
    "src/input.c",
    "src/monitor.c",
    "src/platform.c",
    "src/vulkan.c",
    "src/window.c",
    "src/egl_context.c",
    "src/osmesa_context.c",
    "src/null_platform.h",
    "src/null_joystick.h",
    "src/null_init.c",
    "src/null_monitor.c",
    "src/null_window.c",
    "src/null_joystick.c",
  }

  filter "system:linux"
    files {
      "src/posix_time.h",
      "src/posix_thread.h",
      "src/posix_module.c",
      "src/posix_time.c",
      "src/posix_thread.c",
      "src/x11_platform.h",
      "src/xkb_unicode.h",
      "src/x11_init.c",
      "src/x11_monitor.c",
      "src/x11_window.c",
      "src/xkb_unicode.c",
      "src/glx_context.c",
      "src/linux_joystick.h",
      "src/linux_joystick.c",
      "src/posix_poll.h",
      "src/posix_poll.c",
    }

    defines { "_GLFW_X11" }
