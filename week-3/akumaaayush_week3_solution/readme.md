# Akumaaayush: Week-3 Challenge
 ---

## Untarring the .tar.gz file:
```
    tar -xvf Challenge.tar.gz
```
-This results to a new file named "Find flag from unmounted disk" in the same directory.

---
## Search for the flag
- A simple string search for "flag" resulted to the flag
```
strings Find\ flag\ from\ unmounted\ disk | grep -i "flag"
```
    resulted to:
    FLAG-ggmgk05096

### Flag: ggmgk05096