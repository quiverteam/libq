#
# Project for libq
# 
project(libq C CXX)

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/ *.c *.cc *.cpp *.h *.hh *.hpp *.hxx)

add_library(libq SHARED ${SRCS})

if(DEFINED LINUX_BUILD)
	target_link_libraries(libq -lm -lc -lpthread -ldl)
endif(DEFINED LINUX_BUILD)

if(DEFINED WINDOWS_BUILD)
	#target_link_libraries(libq)
endif(DEFINED WINDOWS_BUILD)

set_target_properties(libq PROPERTIES PREFIX "")
