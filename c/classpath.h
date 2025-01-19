#include "classes/example/GdromClassLoader.class.h"
#include "classes/example/GdromDirectoryRecordHandler.class.h"
#include "classes/filesystem/iso9660/ByteParser.class.h"
#include "classes/filesystem/iso9660/DirectoryRecord.class.h"
#include "classes/filesystem/iso9660/ExtentReader.class.h"
#include "classes/filesystem/iso9660/PrimaryVolumeDescriptor.class.h"
#include "classes/filesystem/iso9660/VolumeParser.class.h"
#include "classes/java/io/PrintStream.class.h"
#include "classes/java/lang/DecimalDigits.class.h"
#include "classes/java/lang/Integer.class.h"
#include "classes/java/lang/Float.class.h"
#include "classes/java/lang/Number.class.h"
#include "classes/java/lang/Object.class.h"
#include "classes/java/lang/String.class.h"
#include "classes/java/lang/System.class.h"
#include "classes/java/lang/Exception.class.h"
#include "classes/java/lang/Throwable.class.h"
#include "classes/java/lang/Backtrace.class.h"
#include "classes/sega/dreamcast/gdrom/G1IF.class.h"
#include "classes/sega/dreamcast/gdrom/GdromIF.class.h"
#include "classes/sega/dreamcast/gdrom/GdromBits.class.h"
#include "classes/sega/dreamcast/gdrom/Gdrom.class.h"
#include "classes/sega/dreamcast/gdrom/GdromExtentReader.class.h"
#include "classes/sega/dreamcast/gdrom/GdromCommandPacketFormat_cd_read.class.h"
#include "classes/sega/dreamcast/gdrom/GdromCommandPacketFormat.class.h"
#include "classes/sega/dreamcast/gdrom/GdromCommandPacketFormat_get_toc.class.h"
#include "classes/sega/dreamcast/gdrom/GdromCommandPacketInterface.class.h"
#include "classes/sega/dreamcast/gdrom/GdromProtocol.class.h"
#include "classes/jvm/internal/Loader.class.h"
#include "classes/jvm/internal/Memory.class.h"
