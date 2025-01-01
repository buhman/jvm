function make_class () {
    while read line; do
        echo "${line%.java}.class"
    done
}

function rename_class_files () {
    while read line; do
        local name="${line//\$/_}"
        if [ ! "$name" = "$line" ]; then
            mv "$line" "$name"
        fi
    done
}

function classpath_mk () {
    echo -n "CLASS_PATH =" > classpath.mk
    while read line; do
        local name="${line//\$/\$\$}"
        echo " \\" >> classpath.mk
        printf "\t${name}.o" >> classpath.mk
    done
    echo >> classpath.mk
}

function classpath_inc_c () {
    truncate -s0 c/classpath.inc.c
    while read line; do
        local name0="${line//\//_}"
        local name1="${name0//$/_}"
        local name="${name1//./_}"
        echo "(const uint8_t *)&_binary_${name}_start," >> c/classpath.inc.c
    done
}

function make_header () {
    while read line; do
        truncate -s0 "${line}.h"

        local name0="${line//\//_}"
        local name1="${name0//$/_}"
        local name="${name1//./_}"

        echo '#pragma once' > "${line}.h"
        echo '' >> "${line}.h"
        echo '#include <stdint.h>' >> "${line}.h"
        echo '' >> "${line}.h"
        echo '#ifdef __cplusplus' >> "${line}.h"
        echo 'extern C {' >> "${line}.h"
        echo '#endif' >> "${line}.h"
        echo '' >> "${line}.h"
        echo "extern uint32_t _binary_${name}_start __asm(\"_binary_${name}_start\");" >> "${line}.h"
        echo "extern uint32_t _binary_${name}_end __asm(\"_binary_${name}_end\");" >> "${line}.h"
        echo "extern uint32_t _binary_${name}_size __asm(\"_binary_${name}_size\");" >> "${line}.h"
        echo '' >> "${line}.h"
        echo '#ifdef __cplusplus' >> "${line}.h"
        echo '}' >> "${line}.h"
        echo '#endif' >> "${line}.h"
    done
}

function classpath_h () {
    truncate -s0 c/classpath.h
    while read line; do
        echo "#include \"$line.h\"" >> c/classpath.h
    done
}

set -e

find sega/ java/ -name '*.class' -exec rm -f {} \;
make -j$(nproc) -f Makefile.dreamcast.mk $(find model/ example/ sega/ java/ -name '*.java' | make_class)
find model/ example/ sega/ java/ -name '*.class' | sort | rename_class_files
find model/ example/ sega/ java/ -name '*.class' | sort | classpath_mk
find model/ example/ sega/ java/ -name '*.class' | sort | classpath_inc_c
find model/ example/ sega/ java/ -name '*.class' | sort | make_header
find model/ example/ sega/ java/ -name '*.class' | sort | classpath_h
