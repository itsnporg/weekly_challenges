import csv
import json

with open('input.csv', 'r') as infile:
    csv_input = list(csv.reader(infile))

    json_output = []
    keys = csv_input[0]

    for values in csv_input[1:]:
        output_dict = {}
        for key, val in zip(keys, values):
            output_dict[key] = val
        output_dict['age'] = int(output_dict['age'])
        json_output.append(output_dict)
    
    print(json_output)
    
    with open('output.json', 'w') as outfile:
        json.dump(json_output,outfile)