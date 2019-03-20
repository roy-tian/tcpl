# 代码风格

代码风格问题一开始很容易被忽略，其实怎么强调也不过分。因为良好的代码风格，可以让使用你的代码的人（包括你自己）更好地理解你的意图，更方便地使用它们。回顾一下你编写的求素数的函数：

```c
int prime(int n)
{   int k,i,result;
  k=sqrt(n);
  for(i=2;i<=k;i++)
    if(n%i==0)break;
  if(i>k)
    result=1;
  else
    result=0;
  return result;
}
```

首先，程序块两端的大括号有两种约定俗成的风格，一种是各自单独占一行，与函数签名一行左对齐：

```c
int some_func(int some_arg)
{
  // code
}
```
另一种是左括号不换行，右括号单独一行并左对齐：
```c
int some_func(int some_arg) {
  // code
}
```

两种风格的块内代码都要缩进。

二者都有人使用，都是可以接受的风格，没有优劣之分。但回头看你的写法，是不是即没有第一种的对称美，又没有第二种的紧凑美呢。

一些显性的风格问题，比如程序块大括号摆放位置、操作符两端加空格等，虽然无关程序运行结果，但作为即将成为优秀程序员你，一定要写可读性高的代码，并形成自己的一套 style，这样你在将来的实战中，就可以随时 adhere to 团队的 style。

还有几个小问题：
1. 即使条件语句的执行部分只有一句，也不要与条件语句在同一行，那样会引起混淆。
```c
if (clark == super_man) fly(clark); // confusing...

if (bruce == bat_man)
  drive_bat_mobile(bruce);          // pretty clear

```
2. 命名要尽量做到通俗易懂，全称为宜，即使要用缩写尽量用大家都能看懂的，比如 `what_the_fuck` 可缩写为 `wtf`，循环迭代器 `iterator` 可缩写为 `i`。早期的程序员更趋向于简洁风格（`strcmp` 函数：string compare）或全小写下划线分割的风格（`flash_flash_a_100_yard_dash`）；现代编程语言一般更青睐“驼峰名法”（`whatDoYouCallAThreeHumpedCamel`）。它们之间也没有优劣之分。
3. 你无需在程序一开始就把所有量都声明好，随用随申请即可。（这是 C99 标准的特性，你们机房的 VC6 不支持这么做）

仅考虑风格，不考虑代码逻辑，你的代码可修正为：（可以自己先写一遍，然后对比一下。）

```c
int prime(int number)
{   
  int number_sqrt = sqrt(number), i = 2;
  for (; i <= number_sqrt; i++)
  {
    if (number % i == 0)
      break;
  }
  int result;
  if (i > number_sqrt)
    result = 1;
  else
    result = 0;
  return result;
}
```

可以看看一些大牛或大公司是怎么规定代码风格的（略读即可，现在不要深究，会分散精力）：

- [GNU Coding Standard](https://www.gnu.org/prep/standards/html_node/Formatting.html#Formatting)
- [Linux 内核代码风格](https://www.kernel.org/doc/html/latest/translations/zh_CN/coding-style.html)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [C 语言编程规范 - 华为 2011 年风格](https://www.jianshu.com/p/5cc054b09613)