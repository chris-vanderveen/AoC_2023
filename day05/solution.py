def parse_maps(text):
    maps = text.split('\n\n')
    parsed_maps = []
    for map_text in maps:
        map_lines = map_text.split('\n')[1:]
        parsed_map = [tuple(map(int, line.split())) for line in map_lines]
        parsed_maps.append(parsed_map)
    return parsed_maps

def find_value(value, map):
    for triple in map:
        dest = int(triple[0])
        start = int(triple[1])
        length = int(triple[2])
        if start <= value < start + length:
             return dest + (value - start)
    return value

def find_location(seed, maps):
    value = seed
    for map in maps:
        value = find_value(value, map)
        if value is None:
            return None
    return value

def find_seed(location, maps):
    value = location
    for map in reversed(maps):
        value = find_value_reverse(value, map)
        if value is None:
            return None
    return value

def find_value_reverse(value, map):
    for triple in map:
        dest = int(triple[0])
        start = int(triple[1])
        length = int(triple[2])
        if dest <= value < dest + length:
            return start + (value - dest)
    return value

def main():
    with open('input.txt', 'r') as f:
        seeds = list(map(int, f.readline().split()[1:]))
        f.readline() # This eats the extra \n (cursed code) 
        text = f.read()

    seed_locp1 = {}
    maps = parse_maps(text)

    for seed in seeds:
        location = find_location(seed, maps)
        seed_locp1[seed] = location

    print(f'Part 1 - Seed {min(seed_locp1, key=seed_locp1.get)} is at location {min(seed_locp1.values())}')

    for i in range(8572252, 2000000000): # From previous failures we know that 8572252 is too low, so we can start here.
        seed = find_seed(i, maps)
        for j in range(0, len(seeds), 2):
            if seeds[j] <= seed < seeds[j] + seeds[j+1]:
                print(f'Part 2 - Seed {seed} is at location {i}')
                return 'Success'

    for i in range(0, len(seeds), 2):
        print(f'range is {seeds[i]} to {seeds[i+1] + seeds[i]}')
        
if __name__ == '__main__':
    main()