const { readFile,writeFile } = require('fs')
const { 2: fileName} =  process.argv
const util = require('util')


~async function(){

 try {
 const csvContents = await util.promisify(readFile)(fileName,{encoding: 'utf-8'});
 let [objProps,...objValues] = csvContents.split('\r\n');
 const finalJson = []

 objProps = objProps.split(',');

  for (const element of objValues){
    const json = {}
    const objValue = element.split(',');
      for( let i=0; i<objProps.length ;i++){
         json[objProps[i]]= objValue[i]
      }
      finalJson.push(json)
  }

  console.info(JSON.stringify(finalJson))

  await util.promisify(writeFile)('output.json',JSON.stringify(finalJson))
  console.info('Wrote succesfully')
   

 } catch (error) {
   console.error(error);
 }
  
}()