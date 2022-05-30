set(target proto)

find_package(Protobuf REQUIRED)

file(GLOB_RECURSE protos ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)
PROTOBUF_GENERATE_CPP(proto_srcs proto_hdrs ${protos})

add_library(
  ${target}
)

target_sources(
  ${target}
  PUBLIC ${proto_srcs} ${proto_hdrs}
)

target_include_directories(
  ${target}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(
  ${target}
  PUBLIC ${PROTOBUF_LIBRARY}
)
