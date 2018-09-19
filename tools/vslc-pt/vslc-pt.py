import collections
import pytablewriter


class SelectSet:

    def __init__(self, line):
        # example: line = "SELECT(E' -> ε) = {),p,b,g,e,h,m,{,i}"
        left = line.split("=")[0][7:-2]
        right = line.split("=")[1].strip()
        # dec
        self.non_terminator = ""
        self.terminators = []
        # get production
        self.production = left
        # get non_terminator
        for c in left:
            if c != " ":
                self.non_terminator += c
            else:
                break
        # get terminators
        count = 0
        for c in right[0:len(right) - 1]:
            if count % 2 == 1:
                self.terminators.append(c)
            count += 1


if __name__ == '__main__':
    select_set_file = open('select.txt', 'r')
    select_sets = []

    try:
        for line in select_set_file:
            select_sets.append(SelectSet(line))
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
                parsing_table[s.non_terminator][t] = s.production

    # generate parsing table
    writer = pytablewriter.writer.MarkdownTableWriter()
    writer.table_name = "Parsing Table"
    writer.header_list = [' '] + terminators
    matrix = []
    for non_terminator in parsing_table.keys():
        line = [non_terminator]
        for t in terminators:
            if t in parsing_table.get(non_terminator).keys():
                line.append(' ' + parsing_table[non_terminator][t] + ' ')
            else:
                line.append(' ')
        matrix.append(line)
    writer.value_matrix = matrix
    writer.write_table()
