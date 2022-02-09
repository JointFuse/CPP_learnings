#include <string>
#include <vector>

namespace Lib18 {
	// Копирует с-строку в динамичускую память
	// возвращает указатель на копию
	char* strdup(const char* to_copy);
	
	// Находит первое вхождение одной строки в другую
	char* findx(const char* where, const char* what);

	// Сравнивает две строки и возвращает оператор их отношения
	int strcmp(const char*, const char*);

	// Конкатенирует две строки с разделителем dot 
	std::string cat_dot(const std::string& s1, const std::string& s2, const std::string& dot = ".");

	// Конкатенирует две с-строки с разделителем dot
	char* cat_dotc(const char* s1, const char* s2, const char* dot = nullptr);

	// Проверка полиндрома с помощью string
	bool is_palindrome(const std::string& s);

	// Проверка полнидрома с помощью массивов
	bool is_palindrome(const char s[], int n);

	// Проверка полиндрома с помощью указателей
	bool is_palindrome(const char* first, const char* last);

	// Обращает строку
	std::string reverse(const std::string& s);


	// Односвязный список с пропусками
	class Skip_list {
		// Вспомогательная структура данных,
		// единица памяти в листе
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

		// Ссылки на все уровни данных листа
		std::vector<data*> levels;

		// Вставка новой единицы памяти перед существующим
		data* insert(data*& here, const std::string& what, data* down);

		void vcheck(const std::string& s);

		// Запрет на поверхностное копирование
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