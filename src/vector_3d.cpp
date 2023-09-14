#include "vector_3d.hpp"

int Vec3d::squaredMagnitude() const { return x * x + y * y + z * z; }

Vec3d operator+(Vec3d const& a, Vec3d const& b) {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3d operator-(Vec3d const& a, Vec3d const& b) {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Vec3d operator*(Vec3d const& v, int c) { return {v.x * c, v.y * c, v.z * c}; }

// dot product
int operator*(Vec3d const& v, Vec3d const& u) {
  return v.x * u.x + v.y * u.y + v.z * u.z;
}

Vec3d operator/(Vec3d const& v, int c) { return {v.x / c, v.y / c, v.z / c}; }

// cross product
Vec3d operator^(Vec3d const& a, Vec3d const& b) {
  return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
};

std::ostream& operator<<(std::ostream& os, const Vec3d& v) {
  os << "{"
     << " " << v.x << ", " << v.y << ", " << v.z << " }";
  return os;
}

// Vec3d normalize(Vec3d &v) {
//   float magnitude = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
//   return v;
// }