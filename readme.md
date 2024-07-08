skeleton code for llvm passes

```sh
bash install_llvm.sh 
```

Compile the pass and tests

```sh
mkdir build; cd build;
cmake .. -DCMAKE_C_COMPILER=clang-14
make
```

Run simple tests

```sh
build/tests/function_test
build/tests/syscall_test
```

