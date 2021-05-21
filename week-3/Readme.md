
## Cryptography challenge

## Description

I'm sure this disk contain your Hard-Drive password! Can you find it?

## Provided File

Challenge.tar.gz

## Hint

Unzip it

Check File Type

$binwalk filename

Inspect image with FILE(1) and we see it is an ext2 file system image,
not a whole disk.

Opening the file with hexer and paging down through the data we see
"secret.txt" and a quick search for the string "flag"


## Good Luck!!!
