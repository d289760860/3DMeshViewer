
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real>::Vector2 ()
{
    // uninitialized for performance in array construction
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real>::Vector2 (Real fX, Real fY)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real>::Vector2 (const Real* afTuple)
{
    m_afTuple[0] = afTuple[0];
    m_afTuple[1] = afTuple[1];
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real>::Vector2 (const Vector2& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real>::operator const Real* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real>::operator Real* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
template <class Real>
Real Vector2<Real>::operator[] (int i) const
{
//    assert(0 <= i && i <= 1);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
template <class Real>
Real& Vector2<Real>::operator[] (int i)
{
//    assert(0 <= i && i <= 1);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
template <class Real>
Real Vector2<Real>::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
template <class Real>
Real& Vector2<Real>::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
template <class Real>
Real Vector2<Real>::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
template <class Real>
Real& Vector2<Real>::Y ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real>& Vector2<Real>::operator= (const Vector2& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    return *this;
}
//----------------------------------------------------------------------------
template <class Real>
int Vector2<Real>::CompareArrays (const Vector2& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,2*sizeof(Real));
}
//----------------------------------------------------------------------------
template <class Real>
bool Vector2<Real>::operator== (const Vector2& rkV) const
{
    return CompareArrays(rkV) == 0;
}
//----------------------------------------------------------------------------
template <class Real>
bool Vector2<Real>::operator!= (const Vector2& rkV) const
{
    return CompareArrays(rkV) != 0;
}
//----------------------------------------------------------------------------
template <class Real>
bool Vector2<Real>::operator< (const Vector2& rkV) const
{
    return CompareArrays(rkV) < 0;
}
//----------------------------------------------------------------------------
template <class Real>
bool Vector2<Real>::operator<= (const Vector2& rkV) const
{
    return CompareArrays(rkV) <= 0;
}
//----------------------------------------------------------------------------
template <class Real>
bool Vector2<Real>::operator> (const Vector2& rkV) const
{
    return CompareArrays(rkV) > 0;
}
//----------------------------------------------------------------------------
template <class Real>
bool Vector2<Real>::operator>= (const Vector2& rkV) const
{
    return CompareArrays(rkV) >= 0;
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real> Vector2<Real>::operator+ (const Vector2& rkV) const
{
    return Vector2(
        m_afTuple[0]+rkV.m_afTuple[0],
        m_afTuple[1]+rkV.m_afTuple[1]);
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real> Vector2<Real>::operator- (const Vector2& rkV) const
{
    return Vector2(
        m_afTuple[0]-rkV.m_afTuple[0],
        m_afTuple[1]-rkV.m_afTuple[1]);
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real> Vector2<Real>::operator* (Real fScalar) const
{
    return Vector2(
        fScalar*m_afTuple[0],
        fScalar*m_afTuple[1]);
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real> Vector2<Real>::operator/ (Real fScalar) const
{
    Vector2 kQuot;

    if (fScalar != (Real)0.0)
    {
        Real fInvScalar = ((Real)1.0)/fScalar;
        kQuot.m_afTuple[0] = fInvScalar*m_afTuple[0];
        kQuot.m_afTuple[1] = fInvScalar*m_afTuple[1];
    }
    else
    {
        kQuot.m_afTuple[0] = 0;
        kQuot.m_afTuple[1] = 0;
    }

    return kQuot;
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real> Vector2<Real>::operator- () const
{
    return Vector2(
        -m_afTuple[0],
        -m_afTuple[1]);
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real> operator* (Real fScalar, const Vector2<Real>& rkV)
{
    return Vector2<Real>(
        fScalar*rkV[0],
        fScalar*rkV[1]);
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real>& Vector2<Real>::operator+= (const Vector2& rkV)
{
    m_afTuple[0] += rkV.m_afTuple[0];
    m_afTuple[1] += rkV.m_afTuple[1];
    return *this;
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real>& Vector2<Real>::operator-= (const Vector2& rkV)
{
    m_afTuple[0] -= rkV.m_afTuple[0];
    m_afTuple[1] -= rkV.m_afTuple[1];
    return *this;
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real>& Vector2<Real>::operator*= (Real fScalar)
{
    m_afTuple[0] *= fScalar;
    m_afTuple[1] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real>& Vector2<Real>::operator/= (Real fScalar)
{
    if (fScalar != (Real)0.0)
    {
        Real fInvScalar = ((Real)1.0)/fScalar;
        m_afTuple[0] *= fInvScalar;
        m_afTuple[1] *= fInvScalar;
    }
    else
    {
        m_afTuple[0] = 0;
        m_afTuple[1] = 0;
    }

    return *this;
}
//----------------------------------------------------------------------------
template <class Real>
Real Vector2<Real>::Length () const
{
    return sqrt(
        m_afTuple[0]*m_afTuple[0] +
        m_afTuple[1]*m_afTuple[1]);
}
//----------------------------------------------------------------------------
template <class Real>
Real Vector2<Real>::SquaredLength () const
{
    return
        m_afTuple[0]*m_afTuple[0] +
        m_afTuple[1]*m_afTuple[1];
}
//----------------------------------------------------------------------------
template <class Real>
Real Vector2<Real>::Dot (const Vector2& rkV) const
{
    return
        m_afTuple[0]*rkV.m_afTuple[0] +
        m_afTuple[1]*rkV.m_afTuple[1];
}
//----------------------------------------------------------------------------
template <class Real>
Real Vector2<Real>::Normalize ()
{
    Real fLength = Length();

    if (fLength > 0)
    {
        Real fInvLength = ((Real)1.0)/fLength;
        m_afTuple[0] *= fInvLength;
        m_afTuple[1] *= fInvLength;
    }
    else
    {
        fLength = (Real)0.0;
        m_afTuple[0] = (Real)0.0;
        m_afTuple[1] = (Real)0.0;
    }

    return fLength;
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real> Vector2<Real>::Perp () const
{
    return Vector2(m_afTuple[1],-m_afTuple[0]);
}
//----------------------------------------------------------------------------
template <class Real>
Vector2<Real> Vector2<Real>::UnitPerp () const
{
    Vector2 kPerp(m_afTuple[1],-m_afTuple[0]);
    kPerp.Normalize();
    return kPerp;
}
//----------------------------------------------------------------------------
template <class Real>
Real Vector2<Real>::DotPerp (const Vector2& rkV) const
{
    return m_afTuple[0]*rkV.m_afTuple[1] - m_afTuple[1]*rkV.m_afTuple[0];
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
template <class Real>
void Vector2<Real>::ComputeExtremes (int iVQuantity, const Vector2* akPoint,
    Vector2& rkMin, Vector2& rkMax)
{
    assert(iVQuantity > 0 && akPoint);

    rkMin = akPoint[0];
    rkMax = rkMin;
    for (int i = 1; i < iVQuantity; i++)
    {
        const Vector2<Real>& rkPoint = akPoint[i];
        for (int j = 0; j < 2; j++)
        {
            if (rkPoint[j] < rkMin[j])
            {
                rkMin[j] = rkPoint[j];
            }
            else if (rkPoint[j] > rkMax[j])
            {
                rkMax[j] = rkPoint[j];
            }
        }
    }
}
//----------------------------------------------------------------------------
template <class Real>
inline std::ostream& operator<< (std::ostream& rkOStr, const Vector2<Real>& rkV)
{
     return rkOStr << rkV.X() << ' ' << rkV.Y();
}
//----------------------------------------------------------------------------
template <class Real>
inline std::istream& operator >> (std::istream& rkIStr, Vector2<Real>& rkV)
{
	return rkIStr>>rkV[0]>>rkV[1];
}
//------------------------------------------------------------------------------
