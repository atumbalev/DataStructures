# What is the problem with the following code?

```cpp
void fun(unsigned size)
{
    for (unsigned i = size; i >= 0 ; --i)
    {
	Do something
    }
}
```

## The problem is that:

```cpp
unsigned >= 0 is evaluated as true
```
