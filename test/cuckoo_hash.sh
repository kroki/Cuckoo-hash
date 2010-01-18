#! /bin/sh

COUNT=500000

echo "Running the test for $COUNT elements"
./cuckoo_hash 0 $COUNT
