import sys


def is_int(arg):
    try:
        int(arg)
        return True
    except ValueError:
        return False

def is_float(arg):
    try:
        float(arg)
        return True
    except ValueError:
        return False



def remove_newline(arr):
    tmp = len(arr) - 1
    arr[tmp] = arr[tmp].replace('\n','')
    return arr

def convert_each_line(columns,line):
    res =''
    line = line.split(',')
    padding = 8
    line = remove_newline(line)
    for i in range(len(columns)):
        if is_int(line[i]):
            line[i] = int(line[i])
        elif is_float(line[i]):
            line[i] = float(line[i])
        res += ' ' * padding
        res += f'"{columns[i]}":"{line[i]}"' if not is_int(line[i]) and not is_float(line[i]) else f'"{columns[i]}":{line[i]}'

        if i != len(columns) - 1:
            res += ',\n'
        else:
            res += '\n' 


    return res


def solution(input_csv,output_json,format):
    j = open(output_json,'w')
    if format == 'hash':
        j.write('{\n')
    else:
        j.write('[\n')
    with open(input_csv,'r') as f:
        field_names = f.readline().split(',')
        field_names = remove_newline(field_names)
        arr = f.readlines()
        for ind,each_line in enumerate(arr):
            tmp = convert_each_line(field_names,each_line)
            j.write('    {\n')
            j.write(tmp)
            if ind == len(arr)-1:
                j.write('    }\n')
            else:
                j.write('    },\n')
        if format == 'hash':
            j.write('}')
        else:
            j.write(']')
        j.close()



'''
format can be either array or hash
if output_json is specified,the output json file will be named accordingly
else it will be 'output.json' by default
'''

def main(argv):
    if len(argv) > 3:
        print('Invalid no of arguments')
    input_csv = argv[1]
    if len(argv) == 3:
        output_json = argv[2]
    else:
        output_json = 'output.json'
    solution(input_csv,output_json,format = 'array')
        




if __name__ == '__main__':
    main(sys.argv)
