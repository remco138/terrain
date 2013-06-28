#include "vec.h"

//--------------------------vec3i
	vec3i::vec3i()							: x(0), y(0), z(0) {}
	vec3i::vec3i(float x, float y, float z)	: x(x), y(y), z(z) {}
	//vec3i::vec3i(vec3i arg)					: x(arg.x), y(arg.y), z(arg.z) {}
	vec3i::vec3i(vec3u arg)					: x(arg.x), y(arg.y), z(arg.z) {}
	vec3i::vec3i(vec3f arg)					: x(arg.x), y(arg.y), z(arg.z) {}

	vec3i::vec3i(vec2i arg)					: x(arg.x), y(arg.y), z(0) {}
	vec3i::vec3i(vec2u arg)					: x(arg.x), y(arg.y), z(0) {}
	vec3i::vec3i(vec2f arg)					: x(arg.x), y(arg.y), z(0) {}

	double vec3i::length()						{ return sqrt(static_cast<float>(x*x + y*y + z*z)); }

	vec3i& vec3i::operator=(const vec3i& arg)	{ x = arg.x; y = arg.y; z = arg.z; return *this; }

	vec3i vec3i::operator+(const vec3i& arg)	const { return vec3i(x + arg.x, y + arg.y, z + arg.z); }
	vec3i vec3i::operator-(const vec3i& arg)	const { return vec3i(x - arg.x, y - arg.y, z - arg.z); }
	vec3i vec3i::operator*(const vec3i& arg)	const { return vec3i(x * arg.x, y * arg.y, z * arg.z); }
	vec3i vec3i::operator/(const vec3i& arg)	const { return vec3i(x / arg.x, y / arg.y, z / arg.z); }

	vec3i vec3i::operator*(const float& arg)	const { return vec3i(x * arg, y * arg, z * arg); }
	vec3i vec3i::operator/(const float& arg)	const { return vec3i(x / arg, y / arg, z / arg); }

	vec3i& vec3i::operator+=(const vec3i& arg)	{ x += arg.x; y += arg.y; z += arg.z; return *this; }
	vec3i& vec3i::operator-=(const vec3i& arg)	{ x -= arg.x; y -= arg.y; z -= arg.z; return *this; }
	vec3i& vec3i::operator*=(const vec3i& arg)	{ x *= arg.x; y *= arg.y; z *= arg.z; return *this; }
	vec3i& vec3i::operator/=(const vec3i& arg)	{ x /= arg.x; y /= arg.y; z /= arg.z; return *this; }

	
//--------------------------vec3u
	vec3u::vec3u()							: x(0), y(0), z(0) {}
	vec3u::vec3u(float x, float y, float z)	: x(x), y(y), z(z) {}
	vec3u::vec3u(vec3i arg)					: x(arg.x), y(arg.y), z(arg.z) {}
	//vec3u::vec3u(vec3u arg)					: x(arg.x), y(arg.y), z(arg.z) {}
	vec3u::vec3u(vec3f arg)					: x(arg.x), y(arg.y), z(arg.z) {}

	vec3u::vec3u(vec2i arg)					: x(arg.x), y(arg.y), z(0) {}
	vec3u::vec3u(vec2u arg)					: x(arg.x), y(arg.y), z(0) {}
	vec3u::vec3u(vec2f arg)					: x(arg.x), y(arg.y), z(0) {}

	double vec3u::length()						{ return sqrtf(x*x + y*y + z*z); }

	vec3u& vec3u::operator=(const vec3u& arg)	{ x = arg.x; y = arg.y; z = arg.z; return *this; }

	vec3u vec3u::operator+(const vec3u& arg)	const { return vec3u(x + arg.x, y + arg.y, z + arg.z); }
	vec3u vec3u::operator-(const vec3u& arg)	const { return vec3u(x - arg.x, y - arg.y, z - arg.z); }
	vec3u vec3u::operator*(const vec3u& arg)	const { return vec3u(x * arg.x, y * arg.y, z * arg.z); }
	vec3u vec3u::operator/(const vec3u& arg)	const { return vec3u(x / arg.x, y / arg.y, z / arg.z); }	

	vec3u vec3u::operator*(const float& arg)	const { return vec3u(x * arg, y * arg, z * arg); }
	vec3u vec3u::operator/(const float& arg)	const { return vec3u(x / arg, y / arg, z / arg); }

	vec3u& vec3u::operator+=(const vec3u& arg)	{ x += arg.x; y += arg.y; z += arg.z; return *this; }
	vec3u& vec3u::operator-=(const vec3u& arg)	{ x -= arg.x; y -= arg.y; z -= arg.z; return *this; }
	vec3u& vec3u::operator*=(const vec3u& arg)	{ x *= arg.x; y *= arg.y; z *= arg.z; return *this; }
	vec3u& vec3u::operator/=(const vec3u& arg)	{ x /= arg.x; y /= arg.y; z /= arg.z; return *this; }

	
