Project(zlib)


ADD_DEFINITIONS(
-DZLIB_DLL
)

INCLUDE_DIRECTORIES(
	./
)

ADD_LIBRARY(
	zlib SHARED
	
	crc32.h
	deflate.h
	inffast.h
	inffixed.h
	inflate.h
	inftrees.h
	trees.h
	zconf.h
	zconf.in.h
	zlib.h
	zutil.h

	adler32.c
	compress.c
	crc32.c
	deflate.c
	gzio.c
	infback.c
	inffast.c
	inflate.c
	inftrees.c
	minigzip.c
	trees.c
	uncompr.c
	zutil.c
)
