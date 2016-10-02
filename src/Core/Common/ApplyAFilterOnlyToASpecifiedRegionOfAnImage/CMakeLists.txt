cmake_minimum_required( VERSION 2.8.6 )

project( ApplyAFilterOnlyToASpecifiedRegionOfAnImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplyAFilterOnlyToASpecifiedRegionOfAnImage Code.cxx Code.py )
target_link_libraries( ApplyAFilterOnlyToASpecifiedRegionOfAnImage ${ITK_LIBRARIES} )

install( TARGETS ApplyAFilterOnlyToASpecifiedRegionOfAnImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/ApplyAFilterOnlyToASpecifiedRegionOfAnImage
  COMPONENT Code
)

enable_testing()
add_test( NAME ApplyAFilterOnlyToASpecifiedRegionOfAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyAFilterOnlyToASpecifiedRegionOfAnImage )

if(ITK_WRAP_PYTHON)
  add_test(NAME ApplyAFilterOnlyToASpecifiedRegionOfAnImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()
