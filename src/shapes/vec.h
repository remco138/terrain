#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <SFML/System/Vector2.hpp> 
#include <SFML/System/Vector3.hpp> 


template<class T>
class vec2
{
public:
	T x, y;

	vec2()					: x(0), y(0) {}
	vec2(const T x, const T y)		: x(x), y(y) {}
	vec2(const vec2<T>& arg)			: x(arg.x), y(arg.y) {}
	vec2(const sf::Vector2<T>& arg): x(arg.x), y(arg.y) {} 

	double length()			{ return std::sqrt(static_cast<float>(x*x + y*y)); }

	vec2<T>& operator=(const vec2<T>& arg)	{ x = arg.x; y = arg.y; return *this; }

	vec2<T> operator+(const vec2<T>& arg)	const { return vec2<T>(x + arg.x, y + arg.y); }
	vec2<T> operator-(const vec2<T>& arg)	const { return vec2<T>(x - arg.x, y - arg.y); }
	vec2<T> operator*(const vec2<T>& arg)	const { return vec2<T>(x * arg.x, y * arg.y); }
	vec2<T> operator/(const vec2<T>& arg)	const { return vec2<T>(x / arg.x, y / arg.y); }	

	vec2<T> operator*(const float& arg)		const { return vec2<T>(x / arg, y / arg); }
	vec2<T> operator/(const float& arg)		const { return vec2<T>(x / arg, y / arg); }

	vec2<T>& operator+=(const vec2<T>& arg)	{ x += arg.x; y += arg.y; return *this; }
	vec2<T>& operator-=(const vec2<T>& arg)	{ x -= arg.x; y -= arg.y; return *this; }
	vec2<T>& operator*=(const vec2<T>& arg)	{ x *= arg.x; y *= arg.y; return *this; }
	vec2<T>& operator/=(const vec2<T>& arg)	{ x /= arg.x; y /= arg.y; return *this; }
};

template<class T> 
class vec3
{
public:
	T x, y, z;

	vec3()					: x(0), y(0), z(0) {}
	vec3(const T x, const T y, const T z)		: x(x), y(y), z(z) {}
	vec3(const vec3<T>& arg)			: x(arg.x), y(arg.y), z(arg.z) {}
 vec3(const sf::Vector3<T>& arg): x(arg.x), y(arg.y), z(arg.z) {} 

	double length()			{ return std::sqrt(static_cast<float>(x*x + y*y + z*z)); } 

	vec3<T>& operator=(const vec3<T>& arg)	{ x = arg.x; y = arg.y; z = arg.z; return *this; }

	vec3<T> operator+(const vec3<T>& arg)	const { return vec3<T>(x + arg.x, y + arg.y, z + arg.z); }
	vec3<T> operator-(const vec3<T>& arg)	const { return vec3<T>(x - arg.x, y - arg.y, z - arg.z); }
	vec3<T> operator*(const vec3<T>& arg)	const { return vec3<T>(x * arg.x, y * arg.y, z * arg.z); }
	vec3<T> operator/(const vec3<T>& arg)	const { return vec3<T>(x / arg.x, y / arg.y, z / arg.z); }	

	vec3<T> operator*(const float& arg)		const { return vec3<T>(x / arg, y / arg, z / arg); }
	vec3<T> operator/(const float& arg)		const { return vec3<T>(x / arg, y / arg, z / arg); }

	vec3<T>& operator+=(const vec3<T>& arg)	{ x += arg.x; y += arg.y; z += arg.z; return *this; }
	vec3<T>& operator-=(const vec3<T>& arg)	{ x -= arg.x; y -= arg.y; z -= arg.z; return *this; }
	vec3<T>& operator*=(const vec3<T>& arg)	{ x *= arg.x; y *= arg.y; z *= arg.z; return *this; }
	vec3<T>& operator/=(const vec3<T>& arg)	{ x /= arg.x; y /= arg.y; z /= arg.z; return *this; }
};

using vec2i = vec2<int>;
using vec2u = vec2<unsigned int>;
using vec2f = vec2<float>;
using vec3i = vec3<int>;
using vec3u = vec3<unsigned int>;
using vec3f = vec3<float>;


