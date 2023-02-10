# Description
This directory contains C functions to handle input strings. 
They are designed to be run on a Linux machine with OpenSSL installed (to generate the random training data and scramble the results with human training data).

# Specifics
- readbits.c
    - class function to read bits into an array
- strhandler.c
    - uses OpenSSL `RAND_bytes` to generate 5 random strings based on the length of the human-generated strings in `training_data/human-bits.txt`
    - pads bits to correct length and writes all to one CSV file

# Goal Usage
1. Type out as many bits as you can stand into a .txt file, in equal time increments
2. Get the numbers of bits you typed out by running
`cat training_data/human-bits.txt | head -n 5 | awk '{ print length; }'`
3. Put the max and min of these into `./strhandler` to generate a csv with an equal number of random lines, all mixed together
4. Run `./strmixer` to mix the random csv strings with your random strings and pad them out with zeros
5. The resulting `training.csv` and `labels.csv` is your training data
