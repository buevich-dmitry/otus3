cmake_minimum_required(VERSION 3.10)
project(print_ip VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -pedantic -Werror)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_library(print_ip_lib INTERFACE)
target_sources(print_ip_lib INTERFACE ${CMAKE_SOURCE_DIR}/print_ip.h)

add_executable(print_ip main.cpp)
link_libraries(print_ip print_ip_lib)

install(TARGETS print_ip RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEB_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${print_ip_VERSION})
set(CPACK_PACKAGE_CONTACT buevichd@yandex-team.ru)
include(CPack)

