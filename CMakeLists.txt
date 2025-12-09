cmake_minimum_required(VERSION 3.16)

project(FreeCADMbD VERSION 1.0.1 DESCRIPTION "Assembly Constraints and Multibody Dynamics code")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

option(FREECADMBD_BUILD_TESTS "Set to ON to build the Google Test-based C++ test suite." ON)
option(FREECADMBD_BUILD_EXE "Set to ON to build the standalone FreeCADMbD executable." ON)

include(GNUInstallDirs)

if( UNIX )
    set( FREECADMBD_BUILD_SHARED ON )
ELSEIF ( APPLE )
    set( FREECADMBD_BUILD_SHARED ON )
ELSE()
    set( FREECADMBD_BUILD_SHARED OFF )
ENDIF ()

add_compile_definitions(TEST_DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/testapp")
add_subdirectory(FreeCADMbD)
if(FREECADMBD_BUILD_EXE)
    add_subdirectory(FreeCADMbDMain)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/FreeCADMbDMain PROPERTY VS_STARTUP_PROJECT FreeCADMbDMain)
endif()

if(FREECADMBD_BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
    target_compile_definitions(test_run PUBLIC TEST_DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/testapp")
endif()
