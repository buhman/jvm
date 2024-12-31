package filesystem.iso9660;

public class PrimaryVolumeDescriptor extends ByteParser {
  public static final int VOLUME_DESCRIPTOR_TYPE_START = 0;
  public static final int VOLUME_DESCRIPTOR_TYPE_END = 0;
  public static final int STANDARD_IDENTIFIER_START = 1;
  public static final int STANDARD_IDENTIFIER_END = 5;
  public static final int VOLUME_DESCRIPTOR_VERSION_START = 6;
  public static final int VOLUME_DESCRIPTOR_VERSION_END = 6;
  public static final int SYSTEM_IDENTIFIER_START = 8;
  public static final int SYSTEM_IDENTIFIER_END = 39;
  public static final int VOLUME_IDENTIFIER_START = 40;
  public static final int VOLUME_IDENTIFIER_END = 71;
  public static final int VOLUME_SPACE_SIZE_START = 80;
  public static final int VOLUME_SPACE_SIZE_END = 87;
  public static final int VOLUME_SET_SIZE_START = 120;
  public static final int VOLUME_SET_SIZE_END = 123;
  public static final int VOLUME_SEQUENCE_NUMBER_START = 124;
  public static final int VOLUME_SEQUENCE_NUMBER_END = 127;
  public static final int LOGICAL_BLOCK_SIZE_START = 128;
  public static final int LOGICAL_BLOCK_SIZE_END = 131;
  public static final int PATH_TABLE_SIZE_START = 132;
  public static final int PATH_TABLE_SIZE_END = 139;
  public static final int LOCATION_OF_OCCURRENCE_OF_TYPE_L_PATH_TABLE_START = 140;
  public static final int LOCATION_OF_OCCURRENCE_OF_TYPE_L_PATH_TABLE_END = 143;
  public static final int LOCATION_OF_OPTIONAL_OCCURENCE_OF_TYPE_L_PATH_TABLE_START = 144;
  public static final int LOCATION_OF_OPTIONAL_OCCURENCE_OF_TYPE_L_PATH_TABLE_END = 147;
  public static final int LOCATION_OF_OCCURENCE_OF_TYPE_M_PATH_TABLE_START = 148;
  public static final int LOCATION_OF_OCCURENCE_OF_TYPE_M_PATH_TABLE_END = 151;
  public static final int LOCATION_OF_OPTIONAL_OCCURENCE_OF_TYPE_M_PATH_TABLE_START = 152;
  public static final int LOCATION_OF_OPTIONAL_OCCURENCE_OF_TYPE_M_PATH_TABLE_END = 155;
  public static final int DIRECTORY_RECORD_FOR_ROOT_DIRECTORY_START = 156;
  public static final int DIRECTORY_RECORD_FOR_ROOT_DIRECTORY_END = 189;
  public static final int VOLUME_SET_IDENTIFIER_START = 190;
  public static final int VOLUME_SET_IDENTIFIER_END = 317;
  public static final int PUBLISHER_IDENTIFIER_START = 318;
  public static final int PUBLISHER_IDENTIFIER_END = 445;
  public static final int DATA_PREPARER_IDENTIFIER_START = 446;
  public static final int DATA_PREPARER_IDENTIFIER_END = 573;
  public static final int APPLICATION_IDENTIFIER_START = 574;
  public static final int APPLICATION_IDENTIFIER_END = 701;
  public static final int COPYRIGHT_FILE_IDENTIFIER_START = 702;
  public static final int COPYRIGHT_FILE_IDENTIFIER_END = 738;
  public static final int ABSTRACT_FILE_IDENTIFIER_START = 739;
  public static final int ABSTRACT_FILE_IDENTIFIER_END = 775;
  public static final int BIBLIOGRAPHIC_FILE_IDENTIFIER_START = 776;
  public static final int BIBLIOGRAPHIC_FILE_IDENTIFIER_END = 812;
  public static final int VOLUME_CREATION_DATE_AND_TIME_START = 813;
  public static final int VOLUME_CREATION_DATE_AND_TIME_END = 829;
  public static final int VOLUME_MODIFICATION_DATE_AND_TIME_START = 830;
  public static final int VOLUME_MODIFICATION_DATE_AND_TIME_END = 846;
  public static final int VOLUME_EXPIRATION_DATE_AND_TIME_START = 847;
  public static final int VOLUME_EXPIRATION_DATE_AND_TIME_END = 863;
  public static final int VOLUME_EFFECTIVE_DATE_AND_TIME_START = 864;
  public static final int VOLUME_EFFECTIVE_DATE_AND_TIME_END = 880;
  public static final int FILE_STRUCTURE_VERSION_START = 881;
  public static final int FILE_STRUCTURE_VERSION_END = 881;
  public static final int APPLICATION_USE_START = 883;
  public static final int APPLICATION_USE_END = 1394;
  public PrimaryVolumeDescriptor(byte[] array, int offset) {
    super(array, offset);
  }
  public int volumeDescriptorType() {
    return getByte(VOLUME_DESCRIPTOR_TYPE_START);
  }
  public int volumeDescriptorVersion() {
    return getByte(VOLUME_DESCRIPTOR_VERSION_START);
  }
  public int volumeSpaceSize() {
    return getIntLE(VOLUME_SPACE_SIZE_START);
  }
  public int volumeSetSize() {
    return getShortLE(VOLUME_SET_SIZE_START);
  }
  public int volumeSequenceNumber() {
    return getShortLE(VOLUME_SEQUENCE_NUMBER_START);
  }
  public int logicalBlockSize() {
    return getShortLE(LOGICAL_BLOCK_SIZE_START);
  }
  public int pathTableSize() {
    return getIntLE(PATH_TABLE_SIZE_START);
  }
  public int locationOfOccurrenceOfTypeLPathTable() {
    return getShortLE(LOCATION_OF_OCCURRENCE_OF_TYPE_L_PATH_TABLE_START);
  }
  public int locationOfOptionalOccurenceOfTypeLPathTable() {
    return getShortLE(LOCATION_OF_OPTIONAL_OCCURENCE_OF_TYPE_L_PATH_TABLE_START);
  }
  public int locationOfOccurenceOfTypeMPathTable() {
    return getShortLE(LOCATION_OF_OCCURENCE_OF_TYPE_M_PATH_TABLE_START);
  }
  public int locationOfOptionalOccurenceOfTypeMPathTable() {
    return getShortLE(LOCATION_OF_OPTIONAL_OCCURENCE_OF_TYPE_M_PATH_TABLE_START);
  }
}
