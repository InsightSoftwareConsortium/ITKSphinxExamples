get_filename_component(_ITKExternalData_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(${_ITKExternalData_DIR}/ExternalData.cmake)

if(NOT ExternalData_OBJECT_STORES)
  # Use ExternalData_OBJECT_STORES from environment as default.
  set(ExternalData_OBJECT_STORES_DEFAULT "")
  if(DEFINED "ENV{ExternalData_OBJECT_STORES}")
    file(TO_CMAKE_PATH "$ENV{ExternalData_OBJECT_STORES}" ExternalData_OBJECT_STORES_DEFAULT)
  endif()
endif()

set(ExternalData_OBJECT_STORES "${ExternalData_OBJECT_STORES_DEFAULT}" CACHE STRING
  "Semicolon-separated list of local directories holding data objects in the layout %(algo)/%(hash).")
mark_as_advanced(ExternalData_OBJECT_STORES)
if(NOT ExternalData_OBJECT_STORES)
  set(ExternalData_OBJECT_STORES "${CMAKE_BINARY_DIR}/ExternalData/Objects")
  file(MAKE_DIRECTORY "${ExternalData_OBJECT_STORES}")
endif()
list(APPEND ExternalData_OBJECT_STORES
  # Local data store populated by the ITK pre-commit hook
  "${CMAKE_SOURCE_DIR}/.ExternalData"
  )

set(ITK_SPHINX_EXAMPLES_DATA_RELEASED_ROOT_CID bafybeib6yijwyl52gkalx6griio2wsibowlrt3v5wmkkuqlnuvku64c3ra)

set(ExternalData_URL_ALGO_CID_lower cid)
set(ExternalData_URL_TEMPLATES "" CACHE STRING
  "Additional URL templates for the ExternalData CMake script to look for testing data. E.g.
file:///var/bigharddrive/%(algo)/%(hash)")
mark_as_advanced(ExternalData_URL_TEMPLATES)
if(NOT ITK_FORBID_DOWNLOADS)
  list(APPEND ExternalData_URL_TEMPLATES
    # Local IPFS gateway
    "http://127.0.0.1:8080/ipfs/%(hash)"

    # Data published on GitHub Pages (note: not complete due to file size
    # limit)
    "https://insightsoftwareconsortium.github.io/ITKTestingData/%(algo)/%(hash)"

    # Released data rsync'd to Kitware's Apache web server
    "https://itk.org/files/ExternalData/%(algo)/%(hash)"

    # Restricted gateway with released data
    "https://itk.mypinata.cloud/ipfs/${ITK_SPHINX_EXAMPLES_DATA_RELEASED_ROOT_CID}/Objects/CID/%(hash)"

    # New data on web3.storage
    "https://w3s.link/ipfs/%(hash)"

    # Released data on web3.storage
    "https://${ITK_SPHINX_EXAMPLES_DATA_RELEASED_ROOT_CID}.ipfs.w3s.link/Objects/CID/%(hash)"

    # Released data on estuary.tech
    "https://api.estuary.tech/gw/ipfs/${ITK_SPHINX_EXAMPLES_DATA_RELEASED_ROOT_CID}/Objects/CID/%(hash)"

    # Protocol Labs gateway
    "https://${ITK_SPHINX_EXAMPLES_DATA_RELEASED_ROOT_CID}.ipfs.dweb.link/Objects/CID/%(hash)"

    # Gateway for arbitrary new files, uploaded to web3.storage
    "https://dweb.link/ipfs/%(hash)"

    # Protocol Labs gateway
    "https://ipfs.io/ipfs/%(hash)"

    # Cloudflare gateway
    "https://cloudflare-ipfs.com/ipfs/%(hash)"

    # DataLad repository on gin.g-node.org
    "https://gin.g-node.org/InsightSoftwareConsortium/ITKSphinxExamplesData/raw/main/Objects/CID/%(hash)"
    )
endif()

# Tell ExternalData commands to transform raw files to content links.
set(ExternalData_LINK_CONTENT CID)

# Emscripten currently has difficulty reading symlinks.
if(EMSCRIPTEN)
  set(ExternalData_NO_SYMLINKS 1)
endif()

# Match series of the form <base>.<ext>, <base>.<n>.<ext> such that <base> may
# end in a (test) number that is not part of any series numbering.
set(ExternalData_SERIES_PARSE "()(\\.[^./]*)$")
set(ExternalData_SERIES_MATCH "(\\.[0-9]+)?")

# Sometimes we want to download very large files.
set(ExternalData_TIMEOUT_ABSOLUTE 900)
