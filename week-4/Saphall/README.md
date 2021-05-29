# Saphall | Week-4 | RECrypto Challenge: 3.Endianness16

> ## FLAG: itsnporg{Rust_1s_4m4z1ng_4c1a3f3e7!}

*** 

## Step-1 : Downloaded '.exe' file with comand:

        wget 'https://github.com/itsnporg/weekly_challenges/raw/main/week-4/ctf.exe'

*** 

## Step-2 : Used 'strings' command  with 'grep' to find anything about flag.

        strings ctf.exe | grep -i flag 

Nothing was found.

*** 

## Step-3 : Used the command again with reversed 'flag' i.e. 'galf'

        strings ctf.exe | grep -i galf 

Ok, this got me something:

`tig.tsig//:sptthc.tnetnocresubuhimihGtiniBehT/moaed5d221cacf8/er36196bce516eb66152bda2f8/war/9f82b8d6142b67d90ded47f1277118bff0d.......txt.galf/`

I couldn't figure out what it was, until I searched about 'Endianness'.

*** 

## Step-4 : Figured out a link with swap endianness to 'Raw data' format and '16 byte' word length.

        https://gist.githubusercontent.com/TheBinitGhimire/8fcac122d5dea166be615ecb691638f9/raw/8f2adb25ed09d76b2416d8b2d0ffb8117721f74d/flag.txt

*** 

***

## Step-5 : Visited the link and got the flag.

        itsnporg{Rust_1s_4m4z1ng_4c1a3f3e7!}

***
