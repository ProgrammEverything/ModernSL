cmake_minimum_required(VERSION 3.10.0)
project(ModernSL VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
    "include/*.h" # some editors need include files listed
)
include_directories(include)


add_executable(ModernSL ${SOURCES})

target_link_libraries(ModernSL PRIVATE ${CURSES_LIBRARIES})
target_include_directories(ModernSL PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(ModernSL ncurses)
