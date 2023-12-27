#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <numeric>
#include <vector>

struct Node {
	std::string left;
	std::string right;

	Node() : left(""), right("") {}
	Node(const std::string& left, const std::string& right) : left(left), right(right) {}

	void print() const {
		std::cout << "Left: " << left << ", Right: " << right << std::endl;
	}
};

int part1(std::unordered_map<std::string, Node> nodeMap, std::string directions);
long int part2(std::unordered_map<std::string, Node> nodeMap, std::string directions);
unsigned long long int lcm(unsigned long long int a, unsigned long long int b);
unsigned long long int partTwo(std::unordered_map<std::string, Node> nodeMap, std::string directions);

int main(void) {
	std::ifstream f("input.txt");
	if (!f) {
		std::cerr << "Unable to open file";
	}
	int p1;
	std::string directions, dummy, line, name, left, right;
	std::unordered_map<std::string, Node> nodeMap;
	std::getline(f, directions);
	std::getline(f, dummy);

	while (std::getline(f, line)) {
		name = line.substr(0, 3);
		left = line.substr(7, 3);
		right = line.substr(12, 3);

		Node node = Node(left, right);
		nodeMap[name] = node;
	}

	p1 = part1(nodeMap, directions);
	std::cout << "Part 1: " << p1 << std::endl;
	long int p2 = partTwo(nodeMap, directions);
	std::cout << "Part 2: " << p2 << std::endl;

	return 0;
}

int part1(std::unordered_map<std::string, Node> nodeMap, std::string directions) {
	std::string name, left, right;
	int count = 0;

	left = nodeMap["AAA"].left;
	right = nodeMap["AAA"].right;

	while (name != "ZZZ") {
		char direction = directions[count % directions.size()];

		if (direction == 'L') {
			name = left;
			left = nodeMap[name].left;
			right = nodeMap[name].right;
			count++;
		}
		else if (direction == 'R') {
			name = right;
			left = nodeMap[name].left;
			right = nodeMap[name].right;
			count++;
		}
	}

	return count;
}

unsigned long long int partTwo(std::unordered_map<std::string, Node> nodeMap, std::string directions) {
	std::unordered_map<std::string, Node> ends_with_A;
	std::vector<long long int> steps_to_Z;
	std::string name;

	for (const auto& pair : nodeMap) {
		name = pair.first;
		if (name.back() == 'A') {
			ends_with_A[name] = nodeMap[name];
		}
	}

	for (const auto& pair : ends_with_A) {
		std::string node = pair.first;
		unsigned long long int count = 0;
		
		while (node.back() != 'Z') {
			char direction = directions[count % directions.size()];
			if (direction == 'L') {
				node = nodeMap[node].left;
			}
			else if (direction == 'R') {
				node = nodeMap[node].right;
			}
			count++;
		}
		steps_to_Z.push_back(count);
	}

	unsigned long long int lcm_value = steps_to_Z[0];
	for (size_t i = 1; i < steps_to_Z.size(); i++) {
		lcm_value = lcm(lcm_value, steps_to_Z[i]);
	}

	return lcm_value;
}

unsigned long long int lcm(unsigned long long int a, unsigned long long int b) {
	unsigned long long int temp1 = a, temp2 = b;

	while (temp1 != temp2) {
		if (temp1 > temp2)
			temp1 -= temp2;
		else
			temp2 -= temp1;
	}

	unsigned long long int gcd = temp1;
	return (a / gcd) * b;
}