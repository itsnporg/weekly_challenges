import requests
import timeit
import concurrent.futures
import sys


def thread(session, url):
    session.get(url)


def main():
    url, num = sys.argv[1], 10000
    with concurrent.futures.ThreadPoolExecutor(max_workers=num*0.75)as exec:
        with requests.Session() as session:
            exec.map(thread, [session]*num, [url]*num)
            exec.shutdown(wait=True)


t = timeit.timeit(main, number=1)
print(f'{t} seconds')
