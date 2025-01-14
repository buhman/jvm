package test;

class TestIntegerTrailingZeros {
    public static void main() {
        System.out.println(Integer.numberOfTrailingZeros(-1180362717));
        System.out.println(Integer.numberOfTrailingZeros(2066224196));
        System.out.println(Integer.numberOfTrailingZeros(805306368));
        System.out.println(Integer.numberOfTrailingZeros(-273003009));
        System.out.println(Integer.numberOfTrailingZeros(-609746944));
        System.out.println(Integer.numberOfTrailingZeros(-1299058518));
        System.out.println(Integer.numberOfTrailingZeros(1291028711));
        System.out.println(Integer.numberOfTrailingZeros(-1690243072));
        System.out.println(Integer.numberOfTrailingZeros(877411840));
        System.out.println(Integer.numberOfTrailingZeros(0));
        System.out.println(Integer.numberOfTrailingZeros(-2147483648));
        /*
          0
          2
          28
          0
          19
          1
          0
          12
          9
          32
          31
        */
    }
}
