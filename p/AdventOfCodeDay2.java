package p;

class AdventOfCodeDay2 {
    static float parse_digit(char c) {
        switch (c) {
        case '0': return 0.0f;
        case '1': return 1.0f;
        case '2': return 2.0f;
        case '3': return 3.0f;
        case '4': return 4.0f;
        case '5': return 5.0f;
        case '6': return 6.0f;
        case '7': return 7.0f;
        case '8': return 8.0f;
        case '9': return 9.0f;
        default: return -1.0f;
        }
    }

    static float fabs(float f)
    {
        if (f < 0)
            return -f;
        else
            return f;
    }

    static float fsign(float f)
    {
        if (f < 0)
            return -1;
        else
            return 1;
    }

    static boolean report_safe(float[] line, int length)
    {
        float last = line[0];
        float last_sign = 0.0f;
        for (int i = 1; i < length; i++) {
            float cur = line[i];
            float rate = last - cur;

            if (fabs(rate) < 1 || fabs(rate) > 3)
                return false; // unsafe

            float sign = fsign(rate);
            if (last_sign != 0.0f && sign != last_sign)
                return false; // unsafe

            last_sign = sign;
            last = cur;
        }

        return true; // safe
    }

    static float solve(char[] input) {
        float[] line = new float[100];
        int line_ix = 0;
        int input_ix = 0;
        float num = 0.0f;
        float safe_count = 0.0f;

        while (input_ix < input.length) {
            if (input[input_ix] == ' ' || input[input_ix] == '\n') {
                line[line_ix] = num;
                line_ix += 1;
                num = 0.0f;
            }
            if (input[input_ix] == '\n') {
                if (report_safe(line, line_ix)) {
                    safe_count += 1.0f;
                }
                line_ix = 0;
            }
            float digit = parse_digit(input[input_ix]);
            if (!(digit < 0.0f)) {
                num *= 10.0f;
                num += digit;
            }
            input_ix += 1;
        }

        return safe_count;
    }

    public static void main() {
        char[] input = {
            '7', ' ', '6', ' ', '4', ' ', '2', ' ', '1', '\n',
            '1', ' ', '2', ' ', '7', ' ', '8', ' ', '9', '\n',
            '9', ' ', '7', ' ', '6', ' ', '2', ' ', '1', '\n',
            '1', ' ', '3', ' ', '2', ' ', '4', ' ', '5', '\n',
            '8', ' ', '6', ' ', '4', ' ', '4', ' ', '1', '\n',
            '1', ' ', '3', ' ', '6', ' ', '7', ' ', '9', '\n',
        };

        solve(input);
    }
}
