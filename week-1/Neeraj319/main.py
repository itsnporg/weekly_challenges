import csv
import sys
import json
with open(sys.argv[1], mode='r') as csv_file:
    csv_reader = csv.DictReader(csv_file)
    save_in_list = list()
    for i in csv_reader:
        i['age'] = float(i['age'])
        save_in_list.append(i)
    with open('example.json' , 'w') as file:
        json.dump(save_in_list , file)
