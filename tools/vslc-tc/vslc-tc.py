import collections
from constants import SymbolType


class SelectSet:

    def __init__(self, line):
        # example: line = "SELECT(E' -> ε) = {),p,b,g,e,h,m,{,i}"
        left = line.split("=")[0][7:-2]
        right = line.split("=")[1].strip()
        # dec
        self.non_terminator = ""
        self.terminators = []
        production_right = []
        self.converted_production_right = []
        # get production
        self.production = left
        # get non_terminator
        for c in left:
            if c != " ":
                self.non_terminator += c
            else:
                break
        for c in left.split(" -> ")[1]:
            if c != " ":
                if c == "_":
                    production_right[-1] += c
                else:
                    production_right.append(c)
        for c in production_right:
            self.converted_production_right.append(SymbolType[c])
        # get terminators
        count = 0
        for c in right[0:len(right) - 1]:
            if count % 2 == 1:
                self.terminators.append(c)
            count += 1


if __name__ == '__main__':
    select_set_file = open('select.txt', 'r', encoding='utf-8')
    select_sets = []

    try:
        for line in select_set_file:
            newline = line.replace("'", "_")
            select_sets.append(SelectSet(newline))
    finally:
        select_set_file.close()

    terminators = []
    for s in select_sets:
        for t in s.terminators:
            terminators.append(t)
    temp = []
    for item in terminators:
        if item not in temp:
            temp.append(item)

    terminators = temp

    parsing_table = collections.defaultdict(dict)

    for t in terminators:
        for s in select_sets:
            if t in s.terminators:
                if t in parsing_table[s.non_terminator].keys():
                    raise Exception()  # Check parsing table
                parsing_table[SymbolType[s.non_terminator]][SymbolType[t]] = s.converted_production_right

    # generate expressions
    expressions = []
    for n in parsing_table:
        for t in parsing_table[n]:
            right_symbol = ''
            for s in parsing_table[n][t]:
                right_symbol += ", "+s
            expression = "TABLE_CELL_MACRO_{num}({line}, {column}, {left_symbol} {right_symbol});".format(
                num=len(parsing_table[n][t]), line=n, column=t, left_symbol=n, right_symbol=right_symbol)
            expressions.append(expression)
    with open('expressions.txt', 'w') as f:
        for expression in expressions:
            f.write(expression+"\n")
