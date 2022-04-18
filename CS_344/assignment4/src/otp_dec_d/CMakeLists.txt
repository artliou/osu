
cmake_minimum_required (VERSION 2.8.12)

set (PROJ_NAME otp_dec_d)

project (${PROJ_NAME})

set(CMAKE_BUILD_TYPE Debug)

# Add include folders
include_directories("${PROJECT_SOURCE_DIR}/../common")

# Source Files
set(OTP_DEC_D_SRC
  ${PROJECT_SOURCE_DIR}/otp_dec_d.c
  ${PROJECT_SOURCE_DIR}/../common/common.c
  ${PROJECT_SOURCE_DIR}/../common/common_server.c
)

# Define the output executable
add_executable(${PROJ_NAME} ${OTP_DEC_D_SRC})
