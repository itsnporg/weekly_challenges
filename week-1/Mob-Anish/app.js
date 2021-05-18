//--------- CSV-TO-JSON ------------//

const fs = require('fs'); // fs built-in module
const path = require('path'); // built-in module

// Path to csv file
const filePath = path.join('../', 'data.csv');

// Reading csv file
const csv = fs.readFileSync(filePath, {encoding: 'utf-8'});

// csv to json converter function
const csvToJsonConverter = (csvFile) => {
  // It will contain the final JSON objects in an array
  const output = [];

  // 1) Convert csv data into array using split method
  const array = csvFile.split('\r');

  // 2) array[0] contains the key properties of the json data like: first_name,age.
  const keys = array[0].split(',');
  console.log(keys);

  // 3) Looping through the values of array from index 1
  // Index-1 contains the values of the key properties(keys).
  array.forEach((el, i) => {
    // Index 0 is useless in here.
    if (i < 1) return;

    // The final key value pair will be stored in an object.
    const resultObj = {};

    // Convert the values of current index in an array using split
    // trim remove the /n in your values after split in array(1)
    const currValues = array[i].trim().split(',');

    // Now assigning the values to key properties in an object form
    keys.forEach((el, i) => {
      resultObj[keys[i]] = currValues[i];
    });

    // Pushing to file result array
    output.push(resultObj);
  });

  // Converting the age value to number
  output.forEach((el, i) => {
    if (el.age) {
      el.age = parseInt(el.age);
    }
  });

  console.log(output);
  
  // Finally converting the final output of array objects into json
  fs.writeFileSync('result.json', JSON.stringify(output));
};

if (csv) {
  // Calling converter function
  csvToJsonConverter(csv);
}
