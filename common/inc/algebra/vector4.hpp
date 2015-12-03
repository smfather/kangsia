#ifndef VECTOR4_H
#define VECTOR4_H

namespace algebra
{
	template < typename T >
	class vector4
	{
	public: 
		vector4() : x(0), y(0), z(0), w(0) {}
		vector4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
		vector4(T val) : x(val), y(val), z(val), w(val) {}
		vector4(const vector4& vec4) : x(vec4.x), y(vec4.y), z(vec4.z), w(vec4.w) {}
		~vector4() {}

		vector4 operator+ (vector4& v4){
			return vector4(x + v4.x, y + v4.y, z + v4.z, w + v4.w);
		}
		vector4 operator- (vector4& v4){
			return vector4(x - v4.x, y - v4.y, z - v4.z, w - v4.w);
		}
// 		template<typename T1>
// 		vector4 operator* (T1 val){
// 			return vector4(val * x, val * y, val * z, val * w)
// 		}
		T operator() (unsigned id){
			assert(id > 3 && "Error - T vector4::operator() (int id > 3)");
			return *((&x) + id);
		}
		void operator+= (vector4& v4){ x += v4.x; y += v4.y; z += v4.z; w += v4.w; }

	public:
		T x, y, z, w;
	};

	template< typename T1 >
		vector4<double> operator* (T1 sv, vector4<double> vv){
			vector4<double> v4(sv * vv.x, sv * vv.y, sv * vv.z, sv * vv.w);
			return v4;
	}
// 	template < typename T >
// 	vector4<T> operator* (T sv, vector4<T>& vv){
// 		return vector4<T>(sv * vv.x, sv * vv.y, sv * vv.z, sv * vv.w);
// 	}
// 	template < typename T >
// 	vector4<T> operator* (vector4<T>& vv, T sv){
// 		return vector4<T>(sv * vv.x, sv * vv.y, sv * vv.z, sv * vv.w);
// 	}
	template< typename T >
	std::ostream& operator<<(std::ostream& os, vector4<T>& v)
	{
		std::ios::right;
		os << v.x << " " << v.y << " " << v.z << " " << v.w;
		return os;
	}
}

#endif