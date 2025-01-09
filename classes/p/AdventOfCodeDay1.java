package p;

class AdventOfCodeDay1 {
    public static int part1() {
        int[] input = {3,   4,
                       4,   3,
                       2,   5,
                       1,   3,
                       3,   9,
                       3,   3};

        int[] left = new int[input.length / 2];
        int[] right = new int[input.length / 2];

        for (int i = 0; i < input.length / 2; i++) {
            left[i] = input[i * 2];
            right[i] = input[i * 2 + 1];
        }

        // bubble sort left
        while (true) {
            boolean swapped = false;
            for (int i = 1; i < left.length; i++) {
                if (left[i - 1] > left[i]) {
                    int tmp = left[i - 1];
                    left[i - 1] = left[i];
                    left[i] = tmp;
                    swapped = true;
                }
            }
            if (!swapped)
                break;
        }

        // bubble sort right
        while (true) {
            boolean swapped = false;
            for (int i = 1; i < right.length; i++) {
                if (right[i - 1] > right[i]) {
                    int tmp = right[i - 1];
                    right[i - 1] = right[i];
                    right[i] = tmp;
                    swapped = true;
                }
            }
            if (!swapped)
                break;
        }

        int sum = 0;
        for (int i = 0; i < left.length; i++) {
            int dist = left[i] - right[i];
            if (dist < 0)
                dist = -dist;
            sum += dist;
        }
        return sum;
    }

    public static void main(String[] args) {
        System.out.println(part1());
    }
}
