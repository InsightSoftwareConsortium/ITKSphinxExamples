cmake_minimum_required( VERSION 2.8.5 )

if( COMMAND CMAKE_POLICY )
  cmake_policy( SET CMP0003 NEW )
endif( COMMAND CMAKE_POLICY )

project( ITKExamples )

include( ${CMAKE_SOURCE_DIR}/Superbuild.cmake )
