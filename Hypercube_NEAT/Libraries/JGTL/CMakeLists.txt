Project(JGTL)


INCLUDE_DIRECTORIES(
	include
)

ADD_EXECUTABLE(
	CircularBufferExample

	examples/CircularBuffer.cpp
)

SET_TARGET_PROPERTIES(CircularBufferExample PROPERTIES DEBUG_POSTFIX _d)

ADD_EXECUTABLE(
	PoolMapExample

	examples/PoolMap.cpp
)

SET_TARGET_PROPERTIES(PoolMapExample PROPERTIES DEBUG_POSTFIX _d)

ADD_EXECUTABLE(
	VariantExample

	examples/Variant.cpp
)

SET_TARGET_PROPERTIES(VariantExample PROPERTIES DEBUG_POSTFIX _d)

ADD_EXECUTABLE(
	QuickProfExample

	examples/QuickProf.cpp
)

SET_TARGET_PROPERTIES(QuickProfExample PROPERTIES DEBUG_POSTFIX _d)

ADD_EXECUTABLE(
	UnitsExample

	examples/Units.cpp
)

SET_TARGET_PROPERTIES(UnitsExample PROPERTIES DEBUG_POSTFIX _d)

ADD_EXECUTABLE(
	MapTests

	tests/MapTests.cpp
)

SET_TARGET_PROPERTIES(MapTests PROPERTIES DEBUG_POSTFIX _d)

ADD_EXECUTABLE(
	VariantTests

	tests/VariantTests.cpp
)

SET_TARGET_PROPERTIES(VariantTests PROPERTIES DEBUG_POSTFIX _d)


