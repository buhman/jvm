set -eux

sh generate_classpath.sh
rm -f main.bin main.elf jvm.iso
make -f Makefile.dreamcast.mk jvm.iso
../cdi4dc jvm.iso jvm.cdi > /dev/null
