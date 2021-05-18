package main

import (
	"encoding/csv"
	"encoding/json"
	"fmt"
	"log"
	"os"
	"strconv"
)

func main() {
	// Open the first argument passed as the given csv file
	csvFile, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	defer csvFile.Close()

	// instantiate a new reader pointer
	reader := csv.NewReader(csvFile)

	// read from csv file and store in records
	records, err := reader.ReadAll()
	if err != nil {
		log.Fatal(err)
	}

	// define struct to store the data
	type People struct {
		FirstName string `json:"first_name"`
		LastName  string `json:"last_name"`
		Age       int    `json:"age"`
	}

	// instantiate a sturct and slice of structs
	var info People
	var allInfo []People

	// loop over the rows of csv data
	for index, rec := range records {
		// first index returns the name of columns in csv so we skip
		if index == 0 {
			continue
		}

		// each item in the row is mapped to corresponding var in struct
		info.FirstName = rec[0]
		info.LastName = rec[1]
		info.Age, err = strconv.Atoi(rec[2])
		if err != nil {
			log.Fatal(err)
		}
		// the struct is appended to the slice
		allInfo = append(allInfo, info)
	}

	// encode to json and store it
	data, err := json.Marshal(allInfo)
	if err != nil {
		log.Fatal(err)
	}
	// print json to stdout
	fmt.Println(string(data))

	// create a new json file and open it
	jsonFile, err := os.Create("data.json")
	if err != nil {
		log.Fatal(err)
	}
	defer jsonFile.Close()

	// write the data into json file
	jsonFile.Write(data)
  
	fmt.Println("Parsing CSV to JSON successful! JSON data stored in data.json")

}
