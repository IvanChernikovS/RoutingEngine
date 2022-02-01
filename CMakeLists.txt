cmake_minimum_required(VERSION 3.19)
project(CommunicationHub)

set(CMAKE_CXX_STANDARD 14)

find_package (Threads REQUIRED)
find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(CommunicationHub SocketConnection.cpp
        Message.cpp
        ConfigParser.cpp
        main.cpp)

target_link_libraries(CommunicationHub
        ${CMAKE_THREAD_LIBS_INIT}
        ${Protobuf_LIBRARIES}
        jsoncpp
        )