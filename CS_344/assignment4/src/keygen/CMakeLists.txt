
cmake_minimum_required (VERSION 2.8.12)

set (PROJ_NAME keygen)

project (${PROJ_NAME})

set(CMAKE_BUILD_TYPE Debug)

# Add include folders
include_directories("${PROJECT_SOURCE_DIR}/include")

# Source Files
set(KEYGEN_SRC
  ${PROJECT_SOURCE_DIR}/keygen.c
)

# Define the output executable
add_executable(${PROJ_NAME} ${KEYGEN_SRC})
