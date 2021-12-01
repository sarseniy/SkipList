#include "tests.h"
#include "SkipList.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <chrono>

class TimeMeasure {
public:
	void start() {
		start_time_ = std::chrono::high_resolution_clock::now();
	}
	void stop() {
		stop_time_ = std::chrono::high_resolution_clock::now();
	}
	size_t elapsed() const {
		auto elapsed_time = stop_time_ - start_time_;
		return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count();
	}
private:
	std::chrono::high_resolution_clock::time_point start_time_, stop_time_;
};

class RandomGenerator {
public:
	static int create_integer(int min, int max) {
		std::mt19937_64 engine(42);
		std::uniform_int_distribution<int> distr(min, max);
		int v;
		v = distr(engine);
		return v;
	}

	static size_t create_integer_t(int min, int max, size_t seed=42) {
		std::mt19937_64 engine(seed);
		std::uniform_int_distribution<size_t> distr(min, max);
		size_t v;
		v = distr(engine);
		return v;
	}
};

int main()
{
    TEST();
	std::ofstream outf("res.txt");
	size_t num_of_series = 1000;
	std::vector<std::list<int>> l(num_of_series);
    std::vector<SkipList<int>> v;
	for (size_t i = 0; i < num_of_series; i++)
	{
		v.push_back(SkipList<int>(10ul));
	}
	TimeMeasure t;
	
	for (size_t i = 0; i < 1000; i++)
	{
		size_t ind = RandomGenerator::create_integer_t(1, 10000000, i);

		for (size_t j = 0; j < num_of_series; j++)
		{
			/*auto it = l[j].begin();
			for (size_t k = 0; l[0].size() != 0 and k < ind % l[0].size(); k++)
			{
				it++;
			}
			l[j].insert(it, ind);*/
			v[j].Insert(ind, 0);
		}
		std::cout << i << std::endl;
	}

	for (size_t i = 0; i < 1000; i++)
	{
		size_t ind = RandomGenerator::create_integer_t(1, 10000000, i);
		t.start();
		for (size_t j = 0; j < num_of_series; j++)
		{
			//std::find(l[j].begin(), l[j].end(), ind);
			v[j].Find(ind);
		}
		t.stop();

		double time_gone = t.elapsed();
		double res = time_gone / static_cast<double>(num_of_series);
		std::cout << std::fixed << i << ' ' << res << '\n';
		outf << std::fixed << i << ' ' << res << '\n';
	}

    return 0;
}