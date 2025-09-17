#pragma once

class point3D {
private:
    float x_ = NAN;
    float y_ = NAN;
    float z_ = NAN;

public:
    point3D (float x, float y, float z);
    /**
     * Get the corresponding coordinate of the point
     * @retval corresponding coordinate of the point
     */
    float get_x();
    float get_y();
    float get_z();
    /**
     * Set all coordinates of the point to NAN
     */
    void invalidate();
}

class Polygon3D {
private:
    std::vector<point3D> vertices[6];
public:
    /**
     * Add a vertice to polygon
     * @param  new_vertice new vertice to add
     */
    void add_vertice(const point3D& new_vertice);
    /**
     * Remove vertice by index
     * @param index index of vertice to remove
    */
    void remove_vertice_at(uint32_t index);
}

class vec3D {
private:
    float x_ = NAN;
    float y_ = NAN;
    float z_ = NAN;
public:
    point3D (const point3D& a, const point3D& b);
    /**
     * Get the corresponding coordinate of the point
     * @retval corresponding coordinate of the point
     */
    float get_x();
    float get_y();
    float get_z();
    /**
     * Set all coordinates of the point to NAN
     */
    void invalidate();
}

vec3D
vector_product(const vec3D& A, const vec3D& B);

float
scalar_product(const vec3D& A, const vec3D& B);
