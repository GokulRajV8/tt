all: test

vector.obj:
	cl -c vector.c

matrix.obj:
	cl -c matrix.c

vector_transform_layer.obj:
	cl -c vector_transform_layer.c

vector_transform_block.obj:
	cl -c vector_transform_block.c

test.obj:
	cl -c test.c

test: vector.obj matrix.obj vector_transform_layer.obj vector_transform_block.obj test.obj
	link vector.obj matrix.obj vector_transform_layer.obj vector_transform_block.obj test.obj /out:build\test.exe
	del *.obj
