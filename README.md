Unoffical C++ API for dict.cc

## Prequisites
curl and curlpp have to be installed on the system.

## Installation

So far only a quick and dirty solution is available:

    bash compile_and_install_ubuntu.sh

Works definitely under Ubuntu, other OS unsure and untested. CMake file will follow.

## Usage of the CLI

Type

    dictcc -h

## Usage of the Library
An example of how the library is supposed to be used is given with the CLI (*dictcc.cc*).  The following
code creates a dictionary and performs a search.

```c++
#include "dict.h"

...

dictionary = dictcc::creator::create(lang);
result = dictionary->search(search_chr);
```

`dictcc::creator::create` takes a string e.g. DESV and returns a
`std::smart_ptr` to a dictionary object.  The return value of the search
function is a smart pointer to a `std::pair` of two string vectors, each
corresponding to one language.
