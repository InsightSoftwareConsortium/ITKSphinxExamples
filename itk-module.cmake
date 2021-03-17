set(DOCUMENTATION "This module builds the examples found at https://github.com/InsightSoftwareConsortium/ITKSphinxExamples")

itk_module(SphinxExamples
  DEPENDS
    ITKCommon
  DESCRIPTION
    "${DOCUMENTATION}"
  EXCLUDE_FROM_DEFAULT
)
