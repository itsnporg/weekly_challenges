// Created with Deno as runtime,
// don't forget to use runtime flags
// --allow-read and --allow-write

// take first argument as the csv file and read to text
const text = Deno.readTextFileSync(Deno.args[0]);

// separate out header first line and body
const [firstLine, ...lines] = text.split("\n");
// assignt the header items to keys array
const keys = firstLine.split(",");
// initialize a empty array to contain all objects
const list = [];
// for each line in the body/lines
lines.forEach((line) => {
  // initialize a empty object
  const obj = {};
  // store individual items of line in items array
  const items = line.split(",");
  // for each item in keys, we create a new pair in obj with
  // corresponding data fromm items and parseint on age
  keys.forEach((_, index) => {
    if (keys[index] === "age") {
      obj[keys[index]] = parseInt(items[index]);
    } else {
      obj[keys[index]] = items[index];
    }
  });
  // push the newly created object inside list array
  list.push(obj);
});

// store the json obtained in string form for writing to file
const data = JSON.stringify(list);
// write the json data to data.json file
Deno.writeTextFileSync("./data.json", data);
