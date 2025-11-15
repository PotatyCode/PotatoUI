-- premake5.lua
workspace "PotatoTiler"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "App"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    -- Platform-specific settings
    filter "system:windows"
        systemversion "latest"
    filter "system:linux"
        pic "On"
    filter {}
-- Raylib Library
project "raylib"
    location "vendor/raylib"
    kind "StaticLib"
    language "C"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files {
        "vendor/raylib/src/*.c"
    }
    includedirs {
        "vendor/raylib/src",
        "vendor/raylib/src/external/glfw/include"
    }
    defines { "PLATFORM_DESKTOP" }
    filter "system:windows"
        defines { "_GLFW_WIN32" }
    filter "system:linux"
        defines { "_GLFW_X11" }
    filter "system:macosx"
        defines { "_GLFW_COCOA" }
    filter {}
-- CORE Library
project "Core"
    location "Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/include/**.h",
        "%{prj.name}/include/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/include",
        "vendor/raylib/src",  -- Adjust path to your raylib installation
        "vendor/raylib-cpp/include"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        defines { "DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
        defines { "NDEBUG" }

    filter {}

-- APP Executable
project "App"
    location "App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/include/**.h",
        "%{prj.name}/include/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/include",
        "Core/include",
        "vendor/raylib/src",  -- Adjust path to your raylib installation
        "vendor/raylib-cpp/include"
    }

    links {
        "Core"
    }

    -- Raylib linking (adjust paths based on your setup)
    libdirs {
        "vendor/raylib/lib"  -- Adjust to where raylib libs are
    }

    filter "system:windows"
        links {
            "raylib",
            "winmm",
            "gdi32",
            "opengl32"
        }

    filter "system:linux"
        links {
            "raylib",
            "GL",
            "m",
            "pthread",
            "dl",
            "rt",
            "X11"
        }

    filter "system:macosx"
        links {
            "raylib",
            "OpenGL.framework",
            "Cocoa.framework",
            "IOKit.framework",
            "CoreVideo.framework",
            "CoreAudio.framework",
            "AudioToolbox.framework"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        defines { "DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
        defines { "NDEBUG" }

    filter {}

newaction {
    trigger     = "clean",
    description = "Remove all binaries and generated files",
    execute     = function()
        print("Cleaning...")
        os.rmdir("./bin")
        os.rmdir("./bin-int")
        os.remove("App/Makefile")
        os.remove("Core/Makefile")
        os.remove("Makefile")
        os.remove("*.make")
        print("Done.")
    end
}
