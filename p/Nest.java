public class Nest {
    private String secret = "Hidden message";
    public class InnerClass {
        public void revealSecret() {
            // Direct access to private member of OuterClass
            System.out.println(secret);
        }
    }
}
