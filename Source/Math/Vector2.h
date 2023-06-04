#pragma once

#include "CoreTypes.h"
#include "Templates/IsFloatingPoint.h"

namespace Rt::Math
{
	template<typename T>
	struct Vector2
	{
		static_assert(Rt::Templates::IsFloatingPoint<T>);

		union
		{
			struct
			{
				T X;
				T Y;
			};

			T XY[2];
		};

		FORCEINLINE Vector2<T>() { }
		FORCEINLINE Vector2<T>(T InX, T InY);
		explicit FORCEINLINE Vector2<T>(T InF);

		FORCEINLINE T& Component(int32 Index);
		FORCEINLINE T Component(int32 Index) const;

		FORCEINLINE Vector2<T> operator+(const Vector2<T>& V) const;
		FORCEINLINE Vector2<T> operator-(const Vector2<T>& V) const;
		FORCEINLINE Vector2<T> operator*(const Vector2<T>& V) const;
		FORCEINLINE Vector2<T> operator/(const Vector2<T>& V) const;

		FORCEINLINE Vector2<T> operator+=(const Vector2<T>& V);
		FORCEINLINE Vector2<T> operator-=(const Vector2<T>& V);
		FORCEINLINE Vector2<T> operator*=(const Vector2<T>& V);
		FORCEINLINE Vector2<T> operator/=(const Vector2<T>& V);

		FORCEINLINE Vector2<T> operator*=(T Scale);
		FORCEINLINE Vector2<T> operator/=(T Scale);

		FORCEINLINE Vector2<T> operator+(T A) const;
		FORCEINLINE Vector2<T> operator-(T A) const;
		FORCEINLINE Vector2<T> operator*(T Scale) const;
		FORCEINLINE Vector2<T> operator/(T Scale) const;

		FORCEINLINE bool operator==(const Vector2<T>& V) const;
		FORCEINLINE bool operator!=(const Vector2<T>& V) const;

		FORCEINLINE T operator|(const Vector2<T>& V) const;
		FORCEINLINE T operator^(const Vector2<T>& V) const;

		FORCEINLINE Vector2<T> operator-() const;
	};

	template<typename T>
	Vector2<T>::Vector2(T InX, T InY)
		: X(InX)
		, Y(InY)
	{ }

	template<typename T>
	Vector2<T>::Vector2(T InF)
		: X(InF)
		, Y(InF)
	{ }

	template<typename T>
	T& Vector2<T>::Component(int32 Index) { return XY[Index]; }

	template<typename T>
	T Vector2<T>::Component(int32 Index) const { return XY[Index]; }

	template<typename T> Vector2<T> Vector2<T>::operator+(const Vector2<T>& V) const { return Vector2<T>(X + V.X, Y + V.Y); }
	template<typename T> Vector2<T> Vector2<T>::operator-(const Vector2<T>& V) const { return Vector2<T>(X - V.X, Y - V.Y); }
	template<typename T> Vector2<T> Vector2<T>::operator*(const Vector2<T>& V) const { return Vector2<T>(X * V.X, Y * V.Y); }
	template<typename T> Vector2<T> Vector2<T>::operator/(const Vector2<T>& V) const { return Vector2<T>(X / V.X, Y / V.Y); }

	template<typename T> Vector2<T> Vector2<T>::operator+=(const Vector2<T>& V) { X += V.X; Y += V.Y; return *this; }
	template<typename T> Vector2<T> Vector2<T>::operator-=(const Vector2<T>& V) { X -= V.X; Y -= V.Y; return *this; }
	template<typename T> Vector2<T> Vector2<T>::operator*=(const Vector2<T>& V) { X *= V.X; Y *= V.Y; return *this; }
	template<typename T> Vector2<T> Vector2<T>::operator/=(const Vector2<T>& V) { X /= V.X; Y /= V.Y; return *this; }

	template<typename T> Vector2<T> Vector2<T>::operator*=(T Scale) { X *= Scale; Y *= Scale; return *this; }
	template<typename T> Vector2<T> Vector2<T>::operator/=(T Scale) { X /= Scale; Y /= Scale; return *this; }

	template<typename T> Vector2<T> Vector2<T>::operator+(T A) const { return Vector2<T>(X + A, Y + A); }
	template<typename T> Vector2<T> Vector2<T>::operator-(T A) const { return Vector2<T>(X - A, Y - A); }
	template<typename T> Vector2<T> Vector2<T>::operator*(T Scale) const { return Vector2<T>(X * Scale, Y * Scale); }
	template<typename T> Vector2<T> Vector2<T>::operator/(T Scale) const { return Vector2<T>(X / Scale, Y / Scale); }

	template<typename T> bool Vector2<T>::operator==(const Vector2<T>& V) const { return X == V.X && Y == V.Y; }
	template<typename T> bool Vector2<T>::operator!=(const Vector2<T>& V) const { return X != V.X && Y != V.Y; }

	template<typename T> T Vector2<T>::operator|(const Vector2<T>& V) const { return X * V.X + Y * V.Y; }
	template<typename T> T Vector2<T>::operator^(const Vector2<T>& V) const { return X * V.Y - Y * V.X; }

	template<typename T> Vector2<T> Vector2<T>::operator-() const { return Vector2<T>(-X, -Y); }
}

typedef Rt::Math::Vector2<float> Vector2f;
typedef Rt::Math::Vector2<double> Vector2d;
