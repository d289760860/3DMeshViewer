
#ifndef MIVECTOR2_H
#define MIVECTOR2_H

#include <cmath>
#include <iostream>
#include <fstream>

namespace Mi
{

template <class Real>
class Vector2
{
public:
    // construction
    Vector2 ();  // uninitialized
    Vector2 (Real fX, Real fY);
    Vector2 (const Real* afTuple);
    Vector2 (const Vector2& rkV);

    // coordinate access
    operator const Real* () const;
    operator Real* ();
    Real operator[] (int i) const;
    Real& operator[] (int i);
    Real X () const;
    Real& X ();
    Real Y () const;
    Real& Y ();

    // assignment
    Vector2& operator= (const Vector2& rkV);

    // comparison
    bool operator== (const Vector2& rkV) const;
    bool operator!= (const Vector2& rkV) const;
    bool operator<  (const Vector2& rkV) const;
    bool operator<= (const Vector2& rkV) const;
    bool operator>  (const Vector2& rkV) const;
    bool operator>= (const Vector2& rkV) const;

    // arithmetic operations
    Vector2 operator+ (const Vector2& rkV) const;
    Vector2 operator- (const Vector2& rkV) const;
    Vector2 operator* (Real fScalar) const;
    Vector2 operator/ (Real fScalar) const;
    Vector2 operator- () const;

    // arithmetic updates
    Vector2& operator+= (const Vector2& rkV);
    Vector2& operator-= (const Vector2& rkV);
    Vector2& operator*= (Real fScalar);
    Vector2& operator/= (Real fScalar);

    // vector operations
    Real Length () const;
    Real SquaredLength () const;
    Real Dot (const Vector2& rkV) const;
    Real Normalize ();

    // returns (y,-x)
    Vector2 Perp () const;

    // returns (y,-x)/sqrt(x*x+y*y)
    Vector2 UnitPerp () const;

    // returns DotPerp((x,y),(V.x,V.y)) = x*V.y - y*V.x
    Real DotPerp (const Vector2& rkV) const;

    // Compute the extreme values.
    static void ComputeExtremes (int iVQuantity, const Vector2* akPoint,
        Vector2& rkMin, Vector2& rkMax);

    // special vectors
    static const Vector2 ZERO;    // (0,0)
    static const Vector2 UNIT_X;  // (1,0)
    static const Vector2 UNIT_Y;  // (0,1)
    static const Vector2 ONE;     // (1,1)

private:
    // support for comparisons
    int CompareArrays (const Vector2& rkV) const;

    Real m_afTuple[2];
};

// arithmetic operations
template <class Real>
Vector2<Real> operator* (Real fScalar, const Vector2<Real>& rkV);

// debugging output
template <class Real>
std::ostream& operator<< (std::ostream& rkOStr, const Vector2<Real>& rkV);

template <class Real>
std::istream& operator >> (std::istream& rkIStr, Vector2<Real>& rkV );


#include "MiVector2.inl"

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector2<int> Vector2i;

}

#endif
