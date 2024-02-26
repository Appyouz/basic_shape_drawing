cmake_minimum_required(VERSION 3.28.2)
set(PROJECT_NAME draw_shapes)
project(${PROJECT_NAME})

# set c++ standard
set(CMAKE_CXX_STANDARD 17)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# add your source files
set(SOURCE_FILES 
  src/main.cpp
  )
set (HEADER_FILES
  )

# Add the CMAKE_EXPORT_COMPILE_COMMANDS option
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# SDL2 package
# find_package(SDL2_image REQUIRED)
find_package(SDL2 REQUIRED)


add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# Include the 'include/' directory
target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 )

set(CMAKE_ERROR_DEPRECATED TRUE)
set(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION TRUE)

# Add flags for comprehensive warnings and error messages
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()
