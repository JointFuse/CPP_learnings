template<typename T>
Counted_ptr<T>& Counted_ptr<T>::operator= (const Counted_ptr<T>& obj) 
{
	if (this == &obj) return *this;
	T* newptr = obj.ptr;
	if (cnt && *cnt == 1)
	{
		delete ptr;
	}
	else if (cnt)
	{
		decrease();
	}
	ptr = newptr;
	cnt = obj.cnt;
	increase();
}

template<typename T>
Counted_ptr<T>::~Counted_ptr() 
{
	if (*cnt == 1) {
		delete ptr;
		delete cnt;
	}
	else { 
		decrease();
	} 
}