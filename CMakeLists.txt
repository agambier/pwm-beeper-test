PROJECT(PWMTEST)

cmake_minimum_required(VERSION 3.2)

SET(TOOLS_DIR ${PROJECT_SOURCE_DIR}/../../prebuilts/toolschain/usr/bin/arm-linux-)

# this is required
SET(CMAKE_SYSTEM_NAME Linux)

# specify the cross compiler
SET(CMAKE_C_COMPILER   ${TOOLS_DIR}gcc)
SET(CMAKE_CXX_COMPILER ${TOOLS_DIR}g++)

ADD_SUBDIRECTORY(src)

