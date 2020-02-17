project(arango-validation-tests)

set(test-files 
    "small-sample"
)

#build one executable
set(test_sources)
foreach(test_name IN LISTS test-files) # <- DO NOT EXPAND LIST
    list(APPEND test_sources "${test_name}.cpp")
endforeach()

set(test_target "test-arango-validation")
add_executable("${test_target}" gtest.cpp ${test_sources})
target_include_directories("${test_target}" SYSTEM PRIVATE ${gtest_SOURCE_DIR}/include)
target_link_libraries("${test_target}"
    gtest_main gtest
    arango::validation
)
add_test(NAME "${test_target}_run" COMMAND $<TARGET_FILE:${test_target}>)
set_target_properties (${test_target} PROPERTIES FOLDER tests/${test_target})
