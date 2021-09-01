project(camerav4l2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

set(HDRS
    inc/utils/json.hpp
    inc/utils/Logger.h
    inc/CommonDefs.h
    inc/CDevice.h
    inc/CDeviceConfig.h
    inc/CConfiguration.h
    inc/CWindow.h
)

set(SRCS
    src/main.cpp
    src/CDevice.cpp
    src/CDeviceConfig.cpp
    src/CConfiguration.cpp
    src/CWindow.cpp
)

include_directories(
    ./inc
)

add_executable(camerav4l2 ${HDRS} ${SRCS})
target_link_libraries(camerav4l2 pthread SDL2 SDL2_image)
add_custom_command(
    TARGET camerav4l2 POST_BUILD
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/config.json ${CMAKE_CURRENT_BINARY_DIR}/config.json
)