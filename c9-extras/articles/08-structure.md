继续思考一个问题，这个有一定的难度，你大概率做不出来，只需要考虑“我为什么做不出来”即可：

>【思考】将我们的直方图里的项目升序排列。

首先，排序是一个大问题，但它不是本节的主题，假设存在一个魔术函数：

```c
void magic_sort(int *array, int length)
```

可以将有 `length` 个 `int` 元素的数组 `array[]` 中所有的元素升序排列。这里我们不管它的细节，拿来用就好了。

但是新的问题出现了，排序后我们只得到一个升序数列，但不知道那个字母出现了多少次啊？

怎么办？再定义一个辅助数列，保存 `'a'` - `'z'` 的字母和 `char_table` 绑定再排一遍？如果你能想到这个方法，那我敬你是条汉子，先不说为一件事进行两趟排序操作费时费力且不直观，就问你怎么为这个没有出现频率信息的数组排序？？能吗？

# 新的数据类型

事情又走进了一个死胡同，你是否发现了这样一个问题，迄今为止，我们所进行的所有操作都是针对系统内建数据类型开展的，你会不会觉得这是一个桎梏呢？比如让你求两个复数（![](http://latex.codecogs.com/gif.latex?z$_1$=a$_1$+b$_1$i,z$_2$=a$_2$+b$_2$i)）的和，虽然我们知道计算方法为：

>![](http://latex.codecogs.com/gif.latex?z$_1$+z$_2$=\(a$_1$+a$_2\)$+\(b$_1$+b$_2$\)i)

你只能将 ![](http://latex.codecogs.com/gif.latex?a$_1$,b$_1$,a$_2$,b$_2$) 这些变量分别考虑，C 语言没有 `complex` 类型，我们就写不出这样的函数来：

```c
complex complex_add(complex z1, complex z2)
```

是不是很郁闷？是时候表演真正的技术了！有请 **结构体（structure）** 出场：

```c
struct complex {
    double real_part;           // member of a struct      
    double imaginary_part;      // member of a struct
};

struct complex complex_add(struct complex z1, struct complex z2) {
    struct complex result;
    result.real_part = z1.real_part + z2.real_part;
    result.imaginary_part = z1.imaginary_part + z2.imaginary_part;
    return result;
}
```

我们就好像为 C 语言添加了一个新的复数数据类型 `struct complex`，把实数部分和虚数部分作为复数的**成员**。不是感觉打开了潘多拉之盒，好多问题豁然开朗了呢。当然这个写法还有些啰嗦，可以用 `typedef` 关键字定义一个新类型，就方便多了：

```c
struct complex {
    double real_part;
    double imaginary_part;
};

typedef struct complex complex; // define 'struct complex' as 'complex' for short.

complex complex_add(complex z1, complex z2) {
    complex result;
    result.real_part = z1.real_part + z2.real_part;
    result.imaginary_part = z1.imaginary_part + z2.imaginary_part;
    return result;
}
```

这样 `complex` 就与基本类型的用法没有二致了。现在你对结构体已经有了一个初步的印象。不妨做几个练习：

>【习题4.1】 编写 `set_complex` 函数，为 `z` 设定新的数值。（考虑为什么 `z` 是指针类型？） 
> ```c
>    void set_complex(complex *z, double real, double imaginary);
> ```
>【习题4.2】 从以下的函数中选一到两个写出实现：
>```c 
>    complex complex_subtruct(complex z1, complex z2);
>    complex complex_multiply(complex z1, complex z2);
>    complex complex_divide(complex z1, complex z2);
>    complex complex_conjugate(complex z);
>    complex complex_reciplrocal(complex z);
>```

对了，还有一个问题，当变量是一个指向结构体的指针时，比如，`complex *z`，那么引用结构体的成员的操作就不再是 `z.real_part`，而是 `z->real_part`，一个指针很形象吧。（我相信你已经通过编译器的出错提示改正过来了。）

其实 C99 里已经实现了[复数算术](https://en.cppreference.com/w/c/numeric/complex)，我们不知不觉中造了个小轮子，你不提示我还真不知道。哈哈。

回到为直方图排序问题，现在你很自然就会想到怎样改进这个频率表里元素的类型：

```c
typedef struct charfq {
    char character;
    int frequency;
} charfq;

charfq charfq_table[KINDS_OF_CHAR];

. . .

void magic_sort_for_charfq(charfq charfq_table[], int array_size);
```

通过结构体，我们模拟出新的数据类型，问题就解决了。综合一下结构体的知识来小试牛刀吧：

>【习题】尝试编写一个学生的结构体，其中保存姓名、性别、“心理·生活·人生”考试成绩等信息。用一个数组保存全班同学的信息。然后：打印全班的成绩单。
