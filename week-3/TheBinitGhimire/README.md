# TheBinitGhimire: Week-3 Solution

## FLAG: FLAG-ggmgk05096

***

## Downloading Challenge File

```bash
wget "https://github.com/itsnporg/weekly_challenges/raw/main/week-3/Challenge.tar.gz"
```

***

## Untarring the .tar.gz File

```bash
tar -xvf Challenge.tar.gz
```

This will create a new file "Find flag from unmounted disk" in the current directory.

***

## Checking File Type

```bash
file Find\ flag\ from\ unmounted\ disk
```

This will return the following:

```
Find flag from unmounted disk: Linux rev 1.0 ext2 filesystem data (mounted or unclean), UUID=91c0fd20-bd3d-44e3-bfbb-1c18a9c0a20b
```

***

## Using Binwalk to extract the file

```bash
binwalk -e Find\ flag\ from\ unmounted\ disk
```

This will create a directory named "_Find flag from unmounted disk". Now, I need to go inside it.

```bash
cd _Find\ flag\ from\ unmounted\ disk.extracted/
```

Inside this directory, there will be a file named "0.ext" and a directory named "ext-root".

***

## Opening 0.ext in Vi

```bash
vi 0.ext
```

***

## Checking for the Flag

Type this inside Vi and press enter:

```bash
/FLAG
```

You will find "**FLAG-ggmgk05096**", which is the flag for this challenge.

***