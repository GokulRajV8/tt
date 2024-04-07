all: test

matrix.obj:
	cl -c matrix.c

test.obj:
	cl -c test.c

test: matrix.obj test.obj
	cl /Fe: build\test.exe matrix.obj test.obj
	del *.obj
