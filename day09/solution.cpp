#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::istream_iterator;

bool zeroes(const vector<long> &nums) {
	return all_of(nums.begin(), nums.end(), [](long x) { return x == 0; });
}

static vector<long> find_difference(const vector<long> &nums) {
	vector<long> difference;

	for (size_t i = 1; i < nums.size(); i++) {
		difference.push_back(nums[i] - nums[i - 1]);
	}

	return difference;
}

static long find_next(const vector<long> &nums) {
    vector<long> differences = find_difference(nums);

    if (zeroes(differences)) {
        if (differences.size() == 1) {
            return nums.back();
        }
        return nums.back() + differences.back();
    }

    return nums.back() + find_next(differences);
}

static long find_prev(const vector<long> &nums) {
	vector<long> difference = find_difference(nums);

	if (zeroes(difference)) {
		return nums.front() - difference.front();
	}

	return nums.front() - find_prev(difference);
}

int main() {
	ifstream file("input.txt");

	long part1 = 0, part2 = 0;
	string line;
	while(getline(file, line)) {
		istringstream iss(line);
		vector<long> nums(istream_iterator<int>(iss), {});
		part1 += find_next(nums);
		part2 += find_prev(nums);

		nums.clear();
	}

	cout << "Part 1: " << part1 << endl;
	cout << "Part 2: " << part2 << endl;

	return 0;
}