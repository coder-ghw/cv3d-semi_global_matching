add_custom_target(memcheck)
add_custom_target(check)

function(ADD_TEST_MODULE module_name test_file)
    add_executable(UnitTest-${module_name}
        ${test_file}
        ${PROJECT_SOURCE_DIR}/test/test_utils.cpp
    )
    target_include_directories(UnitTest-${module_name}
        PRIVATE ${PROJECT_SOURCE_DIR}/src
        PRIVATE ${PROJECT_SOURCE_DIR}/test
        PRIVATE ${PROJECT_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR})

    target_link_libraries(UnitTest-${module_name}
        gtest
        gtest_main
        pthread
        sgbm-static)

    target_compile_definitions(UnitTest-${module_name}
        PUBLIC -DTEST_TRACE_DIR=\"${CMAKE_BINARY_DIR}/debug_output/\"
    )

    add_test(NAME ${module_name} COMMAND UnitTest-${module_name})

    add_custom_target(${module_name}-memcheck
        COMMAND valgrind --tool=memcheck --leak-check=full ./UnitTest-${module_name}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/${module_name})

    add_custom_target(${module_name}-check
        COMMAND UnitTest-${module_name}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/${module_name})

    add_dependencies(memcheck ${module_name}-memcheck)
    add_dependencies(check ${module_name}-check)
endfunction()
