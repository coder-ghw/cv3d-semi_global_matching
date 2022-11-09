set(TEST_MODULE test_sgbm)
ADD_TEST_MODULE(${TEST_MODULE}
  ${CMAKE_CURRENT_SOURCE_DIR}/test_sgbm.cpp)

target_compile_definitions(UnitTest-${TEST_MODULE}
  PUBLIC -DTEST_SGBM_FILE_IN_L=\"${PROJECT_SOURCE_DIR}/test/data/Reindeer/view1.png\"
  PUBLIC -DTEST_SGBM_FILE_IN_R=\"${PROJECT_SOURCE_DIR}/test/data/Reindeer/view5.png\")
