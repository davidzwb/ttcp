cmake_minimum_required(VERSION 2.8)

project(ttpc)
#add_executable(${PROJECT_NAME} "main.cpp")
file(GLOB server_sources *.cpp *.h server/*.cpp)
add_executable(server ${server_sources})

target_compile_options(server PUBLIC -std=c++11 -Wall -Wfloat-conversion)

file(GLOB client_sources *.cpp *.h client/*.cpp)
add_executable(client ${client_sources})

target_compile_options(client PUBLIC -std=c++11 -Wall -Wfloat-conversion)

file(GLOB ttcp_server_sources *.cpp *.h ttcp/server/*.cpp)
add_executable(ttcp-server ${ttcp_server_sources})

target_compile_options(ttcp-server PUBLIC -std=c++11 -Wall -Wfloat-conversion)

file(GLOB ttcp_client_sources *.cpp *.h ttcp/client/*.cpp)
add_executable(ttcp-client ${ttcp_client_sources})

target_compile_options(ttcp-client PUBLIC -std=c++11 -Wall -Wfloat-conversion)
