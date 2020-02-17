cmake_minimum_required(VERSION 3.12)
project(arangodb-validation VERSION 0.0.1 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## OPTIONS
option(ARANGO_VALIDATION_TESTS "build tests" ON)

## general setup and includes
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON) # XCode / VS folders

set(ARANGO_VALIDATION_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include(ext_cmake_setup)
include(ext_cmake_install)

add_subdirectory(external_libs/velocypack EXCLUDE_FROM_ALL)
add_subdirectory(external_libs/googletest EXCLUDE_FROM_ALL)

set(FORCE_COLORED_OUTPUT ON)
ext_colored_compiler_ouput()


if(LINUX)
elseif(MSVC)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${EXT_OUTDIR}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${EXT_OUTDIR}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXT_OUTDIR}")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
elseif(APPLE)
else()
endif()

# include build dir to find version.hpp
set(CMAKE_INCLUDE_CURRENT_DIR ON)

### define header only lib
add_library(arango-validation STATIC
    src/validation.cpp
)

target_link_libraries(arango-validation PUBLIC
   velocypack 
)

target_include_directories(arango-validation PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)
target_compile_features(arango-validation PUBLIC cxx_std_17)
target_compile_options(arango-validation PRIVATE
    $<$<AND:$<CONFIG:Debug>,$<BOOL:ARANGO_VALIDATION_WARNINGS>>:${ext_stone-warnings}>
)
target_compile_definitions(arango-validation PUBLIC
)

# set up folder structure for XCode and VisualStudio
#set_target_properties (arango-validation PROPERTIES FOLDER libext) #not for interface libraries
#source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${arango-validation-header} ${arango-validation-source})

add_library(arango::validation ALIAS arango-validation)

## testing
if(ARANGO_VALIDATION_TESTS)
    ext_log("arango-validation tests enabled")
    include(CTest)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    ext_add_test_subdirectory("google" tests)
else()
    ext_log("arango-validation tests disabled")
endif()

## velocypack requires install routine to make this work
# ## installation
# if(COMMAND ext_install)
#     set_target_properties(arango-validation PROPERTIES EXPORT_NAME validation)
# 
#     ext_install(arango-validation include/validation)
# 
#     install(TARGETS arango-validation
#         EXPORT arango-validation-targets
#         DESTINATION ${CMAKE_INSTALL_PREFIX}
#     )
# 	install(
#         EXPORT arango-validation-targets
# 		FILE arango-validation-config.cmake
#         NAMESPACE arango::
#         DESTINATION ${CMAKE_INSTALL_PREFIX}
#     )
# endif()
