package java.lang;

class String {
    private final byte[] value;

    public String() {
        this.value = new byte[0];
    }

    public String(String original) {
        this.value = original.value;
    }

    public String(byte[] value) {
        this.value = value;
    }

    public byte[] getBytes() {
        return this.value;
    }
}