//--------------------------vec3f
	vec3f::vec3f()							: x(0), y(0), z(0) {}
	vec3f::vec3f(float x, float y, float z)	: x(x), y(y), z(z) {}
	vec3f::vec3f(vec3i arg)					: x(arg.x), y(arg.y), z(arg.z) {}
	vec3f::vec3f(vec3u arg)					: x(arg.x), y(arg.y), z(arg.z) {}
	//vec3f::vec3f(vec3f arg)					: x(arg.x), y(arg.y), z(arg.z) {}

	vec3f::vec3f(vec2i arg)					: x(arg.x), y(arg.y), z(0) {}
	vec3f::vec3f(vec2u arg)					: x(arg.x), y(arg.y), z(0) {}
	vec3f::vec3f(vec2f arg)					: x(arg.x), y(arg.y), z(0) {}

	double	vec3f::length()						{ return sqrtf(x*x + y*y + z*z); }
	void	vec3f::normalize()					{ float len = this->length(); x /= len; y/= len; z/= len; }

	vec3f& vec3f::operator=(const vec3f& arg)	{ x = arg.x; y = arg.y; z = arg.z; return *this; }

	vec3f vec3f::operator+(const vec3f& arg)	const { return vec3f(x + arg.x, y + arg.y, z + arg.z); }
	vec3f vec3f::operator-(const vec3f& arg)	const { return vec3f(x - arg.x, y - arg.y, z - arg.z); }
	vec3f vec3f::operator*(const vec3f& arg)	const { return vec3f(x * arg.x, y * arg.y, z * arg.z); }
	vec3f vec3f::operator/(const vec3f& arg)	const { return vec3f(x / arg.x, y / arg.y, z / arg.z); }	

	vec3f vec3f::operator*(const float& arg)	const { return vec3f(x * arg, y * arg, z * arg); }
	vec3f vec3f::operator/(const float& arg)	const { return vec3f(x / arg, y / arg, z / arg); }

	vec3f& vec3f::operator+=(const vec3f& arg)	{ x += arg.x; y += arg.y; z += arg.z; return *this; }
	vec3f& vec3f::operator-=(const vec3f& arg)	{ x -= arg.x; y -= arg.y; z -= arg.z; return *this; }
	vec3f& vec3f::operator*=(const vec3f& arg)	{ x *= arg.x; y *= arg.y; z *= arg.z; return *this; }
	vec3f& vec3f::operator/=(const vec3f& arg)	{ x /= arg.x; y /= arg.y; z /= arg.z; return *this; }

//--------------------------vec2i
	vec2i::vec2i()							: x(0), y(0) {}
	vec2i::vec2i(float x, float y)			: x(x), y(y) {}
	vec2i::vec2i(vec3i arg)					: x(arg.x), y(arg.y) {}
	vec2i::vec2i(vec3u arg)					: x(arg.x), y(arg.y) {}
	vec2i::vec2i(vec3f arg)					: x(arg.x), y(arg.y) {}

	//vec2i::vec2i(vec2i arg)					: x(arg.x), y(arg.y) {}
	vec2i::vec2i(vec2u arg)					: x(arg.x), y(arg.y) {}
	vec2i::vec2i(vec2f arg)					: x(arg.x), y(arg.y) {}
	vec2i::vec2i(sf::Vector2i arg)			: x(arg.x), y(arg.y) {}

	double vec2i::length()						{ return sqrtf(x*x + y*y); }

	vec2i& vec2i::operator=(const vec2i& arg)	{ x = arg.x; y = arg.y; return *this; }

	vec2i vec2i::operator+(const vec2i& arg)	const { return vec2i(x + arg.x, y + arg.y); }
	vec2i vec2i::operator-(const vec2i& arg)	const { return vec2i(x - arg.x, y - arg.y); }
	vec2i vec2i::operator*(const vec2i& arg)	const { return vec2i(x * arg.x, y * arg.y); }
	vec2i vec2i::operator/(const vec2i& arg)	const { return vec2i(x / arg.x, y / arg.y); }	

	vec2i vec2i::operator*(const float& arg)	const { return vec2i(x * arg, y * arg); }
	vec2i vec2i::operator/(const float& arg)	const { return vec2i(x / arg, y / arg); }

	vec2i& vec2i::operator+=(const vec2i& arg)	{ x += arg.x; y += arg.y; return *this; }
	vec2i& vec2i::operator-=(const vec2i& arg)	{ x -= arg.x; y -= arg.y; return *this; }
	vec2i& vec2i::operator*=(const vec2i& arg)	{ x *= arg.x; y *= arg.y; return *this; }
	vec2i& vec2i::operator/=(const vec2i& arg)	{ x /= arg.x; y /= arg.y; return *this; }

