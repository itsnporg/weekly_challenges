const fs = require("fs");
const fileName = process.argv[2];

const csvToJSON = (fileName) => {
  fs.readFile(fileName, "utf-8", (error, csvData) => {
    if (error) {
      return console.log("Failed to load csv file.");
    }
    const arrayOfJson = [];
    const csv2array = csvData.split("\n");
    const keys = csv2array[0].trim().split(",");
    const arrayOfValues = csv2array.slice(1);

    arrayOfValues.forEach((item) => {
      const result = {};
      const eachArrayOfValue = item.trim().split(",");
      for (let i = 0; i < keys.length; i++) {
        result[keys[i]] = eachArrayOfValue[i];
      }
      arrayOfJson.push(result);
    });

    fs.writeFile("data.json", JSON.stringify(arrayOfJson), (error) => {
      if (error) {
        console.log(error.message);
        return;
      }
      console.log("Successfully saved in data.json file.");
    });
  });
};

csvToJSON(fileName);