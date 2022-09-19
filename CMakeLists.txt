cmake_minimum_required(VERSION 3.10)

project(Server)

find_package(OpenCV REQUIRED COMPONENTS core imgcodecs)

find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON)

add_executable(Server
  ${CMAKE_SOURCE_DIR}/src/FlipJpegRequestHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/HttpServerApplication.cpp
  ${CMAKE_SOURCE_DIR}/src/main.cpp
)

target_include_directories(Server PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Server PRIVATE
  opencv_core
  opencv_imgcodecs
  Poco::Foundation
  Poco::Util
  Poco::Net 
  Poco::XML
  Poco::JSON
)
