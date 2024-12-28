all: $(patsubst %.cpp,%.elf,$(wildcard example/*.cpp))

OPT = -Og

MAKEFILE_PATH := $(patsubst %/,%,$(dir $(abspath $(firstword $(MAKEFILE_LIST)))))
LIB ?= $(MAKEFILE_PATH)/dreamcast
CFLAGS += -D__dreamcast__
CFLAGS += -DDEBUG
#CFLAGS += -DDEBUG_PRINT
CFLAGS += -I$(MAKEFILE_PATH)
CFLAGS += -I$(MAKEFILE_PATH)/dreamcast/
CFLAGS += -Wno-error=strict-aliasing -fno-strict-aliasing
CARCH = -m4-single -ml

include dreamcast/base.mk
include dreamcast/common.mk
include dreamcast/headers.mk

include java.mk

%.class.o: %.class
	$(BUILD_BINARY_O)

%.class.h: %.class
	$(BUILD_BINARY_H)

libgcc/%.o: $(LIBGCC)
	@mkdir -p $(dir $@)
	ar x --output $(dir $@) $(LIBGCC) $(notdir $@)
	sh4-none-elf-objdump -t $@ \
		| grep -E '[.]hidden' \
		| grep -vE 'UND' \
		| cut -d' ' -f10 \
		| xargs rebind --visibility=default $@

LIBGCC_OBJ = \
	libgcc/_divdi3.o \
	libgcc/_udiv_qrnnd_16.o \
	libgcc/_clz.o \
	libgcc/_moddi3.o \
	libgcc/_fixdfdi.o \
	libgcc/_fixunsdfdi.o \
	libgcc/_fixunssfdi.o \
	libgcc/_floatdisf.o \
	libgcc/_floatdidf.o \
	libgcc/_sdivsi3.o \
	libgcc/_fixsfdi.o \
	libgcc/_div_table.o \
	libgcc/_movmem_i4.o

include classpath.mk

CLASS_FILES = \
	p/polygon_type_0.class.o \
	p/vertex_polygon_type_0.class.o \
	p/end_of_list.class.o \
	p/DreamcastVideo2.class.o

main.elf: LDSCRIPT = $(LIB)/main.lds
main.elf: $(START_OBJ) $(OBJ) $(MAIN_OBJ) $(MAIN_DREAMCAST_OBJ) $(LIBGCC_OBJ) $(CLASS_FILES) $(CLASS_PATH)
