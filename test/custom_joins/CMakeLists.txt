# if(NOT CLANG_TIDY)
#   add_subdirectory(adbc)
# endif()
# add_subdirectory(capi)
# add_subdirectory(udf_function)

set(TEST_CUSTOM_JOIN_OBJECTS
    test_custom_join.cpp
    )

# if(NOT WIN32)
#   set(TEST_CUSTOM_API_OBJECTS ${TEST_CUSTOM_API_OBJECTS} test_custom_read_only.cpp)
# endif()

# if(DUCKDB_EXTENSION_TPCH_SHOULD_LINK)
#   include_directories(../../extension/tpch/include)
#   set(TEST_CUSTOM_API_OBJECTS ${TEST_CUSTOM_API_OBJECTS} test_tpch_with_relations.cpp
#                        serialized_plans/test_plan_serialization_bwc.cpp)
# endif()

add_library_unity(test_custom_join OBJECT ${TEST_CUSTOM_JOIN_OBJECTS})
set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:test_custom_join>
    PARENT_SCOPE)
