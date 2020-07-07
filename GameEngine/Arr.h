#pragma once

#include <initializer_list>
#include <algorithm>

template <class T> class Arr {
	T* data;
	int s;
	
	void init(int size);
public:
	Arr<T>(int size);
	Arr<T>(std::initializer_list<T> arr);
	Arr<T>(const Arr<T>& old);
	~Arr<T>();

	T& operator [](int i);
	Arr<T>& operator =(const Arr<T>& a);

	int size() const;

	//Iterator stuff
	class it {
		int i;
		T* d;
		it(int index, T* data) : i(index), d(data) {}
		friend Arr<T>;
	public:
		inline it& operator ++() {
			i++;
			return *this;
		}
		inline T operator *() { return d[i]; }
		inline bool operator !=(it it2) { return i != it2.i; }
	};

	inline it begin() { return it(0, data); }
	inline it end() { return it(s, data); }
};

template<class T>
inline void Arr<T>::init(int size)
{
	data = new T[size + 1]; //+1 for null terminator
	s = size;
}

template<class T>
inline Arr<T>::Arr(int size)
{
	init(size);
}

template<class T>
inline Arr<T>::Arr(std::initializer_list<T> arr)
{
	init(arr.s);

	std::copy(arr.begin(), arr.end(), data);
}

template<class T>
inline Arr<T>::Arr(const Arr<T>& old)
{
	init(old.s);

	memcpy(data, old.data, s * sizeof(T));
}

template<class T>
inline Arr<T>::~Arr()
{
	delete[] data;
}

template<class T>
inline T& Arr<T>::operator[](int i)
{
	return data[i];
}

template<class T>
inline Arr<T>& Arr<T>::operator=(const Arr<T>& a)
{
	init(a.s); 

	memcpy(data, a.data, s * sizeof(T));

	return *this;
}

template<class T>
inline int Arr<T>::size() const
{
	return s;
}