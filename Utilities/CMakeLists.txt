configure_file(${ITKSphinxExamples_SOURCE_DIR}/Utilities/CodeSwarm.sh.in
  ${ITKSphinxExamples_BINARY_DIR}/Utilities/CodeSwarm.sh
  @ONLY
)

if(BUILD_DOCUMENTATION)
  file(COPY ${ITKSphinxExamples_SOURCE_DIR}/Utilities/SphinxExtensions/breathe/documentation/source/_static/breathe.css
    DESTINATION ${ITKSphinxExamples_BINARY_DIR}/html/_static
    )
endif()
