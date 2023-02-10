# Training Data String Generation
## Description
This directory contains C functions to handle input strings. 
They are designed to be run on a Linux machine with OpenSSL installed (to generate the random training data and scramble the results with human training data).

## Specifics
- `readbits.c`
    - Unused class function to read bits into an array
- `randstr.c`
    - uses OpenSSL `RAND_bytes` to generate 5 random strings based on the length of the human-generated strings in `training_data/human-bits.txt`
    - pads bits to correct length and writes them to a txt file
- `strmixer.c`
    - takes human generated strings from a txt file
    - takes machine generated strings from a txt file
    - shuffles them and puts them in a csv with labels
        - result: `training.csv`
        - labels: `labels.csv`

## Usage
1. Type out as many bits (0 and 1) as you can stand into a .txt file, in equal time increments with newlines between them
    - For example, `101101101011100111...` for a minute, then hit `Enter`, and repeat n times.
2. Get the length of the longest and shortest strings you typed out by running `./minmax.sh [your-file]`
3. Run `./randstr [min] [max] [num_str] [filename]` to generate a file with an equal number of random lines
4. Run `./strmixer [max] [num_str_per_file] [human_filename] [rand_filename]` to shuffle all the strings, zero-pad them, and put them into csv files
5. The resulting `training.csv` and `labels.csv` is your training data
