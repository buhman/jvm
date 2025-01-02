set -eux

#(cd ../jvm; sh generate_classpath.sh)
#(cd ../jvm; make -f Makefile.dreamcast.mk main.bin)
#cp ../jvm/main.bin jvm.bin
#make gdrom-jvm-boot-ip-bin
#make ip.iso

rm -f main.bin main.elf jvm.iso
make -f Makefile.dreamcast.mk jvm.iso
../cdi4dc jvm.iso jvm.cdi > /dev/null
