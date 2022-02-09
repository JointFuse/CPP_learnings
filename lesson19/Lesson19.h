#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <fstream>

#define vector true_vector

namespace MyLib {
	using namespace std;
	
	struct Int {
		int val;

		Int(const int& value) : val{ value } { }

		Int& operator= (const Int&);
		Int operator+ (const Int&);
		Int operator- (const Int&);
		Int operator* (const Int&);
		Int operator/ (const Int&);
	};

	ostream& operator<< (ostream&, const Int&);
	istream& operator>> (istream&, const Int&);

	template<typename N>		// requires Number<T> ()
	struct Number {
		N val;

		Number(const N& value) : val{ value } { }
		template<typename U>
		Number(const Number<U>& value) : val{N(value.val)} { }

		Number& operator= (const Number&);
		template<typename U>
		Number& operator+= (const Number<U>&);
		template<typename U>
		Number operator+ (const Number<U>&) const;
		template<typename U>
		Number operator- (const Number<U>&) const;
		template<typename U>
		Number operator* (const Number<U>&) const;
		template<typename U>
		Number operator/ (const Number<U>&) const;
		Number operator% (const Number&) const;
	};

	template<typename N>		// requires Number<N> ()
	ostream& operator<< (ostream&, const Number<N>&);
	template<typename N>		// requires Number<N> ()
	istream& operator>> (istream&, const Number<N>&);

#include "Number.inl"

	template<typename T>
	struct Allocator {
		T* allocate(int n);
		void deallocate(T* p, int n);
		void construct(T* p, const T& v);
		void destroy(T* p);
	};

#include "Allocator.inl"

	template<typename T, typename A = Allocator<T>>	// require Random_acess_iterator<T> ()
	class Vector {
		int cap;
		int sze;
		T* elem;
		A alloc;
	public:
		Vector() : cap{ 0 }, sze{ 0 }, elem{ nullptr } { }
		explicit Vector(int);
		Vector(const Vector<T>&);
		Vector(int, const T&);

		void resize(int);
		void reserve(int);
		void push_back(const T&);
		
		int size()		const { return sze; }
		int capacity()	const { return cap; }

		T& at(int);
		const T& at(int) const;

		Vector& operator= (const Vector&);
		T& operator[] (int i)			 { return elem[i]; }
		const T& operator[] (int i) const{ return elem[i]; }

		~Vector();
	};

#include "Vector.inl"

	template<typename T, typename A = Allocator<T>>
	class true_vector {
		Vector<T, A>* ptr;
	public:
		true_vector() : ptr(new Vector<T, A>()) { }
		explicit true_vector(int n) : ptr(new Vector<T, A>(n)) { }
		true_vector(const true_vector<T, A>& v) : ptr(new Vector<T, A>(*v)) { }
		true_vector(int n, const T& t) : ptr(new Vector<T, A>(n, t)) { }

		void resize(int n)		{ ptr->resize(n); }
		void reserve(int n)		{ ptr->reserve(n); }
		void push_back(const T& t){ ptr->push_back(t); }

		int size()		const { return ptr->size(); }
		int capacity()	const { return ptr->capacity(); }

		T& at(int i)			{ return ptr->at(i); }
		const T& at(int i) const{ return ptr->at(i); }

		Vector<T, A>& operator* () { return *ptr; }
		const Vector<T, A>& operator* () const { return *ptr; }
		true_vector<T, A>& operator= (const true_vector<T, A>& v) { *ptr = *v; return *this; }
		T& operator[] (int i) { return (*ptr)[i]; }
		const T& operator[] (int i) const { return (*ptr)[i]; }

		~true_vector() { ptr->~Vector<T, A>(); }
	};

	template<typename T, typename A>
	void vec_check(const vector<T, A>& vec, string desc = "Noname Vec")
	{
		cout << '[' << desc << "] check info = {\n"
			 << "\t Capacity = " << vec.capacity() <<'\n'
			 << "\t Size = " << vec.size() << '\n'
			 << "\t Members:\n\t{ ";
		for (int i{ 0 }; i < vec.size(); ++i) { 
			cout << vec[i] 
				 << (i == vec.size() - 1 ? " " : ", "); 
		}
		cout << "}\n};\n";
	}

	template<typename T>
	class Unique_ptr {
		T* ptr;

		Unique_ptr(const Unique_ptr&);
		Unique_ptr& operator= (const Unique_ptr&);
	public:
		Unique_ptr(T* pointer) :ptr{ pointer } { }

		T* release() {
			T* ret = ptr;
			ptr = nullptr;
			return ret;
		}

		T* operator-> () const { return ptr; }
		T& operator* ()	{ return *ptr; }

		~Unique_ptr() {
			if (ptr != nullptr)
				{ delete ptr; }
		}
	};

	template<typename T>
	class Counted_ptr {
		T* ptr;
		int* cnt;
		
		void increase() { ++(*cnt); }
		void decrease() { 
			--(*cnt);
			if (*cnt < 1) 
				{ throw exception("counted ptr: count err"); }
		}
	public:
		Counted_ptr() : ptr{ nullptr }, cnt{ nullptr } { }
		Counted_ptr(T* pointer) : ptr{ pointer }, cnt{ new int{1} } { }
		Counted_ptr(const Counted_ptr& obj)
			: ptr{ obj.ptr }, cnt{ obj.cnt }
		{ increase(); }

		int count() const { return *cnt; }

		Counted_ptr& operator= (const Counted_ptr& obj);

		T* operator->() const {
			if (ptr == nullptr)
				{ throw exception("counted ptr empty"); }
			return ptr; 
		}
		T& operator* ()	{ 
			if (ptr == nullptr)
				{ throw exception("counted ptr empty"); }
			return *ptr; 
		}

		~Counted_ptr();
	};

#include "Counted_ptr.inl"

	class File_handle {
		ofstream outfile;
		ifstream infile;
	public:
		File_handle(string name) : outfile{ name, ios_base::app }, infile{ name }
		{
			if (!infile || !outfile)
				{ throw exception("can't open file"); }
		} 

		template<typename S>
		auto& operator<< (const S& s)
		{
			return outfile << s;
		}
		template<typename L>
		auto& operator>> (L& l)
		{
			return infile >> l;
		}

		ifstream& operator* () { return infile; }

		~File_handle()
		{
			infile.close();
			outfile.close();
		}
	};

	class Tracer {
		string c;
		string d;
	public:
		Tracer(string constructor, string destructor)
			: c{ constructor }, d{ destructor }
		{
			cout << c << '\n';
		}
		Tracer(const Tracer& obj) : c{ "copy of " + obj.c}, d{ "copy of " + obj.d }
		{
			cout <<  c << '\n';
		}

		Tracer& operator= (const Tracer& right)
		{
			if (this == & right) return *this;
			cout << d <<  " and setted by " << right.c << '\n';
			c = "setted by " + right.c;
			d = "setted by " + right.d;
			return *this;
		}

		~Tracer()
		{
			cout << d << '\n';
		}
	};
}