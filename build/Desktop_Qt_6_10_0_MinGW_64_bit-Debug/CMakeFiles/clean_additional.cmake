# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ZombieRising_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ZombieRising_autogen.dir\\ParseCache.txt"
  "ZombieRising_autogen"
  )
endif()
