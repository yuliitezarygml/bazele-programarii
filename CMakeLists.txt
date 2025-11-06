cmake_minimum_required(VERSION 3.26)
project(lab1 CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(varianta5 "lab 1/Varianta 5 .cpp"
        "lab 1/varianta 9.cpp"
        "lab 2/17.cpp"
        "lab 2/15.cpp"
        "lab 2/13.cpp")
add_executable(varianta6 "lab 1/Varianta 6 .cpp")

# Alias: rulează 'untitled' dar construiește varianta6
add_executable(untitled ALIAS varianta6)

# opțional: pune executabilele în cmake-build-*/bin
set_target_properties(varianta5 varianta6 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
