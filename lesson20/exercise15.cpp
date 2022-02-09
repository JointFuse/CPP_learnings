#include <vector>
#include <iostream>
#include <string>

using namespace std;

//------------------------------------------------------------------------------

template<typename T>
class pvector {
protected:
	vector<T*> ptrs;
public:
	using size_type = unsigned long;
	using iterator = typename vector<T*>::iterator;
	using const_iterator = typename vector<T*>::const_iterator;

	pvector() :ptrs() { }
	explicit pvector(size_type s) :ptrs(s, nullptr) { }
	pvector(initializer_list<T>);

	pvector(const pvector<T>&);
	pvector& operator=(const pvector<T>&);

	pvector(pvector<T>&&);
	pvector& operator=(pvector<T>&&);

	void push_back(T* v)		{ ptrs.push_back(v); }
	size_type size()	const	{ return ptrs.size(); }
	size_type capacity()const	{ return ptrs.capacity(); }

	bool operator==(const pvector<T>&) const;
	bool operator!=(const pvector<T>&) const;

	T*& operator[](size_type i)		{ return ptrs[i]; }
	T* operator[](size_type i) const{ return ptrs[i]; }

	iterator begin(){ return ptrs.begin(); }
	iterator end()	{ return ptrs.end(); }
	const_iterator begin()const { return ptrs.begin(); }
	const_iterator end()  const { return ptrs.end(); }

	T* front()	{ return ptrs[0]; }
	T* back()	{ return ptrs[size() -1]; }

	~pvector();
};

//------------------------------------------------------------------------------

template<typename T>
pvector<T>::pvector<T>(initializer_list<T> list)
	: ptrs()
{
	for (auto v : list)
		{ ptrs.push_back(v); }
}

template<typename T>
pvector<T>::pvector<T>(const pvector<T>& pv)
	: ptrs()
{
	for(auto v : pv)
		{ ptrs.push_back(new T(*v)); }
}

template<typename T>
pvector<T>& pvector<T>::operator=(const pvector<T>& pv)
{
	if (this == &pv) { return *this; }
	pvector<T*> newptrs(pv);
	swap(*this, newptrs);
	return *this;
}

template<typename T>
pvector<T>::~pvector<T>()
{
	for (T* ptr : ptrs)
		{ delete ptr; }
}

//------------------------------------------------------------------------------

template<typename T>
pvector<T>::pvector<T>(pvector<T>&& pv)
	: ptrs()
{
	swap(ptrs, pv.ptrs);
}

template<typename T>
pvector<T>& pvector<T>::operator=(pvector<T>&& pv)
{
	if (this == &pv) { return *this; }
	swap(ptrs, pv.ptrs);
	return *this;
}

//------------------------------------------------------------------------------

template<typename T>
bool pvector<T>::operator==(const pvector<T>& pv) const
{
	if (this->size() != pv.size())
		{ return false; }
	for (int i{0}; i < size(); ++i)
		if (ptrs[i] != pv[i])
			{ return false; }
	return true;
}

template<typename T>
bool pvector<T>::operator!=(const pvector<T>& pv) const
{
	return !(*this == pv);
}

//------------------------------------------------------------------------------

pvector<int> f(const pvector<int>& pv)
{
	pvector<int> ret(pv);
	return ret;
}

//------------------------------------------------------------------------------

/* Exercise 16 */
template<typename T>
struct ovector : pvector<T> {
	class iterator;

	using pvector<T>::pvector;
	using pvector<T>::size_type;

	iterator begin(){ return this->ptrs.begin(); }
	iterator end()	{ return this->ptrs.end(); }

	T& operator[](size_type i) { return *this->ptrs[i]; }
	T operator[](size_type i) const { return *this->ptrs[i]; }
};

template<typename T>
class ovector<T>::iterator {
	typename vector<T*>::iterator it;
public:
	iterator(typename vector<T*>::iterator iter) : it(iter) { }
	iterator(const iterator& iter) : it(iter.it) { }

	iterator& operator++() { ++it; return *this; }
	iterator& operator--() { --it; return *this; }

	bool operator==(const iterator& iter) const { return it == iter.it; }
	bool operator!=(const iterator& iter) const { return it != iter.it; }

	T& operator*() { return **it; }
};
//------------------------------------------------------------------------------

/* Exercise 17 */
template<typename T>
class ownership_vector {
	vector<T*> dat;
	vector<T*> own;
public:
	using size_type = unsigned long;
	using iterator = typename vector<T*>::iterator;
	using const_iterator = typename vector<T*>::const_iterator;

	ownership_vector() : dat(), own() { }
	
	void push_back(T& v) { dat.push_back(&v); }
	void push_back(T* v) { dat.push_back(v); own.push_back(v); }

	T*& operator[](size_type i)		{ return dat[i]; }
	T* operator[](size_type i) const{ return dat[i]; }

	size_type size()	const { return dat.size(); }
	size_type capacity()const { return dat.capacity(); }

	~ownership_vector();
};

template<typename T>
ownership_vector<T>::~ownership_vector<T>()
{
	for (T* p : own)
		{ delete p; }
}

//------------------------------------------------------------------------------

int main()
{
	pvector<int> pv;
	for (int i{0}; i < 10; ++i)
		{ pv.push_back(new int(i)); }
	cout << "pv *front() = " << *pv.front() << '\n'
		 << "pv *back() = " << *pv.back() << '\n'
		 << "pv **begin() = " << **pv.begin() << '\n'
		 << "pv **(--end()) = " << **(--pv.end()) << '\n';
	pvector<int> pv1(f(pv));
	cout << "11 = " << *pv1.front() << '\n';
	pv1 = f(pv);
	cout << "12 = " << *pv1.front() << '\n';
	
	ovector<int> ov;
	for (int i{ 0 }; i < 10; ++i)
		{ ov.push_back(new int(i)); }
	cout << "ov[0] = " << ov[0] << '\n'
		 << "ov[size() - 1] = " << ov[ov.size() - 1] << '\n'
		 << "*ov.begin() = " << *ov.begin() << '\n'
		 << "*(--ov.end()) = " << *(--ov.end()) << '\n';

	ownership_vector<int> ownv;
	ownv.push_back(new int(99));
	ownv.push_back(ov[0]);

	return 0;
}