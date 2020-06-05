cmake_minimum_required(VERSION 3.0.0)
project(deltaRB VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(delta src/deltaServo.cpp src/face_detection.cpp src/empy.cpp)

add_executable(deltaRB main.cpp )
target_link_libraries(deltaRB delta ${OpenCV_LIBS} ${PYTHON_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
