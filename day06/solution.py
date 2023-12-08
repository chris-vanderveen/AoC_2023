def solution():
	with open('input.txt', 'r') as f:
		time = f.readline().split()[1:]
		record = f.readline().split()[1:]

	num_winsp1 = calc_winsp1(time, record)
	real_dist, real_time = part_2(time, record)
	num_winsp2 = calc_winsp2(real_time, real_dist)

	p1 = 1
	for num in num_winsp1:
		p1 *= num

	print(f'Part 1: {p1}')
	print(f'Part 2: {num_winsp2}')

def part_2(time, record):
	real_time = ''
	real_dist = ''

	for num in time:
		real_time += num
	for dist in record:
		real_dist += dist

	return int(real_dist), int(real_time)

def calc_winsp1(time, record):
	num_ways = []
	for i in range(len(time)):
		count = 0
		for j in range(int(time[i])):
			velocity = j
			time_left = int(time[i]) - j
			if (velocity * time_left) > int(record[i]):
				count += 1
		num_ways.append(count)

	return num_ways

def calc_winsp2(real_time, real_dist):
	count = 0
	for i in range(real_time):
		velocity = i
		time_left = real_time - i
		if (velocity * time_left) > real_dist:
			count += 1
	return count
	
solution()