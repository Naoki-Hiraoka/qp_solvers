cmake_minimum_required(VERSION 2.8.12)
project(proxsuite)

set(CMAKE_BUILD_TYPE Release)

find_package(catkin REQUIRED COMPONENTS
  )

include(ExternalProject)

execute_process(COMMAND
  git config --global http.sslVerify false)

ExternalProject_Add(
  proxsuite
  GIT_REPOSITORY https://github.com/Simple-Robotics/proxsuite
  GIT_TAG v0.7.2 
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF -DBUILD_WITH_VECTORIZATION_SUPPORT=OFF
  )
