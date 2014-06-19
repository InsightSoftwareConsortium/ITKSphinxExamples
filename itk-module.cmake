set( DOCUMENTATION "This module builds the examples found at http://itk.org/ITKExamples" )

itk_module(SphinxExamples
  DEPENDS
    ITKCommon
    EXCLUDE_FROM_DEFAULT
  DESCRIPTION
    "${DOCUMENTATION}"
  )
