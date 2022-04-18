cmake_minimum_required (VERSION 2.8.11)

SET(NUMT "1" CACHE STRING "Number of Threads")
SET(NUMNODES "64" CACHE STRING "Number of Nodes")

set (PROJ_NAME cs475-project1)

project (${PROJ_NAME})

# Add include folders
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/platform/include")

set(PLATFORM_SRCS
  ${PROJECT_SOURCE_DIR}/platform/src/CSVLogger.cpp
  ${PROJECT_SOURCE_DIR}/platform/src/ThreadManager.cpp
)

set(PROJECT_SRCS
  ${PROJECT_SOURCE_DIR}/src/project1.cpp
  ${PROJECT_SOURCE_DIR}/src/curveCalc.cpp
)

# Compilier settings
set(CMAKE_CXX_FLAGS "-O3 -lm -fopenmp")

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/local/include -L/usr/local/lib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib")

#add_definitions(-DNUMT=${NUMT})
#add_definitions(-DNUMNODES=${NUMNODES})

add_executable(${PROJ_NAME} ${PLATFORM_SRCS} ${PROJECT_SRCS})
