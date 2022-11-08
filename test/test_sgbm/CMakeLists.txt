set(TEST_MODULE test_image_process)
ADD_TEST_MODULE(${TEST_MODULE}
	${CMAKE_CURRENT_SOURCE_DIR}/test_sgbm.cpp)