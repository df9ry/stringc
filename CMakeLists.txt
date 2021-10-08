cmake_minimum_required(VERSION 3.14)

project(stringc LANGUAGES C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
  stringc.c
)

set(HEADERS
  stringc/stringc.h
)

add_library(stringc STATIC
  ${SOURCES}
  ${HEADERS}
)

set_target_properties(stringc PROPERTIES
  PUBLIC_HEADER stringc/stringc.h)

target_compile_definitions(stringc PRIVATE STRINGC_LIBRARY)

install(TARGETS stringc
  LIBRARY DESTINATION       "${CMAKE_BUILD_TYPE}/lib"
  ARCHIVE DESTINATION       "${CMAKE_BUILD_TYPE}/lib"
  PUBLIC_HEADER DESTINATION "${CMAKE_BUILD_TYPE}/include/stringc")

set(APP_EXE stringc_test)
add_executable(${APP_EXE} stringc_test.c)
target_link_libraries(${APP_EXE} stringc)
add_test(Test, ${APP_EXE})
