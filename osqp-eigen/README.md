# osqp-eigen

```cmake
find_package(OsqpEigen REQUIRED)
catkin_package(
  DEPENDS OsqpEigen
)
target_link_libraries(${PROJECT_NAME} OsqpEigen::OsqpEigen)
```
