cmake_minimum_required(VERSION 3.0.2)
project(qpoases)

set(CMAKE_BUILD_TYPE Release)

include(ExternalProject)

find_package(catkin REQUIRED)

execute_process(COMMAND
  git config --global http.sslVerify false)
ExternalProject_Add(
  qpOASES
  GIT_REPOSITORY https://github.com/coin-or/qpOASES
  GIT_TAG releases/3.2.1
  PATCH_COMMAND sed -i -e "s/qpOASES\ STATIC/qpOASES\ SHARED/g" ./CMakeLists.txt # デフォルトでは.aファイルが生成されるが、.soファイルを生成したいため
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${CATKIN_DEVEL_PREFIX}
  #INSTALL_COMMAND echo "install"
  )

catkin_package(
 INCLUDE_DIRS ${CATKIN_DEVEL_PREFIX}/include
 LIBRARIES qpOASES
 )
