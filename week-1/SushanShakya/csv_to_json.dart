import 'dart:io';
import 'dart:convert';
void main() {
   File file =  File("../data.csv");
   File oFile = File('./output.json');
   List<String> lines = file.readAsLinesSync();
   List<String> titles = lines[0].split(',').toList();
   List<Map<String,dynamic>> data = [];
   lines.skip(1).forEach((e) {
      List<String> datum = e.split(',');
      Map<String,dynamic> current = {};
      for(int i = 0; i<titles.length; i++) {
         String currentTitle = titles[i]; 
         dynamic data;
         if(currentTitle == "age") {
            data = int.parse(datum[i]);
         }else{
            data = datum[i];
         } 
         current[currentTitle] = data;
      }
      data.add(current);
   });
   var writer = oFile.openWrite();
   writer.write(jsonEncode(data));
   writer.close();
   writer.done.then((_) {
      exit(0);
   });
}
