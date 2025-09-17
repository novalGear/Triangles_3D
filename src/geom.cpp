#include "geometry.hpp"

point3D::point3D (float x, float y, float z): x_(x), y_(y), z_(z) {}

float point3D::get_x() { return x_; }
float point3D::get_y() { return y_; }
float point3D::get_z() { return z_; }

void point3D::invalidate() {
    x_ = NAN;
    y_ = NAN;
    z_ = NAN;
}

vec3D::vec3D (const point3D& a, const point3D& b):
    x_(b.get_x() - a.get_x()),
    y_(b.get_y() - a.get_y()),
    z_(b.get_z() - a.get_z()) {}

float vec3D::get_x() { return x_; }
float vec3D::get_y() { return y_; }
float vec3D::get_z() { return z_; }

void vec3D::invalidate() {
    x_ = NAN;
    y_ = NAN;
    z_ = NAN;
}

vec3D
vector_product(const vec3D& A, const vec3D& B) {
    float x1 = A.get_x(), y1 = A.get_y(), z1 = A.get_z();
    float x2 = B.get_x(), y2 = B.get_y(), z2 = B.get_z();

    vec3D vector_res(
        y1 * z2 - z1 * y2,
        z1 * x2 - x1 * z2,
        x1 * y2 - y1 * x2
    );
    return vec3D;
}

float
scalar_product(const vec3D& A, const vec3D& B) {
    float scalar_res = A.get_x() * B.get_x() + A.get_y() * B.get_y() + A.get_z() * B.get_z();
}
