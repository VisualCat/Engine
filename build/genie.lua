solution "visualcat_engine"
  
  configurations {
    "Release",
    "Debug"
  }

  platforms {
    "x64",
    "x32",
    "Native",
  }
  
  language "C++"

PROJ_DIR = path.getabsolute("..")

project "project0"
  kind "ConsoleApp"

  configuration "Debug"

  defines { "_GLFW_WGL" }
  defines { "_GLFW_WIN32" }
  defines { "_GLFW_USE_OPENGL" }
  defines { "GLEW_STATIC" }
 


  includedirs{
    path.join(PROJ_DIR, "include"),
    path.join(PROJ_DIR, "include/GLFW"),
   
    
  }

  libdirs { 
    path.join(PROJ_DIR, "deps"),
  
  }
  
  files { 

    path.join(PROJ_DIR,"./include/GLFW/*.h"),
    --path.join(PROJ_DIR,"./include/GLFW/*.c"),
    
    path.join(PROJ_DIR,"./src/*.cc"),

    path.join(PROJ_DIR,"./include/platform_types.h"),
    
    path.join(PROJ_DIR,"./src/main.cc"),

    path.join(PROJ_DIR,"./src/GLFW/init.c"),
    path.join(PROJ_DIR,"./src/GLFW/monitor.c"),
    path.join(PROJ_DIR,"./src/GLFW/context.c"),
    path.join(PROJ_DIR,"./src/GLFW/vulkan.c"),
    path.join(PROJ_DIR,"./src/GLFW/internal.h"),
    path.join(PROJ_DIR,"./src/GLFW/window.c"),
    path.join(PROJ_DIR,"./src/GLFW/input.c"),
    path.join(PROJ_DIR,"./src/GLFW/wgl_context.c"),
    path.join(PROJ_DIR,"./src/GLFW/wgl_context.h"),
    path.join(PROJ_DIR,"./src/GLFW/egl_context.c"),
    path.join(PROJ_DIR,"./src/GLFW/egl_context.h"),
    path.join(PROJ_DIR,"./src/GLFW/win32_init.c"),
    path.join(PROJ_DIR,"./src/GLFW/win32_joystick.c"),
    path.join(PROJ_DIR,"./src/GLFW/win32_joystick.h"),
    path.join(PROJ_DIR,"./src/GLFW/win32_monitor.c"),
    path.join(PROJ_DIR,"./src/GLFW/win32_platform.h"),
    path.join(PROJ_DIR,"./src/GLFW/win32_tls.h"),
    path.join(PROJ_DIR,"./src/GLFW/win32_tls.c"),
    path.join(PROJ_DIR,"./src/GLFW/win32_time.c"),
    path.join(PROJ_DIR,"./src/GLFW/win32_window.c"),

  }

  links { "opengl32",
            "user32", 
            "gdi32" ,
            "shell32",
            }


  flags{"Symbols"}
