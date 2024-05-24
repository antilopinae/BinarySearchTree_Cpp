cmake_minimum_required(VERSION 3.27)
project(Lab4)

set(CMAKE_CXX_STANDARD 23)

set(APP_DOMAIN ./lib)

include_directories(${APP_DOMAIN})

set(
        SOURCE_FILES
        main.cpp
        Debugging.h
        Testing.h
        ${APP_DOMAIN}/BinarySearchTree.h
        ${APP_DOMAIN}/Exception.h
        ${APP_DOMAIN}/LinkedList.h
        ${APP_DOMAIN}/TypeObject.h
        ${APP_DOMAIN}/VectorList.h
        lib/BinarySearchTree.h
)

add_executable(Lab4 ${SOURCE_FILES})
