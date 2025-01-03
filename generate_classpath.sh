#!/bin/bash

set -eu pipefail

function java_to_class () {
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

declare -a boot_classes=(
    example/GdromClassLoader.class
    example/GdromDirectoryRecordHandler.class
    filesystem/iso9660/ByteParser.class
    filesystem/iso9660/DirectoryRecord.class
    filesystem/iso9660/ExtentReader.class
    filesystem/iso9660/PrimaryVolumeDescriptor.class
    filesystem/iso9660/VolumeParser.class
    java/io/PrintStream.class
    java/lang/DecimalDigits.class
    java/lang/Integer.class
    java/lang/Object.class
    java/lang/String.class
    java/lang/System.class
    java/misc/Memory.class
    sega/dreamcast/gdrom/G1IF.class
    sega/dreamcast/gdrom/GdromIF.class
    sega/dreamcast/gdrom/GdromBits.class
    sega/dreamcast/gdrom/Gdrom.class
    sega/dreamcast/gdrom/GdromExtentReader.class
    sega/dreamcast/gdrom/GdromCommandPacketFormat_cd_read.class
    sega/dreamcast/gdrom/GdromCommandPacketFormat.class
    sega/dreamcast/gdrom/GdromCommandPacketFormat_get_toc.class
    sega/dreamcast/gdrom/GdromCommandPacketInterface.class
    sega/dreamcast/gdrom/GdromProtocol.class
    jvm/internal/Loader.class
)

function boot_classes () {
    local length=${#boot_classes[@]}

    for ((i=0;i<length;i++)); do
        local class="${boot_classes[i]}"
        echo "$class"
    done
}

function boot_sources () {
    local length=${#boot_classes[@]}

    for ((i=0;i<length;i++)); do
        local class="${boot_classes[i]}"
        local source="${class%.class}.java"
        if [ -f "$source" ]; then
           echo "$source"
        fi
    done
}

declare -a application_classes=(
    Main.class
    example/DreamcastVideo2.class
    model/FacePTN.class
    model/ModelObject.class
    model/UntitledModel.class
    model/Vec2.class
    model/Vec3.class
    sega/dreamcast/holly/Background.class
    sega/dreamcast/holly/Core.class
    sega/dreamcast/holly/CoreBits.class
    sega/dreamcast/holly/VideoOutput.class
    sega/dreamcast/holly/VideoOutputMode.class
    sega/dreamcast/holly/ISPTSP.class
    sega/dreamcast/holly/RegionArray.class
    sega/dreamcast/holly/RegionArray_OPBSize.class
    sega/dreamcast/holly/TABits.class
    sega/dreamcast/holly/TAFIFOPolygonConverter.class
    sega/dreamcast/holly/TAGlobalParameter.class
    sega/dreamcast/holly/TAGlobalParameter_end_of_list.class
    sega/dreamcast/holly/TAGlobalParameter_polygon_type_0.class
    sega/dreamcast/holly/TAVertexParameter.class
    sega/dreamcast/holly/TAVertexParameter_polygon_type_3.class
    sega/dreamcast/holly/TextureMemoryAllocation.class
    java/lang/Math.class
    java/misc/Resource.class
)

function application_classes () {
    local length=${#application_classes[@]}

    for ((i=0;i<length;i++)); do
        local class="${application_classes[i]}"
        echo "$class"
    done
}

function application_sources () {
    local length=${#application_classes[@]}

    for ((i=0;i<length;i++)); do
        local class="${application_classes[i]}"
        local source="${class%.class}.java"
        if [ -f "$source" ]; then
           echo "$source"
        fi
    done
}

function find_classes () {
    find model/ example/ sega/ java/ filesystem/ -name '*.class' -not -name 'Test*' | sort
}

function find_sources () {
    find model/ example/ sega/ java/ filesystem/ -name '*.java' -not -name 'Test*' | sort
}


find . -name '*.class' -exec rm -f {} \;

make -f Makefile.dreamcast.mk $(boot_sources | java_to_class)
find . -name '*.class' | rename_class_files
boot_classes | classpath_mk
boot_classes | classpath_inc_c
boot_classes | make_header
boot_classes | classpath_h

make -f Makefile.dreamcast.mk $(application_sources | java_to_class)
find . -name '*.class' | rename_class_files

boot_classes | sort > classes.txt
application_classes | sort >> classes.txt
