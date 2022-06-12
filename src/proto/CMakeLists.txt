set(target_cpp proto_cpp)

set(Protobuf_DEBUG "ON")
find_package(Protobuf REQUIRED COMPONENTS protoc libprotobuf)

file(GLOB_RECURSE protos ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)

PROTOBUF_GENERATE_CPP(
  proto_cpp_srcs
  proto_cpp_hdrs
  ${protos}
)

PROTOBUF_GENERATE_PYTHON(
  proto_python_srcs
  ${protos}
)

add_library(
  ${target_cpp}
)

target_sources(
  ${target_cpp}
  PRIVATE ${proto_cpp_srcs} ${proto_cpp_hdrs}
)

target_include_directories(
  ${target_cpp}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(
  ${target_cpp}
  PUBLIC ${PROTOBUF_LIBRARY}
)

set(target_python proto_python)

add_custom_target(
  ${target_python}
  ALL
  DEPENDS ${proto_python_srcs}
)

add_custom_command(
  TARGET ${target_python}
  POST_BUILD
  VERBATIM
  COMMAND_EXPAND_LISTS
  COMMAND ${CMAKE_COMMAND} -E copy
          ${proto_python_srcs}
          ${CMAKE_SOURCE_DIR}/src/python
)
