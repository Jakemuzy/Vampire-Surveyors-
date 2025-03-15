/*
-- Jake Math Library --

Author: Jake Muzyka
Date: March 7, 2025
Description:
    This is my own custom math library, specialized in matrix transformations

*/

#include <ostream>


struct vec2 {
    float x, y;
};

class vec3
{
public:
    float columns[3];
    /*
    float& x = columns[0];
    float& y = columns[1];
    float& z = columns[2];
    */

    vec3();                             //  Fill with 0 if no parameters
    vec3(float initializer);            // Fill with paramter value
    vec3(float x, float y, float z);    // Custom values

    // For Identity Matrix
    void identity(int j);

    // Operators
    friend std::ostream& operator<<(std::ostream &os, const vec3 &obj);
    vec3 operator*(float scalar) const;
    vec3 operator-(vec3 other) const;
    vec3 operator+(vec3 other) const;

    vec3 &operator->();
    float& operator[](int i);
    
};



class mat3
{
private:
public:
    vec3 rows[3];

    mat3();                 // Identity
    mat3(float initalizer); // Fill with values

    // Matrix Operations
    void transpose();
    mat3& translate(float x, float y);
    mat3 inverse();
    void rotateAround()
    {
    }

    //Specifies the bonuds for the orthographic projection
    mat3& orthographic(float lBound, float rBound, float bBound, float tBound);

    // Operators
    friend std::ostream &operator<<(std::ostream &os, const mat3 &obj);
    mat3 operator*(float scalar) const;
    mat3 operator*(mat3 obj) const;         // Dot product
    vec3 operator*(const vec3 &obj) const   // mat * vec BAD
    {
       return vec3();
    }
    vec3 &operator[](int i);                //  Indexing

};



/*
friend vec2& clipSpace(float lBound, float rBound, float bBound, float tBound, float x, float y)
{
    vec2 clip;
}
*/
