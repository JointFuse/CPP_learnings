#include <vector>
#include <list>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <set>
#include <algorithm>

using namespace std;
using namespace chrono;

//-------------------------------------------------------------------------------------------------

inline default_random_engine& get_rand()
{
	static default_random_engine ran;	// note: not thread_local
	return ran;
};

inline void seed_randint(int s) { get_rand().seed(s); }

inline int randint(int min, int max) { return uniform_int_distribution<>{min, max}(get_rand()); }

inline int randint(int max) { return randint(0, max); }

//-------------------------------------------------------------------------------------------------

long long vec_test(int n, int loop)
{
	seed_randint(0);

	auto t1 = system_clock::now();

	for (int j{ 0 }; j < loop; ++j) {
		vector<int> iv;
		for (int i{ 0 }; i < n; ++i) {
			int r{ randint(n) };
			auto p = find_if(iv.begin(), iv.end(),
							 [&](int x) { return x > r; });
			iv.insert(p, r);
		}
	}

	auto t2 = system_clock::now();
	return duration_cast<milliseconds>(t2 - t1).count();
}

//-------------------------------------------------------------------------------------------------

long long lis_test(int n, int loop)
{
	seed_randint(0);

	auto t1 = system_clock::now();

	for (int j{ 0 }; j < loop; ++j) {
		list<int> iv;
		for (int i{ 0 }; i < n; ++i) {
			int r{ randint(n) };
			auto p = find_if(iv.begin(), iv.end(),
							 [&](int x) { return x > r; });
			iv.insert(p, r);
		}
	}

	auto t2 = system_clock::now();
	return duration_cast<milliseconds>(t2 - t1).count();
}

//-------------------------------------------------------------------------------------------------

long long set_test(int n, int loop)
{
	seed_randint(0);

	auto t1 = system_clock::now();
	
	for (int j{ 0 }; j < loop; ++j) {
		set<int> iv;
		for (int i{ 0 }; i < n; ++i) {
			int r{ randint(n) };
			iv.insert(r);
		}
	}

	auto t2 = system_clock::now();
	return duration_cast<milliseconds>(t2 - t1).count();
}

//-------------------------------------------------------------------------------------------------

int main()
{
	ofstream result("vector_and_list_test.txt");
	if (!result) { cout << "File open error!" << endl; return 1; }

	constexpr int n_min{0};
	constexpr int n_max{100000000};
	constexpr int n_step{100};
	constexpr int loop{1};
	constexpr int tablewidth{15};

	result << "Nmax = " << n_max << "; Nmin = " << n_min 
		   << "; Nstep = " << n_step << "; loop = " << loop << ".\n|"
		   << setw(tablewidth) << "size - N" << '|'
		   << setw(tablewidth) << "vector time, ms" << '|'
		   << setw(tablewidth) << "list time, ms" << '|' 
		   << setw(tablewidth) << "set time, ms" << '|' << '\n';

	for (int i{ n_min }; pow(10, i) < n_max; ++i) {
		static int progr{0};
		auto t1 = system_clock::now();

		result << '|' << setw(tablewidth) << i << '|'
			   << setw(tablewidth) << vec_test(pow(10, i), loop) << '|'
			   << setw(tablewidth) << lis_test(pow(10, i), loop) << '|'
			   << setw(tablewidth) << set_test(pow(10, i), loop) << '|' << '\n';

		auto t2 = system_clock::now();
		if (progr < i * 100 / log10(n_max - n_min)) {
			progr = i * 100 / log10(n_max - n_min);
			cout << "progres: [" << progr << "%]\t"
				 << "processed N: [" << pow(10, i) << "]\t"
				 << "last culculation time: [" << duration_cast<milliseconds>(t2 - t1).count()
				 << " ms]\n";
		}
	}

	return 0;
}