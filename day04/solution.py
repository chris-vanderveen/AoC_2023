def main():
    p1 = 0
    p2 = 0
    with open('day04/lotto.txt', 'r') as f:
        data = f.read().splitlines()

    winning, numbers = parser(data)
    print(winning)
    print(numbers)
    p1 = calc_score(winning, numbers)
    p2 = calc_cards(winning, numbers)

    print(f"Part 1: {p1}")
    print(f"Part 2: {p2}")

def parser(input):
    winning = []
    cards = []
    numbers = []
    for card in input:
        card = card.split(": ")
        cards.append(card[1].strip())

    for nums in cards:
        winning.append(nums.split('|')[0].strip())
        numbers.append(nums.split('|')[1].strip())

    for i, nums in enumerate(winning):
        nums = nums.split()
        winning[i] = set(nums)

    for i, nums in enumerate(numbers):
        nums = nums.split()
        numbers[i] = set(nums)

    return winning, numbers

def calc_score(winning, numbers):
    score = 0
    for win, num in zip(winning, numbers):
        intersect = win.intersection(num)
        if len(intersect) > 0:
            score += 2**(len(intersect) - 1)

    return score

def calc_cards(winning, numbers, start=0):
    if start >= len(winning):
        return 0

    intersect = winning[start].intersection(numbers[start])
    total_cards = 1  # count the current card

    for num in intersect:
        num = int(num)
        for i in range(1, num + 1):
            if start + i < len(winning):
                total_cards += calc_cards(winning, numbers, start + i)

    return total_cards

main()