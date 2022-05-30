set(target common)

file(GLOB_RECURSE srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

if (srcs)
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
    PUBLIC proto_cpp
  )
else()
  add_library(
    ${target}
    INTERFACE
  )
  target_include_directories(
    ${target}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )
  target_link_libraries(
    ${target}
    INTERFACE proto_cpp
  )
endif()

