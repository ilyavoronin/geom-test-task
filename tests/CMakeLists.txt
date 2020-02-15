project(geom_test_task_tests)

add_executable(geom_test_task_tests_run testVec.cpp
              ../include/vec.h ../src/vec.cpp
              testCutBuilder.cpp
              ../include/CutBuilder.h ../src/CutBuilder.cpp)

target_link_libraries(geom_test_task_tests_run gtest gtest_main)