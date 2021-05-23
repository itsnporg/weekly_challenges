package main

import (
	"bytes"
	"encoding/csv"
	"encoding/json"
	"log"
	"os"
)

func main() {
	inputFileName := os.Args[1]
	if inputFileName == "" {
		inputFileName = "data.csv"
	}

	CSVtoJSON(inputFileName)
}

func CSVtoJSON(inputFileName string) {
	// Either the first supplied argument or data.csv

	// Open input and output files
	inputFile, err := os.Open(inputFileName)
	if err != nil {
		log.Fatalf("Error while opening file %s\n", inputFileName)
	}
	defer inputFile.Close()

	outputFileName := "result.json"
	outputFile, err := os.Create(outputFileName)
	if err != nil {
		log.Fatalf("Error while creating file %s\n", outputFileName)
	}
	defer outputFile.Close()

	csvReader := csv.NewReader(inputFile)
	inputData, err := csvReader.ReadAll()
	if err != nil {
		log.Fatalf("Error while reading file\n %v\n", err)
	}

	mapData := make([]map[string]string, len(inputData)-1)
	headers := inputData[0]
	for i, row := range inputData[1:] {
		mapData[i] = map[string]string{}
		for x, title := range headers {
			mapData[i][title] = row[x]
		}
	}

	jsonBytes, err := json.Marshal(mapData)
	if err != nil {
		log.Fatalf("Error while marshaling to json \n %v\n", err)
	}
	var jsonOutput bytes.Buffer
	json.Indent(&jsonOutput, jsonBytes, "", "\t")
	jsonOutput.WriteTo(outputFile)
}
