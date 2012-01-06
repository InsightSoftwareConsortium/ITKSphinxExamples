find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )
# For comparing example outputs to their regression baseline's.
add_executable( ImageCompare ImageCompare.cxx )
target_link_libraries( ImageCompare ${ITK_LIBRARIES} )

# Creates a test that compares the output image of an example to its baseline
# image.  The first argument is the example name.  It is assumed that the
# corresponding test is ${example_name}Test.  The second argument is the
# baseline file prefix.  It expected that the baseline image file will live in
# the source tree at ${example_name}/${baseline_prefix}Baseline.ext.md5 and the
# output of the example to compare against will be placed in the binary tree at
# ${example_name}/${baseline_prefix}.ext.
function( compare_to_baseline example_name baseline_prefix )
  file( GLOB baseline_image ${CMAKE_CURRENT_SOURCE_DIR}/${example_name}/${baseline_prefix}Baseline.* )
  string( REPLACE .md5 "" baseline_image "${baseline_image}" )
  get_filename_component( baseline_image_file "${baseline_image}" NAME )
  set( baseline_image "${CMAKE_CURRENT_BINARY_DIR}/${example_name}/${baseline_image_file}" )
  message( " Baseline ${baseline_image}" )
  string( REPLACE Baseline "" test_image "${baseline_image}" )
  add_test( ${example_name}Test${baseline_prefix}BaselineComparison
    "${ITK_EXAMPLES_BINARY_DIR}/src/Examples/ImageCompare" "${test_image}" "${baseline_image}" )
  set_tests_properties( ${example_name}Test${baseline_prefix}BaselineComparison
    PROPERTIES DEPENDS ${example_name}Test )
endfunction()

add_subdirectory( Filtering )
