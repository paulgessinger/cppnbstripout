#!/bin/bash
set -e

tmp_dir=$(mktemp -d)
raw=$tmp_dir/raw.ipynb
ref=../ref.ipynb
act1=act1.ipynb
act2=act2.ipynb

curl https://raw.githubusercontent.com/jupyter/notebook/master/docs/source/examples/Notebook/Running%20Code.ipynb > $raw

echo "Test 1"
cat $raw | ./cppnbstripout > $act1
diff $ref $act1 > /dev/null
echo "Test 2"
./cppnbstripout $raw > $act2
diff $ref $act2 > /dev/null
echo "All good"
