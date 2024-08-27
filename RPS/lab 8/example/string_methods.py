def number_of_words(line):
     return sum(map(lambda x: int(x.isalpha()), line.split()))

def number_of_defined_characters(line, symbol):
    return line.count(symbol)

def number_of_symbols(line): 
     return len(line)

def number_of_universal_symbols(line):
    return len(set(line))
