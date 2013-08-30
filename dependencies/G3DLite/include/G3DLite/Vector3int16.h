/**
  @file Vector3int16.h
  
  @maintainer Morgan McGuire, matrix@brown.edu

  @created 2003-04-07
  @edited  2003-06-24
  Copyright 2000-2004, Morgan McGuire.
  All rights reserved.
 */

#ifndef G3DLITE_VECTOR3INT16_H
#define G3DLITE_VECTOR3INT16_H

#include "G3DLite/platform.h"
#include "G3DLite/g3dmath.h"
#include "G3DLite/HashTrait.h"

#ifdef _MSC_VER
// Turn off "conditional expression is constant" warning; MSVC generates this
// for debug assertions in inlined methods.
#pragma warning (disable : 4127)
#endif


namespace G3DLite {

/**
 \class Vector3int16
 A Vector3 that packs its fields into uint16s.
 */
G3DLITE_BEGIN_PACKED_CLASS(2)
class Vector3int16 {
private:
    // Hidden operators
    bool operator<(const Vector3int16&) const;
    bool operator>(const Vector3int16&) const;
    bool operator<=(const Vector3int16&) const;
    bool operator>=(const Vector3int16&) const;

public:
    G3DLite::int16              x;
    G3DLite::int16              y;
    G3DLite::int16              z;

    Vector3int16() : x(0), y(0), z(0) {}
    Vector3int16(G3DLite::int16 _x, G3DLite::int16 _y, G3DLite::int16 _z) : x(_x), y(_y), z(_z) {}
    Vector3int16(const class Vector3& v);
    Vector3int16(class BinaryInput& bi);

    void serialize(class BinaryOutput& bo) const;
    void deserialize(class BinaryInput& bi);

    inline G3DLite::int16& operator[] (int i) {
        debugAssert(i <= 2);
        return ((G3DLite::int16*)this)[i];
    }

    inline const G3DLite::int16& operator[] (int i) const {
        debugAssert(i <= 2);
        return ((G3DLite::int16*)this)[i];
    }

    inline Vector3int16 operator+(const Vector3int16& other) const {
        return Vector3int16(x + other.x, y + other.y, z + other.z);
    }

    inline Vector3int16 operator-(const Vector3int16& other) const {
        return Vector3int16(x - other.x, y - other.y, z - other.z);
    }

    inline Vector3int16 operator*(const Vector3int16& other) const {
        return Vector3int16(x * other.x, y * other.y, z * other.z);
    }

    inline Vector3int16 operator*(const int s) const {
        return Vector3int16(int16(x * s), int16(y * s), int16(z * s));
    }

    inline Vector3int16& operator+=(const Vector3int16& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    inline Vector3int16& operator-=(const Vector3int16& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    inline Vector3int16& operator*=(const Vector3int16& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    inline bool operator== (const Vector3int16& rkVector) const {
        return ( x == rkVector.x && y == rkVector.y && z == rkVector.z );
    }

    inline bool operator!= (const Vector3int16& rkVector) const {
        return ( x != rkVector.x || y != rkVector.y || z != rkVector.z );
    }

    Vector3int16 max(const Vector3int16& v) const {
        return Vector3int16(std::max(x, v.x), std::max(y, v.y), std::max(z, v.z));
    }

    Vector3int16 min(const Vector3int16& v) const {
        return Vector3int16(std::min(x, v.x), std::min(y, v.y), std::min(z, v.z));
    }

    std::string toString() const;
}
G3D_END_PACKED_CLASS(2)


template <> struct HashTrait<G3DLite::Vector3int16> {
    static size_t hashCode(const G3DLite::Vector3int16& key) { return static_cast<size_t>(key.x + ((int)key.y << 5) + ((int)key.z << 10)); }
};

} // namespace G3DLite

#endif