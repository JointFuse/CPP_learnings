#include <string>
#include <vector>

namespace Lib18 {
	// �������� �-������ � ������������ ������
	// ���������� ��������� �� �����
	char* strdup(const char* to_copy);
	
	// ������� ������ ��������� ����� ������ � ������
	char* findx(const char* where, const char* what);

	// ���������� ��� ������ � ���������� �������� �� ���������
	int strcmp(const char*, const char*);

	// ������������� ��� ������ � ������������ dot 
	std::string cat_dot(const std::string& s1, const std::string& s2, const std::string& dot = ".");

	// ������������� ��� �-������ � ������������ dot
	char* cat_dotc(const char* s1, const char* s2, const char* dot = nullptr);

	// �������� ���������� � ������� string
	bool is_palindrome(const std::string& s);

	// �������� ���������� � ������� ��������
	bool is_palindrome(const char s[], int n);

	// �������� ���������� � ������� ����������
	bool is_palindrome(const char* first, const char* last);

	// �������� ������
	std::string reverse(const std::string& s);


	// ����������� ������ � ����������
	class Skip_list {
		// ��������������� ��������� ������,
		// ������� ������ � �����
		struct data {
			data(data* n, data* d, std::string v)
				:value{v}, next{n}, down{d}	{ }

			std::string value{ 0 };
			data* next{ nullptr };
			data* down{ nullptr };

			~data();
		private:
			data(const data&);
			data& operator= (const data&);
		};

		// ������ �� ��� ������ ������ �����
		std::vector<data*> levels;

		// ������� ����� ������� ������ ����� ������������
		data* insert(data*& here, const std::string& what, data* down);

		void vcheck(const std::string& s);

		// ������ �� ������������� �����������
		Skip_list(const Skip_list&);
		Skip_list& operator= (const Skip_list&);
	public:
		Skip_list(int number_of_levels) 
			: levels(number_of_levels, nullptr) { }

		void add(const std::string& value);
		void del(const std::string& value);
		bool search(const std::string& value);

		~Skip_list();
	};
}