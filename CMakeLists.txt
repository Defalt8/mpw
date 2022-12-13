cmake_minimum_required( VERSION 3.4 )
project( MPW VERSION 0.5.17 DESCRIPTION "multi-platform windowing" )

set( BUILD_TESTS ON CACHE BOOL "" )

set( MPW_HEADER_FILES
	include/mpw/common
	include/mpw/enums
	include/mpw/events
	include/mpw/display
	include/mpw/window
	include/mpw/all
)

add_subdirectory( dep/dspp dep_dspp )

add_library( mpw INTERFACE )
target_include_directories( mpw INTERFACE include dep/dspp/include dep/glfl/include )
target_link_libraries( mpw INTERFACE dspp )
if( WIN32 )
	target_link_libraries( mpw INTERFACE user32 opengl32 )
else()
	target_link_libraries( mpw INTERFACE X11 GL )
endif()
install( FILES ${MPW_HEADER_FILES} DESTINATION include/mpw )

if( BUILD_TESTS 
	AND "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}"
)
	add_subdirectory( test mpw_tests )
endif()
