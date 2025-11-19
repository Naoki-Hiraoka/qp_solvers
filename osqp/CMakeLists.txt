cmake_minimum_required(VERSION 2.8.12)
project(osqp)

set(CMAKE_BUILD_TYPE Release)

include(ExternalProject)

execute_process(COMMAND
  git config --global http.sslVerify false)

# CTRLC: default=ON. 最適化計算中にctrl-cに対するsignal handlerが設定される. マルチスレッドでosqpを使う場合に、最適化計算終了後にsignal handlerがもとに戻らない場合があるため無効化する
#   https://github.com/osqp/osqp/issues/757
#   v1.0.0以降はオプションの名前がOSQP_ENABLE_INTERRUPTへと変更される
ExternalProject_Add(
  osqp
  GIT_REPOSITORY https://github.com/oxfordcontrol/osqp
  GIT_TAG v0.6.2
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -DCMAKE_BUILD_TYPE=Release -DCTRLC=OFF
  INSTALL_COMMAND echo "install"
  )

install(CODE "execute_process(COMMAND make install WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/osqp-prefix/src/osqp-build)")
