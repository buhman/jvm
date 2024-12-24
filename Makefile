%.csv: %.ods
	libreoffice --headless --convert-to csv:"Text - txt - csv (StarCalc)":44,34,76,,,,true --outdir $(dir $@) $<

%.class: %.java
	javac $<

OBJ = \
	c/decode.o \
	c/class_file.o \
	c/debug_class_file.o \
	c/malloc.o \
	c/file.o \
	c/execute.o \
	c/memory_allocator.o \
	c/class_resolver.o \
	c/hash_table.o

MAIN_OBJ = \
	$(OBJ) \
	c/frame.o

PRINT_CLASS_OBJ = \
	$(OBJ) \
	c/print_class.o \

CC ?= gcc
ARCH = -m32
CFLAGS ?= -Wall -Werror -Wfatal-errors -Wno-error=unused-variable -std=c2x -DDEBUG -g
OPT ?= -O0
DEPFLAGS = -MMD -MP

%.o: %.c
	$(CC) $(ARCH) $(CFLAGS) $(OPT) $(DEPFLAGS) -MF ${<}.d -c $< -o $@

print_class: $(PRINT_CLASS_OBJ)
	$(CC) $(ARCH) $^ -o $@

main: $(MAIN_OBJ)
	$(CC) $(ARCH) $^ -o $@

clean:
	rm -f main print_class c/*.o

.SUFFIXES:
.INTERMEDIATE:
.SECONDARY:
.PHONY: all clean phony

%: RCS/%,v
%: RCS/%
%: %,v
%: s.%
%: SCCS/s.%
