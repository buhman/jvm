package p;

class Float {
    public static void main() {
        test2();
    }

    static float test() {
        float a = 1.0f;
        float b = a / 3.0f;
        float c = b * 2.0f;
        float d = c + 5.0f;
        float e = d - 0.5f;
        float f = -e;
        float g = f % 2.0f;
        int h = (int)g;
        return h;
    }

    static float test2() {
        float[] arr = {1.0f, 2.1f, 3.2f, 4.3f};
        float sum = 0;
        for (int i = 0; i < arr.length; i++) {
            sum += arr[i];
        }
        boolean b = sum < 1.0f;
        float i = 0.0f;
        if (b)
            i = 1.0f;
        return i * 4.2f;
    }
}
