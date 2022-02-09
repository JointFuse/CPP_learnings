/*	
	���������� ��� ����������� �������� 
	������� �����\������ � ������� 
	������������ ������

	������� ������:

	26.07.2021 - ���������� ������� ����������� �.

*/

#include </Users/tony/source/repos/libs/std_lib_facilities.h>

namespace Fios {
	// ����� ��� ����� ������ �����/������ ������
	class Float_stream {
	private:
		vector<ostream> o;	// �������� ������
		vector<istream> i;	// ������� ������

		vector<string> o_names;	// ����� �������� ������� 
		vector<string> i_names;	// ����� ������� �������

		string o_current;		// ��� ������������� ��������� ������
		string i_current;		// ��� ������������� �������� ������

	public:
		Float_stream();									// �� ��������� ������������ ������ cin � cout
		Float_stream(const string& name, bool is_out);	// ������������ ���� ��� ����� � ���� � ������ name
														// is_out ���������� ����������� �������������� ������

		class fios_error{};	// ��� ��������� ���������������� ������

		ostream& o_curr();	// ���������� ������ �� ������������ �������� �����
		istream& i_curr();	// ���������� ������ �� ������������ ������� �����

		void o_set(const string& name);	// ������������ ������ ������
		void i_set(const string& name);	// ������������ ������ �����
	};
}