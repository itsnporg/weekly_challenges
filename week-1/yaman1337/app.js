const fs = require('fs');
const fileName = process.argv[2];

convert2json(fileName)

function convert2json(fileName) {
  fs.readFile(fileName, 'utf-8', (err, csv) => {
    if (err) {
      console.log('Failed to load csv');
      return
    };
    const arrayOfJson = [];
    const csv2array = csv.split('\n');
    const keys = csv2array[0].split(',');

    const arrayOfValues = csv2array.slice(1);
    arrayOfValues.forEach(item => {
      const jsonData = {};
      const eachArrayOfValue = item.split(',');
      for (var i = 0; i < keys.length; i++) {
        jsonData[keys[i]] = eachArrayOfValue[i];
      };
      arrayOfJson.push(jsonData);
    });

    fs.writeFile('output.json',JSON.stringify(arrayOfJson),(err) => {
      if(err) {
        console.log(err.message);
        return
      }
      console.log('File successfully saved in output.json');
    });
    
  });
}




