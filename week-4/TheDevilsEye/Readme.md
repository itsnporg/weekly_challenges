# TheDevilsEye: Week-4 | RECrypto Challenge: 3.Endianness16

## FLAG: itsnporg{Rust_1s_4m4z1ng_4c1a3f3e7!}   

*** 

## Step 1 Finding the Hex value of the file   

The "ctf.exe" file was downloaded and was opened with HXD hex editor. Nothing extraordinary was seen in the hex editor.   

*** 

## Step 2 Opening the file in Linux terminal   

"strings ctf.exe" command was used to find any suspicious strings in the file.   
Nothing out of ordinary was found.  



*** 

## Step 3 Searching for keywords in hex editor

Keywords, "flag", "galf", "binit", "tinib", "https", "sptth" were searched in hex editor.
A suspicious text that looked like a link was found. "tig.tsig//:sptthc.tnetnocresubuhimihGtiniBehT/moaed5d221cacf8/er36196bce516eb66152bda2f8/war/9f82b8d6142b67d90ded47f1277118bff0d.......txt.galf/"

*** 

## Step 4 Converting Endianess of hex values 
The hex values of the suspicious looking text were converted to little endian in an order.   
Firstly, individual words dividing by ".", "/", ":" was subjected to converter which gave output:   
> git.gist//:chttps.TheBinitGhimihubusercontent/8fcac122d5deaom/8f2adb25166be615ecb69163re/raw/flag.txt.......d0ffb8117721f74ded09d76b2416d8b28f9   
This was not a valid link which is why another approach was taken.   
Each offset was subjected to endianess converter which was then converted to ASCII value which gave us the link   
> https://gist.githubusercontent.com/TheBinitGhimire/8fcac122d5dea166be615ecb691638f9/raw/8f2adb25ed09d76b2416d8b2d0ffb8117721f74d/flag.txt   

## Step 5 Finding the flag   

itsnporg{Rust_1s_4m4z1ng_4c1a3f3e7!}
This flag was found after going through the accquired link.   


*** 
