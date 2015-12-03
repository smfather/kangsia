#ifndef EULER_PARAMETER_HPP
#define EULER_PARAMETER_HPP

namespace algebra
{
	template<typename T>
	class euler_parameter
	{
	public:
		euler_parameter() : e0(0), e1(0), e2(0), e3(0) {}
		euler_parameter(T _e0, T _e1, T _e2, T _e3) : e0(_e0), e1(_e1), e2(_e2), e3(_e3) {}
		euler_parameter(const euler_parameter& ep) : e0(ep.e0), e1(ep.e1), e2(ep.e2), e3(ep.e3) {}
		~euler_parameter(){}

		euler_parameter operator+(euler_parameter& v4){
			return euler_parameter(e0 + v4.e0, e1 + v4.e1, e2 + v4.e2, e3 + v4.e3);
		}

		T dot(){
			return e0*e0 + e1*e1 + e2*e2 + e3*e3;
		}

		T& operator() (unsigned id){
			assert(id > 3 && "Error - T vector4::operator() (int id > 3)");
			return *((&e0) + id);
		}

		T* Pointer() { return &e0; }

		T e0, e1, e2, e3;
	};

	template<typename T2>
	euler_parameter<T2> operator*(int val, euler_parameter<T2>& ep){
		return euler_parameter<T2>(val * ep.e0, val * ep.e1, val * ep.e2, val * ep.e3);
	}

	template<typename T2>
	euler_parameter<T2> operator*(double val, euler_parameter<T2>& ep){
		return euler_parameter<T2>(val * ep.e0, val * ep.e1, val * ep.e2, val * ep.e3);
	}

	template<typename T2>
	euler_parameter<T2> operator*(unsigned int val, euler_parameter<T2>& ep){
		return euler_parameter<T2>(val * ep.e0, val * ep.e1, val * ep.e2, val * ep.e3);
	}
}

#endif