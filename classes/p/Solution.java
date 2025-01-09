package p;

class Rule {
    public final int left;
    public final int right;

    public Rule(int left, int right) {
        this.left = left;
        this.right = right;
    }
};

class Array {
    public int[] num;
    public int length;

    public Array(int size) {
        this.num = new int[size];
        this.length = 0;
    }

    public void append(int n) {
        num[length] = n;
        length += 1;
    }
};

class InputParser {
    byte[] buf;
    int ix;

    public InputParser(byte[] buf) {
        this.buf = buf;
        this.ix = 0;
    }

    static int parse_base10_digit(byte c)
    {
        switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        default: return -1;
        }
    }

    int parse_base10() {
        int n = 0;

        while (true) {
            int digit = parse_base10_digit(buf[ix]);
            if (digit == -1)
                break;

            n *= 10;
            n += digit;

            ix += 1;
        }

        return n;
    }

    void parse_consume(char c) {
        if (buf[ix] != (byte)c) {
            // error
            while (true);
        }
        ix += 1;
    }

    public void parse_skip(char c) {
        while (ix < buf.length && buf[ix] == (byte)c) {
            ix += 1;
        }
    }

    boolean parse_match(char c) {
        if (buf[ix] == (byte)c) {
            parse_skip(c);
            return true;
        } else {
            return false;
        }
    }


    public boolean end_of_rules() {
        return buf[ix] == '\n';
    }

    public Rule parse_rule() {
        int left = parse_base10();
        parse_consume('|');
        int right = parse_base10();
        parse_consume('\n');

        return new Rule(left, right);
    }

    public boolean end_of_updates() {
        return ix >= buf.length;
    }

    public Array parse_update() {
        Array update = new Array(10);

        while (true) {
            int n = parse_base10();
            parse_skip(',');

            update.append(n);

            if (parse_match('\n'))
                return update;
        }
    }
}

class Solution {
    static String input = """
        47|53
        97|13
        97|61
        97|47
        75|29
        61|13
        75|53
        29|13
        97|29
        53|29
        61|53
        97|53
        61|29
        47|13
        75|47
        97|75
        47|61
        75|61
        47|29
        75|13
        53|13

        75,47,61,53,29
        97,61,53,29,13
        75,29,13
        75,97,47,61,53
        61,13,29
        97,13,75,29,47
        """;

    static boolean rule_match(Rule rule, int a, int b)
    {
        return rule.left == a && rule.right == b;
    }


    static boolean sort_numbers(Rule[] rules, int rules_length, Array update) {
        boolean at_least_one_swap = false;
        while (true) {
            boolean swapped = false;
            for (int i = 0; i < update.length - 1; i++) {
                int a = update.num[i + 0];
                int b = update.num[i + 1];

                for (int j = 0; j < rules_length; j++) {
                    if (rule_match(rules[j], b, a)) {
                        swapped = true;
                        at_least_one_swap = true;
                        update.num[i + 0] = b;
                        update.num[i + 1] = a;
                    }
                }
            }
            if (!swapped)
                break;
        }

        return at_least_one_swap;
    }

    static int solve(boolean correctly_ordered) {
        InputParser parser = new InputParser(input.getBytes());

        Rule rules[] = new Rule[100];
        int rules_length = 0;
        while (!(parser.end_of_rules())) {
            Rule rule = parser.parse_rule();
            rules[rules_length] = rule;
            rules_length += 1;
        }

        parser.parse_skip('\n');

        int sum = 0;
        while (!(parser.end_of_updates())) {
            Array update = parser.parse_update();

            boolean at_least_one_swap = sort_numbers(rules, rules_length, update);
            if (correctly_ordered ^ at_least_one_swap) {
                sum += update.num[update.length / 2];
            }
        }
        return sum;
    }

    public static void main() {
        solve(true);  // part1
        solve(false); // part2
    }
}
