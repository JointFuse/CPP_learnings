#include <string>

namespace My_pointers {
	// Transform upper letters to lower letters
	extern void to_lower(char*);

	// Copy C string (with '0' at end) to 
	// dynamic allocated memory place
	extern char* strdup(const char*);

	// ������� ������ ��������� ������
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
		Link* prev;				// ������ ����������� ��������
		Link* succ;				// ������ ���������� ��������
	public:
		God value;				// �������� ��������
		Link(const God& g, Link* p = nullptr, Link* s = nullptr)
			:value{g}, prev{p}, succ{s} {}

		Link* insert(Link*);	// ��������� ����� ������� ����� ������ ��������
		Link* add(Link*);		// ��������� ����� ������� ����� ������� �������
		Link* add_ordered(Link*);	// ��������� ����� ������� � ����������
									// ������������������ �������
		Link* erase();			// ������� ������ ������ �� ������
		Link* find_name(const std::string&);				// ����� � ������
		const Link* find_name(const std::string&) const;	// ����� � ����������� ������

		Link* advance(int);						// ����������� �� ������

		Link* next()	const { return succ; }	// ������� ���������� ��������
		Link* previous()const { return prev; }	// ������� ����������� ��������
	};

	std::ostream& operator<< (std::ostream&, const God&);
	std::ostream& operator<< (std::ostream&, const Mithology&);
	void print_all(Link* p);
 }