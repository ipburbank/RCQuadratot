Project(tinyxmldll)


ADD_DEFINITIONS(
-DTIXML_USE_STL
-D_USE_MATH_DEFINES
-DTINYXMLDLL_EXPORTS
)

INCLUDE_DIRECTORIES(../zlib/include)


ADD_LIBRARY(
	tinyxmldll 
	SHARED

	include/tinyxmldll.h

	src/tinyxmldll.cpp
	src/tinyxmlparserdll.cpp
	src/tinyxmlerrordll.cpp
)

#TARGET_LINK_LIBRARIES(
#	tinyxmldll
#
#	zlib
#)

SET_TARGET_PROPERTIES(tinyxmldll PROPERTIES DEBUG_POSTFIX _d)


