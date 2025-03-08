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
protected:
public:
    float columns[3];
    float x, y, z;

    //  Fill with 0 if no parameters
    vec3()
    {
        for (int i = 0; i < 3; i++)
        {
            columns[i] = 0;
        }

        x = columns[0];
        y = columns[1];
        z = columns[2];
    }
    // Fill with paramter value
    vec3(float initializer)
    {
        for (int i = 0; i < 3; i++)
        {
            columns[i] = initializer;
        }
        x = columns[0];
        y = columns[1];
        z = columns[2];
    }
    // Custom values
    vec3(float x, float y, float z)
    {
        columns[0] = x;
        columns[1] = y;
        columns[2] = z;

        this->x = columns[0];
        this->y = columns[1];
        this->z = columns[2];
    }

    // For Identity Matrix
    void identity(int j)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == j)
                columns[i] = 1;
            else
                columns[i] = 0;
        }

        x = columns[0];
        y = columns[1];
        z = columns[2];
    }

    // Operators
    friend std::ostream& operator<<(std::ostream &os, const vec3 &obj)
    {
        for (int i = 0; i < 3; i++)
        {
            os << obj.columns[i] << " ";
        }
        os << "\n";
        return os;
    }

    vec3& operator*(float scalar)
    {
        vec3 copy;
        for (int i = 0; i < 3; i++)
        {
            copy.columns[i] = (*this).columns[i] * scalar;
        }
        return copy;
    }

    vec3& operator-(vec3 other)
    {
        vec3 copy;
        copy.columns[0] = (*this).columns[0] - other.columns[0];
        copy.columns[1] = (*this).columns[1] - other.columns[1];
        copy.columns[2] = (*this).columns[2] - other.columns[2];
        return copy;
    }
    vec3 &operator+(vec3 other)
    {
        vec3 copy;
        copy.columns[0] = (*this).columns[0] + other.columns[0];
        copy.columns[1] = (*this).columns[1] + other.columns[1];
        copy.columns[2] = (*this).columns[2] + other.columns[2];
        return copy;
    }

    float& operator[](int i)
    {
        return columns[i];
    }

    vec3 &operator->()
    {
        return *this;
    }
};

class mat3
{
private:
public:
    vec3 rows[3];

    // Identity
    mat3()
    {
        for (int i = 0; i < 3; i++)
        {
            vec3 ident(0);
            ident.identity(i);
            rows[i] = ident;
        }
    }

    // Fill with values
    mat3(float initalizer)
    {

        for (int i = 0; i < 3; i++)
        {
            rows[i] = vec3(initalizer);
        }
    }

    // Matrix Operations
    void transpose()
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

    mat3& translate(float x, float y)
    {
        (*this).rows[0].columns[2] += x;
        (*this).rows[1].columns[2] += y;

        return (*this);
    }

    mat3& inverse()
    {
        // Zero matrix to start
        mat3 inv(0);

        double det = (*this).rows[0].columns[0] * ((*this).rows[1].columns[1] * (*this).rows[2].columns[2] - (*this).rows[2].columns[1] * (*this).rows[1].columns[2]) -
                     (*this).rows[0].columns[1] * ((*this).rows[1].columns[0] * (*this).rows[2].columns[2] - (*this).rows[1].columns[2] * (*this).rows[2].columns[0]) +
                     (*this).rows[0].columns[2] * ((*this).rows[1].columns[0] * (*this).rows[2].columns[1] - (*this).rows[1].columns[1] * (*this).rows[2].columns[0]);

        double invdet = 1 / det;

        inv.rows[0].columns[0] = ((*this).rows[1].columns[1] *  (*this).rows[2].columns[2] -  (*this).rows[2].columns[1] *  (*this).rows[1].columns[2]) * invdet;
        inv.rows[0].columns[1] = ((*this).rows[0].columns[2] *  (*this).rows[2].columns[1] -  (*this).rows[0].columns[1] *  (*this).rows[2].columns[2]) * invdet;
        inv.rows[0].columns[2] = ((*this).rows[0].columns[1] * (*this).rows[1].columns[2] - (*this).rows[0].columns[2] * (*this).rows[1].columns[1]) * invdet;

        inv.rows[1].columns[0] = ((*this).rows[1].columns[2] *  (*this).rows[2].columns[0] -  (*this).rows[1].columns[0] *  (*this).rows[2].columns[2]) * invdet;
        inv.rows[1].columns[1] = ((*this).rows[0].columns[0] * (*this).rows[2].columns[2] - (*this).rows[0].columns[2] * (*this).rows[2].columns[0]) * invdet;
        inv.rows[1].columns[2] = ((*this).rows[1].columns[0] *  (*this).rows[0].columns[2] -  (*this).rows[0].columns[0] *  (*this).rows[1].columns[2]) * invdet;

        inv.rows[2].columns[0] = ((*this).rows[1].columns[0] * (*this).rows[2].columns[1] - (*this).rows[2].columns[0] * (*this).rows[1].columns[1]) * invdet;
        inv.rows[2].columns[1] = ((*this).rows[2].columns[0] *  (*this).rows[0].columns[2] -  (*this).rows[0].columns[0] *  (*this).rows[2].columns[1]) * invdet;
        inv.rows[2].columns[2] = ((*this).rows[0].columns[0] * (*this).rows[1].columns[1] - (*this).rows[1].columns[0] * (*this).rows[0].columns[1]) * invdet;

        return inv;
    }

    void rotateAronud()
    {
    }

    //Specifies the bonuds for the orthographic projection
    mat3& orthographic(float lBound, float rBound, float bBound, float tBound){
        mat3 ortho;

        ortho[0][0] = 2 / (rBound - lBound);
        ortho[1][1] = 2 / (tBound - bBound);

        ortho[0][2] = -(rBound + lBound) / (rBound - lBound);
        ortho[1][2] = -(tBound + bBound) / (tBound - bBound);

        return ortho;
    }

    float *valuePtr()
    {
        static float values[3][3];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                values[i][j] = rows[i].columns[j];
            }
        }
        return values[0];
    }

    // Operators
    friend std::ostream &operator<<(std::ostream &os, const mat3 &obj)
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

    mat3 &operator*(float scalar)
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

    // Dot product 
    mat3& operator*(mat3 obj)
    {
        mat3 copy(0);

        for (int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    copy.rows[i].columns[j] += (*this).rows[i].columns[k] * obj.rows[k].columns[j];
                }
            }
        }
        return copy;
    }

    // mat * vec        BAD
    mat3& operator*(vec3 obj)
    {
        mat3 copy;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                copy.rows[i].columns[j] += (*this).rows[i].columns[j];
            }
        }
        return copy;
    }

    //  Indexing
    vec3& operator[](int i)
    {
        return rows[i];
    }

    friend vec2& clipSpace(float lBound, float rBound, float bBound, float tBound, float x, float y)
    {
        vec2 clip;
    }
};



