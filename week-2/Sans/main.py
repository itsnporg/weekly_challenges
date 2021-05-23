import requests
import concurrent.futures
import sys
import timeit

def thread(session, url):
    session.head(url)

def main():
    url = sys.argv[1]
    with concurrent.futures.ThreadPoolExecutor(max_workers=500) as exec:
        with requests.Session() as session:
            exec.map(thread,[session]*1000, [url]*1000)
            exec.shutdown(wait=True)

t = timeit.timeit(main, number=1)

print(f"Done in {t} seconds")
