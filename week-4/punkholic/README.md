# punkholic: Week-4 | RECrypto Challenge: 3.Endianness16

## FLAG: itsnporg{Rust_1s_4m4z1ng_4c1a3f3e7!}

*** 

## Step 1 executing
Downloaded the **`ctf.exe`** file and tried executing on Linux

But by the look of things we cannot run it on Linux
*** 

## Step 2 Checking binary with strings

so i used strings to check for anythings sus

**`strings ctf.exe | less`**

i found a weird link with the name of CTF author:

```tig.tsig//:sptthc.tnetnocresubuhimihGtiniBehT/moaed5d221cacf8/er36196bce516eb66152bda2f8/war/9f82b8d6142b67d90ded47f1277118bff0d.......```
*** 

## Step 3 Reversing string
I thought that link is in reverse format so i tried reversing string but it gave more weird output

*** 
## Step 4 Observing the title
After trying everything i observed the title of CTF which is 

**`RECrypto Challenge: 3.Endianness16`**

I researched about `Endianness16` and found out that it is used on many hashing algo
*** 
## Step 5 Searching for decryption 
I searched for decrypting algo on github and found some codes on python and c/c++ but non worked as it used hex converstion

Afterwards i found this site: `https://gchq.github.io/CyberChef/`

And searched for `endianness` and found `swap endianness`

I gave required details and got a link out of it: 

![Not found!!](https://cdn.discordapp.com/attachments/758679454980636724/847385925801738240/Screenshot_from_2021-05-27_13-52-04.png)

`https://gist.githubusercontent.com/TheBinitGhimire/8fcac122d5dea166be615ecb691638f9/raw/8f2adb25ed09d76b2416d8b2d0ffb8117721f74d`
*** 
## Step 5 Opening the link

When i opened that think i got the flag: 
**`itsnporg{Rust_1s_4m4z1ng_4c1a3f3e7!}`**