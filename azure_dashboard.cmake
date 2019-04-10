# ITKExamples Azure DevOps Pipeline Dashboard Script

file(TO_CMAKE_PATH "$ENV{AGENT_BUILDDIRECTORY}" workspace)
set(CTEST_DASHBOARD_ROOT "${workspace}")

file(RELATIVE_PATH dashboard_source_name "${workspace}" "$ENV{BUILD_SOURCESDIRECTORY}")
# Short for Windows path length limitations
set(dashboard_binary_name "ITKEx-bld")
set(CTEST_SITE "Azure.$ENV{AGENT_MACHINENAME}")
set(CTEST_CMAKE_GENERATOR "Ninja")
set(dashboard_do_cache 1)
set(dashboard_superbuild 1)
set(CTEST_BUILD_CONFIGURATION MinSizeRel)
# We are building a pull request that has already been checked out.
#set(dashboard_no_update 1)
set(CTEST_UPDATE_VERSION_ONLY 1)
set(CTEST_CHECKOUT_COMMAND)
set(dashboard_no_update 1)

if(NOT CTEST_BUILD_NAME)
  if(DEFINED ENV{SYSTEM_PULLREQUEST_SOURCEBRANCH})
    set(branch "-$ENV{SYSTEM_PULLREQUEST_SOURCEBRANCH}")
  else()
    set(branch "-master")
    set(dashboard_model Nightly)
  endif()
  if(DEFINED ENV{SYSTEM_PULLREQUEST_PULLREQUESTNUMBER})
    set(pr "-PR$ENV{SYSTEM_PULLREQUEST_PULLREQUESTNUMBER}")
  else()
    set(pr "")
  endif()
  set(CTEST_BUILD_NAME
    "$ENV{AGENT_OS}-Build$ENV{BUILD_BUILDID}${pr}${branch}-Examples")
endif()

string(TIMESTAMP build_date "%Y-%m-%d")
message("CDash Build Identifier: ${build_date} ${CTEST_BUILD_NAME}")
message("CTEST_SITE = ${CTEST_SITE}")
message(STATUS "Including itkexamples_common.cmake...")
include(${CTEST_SCRIPT_DIRECTORY}/itkexamples_common.cmake)
