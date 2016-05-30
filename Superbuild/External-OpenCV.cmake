#---------------------------------------------------------------------------
# Get and build OpenCV

if( NOT OpenCV_TAG )
  set( OpenCV_TAG "3.1.0" )
endif()

ExternalProject_Add(OpenCV
  GIT_REPOSITORY "${git_protocol}://github.com/Itseez/opencv.git"
  GIT_TAG "${OpenCV_TAG}"
  SOURCE_DIR opencv
  BINARY_DIR opencv-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    ${ep_common_args}
    -DBUILD_DOCS:BOOL=FALSE
    -DBUILD_EXAMPLES:BOOL=FALSE
    -DBUILD_TESTS:BOOL=FALSE
    -DBUILD_SHARED_LIBS:BOOL=TRUE
    -DWITH_CUDA:BOOL=FALSE
    -DWITH_FFMPEG:BOOL=FALSE
    -DBUILD_PERF_TESTS:BOOL=FALSE
  INSTALL_COMMAND ""
)

set(OpenCV_DIR ${CMAKE_BINARY_DIR}/opencv-build)
