This directory contains C functions to handle input strings. 
They are designed to be run on a Linux machine with OpenSSL installed (to generate the random training data and scramble the results with human training data).

Specifics: 
- readbits.c
    - class function to read bits into an array
- randgen.c
    - uses OpenSSL `RAND_bytes` to generate 5 random strings based on the length of the human-generated strings in `training_data/human-bits.txt`
    - pads bits to correct length and writes all to one CSV file