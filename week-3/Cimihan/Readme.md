# KiranGhimire: Week-3 Solution (Digital Forensic Chal)

### My Solution


```
wget 'https://github.com/Cimihan123/weekly_challenges/raw/main/week-3/Challenge.tar.gz' -O- | tar xzf -

/tmp/sad on ☁️  (None)
✦ ❯ ls
'Find flag from unmounted disk'
```


```
xxd  Find\ flag\ from\ unmounted\ disk | ag flag

0000a400: 464c 4147 2d67 676d 676b 3035 3039 360a  FLAG-ggmgk05096.

```

**FLAG: FLAG-ggmgk05096**
