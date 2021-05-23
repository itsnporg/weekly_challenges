# KiranGhimire: Week-3 Solution (Digital Forensics Chal)

### My Solution


### The below command will download the file and untar it. The tar.gz file won't be saved except the extracted file.
```
wget 'https://github.com/Cimihan123/weekly_challenges/raw/main/week-3/Challenge.tar.gz' -O- | tar xzf -

/tmp/sad on ☁️  (None)
✦ ❯ ls
'Find flag from unmounted disk'
```


### Use hexdump and search for the string flag. I have used "the silver searcher" to search for the string.


```
xxd  Find\ flag\ from\ unmounted\ disk | ag flag

0000a400: 464c 4147 2d67 676d 676b 3035 3039 360a  FLAG-ggmgk05096.

```

**FLAG: FLAG-ggmgk05096**
