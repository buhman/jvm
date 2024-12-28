package model;

public class FacePNT {
    public int position;
    public int normal;
    public int texture_coordinate;

    FacePNT(int position, int normal, int texture_coordinate) {
        this.position = position;
        this.normal = normal;
        this.texture_coordinate = texture_coordinate;
    }
}
