cmake_minimum_required(VERSION 2.8)
project(INF1060_project)

# $ cmake -D CMAKE_BUILD_TYPE=Release ..

# Set flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas -Wno-variadic-macros")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-long-long -Wno-unused-result")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

IF(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
ENDIF()

# Enable with cmake -DSANITIZE=all or e.g. -DSANITIZE=undefined
# Catches some errors at runtime, quite useful
if (SANITIZE)
  if(SANITIZE MATCHES all)
    set(SANITIZE address undefined shift unreachable null return signed-integer-overflow)
  endif()
  foreach(sanitize_flag ${SANITIZE})
    set(SANITIZE_FLAGS "${SANITIZE_FLAGS} -fsanitize=${sanitize_flag}")
  endforeach()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZE_FLAGS}")
endif()

IF(CMAKE_BUILD_TYPE MATCHES Release)
    # Some variables are read in assert statements which are not included in release mode
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
ENDIF()

# Store executables in <build_folder>/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(CLIENT_DIR "${ROOT_DIR}/client")
set(SERVER_DIR "${ROOT_DIR}/server")
set(INC_DIR "${ROOT_DIR}/include")

# set CMAKE flag so we can add some extra logic when building regular makefile projects
add_definitions(-DCMAKE)

include_directories(${INC_DIR})

#
# CONFIGURE client
#
file(GLOB CLIENT_SRC_FILES
     "${CLIENT_DIR}/*.c"
)
add_executable(client ${CLIENT_SRC_FILES})

#
# CONFIGURE server
#
file(GLOB SERVER_SRC_FILES
     "${SERVER_DIR}/*.c"
)
add_executable(server ${SERVER_SRC_FILES})
