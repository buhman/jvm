package filesystem.iso9660;

public class DirectoryRecord extends ByteParser {
  public static final int LENGTH_OF_DIRECTORY_RECORD_START = 0;
  public static final int LENGTH_OF_DIRECTORY_RECORD_END = 0;
  public static final int EXTENDED_ATTRIBUTE_RECORD_LENGTH_START = 1;
  public static final int EXTENDED_ATTRIBUTE_RECORD_LENGTH_END = 1;
  public static final int LOCATION_OF_EXTENT_START = 2;
  public static final int LOCATION_OF_EXTENT_END = 9;
  public static final int DATA_LENGTH_START = 10;
  public static final int DATA_LENGTH_END = 17;
  public static final int RECORDING_DATE_AND_TIME_START = 18;
  public static final int RECORDING_DATE_AND_TIME_END = 24;
  public static final int FILE_FLAGS_START = 25;
  public static final int FILE_FLAGS_END = 25;
  public static final int FILE_UNIT_SIZE_START = 26;
  public static final int FILE_UNIT_SIZE_END = 26;
  public static final int INTERLEAVE_GAP_SIZE_START = 27;
  public static final int INTERLEAVE_GAP_SIZE_END = 27;
  public static final int VOLUME_SEQUENCE_NUMBER_START = 28;
  public static final int VOLUME_SEQUENCE_NUMBER_END = 31;
  public static final int LENGTH_OF_FILE_IDENTIFIER_START = 32;
  public static final int LENGTH_OF_FILE_IDENTIFIER_END = 32;
  public static final int FILE_IDENTIFIER_START = 33;
  public static final int FILE_IDENTIFIER_END = 32;
  public DirectoryRecord(byte[] array, int offset) {
    super(array, offset);
  }
  public int lengthOfDirectoryRecord() {
    return getByte(LENGTH_OF_DIRECTORY_RECORD_START);
  }
  public int extendedAttributeRecordLength() {
    return getByte(EXTENDED_ATTRIBUTE_RECORD_LENGTH_START);
  }
  public int locationOfExtent() {
    return getIntLE(LOCATION_OF_EXTENT_START);
  }
  public int dataLength() {
    return getIntLE(DATA_LENGTH_START);
  }
  public int fileFlags() {
    return getByte(FILE_FLAGS_START);
  }
  public int fileUnitSize() {
    return getByte(FILE_UNIT_SIZE_START);
  }
  public int interleaveGapSize() {
    return getByte(INTERLEAVE_GAP_SIZE_START);
  }
  public int volumeSequenceNumber() {
    return getShortLE(VOLUME_SEQUENCE_NUMBER_START);
  }
  public int lengthOfFileIdentifier() {
    return getByte(LENGTH_OF_FILE_IDENTIFIER_START);
  }
}
