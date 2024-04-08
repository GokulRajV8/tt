all: test

matrix.obj:
	cl -c matrix.c

vector.obj:
	cl -c vector.c

test.obj:
	cl -c test.c

test: matrix.obj vector.obj test.obj
	cl /Fe: build\test.exe matrix.obj vector.obj test.obj
	del *.obj
