//---------------------------------------------------------------------

template<typename N>
Number<N>& Number<N>::operator= (const Number<N>& right)
{
	val = right.val;
	return *this;
}

//---------------------------------------------------------------------

template<typename N>
	template<typename U>
Number<N>& Number<N>::operator+= (const Number<U>& right)
{
	*this = *this + right;
	return *this;
}

//---------------------------------------------------------------------

template<typename N>
	template<typename U>
Number<N> Number<N>::operator+ (const Number<U>& right) const
{
	return val + right.val;
}

//---------------------------------------------------------------------

template<typename N>
	template<typename U>
Number<N> Number<N>::operator- (const Number<U>& right) const
{
	return val - right.val;
}

//---------------------------------------------------------------------

template<typename N>
	template<typename U>
Number<N> Number<N>::operator* (const Number<U>& right) const
{
	return val * right.val;
}

//---------------------------------------------------------------------

template<typename N>
	template<typename U>
Number<N> Number<N>::operator/ (const Number<U>& right) const
{
	return val / right.val;
}

//---------------------------------------------------------------------

template<typename N>
Number<N> Number<N>::operator% (const Number<N>& right) const
{
	return val % right.val;
}

//---------------------------------------------------------------------

template<typename N>
ostream& operator<< (ostream& os, const Number<N>& obj)
{
	return os << obj.val;
}

//---------------------------------------------------------------------

template<typename N>
istream& operator>> (istream& is, const Number<N>& obj)
{
	return is >> obj.val;
}

//---------------------------------------------------------------------
