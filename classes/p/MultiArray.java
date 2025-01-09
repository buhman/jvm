package p;

class MultiArray {
    static int test() {
        byte[][][] arr = new byte[10][20][30];
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 20; j++) {
                for (int k = 0; k < 30; k++) {
                    arr[i][j][k] = (byte)(i * j * k);
                }
            }
        }
        return arr[2][9][4];
    }

    public static void main() {
        test();
    }
}
