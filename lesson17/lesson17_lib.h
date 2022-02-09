#include <string>

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

	class Link {
		Link* prev;				// Адресс предыдущего элемента
		Link* succ;				// Адресс следующего элемента
	public:
		God value;				// Значение элемента
		Link(const God& g, Link* p = nullptr, Link* s = nullptr)
			:value{g}, prev{p}, succ{s} {}

		Link* insert(Link*);	// Вставляет новый элемент перед данным объектом
		Link* add(Link*);		// Вставляет новый элемент после данного объекта
		Link* add_ordered(Link*);	// Вставляет новый элемент в правильной
									// лексикографической позиции
		Link* erase();			// Удаляет данный объект из списка
		Link* find_name(const std::string&);				// Поиск в списке
		const Link* find_name(const std::string&) const;	// Поиск в константном списке

		Link* advance(int);						// Перемещение по списку

		Link* next()	const { return succ; }	// Возврат следующего элемента
		Link* previous()const { return prev; }	// Возврат предыдущего элемента
	};

	std::ostream& operator<< (std::ostream&, const God&);
	std::ostream& operator<< (std::ostream&, const Mithology&);
	void print_all(Link* p);
 }