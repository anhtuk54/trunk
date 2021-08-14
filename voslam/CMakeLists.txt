project(voslam)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(HDRS_LIB
    src/voslam/utils/Logger.h
)

set(SRCS_LIB
    src/voslam/app/Engine.cpp
    src/voslam/core/Frame.cpp
    src/voslam/core/Configuration.cpp
    src/voslam/core/DeviceMono.cpp
    src/voslam/core/ipc/Looper.cpp
    src/voslam/odo/OdoEstimator.cpp
    src/voslam/slam/SLAMEstimator.cpp
    src/voslam/gui/OdoVisualizer.cpp
)

set(SRCS_TEST_MONO
    src/test/monocular.cpp
)

set(SRCS_TEST_STEREO
    src/test/stereo.cpp
)

include_directories(
    src/voslam/
)

add_executable(monocular ${HDRS_LIB} ${SRCS_LIB} ${SRCS_TEST_MONO})
target_link_libraries( monocular ${OpenCV_LIBS} pthread)

add_executable(stereo ${HDRS_LIB} ${SRCS_LIB} ${SRCS_TEST_STEREO})
target_link_libraries( stereo ${OpenCV_LIBS} pthread)
