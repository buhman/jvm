all: $(patsubst %.cpp,%.elf,$(wildcard example/*.cpp))

OPT = -Og

MAKEFILE_PATH := $(patsubst %/,%,$(dir $(abspath $(firstword $(MAKEFILE_LIST)))))
LIB ?= $(MAKEFILE_PATH)/dreamcast
CFLAGS += -D__dreamcast__
CFLAGS += -DDEBUG
#CFLAGS += -DDEBUG_PRINT
CFLAGS += -I$(MAKEFILE_PATH)/c
CFLAGS += -I$(MAKEFILE_PATH)/dreamcast
CFLAGS += -I$(MAKEFILE_PATH)/
CFLAGS += -Wno-error=strict-aliasing -fno-strict-aliasing
CARCH = -m4-single -ml

include dreamcast/base.mk
include dreamcast/common.mk
include dreamcast/headers.mk
include dreamcast/ip.mk

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

GDROM_JVM_BOOT_OBJ = \
	$(LIB)/example/gdrom_jvm_boot.o \
	$(LIB)/sh7091/serial.o


boot.elf: LDSCRIPT = $(LIB)/ip.lds
boot.elf: $(IP_OBJ) $(START_OBJ) $(GDROM_JVM_BOOT_OBJ)

zero.bin:
	dd if=/dev/zero of=$@ bs=2048 count=1

jvm.iso: boot.bin main.bin zero.bin
	mkisofs \
		-C 0,11702 \
		-sysid     "SEGA SEGAKATANA" \
		-volid     "SAMPLE_GAME_TITLE" \
		-volset    "SAMPLE_GAME_TITLE" \
		-publisher "SEGA ENTERPRISES, LTD." \
		-preparer  "CRI CD CRAFT VER.2.27" \
		-copyright "COPYRIGH.TXT" \
		-abstract  "ABSTRACT.TXT" \
		-biblio    "BIBLIOGR.TXT" \
		-G boot.bin \
		-o $@ \
		-graft-points \
		/0JVM.BIN=./main.bin \
		/1ST_READ.BIN=zero.bin \
		/=$(LIB)/COPYRIGH.TXT \
		/=$(LIB)/ABSTRACT.TXT \
		/=$(LIB)/BIBLIOGR.TXT \
		classes/example/GdromDirectoryRecordHandler.class \
		classes/example/GdromClassLoader.class \
		classes/filesystem/iso9660/ByteParser.class \
		classes/filesystem/iso9660/DirectoryRecord.class \
		classes/filesystem/iso9660/ExtentReader.class \
		classes/filesystem/iso9660/PrimaryVolumeDescriptor.class \
		classes/filesystem/iso9660/VolumeParser.class \
		classes/java/io/PrintStream.class \
		classes/java/lang/DecimalDigits.class \
		classes/java/lang/Integer.class \
		classes/java/lang/Float.class \
		classes/java/lang/Number.class \
		classes/java/lang/Object.class \
		classes/java/lang/String.class \
		classes/java/lang/System.class \
		classes/java/lang/Exception.class \
		classes/java/lang/Throwable.class \
		classes/java/lang/Backtrace.class \
		classes/java/misc/Memory.class \
		classes/jvm/internal/Loader.class \
		classes/sega/dreamcast/gdrom/G1IF.class \
		classes/sega/dreamcast/gdrom/GdromIF.class \
		classes/sega/dreamcast/gdrom/GdromBits.class \
		classes/sega/dreamcast/gdrom/Gdrom.class \
		classes/sega/dreamcast/gdrom/GdromExtentReader.class \
		classes/sega/dreamcast/gdrom/GdromCommandPacketFormat_cd_read.class \
		classes/sega/dreamcast/gdrom/GdromCommandPacketFormat.class \
		classes/sega/dreamcast/gdrom/GdromCommandPacketFormat_get_toc.class \
		classes/sega/dreamcast/gdrom/GdromCommandPacketInterface.class \
		classes/sega/dreamcast/gdrom/GdromProtocol.class \
		classes/Main.class \
		classes/example/JavaCube.class \
		classes/example/JavaCubeDirectoryRecordHandler.class \
		classes/model/FacePTN.class \
		classes/model/ModelObject.class \
		classes/model/CubeModel.class \
		classes/model/Vec2.class \
		classes/model/Vec3.class \
		classes/sega/dreamcast/holly/Background.class \
		classes/sega/dreamcast/holly/CoreBits.class \
		classes/sega/dreamcast/holly/Core.class \
		classes/sega/dreamcast/holly/VideoOutput.class \
		classes/sega/dreamcast/holly/VideoOutputMode.class \
		classes/sega/dreamcast/holly/ISPTSP.class \
		classes/sega/dreamcast/holly/RegionArray.class \
		classes/sega/dreamcast/holly/RegionArray_OPBSize.class \
		classes/sega/dreamcast/holly/TABits.class \
		classes/sega/dreamcast/holly/TAFIFOPolygonConverter.class \
		classes/sega/dreamcast/holly/TAGlobalParameter.class \
		classes/sega/dreamcast/holly/TAGlobalParameter_end_of_list.class \
		classes/sega/dreamcast/holly/TAGlobalParameter_polygon_type_0.class \
		classes/sega/dreamcast/holly/TAVertexParameter.class \
		classes/sega/dreamcast/holly/TAVertexParameter_polygon_type_3.class \
		classes/sega/dreamcast/holly/TextureMemoryAllocation.class \
		classes/java/lang/Math.class \
		classes/java/misc/Resource.class \
		images/java_text.data \
		images/java_cup.data

main.elf: LDSCRIPT = $(LIB)/main.lds
main.elf: $(START_OBJ) $(OBJ) $(MAIN_OBJ) $(MAIN_DREAMCAST_OBJ) $(LIBGCC_OBJ) $(CLASS_PATH)