//--------------------------vec2u
	vec2u::vec2u()							: x(0), y(0) {}
	vec2u::vec2u(float x, float y)			: x(x), y(y) {}
	vec2u::vec2u(vec3i arg)					: x(arg.x), y(arg.y) {}
	vec2u::vec2u(vec3u arg)					: x(arg.x), y(arg.y) {}
	vec2u::vec2u(vec3f arg)					: x(arg.x), y(arg.y) {}

	vec2u::vec2u(vec2i arg)					: x(arg.x), y(arg.y) {}
	//vec2u::vec2u(vec2u arg)					: x(arg.x), y(arg.y) {}
	vec2u::vec2u(vec2f arg)					: x(arg.x), y(arg.y) {}
	vec2u::vec2u(sf::Vector2u arg)			: x(arg.x), y(arg.y) {}

	double vec2u::length()						{ return sqrtf(x*x + y*y); }

	vec2u& vec2u::operator=(const vec2u& arg)	{ x = arg.x; y = arg.y; return *this; }

	vec2u vec2u::operator+(const vec2u& arg)	const { return vec2u(x + arg.x, y + arg.y); }
	vec2u vec2u::operator-(const vec2u& arg)	const { return vec2u(x - arg.x, y - arg.y); }
	vec2u vec2u::operator*(const vec2u& arg)	const { return vec2u(x * arg.x, y * arg.y); }
	vec2u vec2u::operator/(const vec2u& arg)	const { return vec2u(x / arg.x, y / arg.y); }	

	vec2u vec2u::operator*(const float& arg)	const { return vec2u(x * arg, y * arg); }
	vec2u vec2u::operator/(const float& arg)	const { return vec2u(x / arg, y / arg); }

	vec2u& vec2u::operator+=(const vec2u& arg)	{ x += arg.x; y += arg.y; return *this; }
	vec2u& vec2u::operator-=(const vec2u& arg)	{ x -= arg.x; y -= arg.y; return *this; }
	vec2u& vec2u::operator*=(const vec2u& arg)	{ x *= arg.x; y *= arg.y; return *this; }
	vec2u& vec2u::operator/=(const vec2u& arg)	{ x /= arg.x; y /= arg.y; return *this; }

//--------------------------vec2f
	vec2f::vec2f()							: x(0), y(0) {}
	vec2f::vec2f(float x, float y)			: x(x), y(y) {}
	vec2f::vec2f(vec3i arg)					: x(arg.x), y(arg.y) {}
	vec2f::vec2f(vec3u arg)					: x(arg.x), y(arg.y) {}
	vec2f::vec2f(vec3f arg)					: x(arg.x), y(arg.y) {}

	vec2f::vec2f(vec2i arg)					: x(arg.x), y(arg.y) {}
	vec2f::vec2f(vec2u arg)					: x(arg.x), y(arg.y) {}
	//vec2f::vec2f(vec2f arg)					: x(arg.x), y(arg.y) {}
	vec2f::vec2f(sf::Vector2f arg)			: x(arg.x), y(arg.y) {}

	double vec2f::length()						{ return sqrtf(x*x + y*y); }

	vec2f& vec2f::operator=(const vec2f& arg)	{ x = arg.x; y = arg.y; return *this; }

	vec2f vec2f::operator+(const vec2f& arg)	const { return vec2f(x + arg.x, y + arg.y); }
	vec2f vec2f::operator-(const vec2f& arg)	const { return vec2f(x - arg.x, y - arg.y); }
	vec2f vec2f::operator*(const vec2f& arg)	const { return vec2f(x * arg.x, y * arg.y); }
	vec2f vec2f::operator/(const vec2f& arg)	const { return vec2f(x / arg.x, y / arg.y); }	

	vec2f vec2f::operator*(const float& arg)	const { return vec2f(x * arg, y * arg); }
	vec2f vec2f::operator/(const float& arg)	const { return vec2f(x / arg, y / arg); }

	vec2f& vec2f::operator+=(const vec2f& arg)	{ x += arg.x; y += arg.y; return *this; }
	vec2f& vec2f::operator-=(const vec2f& arg)	{ x -= arg.x; y -= arg.y; return *this; }
	vec2f& vec2f::operator*=(const vec2f& arg)	{ x *= arg.x; y *= arg.y; return *this; }
	vec2f& vec2f::operator/=(const vec2f& arg)	{ x /= arg.x; y /= arg.y; return *this; }
