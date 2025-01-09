package p;

class AdventOfCodeDay1_String {
    public static int part1() {
        char[] string_input = {
            '3', ' ', ' ', ' ', '4', '\n',
            '4', ' ', ' ', ' ', '3', '\n',
            '2', ' ', ' ', ' ', '5', '\n',
            '1', ' ', ' ', ' ', '3', '\n',
            '3', ' ', ' ', ' ', '9', '\n',
            '3', ' ', ' ', ' ', '3', '\n',
        };

        int[] input = new int[100];
        int nums = 0;
        for (int i = 0; i < string_input.length; i++) {
            switch (string_input[i]) {
            case '0': input[nums++] = 0; break;
            case '1': input[nums++] = 1; break;
            case '2': input[nums++] = 2; break;
            case '3': input[nums++] = 3; break;
            case '4': input[nums++] = 4; break;
            case '5': input[nums++] = 5; break;
            case '6': input[nums++] = 6; break;
            case '7': input[nums++] = 7; break;
            case '8': input[nums++] = 8; break;
            case '9': input[nums++] = 9; break;
            default: break;
            }
        }


        int[] left = new int[nums / 2];
        int[] right = new int[nums / 2];

        for (int i = 0; i < nums / 2; i++) {
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
