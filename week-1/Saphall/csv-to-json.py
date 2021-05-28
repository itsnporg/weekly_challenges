import sys
import csv
import json

input_csv = ''
output_json = ''

try:
    input_csv = sys.argv[1]
except:
    print('[-] Please enter name of csv file to be converted.')
    exit(0)


def convert(input_csv, output_json):
    try:
        output_json = sys.argv[2]
    except:
        output_json = 'output.json'

    jsonArray = []
    with open(input_csv) as csvv:
        csvReader = csv.DictReader(csvv)
        for row in csvReader:
            row['age'] = int(row['age'])
            jsonArray.append(row)
    with open(output_json, 'w') as jsonn:
        jsonString = json.dumps(jsonArray, indent=4)
        jsonn.write(jsonString)


convert(input_csv, output_json)
