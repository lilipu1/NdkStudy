cmake_minimum_required(VERSION 3.4.1)

add_library(
        jni-lib

        SHARED

        src/main/cpp/FirstCFile.cpp
)


#[[find_library(log-lib
        log)]]


target_link_libraries(jni-lib
        android
        log)