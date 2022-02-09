template<typename T, typename A>
Vector<T, A>::Vector(int n) : cap{ n }, sze{ n }, elem{ alloc.allocate(n) }
{
	if (n < 0) throw exception("bad vec size");
	for (int i{0}; i < n; ++i)
		{ alloc.construct(&elem[i], T()); }
}

template<typename T, typename A>
Vector<T, A>::Vector(const Vector<T>& vec)
	: cap{ vec.size() }, sze{ vec.size() }, elem{ alloc.allocate(vec.capacity()) }
{
	for (int i{0}; i < sze; ++i)
		{ alloc.construct(&elem[i], vec[i]); }
}

template<typename T, typename A>
Vector<T, A>::Vector(int n, const T& val)
	: cap{ n }, sze{ n }, elem{ alloc.allocate(n) }
{
	for (int i{0}; i < sze; ++i)
		{ alloc.construct(&elem[i], val); }
}

template<typename T, typename A>
void Vector<T, A>::resize(int newsize)
{
	reserve(newsize);
	for (int i{sze}; i < newsize; ++i)
		{ alloc.construct(&elem[i], T()); }
	for (int i{newsize}; i < sze; ++i)
		{ alloc.destroy(&elem[i]); }
	sze = newsize;
}

template<typename T, typename A>
void Vector<T, A>::reserve(int newcap)
{
	if (newcap <= cap) return;
	T* p = alloc.allocate(newcap);
	for (int i{0}; i < sze; ++i)
		{ alloc.construct(&p[i], elem[i]); }
	for (int i{0}; i < sze; ++i)
		{ alloc.destroy(&elem[i]); }
	alloc.deallocate(elem, cap);
	cap = newcap;
	elem = p;
}

template<typename T, typename A>
void Vector<T, A>::push_back(const T& obj)
{
	if (cap == 0)		{ reserve(8); }
	else if (sze = cap) { reserve(sze + 2 * cap); }
	alloc.construct(&elem[sze], obj);
	++sze;
}

template<typename T, typename A>
T& Vector<T, A>::at(int i)
{
	if (i < 0 || sze <= i) throw exception("bad vec range");
	return elem[i];
}

template<typename T, typename A>
const T& Vector<T, A>::at(int i) const
{
	if (i < 0 || sze <= i) throw exception("bad vec range");
	return elem[i];
}

template<typename T, typename A>
Vector<T, A>& Vector<T, A>::operator= (const Vector<T, A>& vec)
{
	if (this == &vec) return *this;
	if (vec.sze <= cap) {
		for (int i{0}; i < vec.sze; ++i)
			{ alloc.construct(&elem[i], vec[i]); }
		sze = vec.sze;
		return *this;
	}
	T* p = alloc.allocate(vec.sze);
	for (int i{0}; i < vec.sze; ++i)
		{ alloc.construct(&p[i], vec[i]); }
	for (int i{0}; i < sze; ++i)
		{ alloc.destroy(&elem[i]); }
	alloc.deallocate(elem, cap);
	cap = sze = vec.sze;
	elem = p;
	return *this;
}

template<typename T, typename A>
Vector<T, A>::~Vector<T, A>()
{
	for (int i{0}; i < sze; ++i)
		{ alloc.destroy(&elem[i]); }
	alloc.deallocate(elem, cap);
}