# Getting Started

Because c++ is lacking native support for networking, I had an option to either use native OS api or use external library.
I opted on using external library and choose boost asio for the purpose, the simple reason is that c++ standard has adopted a lot of things
over from boost library. Infact the new c++23 standard that is currently undergoing discussion is supposed to include networking which is
going to be a heavy port of boost/asio library. The same one that I am using.

> The regex to parse url was found here. [regex source](https://datatracker.ietf.org/doc/html/rfc3986#appendix-B)
>
> results in the following subexpression matches:
>
>     $1 = http:
>      $2 = http
>      $3 = //www.ics.uci.edu
>      $4 = www.ics.uci.edu
>      $5 = /pub/ietf/uri/
>      $6 = <undefined>
>      $7 = <>
>      $8 = #Related
>      $9 = Related
>
>   where &lt;undefined&gt; indicates that the component is not present, as is
>   the case for the query component in the above example.  Therefore, we
>   can determine the value of the five components as
>
>      scheme    = $2
>      authority = $4
>      path      = $5
>      query     = $7
>      fragment  = $9

## Setup

Since, the code depends upon boost library and openssl library the two dependencis must first be installed before proceding onwards.
on Ubuntu machine that I wrote it on, one can obtain the two library by following command. Check for your distribution and the way to get the two library.

```
   sudo apt install -y libboost-all-dev && sudo apt install libssl-dev
```

After the above dependencies have been configured, run the provided CMakeLists.txt

For first timers, install cmake.

for Linux users
```
   sudo apt install -y cmake && cmake <src directory with provided CMakeLists.txt>
```

this will create a makefile for you to then run to generate the output binaries

you can now run the program
```
   main <url>
```

the code can be made to run much quicker, if we keep a persistent connection and post get request on it over and over again
instead of closing a request on each new entry. Maybe I will try and implement that, do let me know if you wish for me to
try it using that approach as well. But for now ... we will keep it at this much. ( •̀ ω •́ )✧
