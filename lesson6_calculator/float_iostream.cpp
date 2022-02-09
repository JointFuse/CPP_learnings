#include "float_iostream.h"

using namespace Fios;

const string default_ostream{ "cout" };
const string default_istream{ "cin" };

Float_stream::Float_stream()
{
	o_set(default_ostream);
	i_set(default_istream);
}

Float_stream::Float_stream(const string& n, bool out)
{
	if (out) { o_set(n); return; }
	i_set(n);
}

ostream& Float_stream::o_curr()
{
	for (int i{ 0 }; i < o_names.size(); ++i)
		if (o_current == o_names[i])
			return o[i];

	if (o_names.size() == 0)
		o_set(default_ostream);
	
	return o[0];

}

istream& Float_stream::i_curr()
{
	for (int i{ 0 }; i < i_names.size(); ++i)
		if (i_current == i_names[i])
			return this->i[i];

	if (i_names.size() == 0)
		i_set(default_istream);

	return i[0];
}

void Float_stream::o_set(const string& name)
{
	if (name == default_istream)
		o.push_back(cout);
	else {
		ofstream new_stream(name);
		o.push_back(new_stream);
	}

	o_names.push_back(name);
	o_current = name;
}

void Float_stream::i_set(const string& name)
{
	if (name == default_istream)
		i.push_back(cin);
	else {
		ifstream new_stream(name);
		i.push_back(new_stream);
	}

	i_names.push_back(name);
	i_current = name;
}