set(target funwithprofiler)

file(GLOB_RECURSE srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(
    ${target}
)

target_sources(
    ${target}
    PRIVATE ${srcs}
)

target_link_libraries(
    ${target}
    PRIVATE cache_miss
            locality
            Boost::program_options
)
