import re
from math import prod
from string import punctuation

data = open("day03/input.txt").read().strip()

nums = []
symbols = set()
re_symbols = "|".join(re.escape(s) for s in punctuation if s != ".")
width = len(data.split("\n")[0])
height = len(data.split("\n"))

for i, line in enumerate(data.split("\n")):
    for m in re.finditer(r"\d+", line):
        nums.append((m.group(), i, m.start()))
    for m in re.finditer(re_symbols, line):
        symbols.add((i, m.start()))


def coverage(num, row, col):
    return [
        (y, x)
        for y in range(row - 1, row + 2)
        for x in range(col - 1, col + len(num) + 1)
        if 0 <= y <= width and 0 <= x <= height
    ]


p1 = 0
for n in nums:
    num, row, col = n
    cov = coverage(*n)
    if any(s in cov for s in symbols):
        p1 += int(num)
print(f"Part 1: {p1}")

p2 = 0
for s in symbols:
    matching_nums = set()
    for n in nums:
        num, row, col = n
        if s in coverage(*n):
            matching_nums.add(int(num))
        if len(matching_nums) == 2:
            p2 += prod(matching_nums)
            break
print(f"Part 2: {p2}")