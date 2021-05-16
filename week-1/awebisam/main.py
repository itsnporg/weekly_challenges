import csv
import json
import os

cwd = os.path.dirname(__file__)
csv_path = os.path.join(os.path.dirname(cwd), 'data.csv')
json_path = os.path.join(cwd, 'output.json')

with open(csv_path, newline='') as input_file, open(json_path, 'w') as output_file:
    csv_reader = csv.reader(input_file)
    csv_headings = next(csv_reader)

    data_in_dict = list(csv.DictReader(input_file, csv_headings))

    for row in data_in_dict:
        age = int(row.get('age'))
        row['age'] = age

    json.dump(data_in_dict, output_file)
