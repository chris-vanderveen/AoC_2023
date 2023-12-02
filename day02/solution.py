def main():
    print(f'Part 1: {part1()}')
    print(f'Part 2: {part2()}')

def part1():
    sum = 0
    with open('day02/input.txt') as f:
        input = f.read()

    game = clean_input(input)
    for i in range(1, len(game) + 1):
        if compare_cubes(game[i]):
            sum += i
    
    return sum

def part2():
    sum_powers = 0
    with open('day02/input.txt') as f:
        input = f.read()

    game = clean_input(input)
    for i in range(1, len(game) + 1):
        red = find_max('red', game[i])
        green = find_max('green', game[i])
        blue = find_max('blue', game[i])
        sum_powers += red * green * blue

    return sum_powers

def clean_input(input: str) -> dict:
    games = {}
    input = input.split('\n')

    for i in range(len(input)):
        if i < 10:
            games[i+1] = input[i][8:].strip().split('; ')
        elif i >= 10 and i < 99:
            games[i+1] = input[i][9:].strip().split('; ')
        else:
            games[i+1] = input[i][10:].strip().split('; ')

    return games

def compare_cubes(game: list) -> bool:
    for handful in game:
        hand = handful.split(', ')
        for dice in hand:
            if 'red' in dice:
                num_dice = int(dice[:2])
                if num_dice > 12:
                    return False
            elif 'green' in dice:
                num_dice = int(dice[:2])
                if num_dice > 13:
                    return False
            elif 'blue' in dice:
                num_dice = int(dice[:2])
                if num_dice > 14:
                    return False
    
    return True

def find_max(color: str, game: list) -> int:
    max = 0
    for handful in game:
        hand = handful.split(', ')
        for dice in hand:
            if color in dice:
                num_dice = int(dice[:2])
                if num_dice > max:
                    max = num_dice
    return max

if __name__ == "__main__":
    main()