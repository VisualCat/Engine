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

defines { "_GLFW_X11" }
defines { "_GLFW_USE_OPENGL" }
defines { "GLEW_STATIC" }
defines { "GLEW_NO_GLU" }
defines { "MTR_ENABLED" }
defines { "DMTR_ENABLED" }
defines { "WITH_ALSA" }



includedirs{
    path.join(PROJ_DIR, "include"),
    path.join(PROJ_DIR, "include/GLEW"),
    path.join(PROJ_DIR, "include/IMGUI"),
    path.join(PROJ_DIR, "include/MathLibrary"),
    path.join(PROJ_DIR, "include/glm"),


}

libdirs {
    path.join(PROJ_DIR, "deps"),

}

files {

    path.join(PROJ_DIR,"./include/GLFW/*.h"),
    path.join(PROJ_DIR,"./include/GLEW/*.h"),
    path.join(PROJ_DIR,"./include/IMGUI/*.h"),
    path.join(PROJ_DIR,"./include/IMGUI/*.cpp"),
    path.join(PROJ_DIR,"./include/*.h"),
    --path.join(PROJ_DIR, "include/MathLibrary/*.h"),
    --path.join(PROJ_DIR, "include/MathLibrary/*.cc"),

    path.join(PROJ_DIR,"./src/*.cc"),

    path.join(PROJ_DIR,"./include/platform_types.h"),

    path.join(PROJ_DIR,"./src/main.cc"),

    path.join(PROJ_DIR,"./src/GLEW/*.c"),


    path.join(PROJ_DIR,"./src/GLFW/linux/*.c"),

}


links { "X11",
    "Xrandr",
    --"Xi",
    "Xxf86vm",
    "Xcursor",
    "Xinerama",
    "pthread",
    "GL",
    "dl",
    "asound", }

flags{"Symbols"}

buildoptions_cpp {
    "--std=c++17",
}
