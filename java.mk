%.class: %.java
	javac $<

java/%.class: java/%.java
	javac --source 8 --target 8 --boot-class-path . $<

OBJ = \
	c/decode.o \
	c/class_file.o \
	c/debug_class_file.o \
	c/malloc.o \
	c/execute.o \
	c/memory_allocator.o \
	c/class_resolver.o \
	c/hash_table.o \
	c/frame.o \
	c/printf.o \
	c/parse.o \
	c/unparse.o \
	c/native.o

MAIN_DREAMCAST_OBJ = \
	c/sh7091_scif.o \
	c/main_dreamcast.o

MAIN_HOSTED_OBJ = \
	c/file.o \
	c/main_hosted.o

PRINT_CLASS_OBJ = \
	c/file.o \
	c/print_class.o
