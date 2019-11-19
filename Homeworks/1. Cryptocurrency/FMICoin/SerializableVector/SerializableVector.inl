#include "SerializableVector.h"

template<class T>
SerializableVector<T>::SerializableVector(unsigned size) : m_size(size)
{
    m_capacity = getClosestPowerOf2(size);

    m_data = new T[m_capacity];
}


template<class T>
SerializableVector<T>::SerializableVector(const char *fileName)
{
    readFromBinaryFile(fileName);
}

template <class T>
T& SerializableVector<T>::operator[](unsigned i)
{
    if (i > m_size)
    {
        throw std::out_of_range("Index out of range");
    }

    return m_data[i];
}

template <class T>
const T& SerializableVector<T>::operator[](unsigned i) const
{
    if (i > m_size)
    {
        throw std::out_of_range("Index out of range");
    }

    return m_data[i];
}

template<class T>
void SerializableVector<T>::resize()
{
    T* newData = new T[newCapacity()];

    for (int i = 0; i < m_size; ++i)
    {
        newData[i] = m_data[i];
    }

    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity();
}

//https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
//The result may be expressed by the formula 1U << (lg(v - 1) + 1).
template<class T>
unsigned SerializableVector<T>::getClosestPowerOf2(unsigned num)
{
    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num++;

    return num += (num==0); //if the number was zero it will return 1
}

template<class T>
unsigned SerializableVector<T>::newCapacity() const
{
    return m_capacity ? m_capacity * 2 : 1;
}

template<class T>
void SerializableVector<T>::insert(const T &elem)
{
    if (m_size >= m_capacity)
    {
        resize();
    }

    m_data[m_size++] = elem;
}

template<class T>
SerializableVector<T>::~SerializableVector()
{
    delete[] m_data;
}

template<class T>
void SerializableVector<T>::writeToBinaryFile(const char* fileName) const
{
    std::ofstream outputFile(fileName, std::ios::binary | std::ios::trunc);
    outputFile.write(reinterpret_cast<const char*>(m_data), m_size * sizeof(T));
    outputFile.close();
}

template<class T>
bool SerializableVector<T>::empty() const
{
    return m_size == 0;
}

template<class T>
unsigned SerializableVector<T>::size() const
{
    return m_size;
}

template<class T>
void SerializableVector<T>::readFromBinaryFile(const char *fileName)
{
    std::fstream file(fileName, std::ios::binary | std::ios::in);

    if (file.is_open())
    {
        file.seekg(0, std::ios::end);
        m_size = file.tellg() / sizeof(T);
        m_capacity = getClosestPowerOf2(m_size);
        m_data = new T[m_capacity];

        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char*>(m_data), m_size * sizeof(T));
    }
    else
    {
        file.close();
        file.open(fileName, std::ios::binary | std::ios::out); //Create file

        m_size = 0;
        m_capacity = 0;
        m_data = nullptr;
    }

    file.close();
}

template<class T>
void SerializableVector<T>::remove(const T &elem)
{
    for (int i = 0; i < m_size; ++i)
    {
        if (elem == m_data[i])
        {
            for (int j = i; j < m_size -1; ++j)
            {
                std::swap(m_data[j], m_data[j+1]);
            }
            --m_size;
            return;
        }
    }
}

template<class T>
SerializableVector<T>::SerializableVector() : m_capacity(0), m_size(0), m_data(nullptr) {}

template<class T>
void SerializableVector<T>::bulkInsert(const SerializableVector<T> &other)
{
    reserve(other.size());
    for (int i = 0; i < other.size(); ++i)
    {
        insert(other[i]);
    }
}

template<class T>
void SerializableVector<T>::reserve(unsigned space)
{
    if(m_size + space < m_capacity)
    {
        m_resize(m_size + m_capacity);
    }
}

template<class T>
void SerializableVector<T>::m_resize(unsigned space)
{
    T* newData = new T[getClosestPowerOf2(space)];
}

template<class T>
SerializableVector<T>::SerializableVector(const SerializableVector &other)
{
    copy(other);
}

template<class T>
void SerializableVector<T>::copy(const SerializableVector &other)
{
    m_data = new T[other.m_capacity];
    m_capacity = other.m_capacity;
    m_size = other.m_size;

    for (int i = 0; i < m_size; ++i)
    {
        m_data[i] = other.m_data[i];
    }
}

template<class T>
SerializableVector<T> &SerializableVector<T>::operator=(const SerializableVector& other)
{
    if (this != &other)
    {
        T* tmp = m_data;
        try
        {
            copy(other);
        }
        catch (std::bad_alloc& e)
        {
            m_data = tmp;
            return *this;
        }
        delete [] tmp;
        return *this;
    }
}

template<class T>
T& SerializableVector<T>::last()
{
    return m_data[size() ? size() -1 : 0];
}

template<class T>
const T &SerializableVector<T>::last() const
{
    return m_data[size() ? size() -1 : 0];
}

template<class T>
T &SerializableVector<T>::first()
{
    return m_data[0];
}

template<class T>
const T &SerializableVector<T>::first() const
{
    return m_data[0];
}
