set(Core_MODULES
  Common
  QuadEdgeMesh
  Mesh
  TestKernel
  Transform
  ImageFunction
  ImageAdaptors
  SpatialObjects
)

foreach(_module ${Core_MODULES})
  add_subdirectory_if_module_enabled(${_module})
  add_module_archives(${_module})
endforeach()
