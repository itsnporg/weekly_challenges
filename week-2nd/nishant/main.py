import aiohttp
import asyncio 
import time
import sys

initial_time = time.time()

async def req(session,url):
    async with session.get(url) as response:
        print("Ok")


async def main():

    async with aiohttp.ClientSession() as session:
        url = "https://www.facebook.com"
        for n in range(1,1001):
            await req(session,url)

asyncio.run(main())
print("Requests made in %s seconds"%(time.time() - initial_time))
