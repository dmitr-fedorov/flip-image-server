cmake_minimum_required(VERSION 3.10)

project(Server)

find_package(OpenCV 4.2 REQUIRED)

find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON)

add_executable(Server main.cpp)

target_link_libraries(Server PUBLIC
  ${OpenCV_LIBS}
  Poco::Foundation
  Poco::Util
  Poco::Net 
  Poco::XML
  Poco::JSON
)
