import grequests
import timeit

def test():
    rs = (grequests.get("https://api.countapi.xyz/hit/abhishek/key") for _ in range(10000))
    grequests.map(rs)

time = timeit.timeit(test, number=1)
print(time)
