#include "jml.h"

/*  VEC3    */

vec3::vec3(){
    {
        for (int i = 0; i < 3; i++)
        {
            columns[i] = 0;
        }
    }
}

vec3::vec3(float initializer)
{
    for (int i = 0; i < 3; i++)
    {
        columns[i] = initializer;
    }
}

vec3::vec3(float x, float y, float z)
{
    columns[0] = x;
    columns[1] = y;
    columns[2] = z;
}

void vec3::identity(int j)
{
    for (int i = 0; i < 3; i++)
    {
        if (i == j)
            columns[i] = 1;
        else
            columns[i] = 0;
    }
}

std::ostream &operator<<(std::ostream &os, const vec3 &obj)
{
    for (int i = 0; i < 3; i++)
    {
        os << obj.columns[i] << " ";
    }
    os << "\n";
    return os;
}

vec3 vec3::operator*(float scalar) const
{
    return vec3((*this).columns[0] * scalar, (*this).columns[1] * scalar, (*this).columns[2] * scalar);
}

vec3 vec3::operator-(vec3 other) const
{
    return vec3((*this).columns[0] - other.columns[0], (*this).columns[1] - other.columns[1], (*this).columns[2] - other.columns[2]);
}

vec3 vec3::operator+(vec3 other) const
{
    return vec3((*this).columns[0] + other.columns[0], (*this).columns[1] + other.columns[1], (*this).columns[2] + other.columns[2]);
}

float& vec3::operator[](int i)
{
    return columns[i];
}

vec3& vec3::operator->()
{
    return *this;
}



/*  MAT3    */

mat3::mat3() : mat3(0)
{
    for (int i = 0; i < 3; i++)
    {
        rows[i].identity(i);
    }
    
}

mat3::mat3(float initalizer)
{

    for (int i = 0; i < 3; i++)
    {
        rows[i] = vec3(initalizer);
    }
}

void mat3::transpose()
{
    mat3 copy = *this;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            (*this)[i][j] = copy[j][i];
        }
    }
}

mat3& mat3::translate(float x, float y)
{
    this->rows[0].columns[2] += x;
    this->rows[1].columns[2] += y;

    return (*this);
}

mat3 mat3::inverse()
{
    // Zero matrix to start
    mat3 inv(0);

    double det = this->rows[0].columns[0] * (this->rows[1].columns[1] * this->rows[2].columns[2] - this->rows[2].columns[1] * this->rows[1].columns[2]) -
                 this->rows[0].columns[1] * (this->rows[1].columns[0] * this->rows[2].columns[2] - this->rows[1].columns[2] * this->rows[2].columns[0]) +
                 this->rows[0].columns[2] * (this->rows[1].columns[0] * this->rows[2].columns[1] - this->rows[1].columns[1] * this->rows[2].columns[0]);

    double invdet = 1 / det;

    inv.rows[0].columns[0] = (this->rows[1].columns[1] * this->rows[2].columns[2] - this->rows[2].columns[1] * this->rows[1].columns[2]) * invdet;
    inv.rows[0].columns[1] = (this->rows[0].columns[2] * this->rows[2].columns[1] - this->rows[0].columns[1] * this->rows[2].columns[2]) * invdet;
    inv.rows[0].columns[2] = (this->rows[0].columns[1] * this->rows[1].columns[2] - this->rows[0].columns[2] * this->rows[1].columns[1]) * invdet;

    inv.rows[1].columns[0] = (this->rows[1].columns[2] * this->rows[2].columns[0] - this->rows[1].columns[0] * this->rows[2].columns[2]) * invdet;
    inv.rows[1].columns[1] = (this->rows[0].columns[0] * this->rows[2].columns[2] - this->rows[0].columns[2] * this->rows[2].columns[0]) * invdet;
    inv.rows[1].columns[2] = (this->rows[1].columns[0] * this->rows[0].columns[2] - this->rows[0].columns[0] * this->rows[1].columns[2]) * invdet;

    inv.rows[2].columns[0] = (this->rows[1].columns[0] * this->rows[2].columns[1] - this->rows[2].columns[0] * this->rows[1].columns[1]) * invdet;
    inv.rows[2].columns[1] = (this->rows[2].columns[0] * this->rows[0].columns[2] - this->rows[0].columns[0] * this->rows[2].columns[1]) * invdet;
    inv.rows[2].columns[2] = (this->rows[0].columns[0] * this->rows[1].columns[1] - this->rows[1].columns[0] * this->rows[0].columns[1]) * invdet;

    return inv;
}

mat3& mat3::orthographic(float lBound, float rBound, float bBound, float tBound)
{

    (*this)[0][0] = 2 / (rBound - lBound);
    (*this)[1][1] = 2 / (tBound - bBound);

    (*this)[0][2] = -(rBound + lBound) / (rBound - lBound);
    (*this)[1][2] = -(tBound + bBound) / (tBound - bBound);

    return *this;
}

mat3 mat3::operator*(float scalar) const
{
    mat3 copy;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            (copy).rows[i].columns[j] = rows[i].columns[j] * scalar;
        }
    }
    return copy;
}

mat3 mat3::operator*(mat3 obj) const
{
    mat3 copy(0);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                copy.rows[i].columns[j] += this->rows[i].columns[k] * obj.rows[k].columns[j];
            }
        }
    }
    return copy;
}

std::ostream& operator<<(std::ostream &os, const mat3 &obj)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            os << obj.rows[i].columns[j] << " ";
        }
        os << "\n";
    }
    return os;
}

vec3& mat3::operator[](int i)
{
    return rows[i];
}
