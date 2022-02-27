# GEHash

Author: Adam Freiberg

e-mail: xfreib00@stud.fit.vutbr.cz


## Introduction

GEhash was developed as a part of my bachelor's thesis about *Evolutionary Design of Hash Functions Using Grammatical Evolution*.

Its main focus is on generating hash function for IPv6 used in network flow monitoring.

***
## Build

Project uses CMake to generate build files.

For basic configuration run following commands:
```shell
cmake -S . -B build
cmake --build build
```

## Run

There are two ways to run program.

First is to run program directly:
```shell
./build/src/GEHash ... [parameters]
```

Or use provided shell script:
```shell
./eval.sh ... [parameters]
```

Second option automatically handles multiple runs (to avoid statistical error) and output files.

To display all parameters and their usage, run following command:
```shell
./build/src/GEHash [-h|--help]
```

***
## Output

Output files are in **JSON** format for easier processing. There are two main categories of `status` parameter. First is `progress` and second is `result`, which indicates stage of evolution run.

Example of output data:
```json
[
    ...,
    {
        "fitness": 24579.0,
        "gen": 4,
        "status": "progress"
    },
    {
        "fitness": 24579.0,
        "gen": 5,
        "phenotype": {
            "code": "hash = ~(hash+(~(key)^key<<3)+hash);"
        },
        "status": "result"
    }
]
```

## CMake options

Documentation
- `ENABLE_DOCS` - generate documentation with Doxygen

Dynamic analyzers
- `ENABLE_SANITIZER_ADDRESS` - use address sanitizer
- `ENABLE_SANITIZER_LEAK` - use memory leak sanitizer
- `ENABLE_SANITIZER_UNDEFINED_BEHAVIOR` - use undefined behaviour sanitizer

Static analyzers
- `ENABLE_CLANG_TIDY` - use Clang-tidy static analyzer tool

***
## Dependencies

**Gram** library available at [GitHub](https://github.com/jansvoboda11/gram).

**ChaiScript** library available at [GitHub](https://github.com/ChaiScript/ChaiScript).

**Nlohmann JSON** used lightweight version available at [GitHub](https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent) due to  extensive size of original repository. Full version available [here](https://github.com/nlohmann/json)

**Catch2** test library for C++ available at [GitHub](https://github.com/catchorg/Catch2). Currently using v2.13.4.

***
## Testing

Testing will be added in future releases.

### Unit testing

### Acceptance testing