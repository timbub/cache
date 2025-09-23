## Cache algorithms: LFU(Least Frequently Used) and Ideal 

### Project tree

```text
cache
├── ideal
│   ├── CMakeLists.txt
│   ├── e2e.cpp
│   ├── idealcache.hpp
│   └── main.cpp
└── lfu
    ├── CMakeLists.txt
    ├── e2e.cpp
    ├── lfucache.hpp
    └── main.cpp
```
### Description of algorithms
...
### Run
#### Clone repository
```
git clone ...
cd cache
```
[TYPE] = lfu or ideal

#### Choose folders with type of cache 
```
cd [TYPE]
```
#### Build
```
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build
```
#### Run
```
cd build
./[TYPE]
```

