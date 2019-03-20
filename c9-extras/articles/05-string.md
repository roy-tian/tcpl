# 操练起来吧

之前有一个习题，就是统计输入字符串中 `a-z` 出现的频度，并打印出直方图。

先揭晓一下[答案](answers/stat.c)。

你可能看到了我的 `stat` 函数比你的偷懒了，里边用了诸如 [`islower`](https://en.cppreference.com/w/c/string/byte/islower)、[`isupper`](https://en.cppreference.com/w/c/string/byte/isupper)、[`isspace`](https://en.cppreference.com/w/c/string/byte/isspace)、[`ispunct`](https://en.cppreference.com/w/c/string/byte/ispunct) 这样的库函数，遇到一些简单重复的操作应该先求助于[文档](https://en.cppreference.com/w/c)，文档有些内容较深，没有听说过就不要纠结了，只关注你想了解的部分。尽量读英文版，遇到不认识的专业词汇可以对照一下英文版，慢慢就适应了。

现成的工具拿来就用，**不要自己造轮子**。当然你要是觉得好玩儿，或者想体会一下这些轮子运行的原理，甚至或者你发现了比原来的轮子更优的解决办法，自己造一造也不是不可以 :)

指针来了，不要害怕。如果直接把 `str` 定义为数组，可以得到完全相同的结果。（所以这个题目完全不需要指针，没有超纲：）

```c
#define STRING_CAPACITY 1000

char str[STRING_CAPACITY] = "The quick brown fox jumps over the lazy dog.";
stat(str);      // works as before
print_gram();   // exactly.
```

下面先写点儿代码，放松一下，同时体会一下字符串轮子的力量：（完成后再进行下一部分）

>【习题】编写一个 `int mobile_number(char string[STRING_CAPACITY])` 函数，判断传入的字符串是否是一个格式正确的中国大陆手机号码。是返回 `1`，不是返回 `0`。
>1. 我们的手机号码应符合：共 11 位，首位是 1，第二位是 3、5、7、8、9，为简化思路，忽略其它的限制。
>2. 判断字符串的长度、是否为数字等操作尽量用库函数，别造轮子。
>3. 有余力的话，可以试着把参数修改为 `char *` 类型，观察一下提示的变化。
>4. 再有余力的话可以丰富一下功能，比如判断是哪个运营商的，加入 “+86”、“138-2505-4250” 等格式的判断等等。只要你想。