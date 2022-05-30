set(target cache_miss)

file(GLOB_RECURSE srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(
    ${target}
)

target_sources(
    ${target}
    PRIVATE ${srcs}
)

target_include_directories(
    ${target}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    ${target}
    PUBLIC common
)
