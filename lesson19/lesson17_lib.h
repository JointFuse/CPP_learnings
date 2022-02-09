#include <string>
#include <iostream>

namespace My_pointers {
	// Transform upper letters to lower letters
	extern void to_lower(char*);

	// Copy C string (with '0' at end) to 
	// dynamic allocated memory place
	extern char* strdup(const char*);

	// Находит первое вхождение строки
	extern char* findx(const char* s, const char* x);
}
namespace My_link {
	enum Mithology {
		greece, norway,
		india, slavic
	};

	// God information type
	struct God {
		std::string name;
		std::string weapon;
		std::string transport;
		Mithology from;

		God(const std::string& name, Mithology from, 
			const std::string& transp, const std::string& weapon)
			:name{ name }, weapon{ weapon }, 
			 transport{ transp }, from{ from } { }
	};

	template<typename T>
	class Link {
		Link* prev;				// Адресс предыдущего элемента
		Link* succ;				// Адресс следующего элемента
	public:
		T val;					// Значение элемента
		Link(const T& value, Link* p = nullptr, Link* s = nullptr)
			:val{value}, prev{p}, succ{s} {}
	
		Link* insert(Link*);		// Вставляет новый элемент перед данным объектом
		Link* add(Link*);			// Вставляет новый элемент после данного объекта
		Link* add_ordered(Link*);	// Вставляет новый элемент в правильной
										// лексикографической позиции
		Link* erase();				// Удаляет данный объект из списка
		Link* find(const T&);				// Поиск в списке
		const Link* find(const T&) const;	// Поиск в константном списке

		Link* advance(int);					// Перемещение по списку

		Link* next()	const { return succ; }	// Возврат следующего элемента
		Link* previous()const { return prev; }	// Возврат предыдущего элемента
	};

	bool operator== (const God&, const God&);

	std::ostream& operator<< (std::ostream&, const God&);
	std::ostream& operator<< (std::ostream&, const Mithology&);

	template<typename T>			// requies Output_iterator<T> ()
	void print_all(Link<T>* p);
	
	//----------------------------------------------------------------

	template<typename T>
	Link<T>* Link<T>::insert(Link<T>* n)
	{
		if (!n) return this;
		if (!this) return n;

		n->succ = this;
		if (prev) prev->succ = n;
		n->prev = prev;
		prev = n;

		return n;
	}

	template<typename T>
	Link<T>* Link<T>::add(Link<T>* n)
	{
		if (!n) return this;
		if (!this) return n;

		n->prev = this;
		if (succ) succ->prev = n;
		n->succ = succ;
		succ = n;

		return n;
	}

	template<typename T>
	Link<T>* Link<T>::erase()
	{
		if (!this && succ) return succ;
		if (!this && prev) return prev;
		if (!this) return nullptr;

		Link<T>* ret = nullptr;

		if (succ) {
			ret = succ;
			if (prev)	succ->prev = prev;
			else		succ->prev = nullptr;
			succ = nullptr;
		}
		if (prev) {
			ret = prev;
			if (succ)	prev->succ = succ;
			else		prev->succ = nullptr;
			prev = nullptr;
		}

		return ret;
	}

	template<typename T>
	Link<T>* Link<T>::find(const T& to_find)
	{
		if (!this) return nullptr;

		Link<T>* l = this;
		while (l->prev) l = l->prev;

		while (l) {
			if (l->val == to_find)
				return l;
			l = l->succ;
		}

		return nullptr;
	}

	template<typename T>
	const Link<T>* Link<T>::find(const T& to_find) const
	{
		if (!this) return nullptr;

		const Link<T>* l = this;
		while (l->prev) l = l->prev;

		while (l) {
			if (l->val == to_find)
				return l;
			l = l->succ;
		}

		return nullptr;
	}

	template<typename T>
	Link<T>* Link<T>::advance(int n)
	{
		if (!this)	return nullptr;

		Link<T>* dest = this;
		int nn{ 0 };
		while (nn != n) {
			if (n > 0 && (dest->succ == nullptr))
				break;
			if (n < 0 && (dest->prev == nullptr))
				break;
			if (n < 0)	dest = dest->prev;
			else		dest = dest->succ;
			nn += n / abs(n);
		}
		if (!nn)		return this;

		Link<T>* ret = this;
		if (succ) {
			ret = succ;
			if (prev)	succ->prev = prev;
			else		succ->prev = nullptr;
		}
		if (prev) {
			ret = prev;
			if (succ)	prev->succ = succ;
			else		prev->succ = nullptr;
		}

		if (nn > 0) {
			if (dest->succ) {
				succ = dest->succ;
				succ->prev = this;
			}
			else succ = nullptr;

			prev = dest;
			prev->succ = this;
		}
		else {
			if (dest->prev) {
				prev = dest->prev;
				prev->succ = this;
			}
			else prev = nullptr;

			succ = dest;
			succ->prev = this;
		}

		return ret;
	}

	template<typename T>
	Link<T>* Link<T>::add_ordered(Link<T>* n)
	{
		if (!n) return this;
		if (!this) return n;

		Link<T>* ptr = this;
		while (ptr->prev) ptr = ptr->prev;
		Link<T>* begin = ptr;

		bool in_end(false);
		while (ptr->val.name < n->val.name) {
			if (ptr->succ)	ptr = ptr->succ;
			else { in_end = true; break; }
		}

		if (in_end) {
			n->prev = ptr;
			ptr->succ = n;
			return begin;
		}
		else {
			n->succ = ptr;
			if (ptr->prev) {
				n->prev = ptr->prev;
				n->prev->succ = n;
			}
			ptr->prev = n;
			if (ptr == begin)
				return n;
		}

		return begin;
	}

	//----------------------------------------------------------------

	template<typename T>
	void print_all(Link<T>* p)
	{
		while (p->previous())
			p = p->previous();

		std::cout << "{ " << '\n';
		while (p) {
			std::cout << '\t' << p->val << '\n';
			p = p->next();
		}
		std::cout << "}" << '\n';
	}

	//----------------------------------------------------------------

 }