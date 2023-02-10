#!/bin/sh

if [ "$#" -lt 1 ]
then
        echo "Usage: ./minmax [human-filename]";
        exit -1;
fi

MAX=0 MIN=1000 IFS=
while read -r line; do
  if [ ${#line} -gt $MAX ]; then MAX=${#line}; fi
  if [ ${#line} -lt $MIN ]; then MIN=${#line}; fi
done < "$1"
echo "Max: $MAX\n"
echo "Min: $MIN\n"

# This prints all line numbers 
# cat "$1" | head -n 5 | awk '{ print length; }'
