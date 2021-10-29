cmake_minimum_required(VERSION 3.16)
project(nasoq)

set(CMAKE_BUILD_TYPE Release)

find_package(catkin REQUIRED)

include(ExternalProject)

find_package(PkgConfig REQUIRED)
pkg_check_modules(EIGEN eigen3)

catkin_package(
  INCLUDE_DIRS include include/nasoq
  #iomp5の方がgompよりも10倍くらい速い. nasoqのCMakeLists.txtに行って、target_link_libraryの部分にiomp5を書き足してbuild/nasoq/nasoq-prefix/src/nasoq-build$ ./NASOQ-BIN -i ../nasoq/data/matt_qp1.yml とすると違いがよく分かる
  LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/nasoq-prefix/src/nasoq/lib/libnasoq.a ${CMAKE_CURRENT_BINARY_DIR}/nasoq-prefix/src/nasoq/lib/libmetis.a openblas lapacke iomp5
  DEPENDS EIGEN
  )

ExternalProject_Add(
  nasoq
  GIT_REPOSITORY https://github.com/sympiler/nasoq
  #GIT_TAG v0.1.0
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DNASOQ_BLAS_BACKEND=OpenBLAS -DEIGEN_ROOT=${EIGEN_INCLUDE_DIRS} -DCMAKE_POSITION_INDEPENDENT_CODE=ON
  BUILD_COMMAND cmake --build . --config Release
  INSTALL_COMMAND sh -c "cp -r ${CMAKE_CURRENT_BINARY_DIR}/nasoq-prefix/src/nasoq/include/* ${PROJECT_SOURCE_DIR}/include" && sh -c "cp -r ${CMAKE_CURRENT_BINARY_DIR}/nasoq-prefix/src/nasoq/eigen_interface/include/* ${PROJECT_SOURCE_DIR}/include"
  )

# https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html
# からMKLを入れて、
# source /opt/intel/oneapi/compiler/latest/env/vars.sh
# source /opt/intel/oneapi/mkl/latest/env/vars.sh
# して、
# CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DEIGEN_ROOT=${EIGEN_INCLUDE_DIRS} -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DINTEL_COMPILER_DIR=$ENV{CMPLR_ROOT}/linux/compiler -DINTEL_MKL_DIR=$ENV{MKLROOT} -DINTEL_OMP_DIR=ENV{$CMPLR_ROOT}/linux/compiler
# とし、
# find_package(MKL HINTS $ENV{MKLROOT} REQUIRED)
# target_link_libraries(... MKL::MKL)
# とリンクして、
# export LD_PRELOAD=/opt/intel/oneapi/mkl/2021.4.0/lib/intel64/libmkl_def.so.1:/opt/intel/oneapi/mkl/2021.4.0/lib/intel64/libmkl_avx2.so.1:/opt/intel/oneapi/mkl/2021.4.0/lib/intel64/libmkl_core.so.1:/opt/intel/oneapi/mkl/2021.4.0/lib/intel64/libmkl_intel_lp64.so.1:/opt/intel/oneapi/mkl/2021.4.0/lib/intel64/libmkl_intel_thread.so.1:/opt/intel/oneapi/compiler/2021.4.0/linux/compiler/lib/intel64_lin/libiomp5.so
# とすると、OpenBLASの代わりにMKLが使える. 10倍くらい速い. が、それでもOSQPより500倍くらい遅い
