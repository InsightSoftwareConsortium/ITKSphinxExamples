if(ENABLE_QUICKVIEW)
add_subdirectory_if_module_enabled(VtkGlue)
endif()

add_subdirectory_if_module_enabled( NumPy )
