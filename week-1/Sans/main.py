import sys

writefile = []

with open(sys.argv[1]) as mainfile:
    keys = mainfile.readline().replace("\n","").split(",")
    print (keys)
    for i in mainfile.read().splitlines():
        jsondata = {}
        i = i.split(",")
        for count, key in enumerate(keys):
            data = i[count]
            try:
                data = int(data)
            except ValueError:
                data = data
            finally:
                jsondata[key] = data
        writefile.append(jsondata)

output = str(writefile).replace("'", '"')
print(output)

with open("output.json", "w+") as outfile:
    outfile.write(output)