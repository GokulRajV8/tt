all: test

matrix.obj:
	cl -c matrix.c

vector.obj:
	cl -c vector.c

vector_transform_layer.obj:
	cl -c vector_transform_layer.c

vector_transform_block.obj:
	cl -c vector_transform_block.c

test.obj:
	cl -c test.c

test: matrix.obj vector.obj vector_transform_layer.obj vector_transform_block.obj test.obj
	link matrix.obj vector.obj vector_transform_layer.obj vector_transform_block.obj test.obj /out:build\test.exe
	del *.obj
