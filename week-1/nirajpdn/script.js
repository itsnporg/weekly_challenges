const fs = require("fs");
const path = require("path");
const filePath = path.join(__dirname, "../data.csv");
function csvToJSON(filePath) {
  fs.readFile(filePath, "utf8", (error, csvData) => {
    let rows = csvData.split("\n");
    let output = [];
    const keys = rows[0].split(",");
    for (let row of rows) {
      const result = {};
      if (rows.indexOf(row) !== 0) {
        const rowDataArray = row.split(",");
        for (let i in rowDataArray) {
          result[keys[i]] = rowDataArray[i];
        }
        output.push(result);
      }
    }
    output = JSON.stringify(output);
    fs.writeFile("result.json", output, (error) => {
      if (!error) {
        console.log("Output is written in result.json file in same directory");
      }
    });
  });
}
csvToJSON(filePath);
