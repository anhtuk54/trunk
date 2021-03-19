
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

include_directories(
    ./utils
)

add_subdirectory(creation_abstract_factory)
add_subdirectory(creation_builder)
add_subdirectory(creation_prototype)