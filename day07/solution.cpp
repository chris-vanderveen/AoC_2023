#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#define FILENAME "input.txt"

struct CardHand
{
	std::string hand;
	int bet;
	int type;

	CardHand(const std::string &hand, int bet, int type = 0) : hand(hand), bet(bet), type(type) {}
	
};

int hand_type(CardHand& info);
std::tuple<char, int, char, int> most_and_second_most_repeated_char(const std::string &str);
std::string replace_char(const std::string& str, char old_char, char new_char);
bool compare_hands(const std::string str1, std::string str2);
int wild_hand_type(CardHand& cardhand);
void part1(void);
void part2(void);


std::ostream& operator<<(std::ostream &os, const CardHand &hand) {
    os << "Hand: " << hand.hand << ", Bet: " << hand.bet << ", Type:" << hand.type;
    return os;
}

int main() {
	part1();
	part2();
	return 0;
}

int hand_type(CardHand& info) {
	std::string cards = info.hand;
	auto [max_char, max_count, second_max_char, second_max_count] = most_and_second_most_repeated_char(cards);
	// Five of a kind
	if (max_count == 5) {
		return 7;
	} // Four of a kind
	else if (max_count == 4) {
		return 6;
	} // Full house
	else if (max_count == 3 && second_max_count == 2) {
		return 5;
	} // Three of a kind
	else if (max_count == 3) {
		return 4;
	} // Two pairs
	else if (max_count == 2 && second_max_count == 2) {
		return 3;
	} // One pair
	else if (max_count == 2) {
		return 2;
	} else {
		return 1;
	}
}

std::tuple<char, int, char, int> most_and_second_most_repeated_char(const std::string &str) {
    std::map<char, int> char_counts;
    for (char c : str) {
        char_counts[c]++;
    }

    char max_char = str[0], second_max_char = '\0';
    int max_count = char_counts[max_char], second_max_count = 0;
    for (const auto &pair : char_counts) {
        if (pair.second > max_count) {
            second_max_char = max_char;
            second_max_count = max_count;
            max_char = pair.first;
            max_count = pair.second;
        } else if (pair.second > second_max_count && pair.first != max_char) {
            second_max_char = pair.first;
            second_max_count = pair.second;
        }
    }

    return {max_char, max_count, second_max_char, second_max_count};
}

int card_value(char c) {
	if (c >= '2' && c <= '9') {
		return c - '0';
	}
	switch (c)
	{
	case 'T': return 10;
	case 'J': return 1; // NOTE: This change makes part 1 wrong, Change it back to 11 to make Part 1 work again and vice versa.
	case 'Q': return 12;
	case 'K': return 13;
	case 'A': return 14;
	default: throw std::invalid_argument("Invalid card character.");
	}
}

bool compare_hands(const std::string str1, std::string str2) {
	for (int i = 0; i < 5; i++) {
		int val1 = card_value(str1[i]);
		int val2 = card_value(str2[i]);
		if (val1 != val2) {
			return val1 < val2;
		}
	}

	return false;
}

void part1(void) {
		std::ifstream file(FILENAME);
	if (!file) {
		std::cerr << "Unable to open file";
	}

	std::vector<CardHand> hands;
	std::string hand;
	int bet, winnings = 0;
	while(file >> hand >> bet) {
		CardHand data = CardHand(hand, bet);
		data.type = hand_type(data);
		if (hands.size() == 0) {
			hands.push_back(data);
		} else {
			bool inserted = false;
			for (int i = 0; i < hands.size() && !inserted; i++) {
				if ((data.type < hands[i].type) || ((data.type == hands[i].type) && (compare_hands(data.hand, hands[i].hand)))) {
					hands.insert(hands.begin() + i, data);
					inserted = true;
				}
			}
			if (!inserted) {
			hands.push_back(data);
			}
		}
	}

	for (int i = 0; i < hands.size(); i++) {
		winnings += hands[i].bet * (i + 1);
	}

	std::cout << "Part 1: " << winnings << std::endl;

	file.close();
}

void part2(void) {
	std::ifstream f(FILENAME);
	if (!f) {
		std::cerr << "Unable to open file";
	}

	std::vector<CardHand> hands;
	std::string hand;
	int bet, winnings = 0;
	while (f >> hand >> bet) {
		CardHand data = CardHand(hand, bet);
		data.type = wild_hand_type(data);
		if (hands.size() == 0) {
			hands.push_back(data);
		} else {
			bool inserted = false;
			for (int i = 0; i < hands.size() && !inserted; i++) {
				if ((data.type < hands[i].type) || ((data.type == hands[i].type) && (compare_hands(data.hand, hands[i].hand)))) {
					hands.insert(hands.begin() + i, data);
					inserted = true;
				}
			}
			if (!inserted) {
				hands.push_back(data);
			}
		}
	}
	for (int i = 0; i < hands.size(); i++) {
		winnings += hands[i].bet * (i + 1);
	}

	std::cout << "Part 2: " << winnings << std::endl;
	f.close();
}

std::string replace_char(const std::string& str, char old_char, char new_char) {
    std::string new_str = str;
    std::replace(new_str.begin(), new_str.end(), old_char, new_char);
    return new_str;
}

int wild_hand_type(CardHand& cardhand) {
    if (cardhand.hand.find('J') == std::string::npos) {
        return hand_type(cardhand);
    } else {
        int max_hand_type = 0;
        std::string cards = "23456789TJQKA";
        for (char c : cards) {
            CardHand new_cardhand = cardhand;
            new_cardhand.hand = replace_char(cardhand.hand, 'J', c);
            int new_hand_type = hand_type(new_cardhand);
            if (new_hand_type > max_hand_type) {
                max_hand_type = new_hand_type;
            }
        }
        return max_hand_type;
    }
}