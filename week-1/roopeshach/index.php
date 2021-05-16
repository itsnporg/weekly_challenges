<?php 

//we can pass multiple files as argument too and consequetive json file will be created.
//For example: php test.csv data.csv test2.csv
if (isset($argc)) {

    for ($i=1; $i < $argc; $i++) {
            csvjson($argv[$i]);
        } 
}
else {
	echo "argc and argv disabled\n";
}


function csvjson($filename){
    //open file
    if($filename){
    $file = fopen($filename, 'r');
    $path = pathinfo($filename);
    $name = $path['filename'].'.json';  
    if(!$file){
        echo ' Cant open file';
    }

    //getting csv header line
    $headers = fgetcsv($file, '1024', ',');

    //add csv content to array and merge

    $json = [];
    while($rows = fgetcsv($file, '1024', ',')){
        $json[] = array_combine($headers, $rows);
    }
    $json = json_encode($json, JSON_NUMERIC_CHECK);

    fclose($file);
    $newfile = fopen($name, 'w') or die('Unable to create new file check your permissions!');
    fwrite($newfile, $json);
    fclose($newfile);
    }
}
?>
