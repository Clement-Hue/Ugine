# Development of UGINE

This project is built using __cmake__, to get started initialize __cmake__

```shell
cmake -S . -B build/<build_name>
```

The current available options are:
- UGINE_TEST: to build the test
- UGINE_DEBUG: to show logging information of ugine
- UGINE_SHARED_LIBRARY: to build Ugine as a dll

for instance:

```shell
cmake -S . -B build/<build_name> -DUGINE_TEST=ON -DUGINE_DEBUG=ON
```
