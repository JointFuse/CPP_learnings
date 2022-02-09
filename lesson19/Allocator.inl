template<typename T>
T* Allocator<T>::allocate(int n)
{
	T* ptr = static_cast<T*>(malloc(n * sizeof(T)));
	if (!ptr) throw exception("bad_alloc");
	return ptr; 
}

template<typename T>
void Allocator<T>::deallocate(T* p, int n)
{
	free(p);
}

template<typename T>
void Allocator<T>::construct(T* p, const T& v)
{
	new(p) T(v);
}

template<typename T>
void Allocator<T>::destroy(T* p)
{
	p->~T();
}