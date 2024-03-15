# code_library

存储的是实现相关的线程池等，存储在`src`里面。

## 注意事项

- 命名的时候，千万不要将自己的文件命名和标准头文件的命名一样，比如说叫`vector.h`，会导致命名冲突，编译就会失败

## 测试

- `valgrind`:`valgrind --leak-check=yes ./main.out arg1 arg2`
- 每一个头文件中都有一个自己写的test()，可以直接测试。