/*
class vec2i;
class vec2u;
class vec2f;
class vec3i;
class vec3u;
class vec3f


template<class T> 
class vec3
{
public:
	T x, y, z;

	vec3()					: x(0), y(0), z(0) {}
	vec3(T x, T y, T z)		: x(x), y(y), z(z) {}
	vec3(vec3i arg)			: x(arg.x), y(arg.y), z(arg.z) {}
	vec3(vec3u arg)			: x(arg.x), y(arg.y), z(arg.z) {}
	vec3(vec3f arg)			: x(arg.x), y(arg.y), z(arg.z) {}

	vec3(vec2i arg)			: x(arg.x), y(arg.y), z(0) {}
	vec3(vec2u arg)			: x(arg.x), y(arg.y), z(0) {}
	vec3(vec2f arg)			: x(arg.x), y(arg.y), z(0) {}

	double length()			{ return sqrt(static_cast<float>(x*x + y*y + z*z)); }

	vec3<T>& operator=(const vec3<T>& arg)	{ x = arg.x; y = arg.y; z = arg.z; return *this; }

	vec3<T> operator+(const vec3<T>& arg)	const { return vec3<T>(x + arg.x, y + arg.y, z + arg.z); }
	vec3<T> operator-(const vec3<T>& arg)	const { return vec3<T>(x - arg.x, y - arg.y, z - arg.z); }
	vec3<T> operator*(const vec3<T>& arg)	const { return vec3<T>(x * arg.x, y * arg.y, z * arg.z); }
	vec3<T> operator/(const vec3<T>& arg)	const { return vec3<T>(x / arg.x, y / arg.y, z / arg.z); }	

	vec3<T> operator*(const float& arg)		const { return vec<T>(x / arg, y / arg, z / arg); }
	vec3<T> operator/(const float& arg)		const { return vec<T>(x / arg, y / arg, z / arg); }

	vec3<T>& operator+=(const vec3<T>& arg)	{ x += arg.x; y += arg.y; z += arg.z; return *this; }
	vec3<T>& operator-=(const vec3<T>& arg)	{ x -= arg.x; y -= arg.y; z -= arg.z; return *this; }
	vec3<T>& operator*=(const vec3<T>& arg)	{ x *= arg.x; y *= arg.y; z *= arg.z; return *this; }
	vec3<T>& operator/=(const vec3<T>& arg)	{ x /= arg.x; y /= arg.y; z /= arg.z; return *this; }
};

class vec3i
{
public:
	int x, y, z;

	vec3i();
	vec3i(float x, float y, float z);
	//vec3i(vec3i arg);
	vec3i(vec3u arg);
	vec3i(vec3f arg);

	vec3i(vec2i arg);
	vec3i(vec2u arg);
	vec3i(vec2f arg);

	double length();

	vec3i& operator=(const vec3i& arg);

	vec3i operator+(const vec3i& arg) const;
	vec3i operator-(const vec3i& arg) const;
	vec3i operator*(const vec3i& arg) const;
	vec3i operator/(const vec3i& arg) const;

	vec3i operator*(const float& arg) const;
	vec3i operator/(const float& arg) const;

	vec3i& operator+=(const vec3i& arg);
	vec3i& operator-=(const vec3i& arg);
	vec3i& operator*=(const vec3i& arg);
	vec3i& operator/=(const vec3i& arg);
};

class vec3u
{
public:
	unsigned int x, y, z;

	vec3u();
	vec3u(float x, float y, float z);
	vec3u(vec3i arg);
	//vec3u(vec3u arg);
	vec3u(vec3f arg);

	vec3u(vec2i arg);
	vec3u(vec2u arg);
	vec3u(vec2f arg);

	double length();

	vec3u& operator=(const vec3u& arg);

	vec3u operator+(const vec3u& arg) const;
	vec3u operator-(const vec3u& arg) const;
	vec3u operator*(const vec3u& arg) const;
	vec3u operator/(const vec3u& arg) const;

	vec3u operator*(const float& arg) const;
	vec3u operator/(const float& arg) const;

	vec3u& operator+=(const vec3u& arg);
	vec3u& operator-=(const vec3u& arg);
	vec3u& operator*=(const vec3u& arg);
	vec3u& operator/=(const vec3u& arg);
};

class vec3f
{
public:
	float x, y, z;

	vec3f();
	vec3f(float x, float y, float z);
	vec3f(vec3i arg);
	vec3f(vec3u arg);
	//vec3f(vec3f arg);

	vec3f(vec2i arg);
	vec3f(vec2u arg);
	vec3f(vec2f arg);

	double length();
	void normalize();

	vec3f& operator=(const vec3f& arg);

	vec3f operator+(const vec3f& arg) const;
	vec3f operator-(const vec3f& arg) const;
	vec3f operator*(const vec3f& arg) const;
	vec3f operator/(const vec3f& arg) const;

	vec3f operator*(const float& arg) const;
	vec3f operator/(const float& arg) const;

	vec3f& operator+=(const vec3f& arg);
	vec3f& operator-=(const vec3f& arg);
	vec3f& operator*=(const vec3f& arg);
	vec3f& operator/=(const vec3f& arg);
};

class vec2i
{
public:
	int x, y;

	vec2i();
	vec2i(float x, float y);
	vec2i(vec3i arg);
	vec2i(vec3u arg);
	vec2i(vec3f arg);

	//vec2i(vec2i arg);
	vec2i(vec2u arg);
	vec2i(vec2f arg);
	vec2i(sf::Vector2i arg);

	double length();

	vec2i& operator=(const vec2i& arg);

	vec2i operator+(const vec2i& arg) const;
	vec2i operator-(const vec2i& arg) const;
	vec2i operator*(const vec2i& arg) const;
	vec2i operator/(const vec2i& arg) const;

	vec2i operator*(const float& arg) const;
	vec2i operator/(const float& arg) const;

	vec2i& operator+=(const vec2i& arg);
	vec2i& operator-=(const vec2i& arg);
	vec2i& operator*=(const vec2i& arg);
	vec2i& operator/=(const vec2i& arg);
};

class vec2u
{
public:
	unsigned int x, y;

	vec2u();
	vec2u(float x, float y);
	vec2u(vec3i arg);
	vec2u(vec3u arg);
	vec2u(vec3f arg);

	vec2u(vec2i arg);
	//vec2u(vec2u arg);	
	vec2u(vec2f arg);
	vec2u(sf::Vector2u arg);

	double length();

	vec2u& operator=(const vec2u& arg);

	vec2u operator+(const vec2u& arg) const;
	vec2u operator-(const vec2u& arg) const;
	vec2u operator*(const vec2u& arg) const;
	vec2u operator/(const vec2u& arg) const;

	vec2u operator*(const float& arg) const;
	vec2u operator/(const float& arg) const;

	vec2u& operator+=(const vec2u& arg);
	vec2u& operator-=(const vec2u& arg);
	vec2u& operator*=(const vec2u& arg);
	vec2u& operator/=(const vec2u& arg);
};

class vec2f
{
public:
	float x, y;

	vec2f();
	vec2f(float x, float y);
	vec2f(vec3i arg);
	vec2f(vec3u arg);
	vec2f(vec3f arg);

	vec2f(vec2i arg);
	vec2f(vec2u arg);
	//vec2f(vec2f arg);
	vec2f(sf::Vector2f arg);

	double length();

	vec2f& operator=(const vec2f& arg);

	vec2f operator+(const vec2f& arg) const;
	vec2f operator-(const vec2f& arg) const;
	vec2f operator*(const vec2f& arg) const;
	vec2f operator/(const vec2f& arg) const;

	vec2f operator*(const float& arg) const;
	vec2f operator/(const float& arg) const;

	vec2f& operator+=(const vec2f& arg);
	vec2f& operator-=(const vec2f& arg);
	vec2f& operator*=(const vec2f& arg);
	vec2f& operator/=(const vec2f& arg);
};
*/
#endif
