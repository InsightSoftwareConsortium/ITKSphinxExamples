set(Bridge_MODULES
  VtkGlue
  NumPy
)

if(ENABLE_QUICKVIEW)
add_subdirectory_if_module_enabled(VtkGlue)
endif()

add_subdirectory_if_module_enabled( NumPy )

foreach(_module ${Bridge_MODULES})
  add_module_archives(${_module})
endforeach()
