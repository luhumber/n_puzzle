# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/MonProjetQt_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/MonProjetQt_autogen.dir/ParseCache.txt"
  "MonProjetQt_autogen"
  )
endif()
