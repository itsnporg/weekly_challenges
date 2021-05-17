import os
import csv
import json 

cur_dir=os.getcwd()
base_dir=os.path.dirname(cur_dir)
with open(os.path.join(base_dir,'data.csv')) as data:
    dicts=csv.DictReader(data,delimiter=',')
    json_output=[]
    for row in dicts:
        row['age']=int(row['age'])
        json_output.append(row)

with open(os.path.join(cur_dir,'json_output.json'),'w') as json_file:
    json.dump(json_output,json_file)


