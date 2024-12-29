package model;

public class UntitledModel {
    public static Vec3[] position;
    public static Vec3[] normal;
    public static Vec2[] texture;
    public static ModelObject[] objects;
    private UntitledModel() {
    }
    static {
        position = new Vec3[8];
        normal = new Vec3[6];
        texture = new Vec2[6];
        objects = new ModelObject[1];
        position[0] = new Vec3(1.0f, 1.0f, -1.0f);
        position[1] = new Vec3(1.0f, -1.0f, -1.0f);
        position[2] = new Vec3(1.0f, 1.0f, 1.0f);
        position[3] = new Vec3(1.0f, -1.0f, 1.0f);
        position[4] = new Vec3(-1.0f, 1.0f, -1.0f);
        position[5] = new Vec3(-1.0f, -1.0f, -1.0f);
        position[6] = new Vec3(-1.0f, 1.0f, 1.0f);
        position[7] = new Vec3(-1.0f, -1.0f, 1.0f);
        normal[0] = new Vec3(0.0f, 1.0f, 0.0f);
        normal[1] = new Vec3(0.0f, 0.0f, 1.0f);
        normal[2] = new Vec3(-1.0f, 0.0f, 0.0f);
        normal[3] = new Vec3(0.0f, -1.0f, 0.0f);
        normal[4] = new Vec3(1.0f, 0.0f, 0.0f);
        normal[5] = new Vec3(0.0f, 0.0f, -1.0f);
        texture[0] = new Vec2(1.0f, 0.0f);
        texture[1] = new Vec2(0.0f, 0.5f);
        texture[2] = new Vec2(0.0f, 0.0f);
        texture[3] = new Vec2(1.0f, 0.5f);
        texture[4] = new Vec2(0.0f, 1.0f);
        texture[5] = new Vec2(1.0f, 1.0f);
        objects[0] = new ModelObject();
        objects[0].faces = new FacePTN[12][3];
        objects[0].faces[0][0] = new FacePTN(4, 0, 0);
        objects[0].faces[0][1] = new FacePTN(2, 1, 0);
        objects[0].faces[0][2] = new FacePTN(0, 2, 0);
        objects[0].faces[1][0] = new FacePTN(2, 0, 1);
        objects[0].faces[1][1] = new FacePTN(7, 1, 1);
        objects[0].faces[1][2] = new FacePTN(3, 2, 1);
        objects[0].faces[2][0] = new FacePTN(6, 3, 2);
        objects[0].faces[2][1] = new FacePTN(5, 4, 2);
        objects[0].faces[2][2] = new FacePTN(7, 1, 2);
        objects[0].faces[3][0] = new FacePTN(1, 0, 3);
        objects[0].faces[3][1] = new FacePTN(7, 1, 3);
        objects[0].faces[3][2] = new FacePTN(5, 2, 3);
        objects[0].faces[4][0] = new FacePTN(0, 3, 4);
        objects[0].faces[4][1] = new FacePTN(3, 4, 4);
        objects[0].faces[4][2] = new FacePTN(1, 1, 4);
        objects[0].faces[5][0] = new FacePTN(4, 0, 5);
        objects[0].faces[5][1] = new FacePTN(1, 1, 5);
        objects[0].faces[5][2] = new FacePTN(5, 2, 5);
        objects[0].faces[6][0] = new FacePTN(4, 0, 0);
        objects[0].faces[6][1] = new FacePTN(6, 3, 0);
        objects[0].faces[6][2] = new FacePTN(2, 1, 0);
        objects[0].faces[7][0] = new FacePTN(2, 0, 1);
        objects[0].faces[7][1] = new FacePTN(6, 3, 1);
        objects[0].faces[7][2] = new FacePTN(7, 1, 1);
        objects[0].faces[8][0] = new FacePTN(6, 3, 2);
        objects[0].faces[8][1] = new FacePTN(4, 5, 2);
        objects[0].faces[8][2] = new FacePTN(5, 4, 2);
        objects[0].faces[9][0] = new FacePTN(1, 0, 3);
        objects[0].faces[9][1] = new FacePTN(3, 3, 3);
        objects[0].faces[9][2] = new FacePTN(7, 1, 3);
        objects[0].faces[10][0] = new FacePTN(0, 3, 4);
        objects[0].faces[10][1] = new FacePTN(2, 5, 4);
        objects[0].faces[10][2] = new FacePTN(3, 4, 4);
        objects[0].faces[11][0] = new FacePTN(4, 0, 5);
        objects[0].faces[11][1] = new FacePTN(0, 3, 5);
        objects[0].faces[11][2] = new FacePTN(1, 1, 5);
    }
}
