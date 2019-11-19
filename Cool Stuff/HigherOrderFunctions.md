# 3 different ways to use higher order functions

For this example we are going to use a Predicate

## 1. Using a template

```cpp
template<class Pred>
bool fun(int a, Pred pa)
{
    return pa(a);
}
```

## 2. Using function pointers

```cpp
bool fun1(int a,bool (*p) (int))
{
    return p(a);
}
```

## 3. Using function pointers again, but prettier

```cpp
using Predicate = bool (*)(int);

bool fun2(int a, Predicate pr)
{
    return pr(a);
}
```
