cmake_minimum_required(VERSION 3.0.2)
project(qpswifteigen)

add_compile_options(-std=c++11)
set(CMAKE_BUILD_TYPE Release)

find_package(catkin REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(EIGEN eigen3>=3.2.7)
find_package(qpSWIFT REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES qpswifteigen
#  CATKIN_DEPENDS other_catkin_pkg
  DEPENDS EIGEN
)

add_library(qpswifteigen SHARED src/qpswifteigen.cpp)
target_link_libraries(qpswifteigen PUBLIC
  qpSWIFT::qpSWIFT-shared
  ${EIGEN_LIBRARIES}
  ${catkin_LIBRARIES})
target_include_directories(qpswifteigen PUBLIC
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN_INCLUDE_DIRS}
  )

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
  )

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  )
