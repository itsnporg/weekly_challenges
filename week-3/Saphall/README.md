# Saphall: Week-3 Solution

> FLAG-ggmgk05096

### Steps:
  
#### 1. Get the '.tar.gz' file.
      
          wget 'https://github.com/itsnporg/weekly_challenges/raw/main/week-3/Challenge.tar.gz'

It will download 'Challenge.tar.gz' file.

#### 2. Extract(Unzip) Tar Gz File with following command.

          tar -xvf Challenge.tar.gz

This will create 'Find flag from unmounted disk' file.

#### 3. Use 'strings' command to extract printable characters from file and save it to 'what-we-need.txt' textfile.

          strings Find\ flag\ from\ unmounted\ disk > what-we-need.txt

#### 4. Lets search for the flag in 'what-we-need.txt' file with grep command:

          grep FLAG what-we-need.txt

#### `BOOM !` we got our flag. i.e. `FLAG-ggmgk05096`.
