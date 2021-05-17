import csv
import json

csvfile=open('../data.csv','r')
jsonfile=open('result.json','w')

fieldnames=("first_name","last_name","age")
datas=csv.DictReader(csvfile,fieldnames)
datas=list(datas)
final_data=[]
for d in datas[1:]:
    final_data.append(d)
print(final_data)

json.dump(final_data,jsonfile)