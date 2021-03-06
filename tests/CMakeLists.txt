project(arango-validation-tests)

set(test-files 
    "small-sample"
)

#build one executable
set(test_sources)
foreach(test_name IN LISTS test-files) # <- DO NOT EXPAND LIST
    list(APPEND test_sources "${test_name}.cpp")
endforeach()

find_package(Filesystem REQUIRED Final Experimental)

set(test_target "test-arango-validation")
add_executable("${test_target}" gtest.cpp ${test_sources})
target_include_directories("${test_target}" SYSTEM PRIVATE ${gtest_SOURCE_DIR}/include)
target_compile_definitions("${test_target}" PRIVATE
    "ARANGO_VALIDATION_TEST_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\""
)

set(validation_lib arango::validation)
if(ARANGO_VALIDATION_BUILD_SHARED)
    set(validation_lib arango-validation-shared)
endif()
target_link_libraries("${test_target}" PRIVATE
    ${validation_lib}    
    gtest_main gtest
    std::filesystem

)
target_compile_definitions("${test_target}" PRIVATE
    FS_HEADER=<${CXX_FILESYSTEM_HEADER}>
    FS_NAMESPACE=${CXX_FILESYSTEM_NAMESPACE}
)

add_test(NAME "${test_target}_run" COMMAND $<TARGET_FILE:${test_target}>)
set_target_properties (${test_target} PROPERTIES FOLDER tests/${test_target})
