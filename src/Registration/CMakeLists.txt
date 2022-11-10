set(Numerics_MODULES
  Common
  Metricsv4
)

foreach(_module ${Numerics_MODULES})
  add_subdirectory_if_module_enabled(${_module})
  add_module_archives(${_module})
endforeach()
