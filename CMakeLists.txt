cmake_minimum_required(VERSION 3.21)

# Configure with vcpkg package manager if enviroment variable and toolchain variable isn't already defined
# Recommend: https://vcpkg.readthedocs.io/en/latest/users/integration/
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
  message(STATUS "VCPKG_ROOT was defined")
endif()

set(ocr_base "../vcpkg/installed/x64-windows")
set(ocr_include "${ocr_base}/include")
set(tesseract_include_dir "${ocr_include}")

message(STATUS "Variable Set: ocr_base | ${ocr_base}")
message(STATUS "Variable Set: ocr_include | ${ocr_include}")
message(STATUS "Variable Set: tesseract | ${tesseract_include_dir}")

# Name of the project (will be the name of the plugin)
project(addon)

# Build a shared library named after the project from the files in `src/`
file(GLOB SOURCE_FILES "src/window-imagetter/*.cc" "src/window-imagetter/*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})

find_package(Tesseract CONFIG REQUIRED)
include_directories(${tesseract_include_dir})

message(STATUS "Include: " ${tesseract} /baseapi.h)
message(STATUS "Include: " ${leptonica} /allheaders.h)

# Gives our library file a .node extension without any "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Essential include files to build a node addon,
# You should add this line in every CMake.js based project
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})

# Essential library files to link to a node addon
# You should add this line in every CMake.js based project
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} libtesseract)
