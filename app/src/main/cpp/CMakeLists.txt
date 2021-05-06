cmake_minimum_required(VERSION 3.10.2)

project("Auto-Il2cppDumper")

add_library(
        native-lib
        SHARED
        native-lib.cpp
        Includes/il2cpp_dump.cpp)

find_library(log-lib log)
target_link_libraries(native-lib ${log-lib})