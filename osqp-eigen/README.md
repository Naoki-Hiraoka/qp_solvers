# osqp-eigen

This package is deprecated because https://github.com/robotology/osqp-eigen/tree/v0.7.0 supports catkin workspaces.

```cmake
find_package(OsqpEigen REQUIRED)
catkin_package(
  DEPENDS OsqpEigen
)
target_link_libraries(${PROJECT_NAME} OsqpEigen::OsqpEigen)
```

注意: `target_link_libraries(${PROJECT_NAME} OsqpEigen::OsqpEigen)`とすると、-isystemでこのワークスペースのdevel/includeがg++の引数に渡されるのだが、-isystemは優先順位末尾に入ってしまう. `include_directories($<TARGET_PROPERTY:OsqpEigen::OsqpEigen,INTERFACE_INCLUDE_DIRECTORIES>)` `target_link_libraries(${PROJECT_NAME} $<TARGET_PROPERTY:OsqpEigen::OsqpEigen,INTERFACE_LINK_LIBRARIES>)` のようにすると大丈夫?