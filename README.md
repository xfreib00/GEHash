# GEHash

<p align="left">
    <a href="https://github.com/xfreib00/GEHash/actions">
        <img src="https://github.com/xfreib00/GEHash/workflows/CMake/badge.svg" alt="Build and test">
    </a>
    <a href="https://github.com/xfreib00/GEHash/actions">
        <img src="https://github.com/xfreib00/GEHash/workflows/clang-format%20Check/badge.svg" alt="Formatting">
    </a>
    <a href="https://github.com/xfreib00/GEHash/releases"><img alt="Release" src="https://img.shields.io/github/v/release/xfreib00/GEHash.svg?logo=github"></a>
</p>

Author: Adam Freiberg

e-mail: xfreib00@stud.fit.vutbr.cz

Tweet about project:

<a href="https://twitter.com/intent/tweet?text=&url=https%3A%2F%2Fgithub.com%2Fxfreib00%2FGEHash">
    <img alt="Twitter" src="https://img.shields.io/twitter/url?style=social&url=https%3A%2F%2Ftwitter.com%2FGEHashGit">
</a>

***
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
## Input

Input consist of two parts, **grammar** used for mapping genotype to phenotype and **training data** used for phenotype evaluation.

### Grammar

Input grammar must be in BNF (Backus–Naur Form). [Example](examples/exam_grammar.txt) of such grammar can be found in examples directory.

### Training data
Training data is set of records composed from two IPv6 addresses and ports. Format of the record is source and destination address, separated every 32 bits by semicolon followed by source and source and destination port, each separated by semicolon as well.

Format of single record looks something like this:
```plain text
32bit;32bit;32bit;32bit;32bit;32bit;32bit;32bit;16bit;16bit;
```
To get a better picture, [example](examples/train_set_example.data) of data set for evaluating phenotypes can be found in examples directory.

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
***

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