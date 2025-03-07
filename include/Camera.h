struct vec3
{
    float x, y, z;
};

struct vec2{
    float x, y;
};

struct mat3{
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
};

enum directions {
    UP, DOWN, LEFT, RIGHT
};


/* Implement, model matrix, view matrix, projection matrix, and then viewport transform*/
class Camera{
private:
    vec2 pos;
public:
    Camera(){
        pos.x = 0;
        pos.y = 0; 

    }
};