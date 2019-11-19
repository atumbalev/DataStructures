# A neat and effective way to remove all gaps from an array

```cpp
template <typename T>
void compact(T* array, size_t &size) {

    size_t write = 0;
    for(size_t read = 0; read < size; ++read) {
        if(array[read]) {
            array[write++] = array[read];
        }
    }

    size = write;
}
```
