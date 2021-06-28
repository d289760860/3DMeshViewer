
#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>
#include <fstream>
#include <cassert>

namespace Mi
{
	
template <class Real>
class Vector3
{
public:
    // construction
    Vector3 ();  // uninitialized
    Vector3 (Real fX, Real fY, Real fZ);
    Vector3 (const Real* afTuple);
    Vector3 (const Vector3& rkV);

    // coordinate access
    operator const Real* () const;
    operator Real* ();
    Real operator[] (int i) const;
    Real& operator[] (int i);
    Real X () const;
    Real& X ();
    Real Y () const;
    Real& Y ();
    Real Z () const;
    Real& Z ();

    // assignment
    Vector3& operator= (const Vector3& rkV);

    // comparison
    bool operator== (const Vector3& rkV) const;
    bool operator!= (const Vector3& rkV) const;
    bool operator<  (const Vector3& rkV) const;
    bool operator<= (const Vector3& rkV) const;
    bool operator>  (const Vector3& rkV) const;
    bool operator>= (const Vector3& rkV) const;

    // arithmetic operations
    Vector3 operator+ (const Vector3& rkV) const;
    Vector3 operator- (const Vector3& rkV) const;
    Vector3 operator* (Real fScalar) const;
    Vector3 operator/ (Real fScalar) const;
    Vector3 operator- () const;

    // arithmetic updates
    Vector3& operator+= (const Vector3& rkV);
    Vector3& operator-= (const Vector3& rkV);
    Vector3& operator*= (Real fScalar);
    Vector3& operator/= (Real fScalar);

    // vector operations
    Real Length () const;
    Real SquaredLength () const;
    Real Dot (const Vector3& rkV) const;
    Real Normalize ();

    // The cross products are computed using the right-handed rule.  Be aware
    // that some graphics APIs use a left-handed rule.  If you have to compute
    // a cross product with these functions and send the result to the API
    // that expects left-handed, you will need to change sign on the vector
    // (replace each component value c by -c).
    Vector3 Cross (const Vector3& rkV) const;
    Vector3 UnitCross (const Vector3& rkV) const;

    // Compute the extreme values.
    static void ComputeExtremes (int iVQuantity, const Vector3* akPoint,
        Vector3& rkMin, Vector3& rkMax);

    // special vectors
    static const Vector3 ZERO;    // (0,0,0)
    static const Vector3 UNIT_X;  // (1,0,0)
    static const Vector3 UNIT_Y;  // (0,1,0)
    static const Vector3 UNIT_Z;  // (0,0,1)
    static const Vector3 ONE;     // (1,1,1)

private:
    // support for comparisons
    int CompareArrays (const Vector3& rkV) const;

    Real m_afTuple[3];
};

// arithmetic operations
template <class Real>
Vector3<Real> operator* (Real fScalar, const Vector3<Real>& rkV);

// debugging output
template <class Real>
std::ostream& operator<< (std::ostream& rkOStr, const Vector3<Real>& rkV);

template <class Real>
std::istream& operator >> (std::istream& rkIStr, Vector3<Real>& rkV );

#include "MiVector3.inl"

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;
typedef Vector3<unsigned char> Vector3uc;
typedef Vector3<int> Vector3i;

}
#endif
