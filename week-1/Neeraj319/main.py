import json
import sys
dict = {}
keys_list = []
empty_list = []
with open(sys.argv[1] , "r") as file:
    for i in file.readline().split(","):
        if i == "age\n":
            dict["age"] = None
            keys_list.append("age")
        else:
            dict[i] = None
            keys_list.append(i)
    for line in file.readlines():
        dict = {**dict}
        for j , keys in enumerate(line.split(',')):
            if keys_list[j] == "age":
                dict[keys_list[j]] = float(keys)
            else:
                dict[keys_list[j]] = keys
        empty_list.append(dict)
with open('example.json' , 'w') as file:
    json.dump(empty_list , file)