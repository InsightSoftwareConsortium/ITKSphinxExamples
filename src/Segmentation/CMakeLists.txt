set(Segmentation_MODULES
  Classifiers
  CMakeLists.txt
  ConnectedComponents
  index.rst
  KLMRegionGrowing
  LabelVoting
  LevelSets
  RegionGrowing
  Voronoi
  Watersheds
)

set(QUICKVIEW_MODULES KLMRegionGrowing)

foreach(_module ${Segmentation_MODULES})
  if(ENABLE_QUICKVIEW OR NOT (${_module} IN_LIST QUICKVIEW_MODULES))
    add_subdirectory_if_module_enabled(${_module})
  endif()
  add_module_archives(${_module})
endforeach()
