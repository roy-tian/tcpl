# 解锁一个新姿势

考虑下面这个小问题：

>编写 `add_one` 函数，传入一个 `int` 参数，为它的值加一。（不要通过返回值形式，直接操作这个参数。）

没有学好指针的你，很快想出了以下的代码：

```c
void add_one(int operand) {
    operand++;
}

int main() {
    int number = 1;
    add_one(number);
    printf("%d", number);   // oops... nothing has changed.
}
```

然并卵，`operand` 在经过 `add_one` 操作后并没有变化。这是因为 C 语言是按**传值**方式传递参数，`add_one` 接收了 `operand` 后，在自己的作用域内把它复制了一份，然后所有操作都针对这份拷贝展开，并没有伤及 `operand` 的肉身。

怎么办？在 C 语言的范畴，不解锁“指针”这个新姿势，你还就真完不成这个操作。你只能把 `operand` 所在的**地址**告诉 `add_one`，然后函数就能顺着这个地址找到 `operand` 的真身，对其施展“加一大法”：

```c
void add_one(int * pointer_to_operand) {
    (*pointer_to_operand)++;
}

int main() {
    int number = 1;
    add_one(&number);
    printf("%d", number);   // everything goes fine.
}
```

观察 `add_one` 的参数，现在变成了 `int * pointer_to_operand`，这是告诉编译器：“现在传进来的 `pointer_to_operand` 不再是一个实际的 `int` 变量，而是一个**地址**信息，你可以使用 **星号操作符** `*`，这样操作 `*pointer_to_operand` 从该地址处找到这个 `int`，之后就可以对它进行 `++` 操作了。（这里为什么要加括号，请参阅[运算符优先级](https://en.cppreference.com/w/c/language/operator_precedence)）。

再观察 `main` 函数里对 `add_one` 的调用，直接把 `int number` 传给 `add_one` 肯定是不对的，因为 `add_one` 只接收地址数据，怎么提供给它呢？C 语言有**取地址操作符** `&`，`&number` 就可以得到 `number` 的地址。

你可以在任意地方自行定义一个**指针变量**，而且你之前的代码里所有变量都可以用 `&` 取它们的地址。比如这样：

```c
int * pointer_to_integer;   // declare a pointer, ready to point to an integer.
int an_integer = 5;         // define an integer with value 5.
pointer_to_integer = &an_integer;
                            // let the pointer point to the integer.
(*pointer_to_integer)++;    // when you operate the pointer, 
printf("%d", an_integer);   // the integer will be changed as an effect.
```

>以及这样：
>```c
>int * pointer_to_integer;   // declare a pointer that pointed to an integer.
>pointer_to_integer = 1234;  // assign a new address.
>(*pointer_to_integer)++;    // directly operate the RAM, Am I as newbee as a hacker ?
>printf("Can I say hello to the world again?");
>```
>不不不，这是一个**非常危险**的操作，因为鬼知道内存中这个 `1234` 地址保存着什么重要信息，系统大概率会阻止你，你基本上没有机会再 hello world，（逃

至此，我们了解了 C 语言指针的第一个作用：**让函数直接修改参数成为了可能。**

给你留两个简单的小作业巩固一下：（完成习题后再进行下一步）

>【习题1】编写 `swap(left, right)` 函数，分别交换两个 `int` 整数、两个 `double` 浮点数、两个 `char[]` 字符串的值。

>【习题2】编写 `trois_swap(left, middle, right)` 函数，两两交换三个参数的值。

>【习题3】可以试试在 `swap(left, right)` 函数中交换两个不同类型参数的值，看看会发生什么。