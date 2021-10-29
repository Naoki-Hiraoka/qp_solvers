cmake_minimum_required(VERSION 3.16)
project(nasoq)

set(CMAKE_BUILD_TYPE Release)

find_package(catkin REQUIRED)

include(ExternalProject)

find_package(PkgConfig REQUIRED)
pkg_check_modules(EIGEN eigen3)

catkin_package(
  INCLUDE_DIRS include include/nasoq
  LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/nasoq-prefix/src/nasoq/lib/libnasoq.a ${CMAKE_CURRENT_BINARY_DIR}/nasoq-prefix/src/nasoq/lib/libmetis.a openblas lapacke gomp
  DEPENDS EIGEN
)

ExternalProject_Add(
  nasoq
  GIT_REPOSITORY https://github.com/sympiler/nasoq
  #GIT_TAG v0.1.0
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DNASOQ_BLAS_BACKEND=OpenBLAS -DEIGEN_ROOT=${EIGEN_INCLUDE_DIRS} #-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} #CMAKE_PREFIX_PATH=$MKLROOT:CMAKE_PREFIX_PATH -DCMAKE_FIND_PACKAGE_PREFER_CONFIG=True -DMKL_THREADING=intel_thread
  INSTALL_COMMAND sh -c "cp -r ${CMAKE_CURRENT_BINARY_DIR}/nasoq-prefix/src/nasoq/include/* ${PROJECT_SOURCE_DIR}/include" && sh -c "cp -r ${CMAKE_CURRENT_BINARY_DIR}/nasoq-prefix/src/nasoq/eigen_interface/include/* ${PROJECT_SOURCE_DIR}/include"
  )
