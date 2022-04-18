cmake_minimum_required (VERSION 2.8.11)

set (PROJ_NAME cs475-project6)

project (${PROJ_NAME})

# Add include folders
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/platform/include")

find_package(OpenCL REQUIRED)
find_package(OpenMP REQUIRED)

include_directories("${OpenCL_INCLUDE_DIR}")
include_directories("${OpenCL_INCLUDE_DIR}")

set(PLATFORM_SRCS
  ${PROJECT_SOURCE_DIR}/platform/src/CSVLogger.cpp
  ${PROJECT_SOURCE_DIR}/platform/src/OpenCL.cpp
  ${PROJECT_SOURCE_DIR}/platform/src/ThreadManager.cpp
)

set(PROJECT_SRCS
  ${PROJECT_SOURCE_DIR}/src/project6.cpp
)

# Compilier settings
set(CMAKE_CXX_FLAGS "-O0 -lm ${OpenMP_CXX_FLAGS} -DDEBUG -g")

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/local/include -L/usr/local/lib")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib")

#add_definitions(-DNUMT=${NUMT})
#add_definitions(-DNUMNODES=${NUMNODES})

add_executable(${PROJ_NAME} ${PLATFORM_SRCS} ${PROJECT_SRCS})
target_link_libraries(${PROJ_NAME} "${OpenCL_LIBRARIES}")