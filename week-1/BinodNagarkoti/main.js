/** @format */
/**
 * node version v16.3.0
 * OS: Windows 11
 * Editor: VS Code 1.58.1
 * Author: Binod Nagarkoti
 * Date (DD/MM/YY): 15/07/2021
 */

/**
 * how to run
 * install node and add to env path
 * open this file with any editor.
 * type node main.js data.csv
 * note: data.csv or any csv file should availabel in the same director as main.js
 */
const sourceFileName = process.argv.slice(2);
const fs = require('fs');

fs.readFile(sourceFileName.toString(), 'utf8', async (error, data) => {
    if (error) {
        console.log(error.message);
        return;
    } else {
        const rows = getRows(data); //['r1c1,r1c2,r1cn','rncn,rncn,rncn']

        if (rows.length > 1) {
            // extract keys from rows => ['k1', 'k2','k3',..., 'kn' ]
            const keys = getKeys(rows);
            // extract all values => [['v1','v2','v3','vn'],['v1','v2','v3','vn'],...['v1','v2','v3','vn']]
            const values = getValues(rows);
            // generate json object from given keys and values. => [obj1, obj2,...objn]
            const json = getJSONObject(keys, values);
            // create and json file in working directory.=> result.json
            writeToJsonFile(json);
        } else {
            // if rows has length of 1 or 0.
            console.log('empty file or bad format.');
        }
    }
});

/* helper function */

/** function to create json file
 * @param {Object} jsonData the json object
 * @return {void}
 *
 */
const writeToJsonFile = (jsonData) => {
    fs.writeFileSync('result.json', JSON.stringify(jsonData, null, 2));
};

/** function to generate json object
 * @param {String[]} keys string array, keys for the json object.
 * @param {string[][]} values two dimesional string array.
 * @return {Object}     return the json object.
 */
const getJSONObject = (keys, values) => {
    return values.map((value) => {
        var temp_obj = new Object();
        for (let i = 0; i < keys.length; i++) {
            temp_obj[keys[i]] = parseIntIf(value[i]);
        }
        return temp_obj;
    });
};

/** function to get values from rows
 * @param {String[]} rows string arrays i.e ['k1,k2,k3...kn','v1,v2,v3..vn','v1,v2,v3..vn',...'v1,v2,v3..vn']
 * @return {String[][]} return two demensional string array. i.e [ ['v1','v2',vn],... [v1,v2,vn]]
 *
 */
const getValues = (rows) => rows.slice(1, rows.length).map((item) => item.split(','));

/** function to get values from rows
 * @param {String[]} rows string arrays i.e ['k1,k2,k3...kn','v1,v2,v3..vn','v1,v2,v3..vn',...'v1,v2,v3..vn']
 * @return {String[]} return string array. i.e [ 'k1','k2',...,kn]
 *
 */
const getKeys = (rows) => rows[0].split(',');

/** function to get values from rows
 * @param {String} data string with escape sequence like newline(\n), Carriage Return (\r).
 * @return {String[]} return string array. i.e  ['s1','s2',..,sn]
 *
 */
const getRows = (data) => data.split(/\r\n|\n/);

/** function to get values from rows
 * @param {String} value string with escape sequence like newline(\n), Carriage Return (\r).
 * @return {String|Number} return number if it is parseable otherwise return string value
 *
 */
const parseIntIf = (value) => {
    if (parseInt(value)) {
        return parseInt(value);
    }
    return value;
};
