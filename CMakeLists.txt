# min version
cmake_minimum_required(CMAKE_VERSION 3.12)
# C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS False)

# template
project(
  game
  VERSION 0.1
  LANGUAGES C)

# required libs
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

# grab header and source files
file(GLOB_RECURSIVE SOURCE_FILES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSIVE HEADER_FILES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.h")

# compile
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# include lib dir

target_include_directories(${PROJECT_NAME}
                           PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib")

# link against
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL_image::SDL_image
                                              SDL_ttf::SDL_ttf)

# set compiler options and features

# C99
target_compile_features(${PROJECT_NAME} PRIVATE c_std_99)

# -Wall -Wextra -Wpedantic
target_compile_options(
  ${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra
                          -Wpedantic>)
