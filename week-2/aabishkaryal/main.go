package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"net/url"
	"os"
	"sync"
	"time"
)

const NUM_WORKERS = 256

var client http.Client

func main() {
	url, err := url.ParseRequestURI(os.Args[1])
	if err != nil {
		log.Fatal("Please enter a valid url")
	}

	client = http.Client{
		Timeout: time.Second * 60,
	}

	start := time.Now()
	SendWebRequestConcurrently(url, 1000)
	executionTime := time.Since(start)
	fmt.Printf("Execution completed in %f seconds.\n", executionTime.Seconds())
}

func SendWebRequestConcurrently(webUrl *url.URL, numJobs int) {
	var wg sync.WaitGroup
	jobs := make(chan *url.URL, NUM_WORKERS)
	for i := 0; i < NUM_WORKERS; i++ {
		wg.Add(1)
		go worker(i+1, jobs, &wg)
	}

	for i := 0; i < numJobs; i++ {
		jobs <- webUrl
	}
	close(jobs)
	wg.Wait()
}

func worker(id int, jobs <-chan *url.URL, wg *sync.WaitGroup) {
	defer wg.Done()
	jobNumber := 1
	for j := range jobs {
		resp, err := SendWebRequest(j)
		if err != nil {
			fmt.Printf("worker:%d jobNumber:%d -- error: %v\n", id, jobNumber, err)
		}
		fmt.Printf("worker:%d jobNumber:%d -- response: %s\n", id, jobNumber, resp)
		jobNumber++
	}
}

func SendWebRequest(url *url.URL) (string, error) {
	resp, err := client.Get(url.String())
	if err != nil {
		return "", fmt.Errorf("error occured while getting url.\t %v", err)
	}
	defer resp.Body.Close()
	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return "", fmt.Errorf("error occued while reading body.\t %v", err)
	}
	msg := string(body)
	return msg, nil
}
