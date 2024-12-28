package p;

class Vec2 {
    float x;
    float y;
}

class VecTest {
    static Vec2[] vtx;

    static {
        vtx = new Vec2[3];
        for (int i = 0; i < 3; i++)
            vtx[i] = new Vec2();
        vtx[0].x =  0.0f;
        vtx[0].y =  1.0f;
        vtx[1].x =  0.866025f;
        vtx[1].y = -0.5f;
        vtx[2].x = -0.866025f;
        vtx[2].y = -0.5f;
    }

    public static float test() {
        return vtx[0].y;
    }

    public static void main(String[] args) {
        System.out.println(test());
    }
}
