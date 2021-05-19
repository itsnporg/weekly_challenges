const fs = require("fs");
const fileName = process.argv[2];

csvToJson(fileName);

function csvToJson(filename) {
  fs.readFile(filename, "utf-8", (err, csv) => {
    if (err) console.log(err);

    const jsonArray = [];
    const csvArray = csv.split("\n");

    const keys = csvArray[0].trim().split(",");
    const values = csvArray.slice(1);

    values.forEach((item) => {
      const json = {};
      const individualValues = item.trim().split(",");
      for (let i = 0; i < keys.length; i++) {
        json[keys[i]] = individualValues[i];
      }
      jsonArray.push(json);
    });

    writeToJson(JSON.stringify(jsonArray));
  });

  const writeToJson = function (jsonArray) {
    fs.writeFile("output.json", jsonArray, (err) => {
      if (err) console.log(err);
      console.log("DONE! Check output.json");
    });
  };
}
