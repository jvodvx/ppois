#include "vector.h"
#include <cmath>

vector::vector() : x(0), y(0), z(0) {}

vector::vector(double x, double y, double z) : x(x), y(y), z(z) {}

double vector::getX() const { return x; }
double vector::getY() const { return y; }
double vector::getZ() const { return z; }

double vector::len() const {
    return sqrt(x * x + y * y + z * z);
}

vector vector::operator+(const vector& v) const {
    return vector(x + v.x, y + v.y, z + v.z);
}

vector& vector::operator+=(const vector& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vector vector::operator-() const {
    return vector(-x, -y, -z);
}

vector vector::operator-(const vector& v) const {
    return vector(x - v.x, y - v.y, z - v.z);
}

vector& vector::operator-=(const vector& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

vector vector::operator*(const vector& v) const {
    return vector(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

vector& vector::operator*=(const vector& v) {
    *this = *this * v;
    return *this;
}

vector vector::operator*(double n) const {
    return vector(x * n, y * n, z * n);
}

vector& vector::operator*=(double n) {
    x *= n;
    y *= n;
    z *= n;
    return *this;
}

vector vector::operator/(const vector& v) const {
    return vector(x / v.x, y / v.y, z / v.z);
}

vector& vector::operator/=(const vector& v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

double vector::operator^(const vector& v) const {
    return (x * v.x + y * v.y + z * v.z) / (len() * v.len());
}

vector operator*(double n, const vector& v) {
    return vector(n * v.x, n * v.y, n * v.z);
}

bool vector::operator>(const vector& v) const {
    return len() > v.len();
}

bool vector::operator>=(const vector& v) const {
    return len() >= v.len();
}

bool vector::operator<(const vector& v) const {
    return len() < v.len();
}

bool vector::operator<=(const vector& v) const {
    return len() <= v.len();
}

bool vector::operator==(const vector& v) const {
    return x == v.x && y == v.y && z == v.z;
}

bool vector::operator!=(const vector& v) const {
    return !(*this == v);
}

std::ostream& operator<<(std::ostream& os, const vector& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

std::istream& operator>>(std::istream& is, vector& v) {
    is >> v.x >> v.y >> v.z;
    return is;
}