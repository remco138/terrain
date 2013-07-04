#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <SFML/System/Vector2.hpp> 
#include <SFML/System/Vector3.hpp> 

template<class T>
class vec3;

template<class T>
class vec2
{
public:
	T x, y;

	vec2()					: x(0), y(0) {}
	vec2(const T x, const T y)		: x(x), y(y) {}
	template<class T2>
	vec2(const vec2<T2>& arg)			: x(arg.x), y(arg.y) {}
	vec2(const sf::Vector2<T>& arg): x(arg.x), y(arg.y) {} 

	double length()			{ return std::sqrt(static_cast<float>(x*x + y*y)); }

	vec3<T> addX(T arg)	{ return vec3<T>(arg, x, y); }
	vec3<T> addY(T arg)	{ return vec3<T>(x, arg, y); }
	vec3<T> addZ(T arg)	{ return vec3<T>(x, y, arg); }


	vec2<T>& operator=(const vec2<T>& arg)	{ x = arg.x; y = arg.y; return *this; }

	vec2<T> operator+(const vec2<T>& arg)	const { return vec2<T>(x + arg.x, y + arg.y); }
	vec2<T> operator-(const vec2<T>& arg)	const { return vec2<T>(x - arg.x, y - arg.y); }
	vec2<T> operator*(const vec2<T>& arg)	const { return vec2<T>(x * arg.x, y * arg.y); }
	vec2<T> operator/(const vec2<T>& arg)	const { return vec2<T>(x / arg.x, y / arg.y); }	

	vec2<T> operator*(const float& arg)		const { return vec2<T>(x * arg, y * arg); }
	vec2<T> operator/(const float& arg)		const { return vec2<T>(x / arg, y / arg); }
	vec2<T> operator+(const float& arg)		const { return vec2<T>(x + arg, y + arg); }
	vec2<T> operator-(const float& arg)		const { return vec2<T>(x - arg, y - arg); }

	vec2<T>& operator+=(const vec2<T>& arg)	{ x += arg.x; y += arg.y; return *this; }
	vec2<T>& operator-=(const vec2<T>& arg)	{ x -= arg.x; y -= arg.y; return *this; }
	vec2<T>& operator*=(const vec2<T>& arg)	{ x *= arg.x; y *= arg.y; return *this; }
	vec2<T>& operator/=(const vec2<T>& arg)	{ x /= arg.x; y /= arg.y; return *this; }

	vec2<T> operator*=(const float& arg)	const { return vec2<T>(x *= arg, y *= arg); }
	vec2<T> operator/=(const float& arg)	const { return vec2<T>(x /= arg, y /= arg); }
	vec2<T> operator+=(const float& arg)	const { return vec2<T>(x += arg, y += arg); }
	vec2<T> operator-=(const float& arg)	const { return vec2<T>(x -= arg, y -= arg); }
};

template<class T> 
class vec3
{
public:
	T x, y, z;

	vec3()									: x(0), y(0), z(0) {}
	vec3(const T x, const T y, const T z)	: x(x), y(y), z(z) {}
	template<class T2>
	vec3(const vec3<T2>& arg)				: x(arg.x), y(arg.y), z(arg.z) {}
	vec3(const sf::Vector3<T>& arg)			: x(arg.x), y(arg.y), z(arg.z) {} 

	double length()			{ return std::sqrt(std::abs(static_cast<float>(x*x + y*y + z*z))); } 

	vec2<T> removeX()	{ return vec2<T>(y, z); }
	vec2<T> removeY()	{ return vec2<T>(x, z); }
	vec2<T> removeZ()	{ return vec2<T>(x, y); }

	vec3<T>& operator=(const vec3<T>& arg)	{ x = arg.x; y = arg.y; z = arg.z; return *this; }

	vec3<T> operator+(const vec3<T>& arg)	const { return vec3<T>(x + arg.x, y + arg.y, z + arg.z); }
	vec3<T> operator-(const vec3<T>& arg)	const { return vec3<T>(x - arg.x, y - arg.y, z - arg.z); }
	vec3<T> operator*(const vec3<T>& arg)	const { return vec3<T>(x * arg.x, y * arg.y, z * arg.z); }
	vec3<T> operator/(const vec3<T>& arg)	const { return vec3<T>(x / arg.x, y / arg.y, z / arg.z); }	

	vec3<T> operator*(const float& arg)		const { return vec3<T>(x * arg, y * arg, z * arg); }
	vec3<T> operator/(const float& arg)		const { return vec3<T>(x / arg, y / arg, z / arg); }
	vec3<T> operator+(const float& arg)		const { return vec3<T>(x + arg, y + arg, z + arg); }
	vec3<T> operator-(const float& arg)		const { return vec3<T>(x - arg, y - arg, z - arg); }

	vec3<T>& operator+=(const vec3<T>& arg)	{ x += arg.x; y += arg.y; z += arg.z; return *this; }
	vec3<T>& operator-=(const vec3<T>& arg)	{ x -= arg.x; y -= arg.y; z -= arg.z; return *this; }
	vec3<T>& operator*=(const vec3<T>& arg)	{ x *= arg.x; y *= arg.y; z *= arg.z; return *this; }
	vec3<T>& operator/=(const vec3<T>& arg)	{ x /= arg.x; y /= arg.y; z /= arg.z; return *this; }

	vec3<T> operator*=(const float& arg)		const { return vec3<T>(x *= arg, y *= arg, z *= arg); }
	vec3<T> operator/=(const float& arg)		const { return vec3<T>(x /= arg, y /= arg, z /= arg); }
	vec3<T> operator+=(const float& arg)		const { return vec3<T>(x += arg, y += arg, z += arg); }
	vec3<T> operator-=(const float& arg)		const { return vec3<T>(x -= arg, y -= arg, z -= arg); }
};

typedef  vec2<int>			vec2i;
typedef  vec2<unsigned int>	vec2u;
typedef  vec2<float>		vec2f;
typedef  vec3<int>			vec3i;
typedef  vec3<unsigned int>	vec3u;
typedef  vec3<float>		vec3f;
/*
if -std=c++11
using vec2i = vec2<int>;
using vec2u = vec2<unsigned int>;
using vec2f = vec2<float>;
using vec3i = vec3<int>;
using vec3u = vec3<unsigned int>;
using vec3f = vec3<float>;
endif
*/
#endif
