cmake_minimum_required ( VERSION 2.8.12 )

project ( dmtransport )

macro(get_WIN32_WINNT version)
    if (WIN32 AND CMAKE_SYSTEM_VERSION)
        set(ver ${CMAKE_SYSTEM_VERSION})
        string(REPLACE "." "" ver ${ver})
        string(REGEX REPLACE "([0-9])" "0\\1" ver ${ver})

        set(${version} "0x${ver}")
    endif()
endmacro()
# Local CMake Modules
set ( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules" )

option( DMT_BUILD_DOCS "Build the DMT Doxygen documentation" ON)
if ( DMT_BUILD_DOCS )
    find_package(Doxygen)
endif ( )

# Import macros
include ( CheckCXXCompilerFlag )

# C++11 Requirement for Linux
if ( NOT WIN32 )
    check_cxx_compiler_flag ( "-std=c++11" COMPILER_SUPPORTS_CXX11 )
    check_cxx_compiler_flag ( "-std=c++0x" COMPILER_SUPPORTS_CXX0X )
    set ( CMAKE_CXX_COMPILER_ARG1 "-std=c++11" )

    if ( COMPILER_SUPPORTS_CXX11 )
        set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11" )
    elseif ( COMPILER_SUPPORTS_CXX0X )
        set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x" )
    else ( )
        message ( STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif ( )
    
    set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3" )  # Optimize
else ( )
    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})

    if ( MINGW )
        check_cxx_compiler_flag ( "-std=c++11" COMPILER_SUPPORTS_CXX11 )
        check_cxx_compiler_flag ( "-std=c++0x" COMPILER_SUPPORTS_CXX0X )
        set ( CMAKE_CXX_COMPILER_ARG1 "-std=c++11" )
    
        if ( COMPILER_SUPPORTS_CXX11 )
            set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
        elseif ( COMPILER_SUPPORTS_CXX0X )
            set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
        else ( )
            message ( STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
        endif ( )
        
        set ( CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++" )
    else ( )
        add_definitions ( "/wd4244 /wd4996" )
    endif ( )
endif ( )

set ( DMT_ENET_DIR "${PROJECT_SOURCE_DIR}/../third-party/enet/Source/Native" )
include_directories ( ${DMT_ENET_DIR} "src" )

add_subdirectory ( src )
add_subdirectory ( tests )

# Docs
if ( DOXYGEN_FOUND AND DMT_BUILD_DOCS )
    if ( DOXYGEN_DOT_FOUND )
        set ( DMT_HAVE_DOT "YES" )
    else ( )
        set ( DMT_HAVE_DOT "NO" )
    endif ( )

    configure_file( "${PROJECT_SOURCE_DIR}/docs/Doxyfile.in"
                    "${CMAKE_INSTALL_PREFIX}/docs/Doxyfile" )

    add_subdirectory ( docs )
endif ( )
