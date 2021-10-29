cmake_minimum_required(VERSION 3.15) # qpSWIFTのCMakeLists.txtにはcmake_minimum_required(VERSION 3.5)と書いてあるが嘘である
project(qpSWIFT)

set(CMAKE_BUILD_TYPE Release)

include(ExternalProject)

ExternalProject_Add(
  qpSWIFT
  GIT_REPOSITORY https://github.com/qpSWIFT/qpSWIFT
  GIT_TAG main
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -DCMAKE_BUILD_TYPE=Release
  INSTALL_COMMAND echo "install"
  )

install(CODE "execute_process(COMMAND make install WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/qpSWIFT-prefix/src/qpSWIFT-build)")
