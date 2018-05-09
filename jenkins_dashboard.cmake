# ITKExamples Jenkins Dashboard Script
#
#
# Corresponding Jenkins build shell commands are:
#
#  cd $WORKSPACE
#  export PLATFORM=Linux
#  export COMPILER=GCC-7.3.0
#  export BUILD_DESCRIPTION=-PR
#  rm -rf ITKExamples-dashboard
#  git clone -b dashboard --single-branch #  https://github.com/InsightSoftwareConsortium/ITKExamples.git ITKExamples-dashboard
#  ctest -S ITKExamples-dashboard/jenkins_dashboard.cmake -VV
#
#
# Corresponding Jenkins Windows build batch commands are:
#
#  cd %WORKSPACE%
#  call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\amd64\vcvars64.bat"
#  rd /s /q ITKExamples-dashboard
#  git clone -b dashboard --single-branch
#  https://github.com/InsightSoftwareConsortium/ITKExamples.git ITKExamples-dashboard
#  ctest -S ITKExamples-dashboard/jenkins_dashboard.cmake -VV

file(TO_CMAKE_PATH "$ENV{WORKSPACE}" workspace)
set(CTEST_DASHBOARD_ROOT "${workspace}")
# In the Jenkins Item
#   Source Code Management
#   --> Git Repositories
#       --> Additional Behaviors
#           --> Checkout to a sub-directory
# Set "Local subdirectory for repo" to ITKExamples-src
set(dashboard_source_name "ITKExamples")
set(dashboard_binary_name "ITKEx-bld")
set(CTEST_SITE "$ENV{NODE_NAME}")
set(dashboard_do_cache 1)
set(CTEST_CMAKE_GENERATOR "Ninja")
set(dashboard_superbuild 1)
set(CTEST_BUILD_CONFIGURATION MinSizeRel)

# The "platform" and "compiler" environmental variables should be set in the
# Jenkins item build configuration.
# An optional "build_description" variable may be set.
if(NOT CTEST_BUILD_NAME)
  set(CTEST_BUILD_NAME "$ENV{PLATFORM}-$ENV{COMPILER}$ENV{BUILD_DESCRIPTION}")
endif()
if(NOT CTEST_SITE)
  set(CTEST_SITE "$ENV{NODE_NAME}")
endif()
string(TIMESTAMP build_date "%Y-%m-%d")
message("CDash Build Identifier: ${build_date} ${CTEST_BUILD_NAME}")
message("CTEST_SITE = ${CTEST_SITE}")
# If using a Jenkins parameterized build with CTestTestModel Choice Parameter
if(NOT DEFINED dashboard_model)
  set(model_parameter "$ENV{CTestTestModel}")
  if(model_parameter)
    set(dashboard_model "${model_parameter}")
  endif()
endif()
message(STATUS "Including itkexamples_common.cmake...")
include(${CTEST_SCRIPT_DIRECTORY}/itkexamples_common.cmake)
