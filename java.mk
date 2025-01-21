#%.class: %.java
#	javac $<

%.class: %.java
	cd ./classes ; \
	javac -Xlint:-options -source 8 -target 8 --boot-class-path . $(<:classes/%=%)

OBJ = \
	c/backtrace.o \
	c/class_file.o \
	c/class_resolver.o \
	c/debug.o \
	c/debug_class_file.o \
	c/decode.o \
	c/execute.o \
	c/fatal.o \
	c/find_attribute.o \
	c/vm.o \
	c/gc.o \
	c/hash_table.o \
	c/malloc.o \
	c/memory_allocator.o \
	c/native.o \
	c/native/class.o \
	c/native/loader.o \
	c/native/math.o \
	c/native/memory.o \
	c/native/object.o \
	c/native/printstream.o \
	c/native/runtime.o \
	c/native/system.o \
	c/parse.o \
	c/parse_type.o \
	c/printf.o \
	c/unparse.o \
	c/vm_instance.o

MAIN_DREAMCAST_OBJ = \
	c/main_dreamcast.o \
	c/sh7091_scif.o \
	c/native/sh4intrinsic.o

MAIN_HOSTED_OBJ = \
	c/file.o \
	c/native/libcinputstream.o \
	c/main_hosted.o

PRINT_CLASS_OBJ = \
	c/file.o \
	c/native/libcinputstream.o \
	c/print_class.o
