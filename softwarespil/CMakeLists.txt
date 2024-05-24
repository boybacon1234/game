cmake_minimum_required(VERSION 3.5)

project(softwarespil LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Sql)
if(NOT Qt5_FOUND)
    message(FATAL_ERROR "Qt5 not found! Please install Qt5.")
endif()

add_executable(softwarespil main.cpp hero.h hero.cpp enemy.h enemy.cpp)
target_link_libraries(softwarespil Qt5::Core Qt5::Sql)


install(TARGETS softwarespil
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
