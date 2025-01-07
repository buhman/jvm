%.csv: %.ods
	libreoffice --headless --convert-to csv:"Text - txt - csv (StarCalc)":44,34,76,,,,true --outdir $(dir $@) $<

include java.mk

CC ?= gcc
ARCH = -m32
CFLAGS += -Wall -Werror -Wfatal-errors -Wno-error=unused-variable -fstack-protector -std=c2x -g
CFLAGS += -DDEBUG
CFLAGS += -DDEBUG_PRINT
LDFLAGS = -lm
OPT ?= -O0
DEPFLAGS = -MMD -MP

%.o: %.c
	$(CC) $(ARCH) $(CFLAGS) $(OPT) $(DEPFLAGS) -MF ${<}.d -c $< -o $@

print_class: $(OBJ) $(PRINT_CLASS_OBJ)
	$(CC) $(ARCH) $(LDFLAGS) $^ -o $@

main: $(OBJ) $(MAIN_HOSTED_OBJ)
	$(CC) $(ARCH) $(LDFLAGS) $^ -o $@

clean:
	rm -f main print_class c/*.o c/*.d *.elf *.bin

.SUFFIXES:
.INTERMEDIATE:
.SECONDARY:
.PHONY: all clean phony

%: RCS/%,v
%: RCS/%
%: %,v
%: s.%
%: SCCS/s.%
