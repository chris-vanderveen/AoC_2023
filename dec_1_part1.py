with open('dec_1.txt') as f:
    data = f.read()

data = data.splitlines()
count = 0
first = 0
index = 0
last_num = 0
number = ''
nums = []

for value in data:
    count = 0
    first = 0
    last = 0
    number = ''
    for i in range(len(value)):
        if value[i].isnumeric() and count == 0:
            first = i
            last = i
            count += 1
        elif value[i].isnumeric() and count > 0:
            last = i
            count += 1

    number = number + value[first]
    number = number + value[last]
    nums.append(int(number))

print(sum(nums))