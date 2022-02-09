/*	
	Библиотека для подключения файловых 
	потоков ввода\вывода с паматью 
	подключаемых файлов

	История версий:

	26.07.2021 - Разработан Майским Александром И.

*/

#include </Users/tony/source/repos/libs/std_lib_facilities.h>

namespace Fios {
	// Класс для смены потока ввода/вывода данных
	class Float_stream {
	private:
		vector<ostream> o;	// Выходные потоки
		vector<istream> i;	// Входные потоки

		vector<string> o_names;	// Имена выходных потоков 
		vector<string> i_names;	// Имена входных потоков

		string o_current;		// Имя используемого выходного потока
		string i_current;		// Имя используемого входного потока

	public:
		Float_stream();									// По умолчанию подключаются потоки cin и cout
		Float_stream(const string& name, bool is_out);	// Подключается ввод или вывод в файл с именем name
														// is_out определяет направление переключаемого потока

		class fios_error{};	// Для индикации необрабатываемых ошибок

		ostream& o_curr();	// Возвращает ссылку на используемый выходной поток
		istream& i_curr();	// Возвращает ссылку на используемый входной поток

		void o_set(const string& name);	// Переключение потока вывода
		void i_set(const string& name);	// Переключение потока ввода
	};
}