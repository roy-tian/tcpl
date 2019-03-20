# 时间复杂度、空间复杂度、性能优化

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

再考虑一下，算法的核心，即计算的过程，还能不能优化了？（考虑完再往下看）

你是否想到了：除了 2 以外所有的素数都是 Odd（这次没有写错吧）？我们知道，能被偶数整除的数必然是合数，那么在循环体中，还有必要去尝试 `number` 是否能被偶数整除吗？没必要了嘛。因此算法可以这样改进：

```c
int prime(int number) {
  if (number < 2)
    return 0;
  if (number == 2)
    return 1;
  if (number % 2 == 0)
    return 0;
  for (int i = 3; i <= sqrt(number); i += 2) {
    if (number % i == 0)
      return 0;
  }
  return 1;
}
```

这样，循环的迭代次数就减少了一半，从而降低了代码的**时间复杂度**。不要小看这一点点的改进，在大规模运算中（以后你大概率会接触），每个算法细微的提升都是非常宝贵的。

还有改进的余地吗？不借助外力的话，这基本上是最优解了（主要是我也想不到了）。那么，有什么外力可以借助呢？还记得你自己是怎么算素数的吗，别想了，你是死记硬背背下来的。这也正是计算机最擅长的，就是要让它死记硬背下来，事先用一个 `char prime_table[100000]` 来保存 10 万以内的素数表，`1` 表示素数，`0` 表示合数，比如在 `prime_table[997]` 处存一个 `1`，`prime_table[998]` 存一个 `0`，用 `prime_table` 辅助求 10 万个数是否为素数，速度那是起飞的存在。准备这个辅助素数表就可以用我们的 `prime` 函数来帮忙，还有其他的算法比较复杂，这里就不展开说了。

```c
// Some magic code to generate asistant prime_table[100000];

int prime(int n) {
  return prime_table[n]; // rocket speed.
}
```

这是一个通过增加**空间复杂度**换取更优**时间复杂度**的思路。另外，这两个复杂度的概念是可以量化的，你会在**数据结构**课程里学习。