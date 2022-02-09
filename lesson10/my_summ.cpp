#include "my_summ.h"

int summ_from_file(const string& file_name)
{
	ifstream ist(file_name);
	if (!ist) error("Unable to open file -> ", file_name);

	int summ{ 0 };
	int buf;
	while (ist >> buf) summ += buf;
	
	return summ;
}