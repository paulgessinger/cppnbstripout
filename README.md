# cppnbstripout

## Building
This project uses a submodule for [`nlohmann::json`](https://github.com/nlohmann/json) and CMake for building.
You need to `git submodule init` and `git submodule update` or use `git clone --recurse-submodule`.

Then, you can run 

```bash
mkdir build 
cd build
cmake .. 
make
```

to build. 

## Installation as git filter
First of all you need to build the project as described above.
In any git repository, you can then configure it as a filter driver like


```bash
git config filter.cppnbstripout.clean '/path/to/cppnbstripout'
git config filter.cppnbstripout.smudge cat
git config filter.cppnbstripout.required true
git config diff.ipynb.textconv '/path/to/cppnpstripout'
```

Additionally you will have to create a `.gitattributes` file (or append to it) with these lines:
```
*.ipynb filter=cppnbstripout
*.ipynb diff=ipynb
```


