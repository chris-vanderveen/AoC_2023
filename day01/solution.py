
def main():
    numbers = ['zero', 'one', 'two', 'three', 'four', 'five',
               'six', 'seven', 'eight', 'nine']
    integers = []
    
    with open('dec_1.txt') as f:
        data = f.read()

    lines = data.splitlines()
    
    for i in range(len(lines)):
        new_string = replace_words(lines[i])
        lines[i] = new_string

    for line in lines:
        integers.append(first_last(line))

    print(sum(integers))

def replace_words(input_string: str) -> str:
    numbers = {'zero': '0', 'one': '1', 'two': '2', 'three': '3', 'four': '4', 
               'five': '5', 'six': '6', 'seven': '7', 'eight': '8', 'nine': '9'}
    
    for word, num in numbers.items():
        if word in input_string:
            new_word = word[0] + num + word[-1]
            input_string = input_string.replace(word, new_word)
    
    return input_string

def first_last(line: str) -> int:
    numbers = []
    num = ''

    for char in line:
        if char.isnumeric():
            numbers.append(char)
            
    num += numbers[0]
    num += numbers[-1]

    return int(num)

main()