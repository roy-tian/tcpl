# 抽象、提炼程序结构

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

风格修正过来了，还有没有其它问题？首先：

> 1 既不是素数，也不是合数。

但是 `prime(1)` 却返回 `1`，这是不符合要求的，因为它是一条“规定”，而不是通过通用的计算所得，所以应禁止不涉及素数/合数问题的 1、0 以及负整数参与到算法中来，我们没有考虑到这个问题，也就是这个函数没有进行**边界检查**，即**健壮性**不佳。处理方法很简单，直接 `if` 掉就行了：

```c
if (number < 2) {
  return 0;
}
```

接下来的代码就变成了：求 ![](http://latex.codecogs.com/gif.latex?n(n\\in\\{n|n\\geq2,n\\in\\mathbb{N}\\})) 是否为素数。对于素数有以下断言：

>![](http://latex.codecogs.com/gif.latex?\\forall{i}\\in\\{i|2\\leq{i}\\leq\\sqrt{n},i\\in\\mathbb{N}\\},n\\bmod{i}\\ne0)

即：对于 ![](http://latex.codecogs.com/gif.latex?n) 而言，![](http://latex.codecogs.com/gif.latex?2) 至 ![](http://latex.codecogs.com/gif.latex?\\sqrt{n}) 之间所有的自然数均不可整除之，遂 ![](http://latex.codecogs.com/gif.latex?n) 为素数。

把思路转化为代码就很容易了。（最好自己尝试一遍，再进行下一节。）

```c
int prime(int number) {
  if (number < 2) {
    return 0;
  }
  for (int i = 2; i <= sqrt(number); i++) {
    if (number % i == 0) {
      return 0;
    }
  }
  return 1;
}
```

注意能在循环内部解决的事情尽量内部解决，拿到外部会使代码混乱，缺乏结构性，且难以读懂。