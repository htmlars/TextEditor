# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\schlichting_texteditor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\schlichting_texteditor_autogen.dir\\ParseCache.txt"
  "schlichting_texteditor_autogen"
  )
endif()
