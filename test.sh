#!/bin/bash
set -e

tmp_dir=$(mktemp -d)
raw=$tmp_dir/raw.ipynb
ref=../ref.ipynb
act1=act1.ipynb
act2=act2.ipynb

curl https://raw.githubusercontent.com/jupyter/notebook/master/docs/source/examples/Notebook/Running%20Code.ipynb > $raw

cat $raw | ./cppnbstripout > $act1
diff $ref $act1 > /dev/null
./cppnbstripout $raw > $act2
diff $ref $act2 > /dev/null
