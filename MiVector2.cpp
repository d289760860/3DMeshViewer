

#include "MiVector2.h"

using namespace Mi;

template<> const Vector2<float> Vector2<float>::ZERO(0.0f,0.0f);
template<> const Vector2<float> Vector2<float>::UNIT_X(1.0f,0.0f);
template<> const Vector2<float> Vector2<float>::UNIT_Y(0.0f,1.0f);
template<> const Vector2<float> Vector2<float>::ONE(1.0f,1.0f);

template<> const Vector2<double> Vector2<double>::ZERO(0.0,0.0);
template<> const Vector2<double> Vector2<double>::UNIT_X(1.0,0.0);
template<> const Vector2<double> Vector2<double>::UNIT_Y(0.0,1.0);
template<> const Vector2<double> Vector2<double>::ONE(1.0,1.0);
