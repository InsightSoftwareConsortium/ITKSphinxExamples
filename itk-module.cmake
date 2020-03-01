set(DOCUMENTATION "This module builds the examples found at https://github.com/InsightSoftwareConsortium/ITKExamples")

itk_module(SphinxExamples
  DEPENDS
    ITKCommon
  DESCRIPTION
    "${DOCUMENTATION}"
  EXCLUDE_FROM_DEFAULT
)
