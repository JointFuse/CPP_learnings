#include <vector>
#include <iostream>
#include <exception>

using namespace std;

template<typename T>
struct Vector : vector<T> {
	class iterator;
	
	iterator begin(){ return { 0, vector<T>::begin(), vector<T>::size() }; }
	iterator end()	{ return { vector<T>::size(), vector<T>::begin(), vector<T>::size() }; }

	using vector<T>::vector;
};

template<typename T>
class Vector<T>::iterator {
	T* curr;
	T* b;
	T* e;

	iterator(T* ptr, T* begin, T* end) : curr(ptr), b(begin), e(end) { }
public:
	using size_type = typename Vector<T>::size_type;

	iterator(size_type iter, vector<T>::iterator begin, size_type size) 
		: curr(&*begin + iter), b(&*begin), e(&*begin + size) { }
	iterator(const iterator& iter) : curr(iter.curr), b(iter.b), e(iter.e) { }

	iterator& operator++() { ++curr; if (e <= curr) { throw exception("iter bigger then back"); } return *this; }
	iterator& operator--() { --curr; if (curr < b) { throw exception("iter smaller then front"); } return *this; }
	iterator operator-(size_type) const;
	iterator operator+(size_type) const;
	iterator& operator-=(size_type);
	iterator& operator+=(size_type);

	long operator-(const iterator& it) const { return curr - it.curr; }

	T& operator*() { return *curr; }
	T operator*() const { return *curr; }
};

template<typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator-(size_type n) const
{
	T* ret = curr - n;
	if (e < curr || curr < b)
		{ throw exception("iterator range error"); }
	return { ret, b, e };
}

template<typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator+(size_type n) const
{
	T* ret = curr + n;
	if (e < curr || curr < b)
		{ throw exception("iterator range error"); }
	return { ret, b, e };
}

template<typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator-=(size_type n)
{
	curr -= n;
	if (e < curr || curr < b)
		{ throw exception("iterator range error"); }
	return *this;
}

template<typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator+=(size_type n)
{
	curr += n;
	if (e < curr || curr < b)
		{ throw exception("iterator range error"); }
	return *this;
}

int main()
{
	Vector<int> iv{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto begin= iv.begin();
	auto end = iv.end();
	cout << "*(begin + 4) = " << *(begin + 4) << '\n'
		 << "*(end - 3) = " << *(end - 3) << '\n';
	begin += 6;
	end -= 7;
	cout << "begin += 6 := " << *begin << '\n'
		 << "end -= 7 := " << *end << '\n'
		 << "begin - end = " << begin - end << '\n';

	return 0;
}