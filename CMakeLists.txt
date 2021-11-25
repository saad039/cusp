cmake_minimum_required(VERSION 3.18.1)

project(cusp VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory(json)
add_subdirectory(ordered-map)
add_subdirectory(spdlog)

include_directories(include)

file(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(cusp ${SRC_FILES})

target_precompile_headers(cusp
  PRIVATE
    <unordered_map>
    <iostream>
    <string>
    <sstream>
    <fstream>
    <vector>
    <map>
    <memory>
    <functional>
    <chrono>
    <algorithm>
    <filesystem>
    <stdexcept>
    <regex>
    [["spdlog/spdlog.h"]]
    [["spdlog/sinks/basic_file_sink.h"]]
    [["spdlog/sinks/stdout_color_sinks.h"]]
    [["util.h"]]
)

target_link_libraries(spdlog PRIVATE pthread)

target_link_libraries(cusp 
                      PRIVATE spdlog  
                      PRIVATE ordered_map 
                      PRIVATE nlohmann_json)