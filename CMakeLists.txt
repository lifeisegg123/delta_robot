cmake_minimum_required(VERSION 3.0.0)
project(deltaRB VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Qt5 5.7.0 REQUIRED COMPONENTS
Widgets Core Gui Sql PrintSupport
)


qt5_wrap_cpp(moc_sources include/DeltaUi.h)
qt5_wrap_ui(uic_sources ui/delta.ui)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(delta src/deltaServo.cpp src/face_detection.cpp src/empy.cpp src/DeltaUi ${moc_sources} ${uic_sources})
target_link_libraries(delta Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(deltaRB main.cpp )
target_link_libraries(deltaRB delta ${OpenCV_LIBS} Qt5::Core Qt5::Gui Qt5::Widgets ${PYTHON_LIBRARIES})

add_executable(visiontst vision_test.cpp )
target_link_libraries(visiontst ${OpenCV_LIBS})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
