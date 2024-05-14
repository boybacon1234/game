cmake_minimum_required(VERSION 3.5)

project(softwarespil LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(softwarespil main.cpp hero.h hero.cpp enemy.h enemy.cpp heromaneger.h heromaneger.cpp)

install(TARGETS softwarespil
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
