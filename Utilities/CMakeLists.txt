configure_file( ${CMAKE_SOURCE_DIR}/Utilities/CreateNewExample.py.in
  ${CMAKE_BINARY_DIR}/Utilities/CreateNewExample.py
  @ONLY
  )

configure_file( ${CMAKE_SOURCE_DIR}/Utilities/ArchiveBinaryData.py.in
  ${CMAKE_BINARY_DIR}/Utilities/ArchiveBinaryData.py
  @ONLY
  )

configure_file( ${CMAKE_SOURCE_DIR}/Utilities/UploadBinaryData.py.in
  ${CMAKE_BINARY_DIR}/Utilities/UploadBinaryData.py
  @ONLY
  )

configure_file( ${ITKExamples_SOURCE_DIR}/Utilities/CodeSwarm.sh.in
  ${ITKExamples_BINARY_DIR}/Utilities/CodeSwarm.sh
  @ONLY
)

if( BUILD_DOCUMENTATION )
  file(COPY ${ITKExamples_SOURCE_DIR}/Utilities/SphinxExtensions/breathe/documentation/source/_static/breathe.css
    DESTINATION ${ITKExamples_BINARY_DIR}/html/_static
    )
endif()
