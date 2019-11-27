# Writing LLVM Pass in 2018

[toc]

---

## Part I
### Build Pass Out of LLVM Source Tree
```bash
% LLVM_HOME=/path/to/LLVM Project/build/
% export LLVM_HOME
% mkdir part1/build && cd part1/build
% cmake ..
% make -j8
```
然后我们可以在build/hello_new_pm_pass/目录下看到.so文件，就是我们刚刚编译生成的pass
### Use Pass
```bash
% cd part1/foo
# 将需要的LLVM工具软链接到本地
% ln -s /path/to/LLVM Project/build/bin/clang-9 ./clang-9
% ln -s /path/to/LLVM Project/build/bin/opt ./opt
% ln -s /path/to/LLVM Project/build/bin/llvm-dis ./llvm-dis
# 生成bitcode文件
% ./clang-9 foo.c -emit-llvm
# llvm反汇编得到.ll可读文件
% ./llvm-dis foo.bc -o foo.ll
# 使用pass
% ./opt -disable-output -load-pass-plugin=/home/zhouxia/Writing_LLVM_Pass_in_2018/part1/build/hello_new_pm_pass/libHelloNewPMPass.so -passes="hello-new-pm-pass" foo.ll
Hello main
Hello hello
```
可以跳过llvm反汇编直接在.bc文件上应用pass


---

## 参考文献
- [1] [Writing LLVM Pass in 2018 — Part I](https://medium.com/@mshockwave/writing-llvm-pass-in-2018-part-i-531c700e85eb)