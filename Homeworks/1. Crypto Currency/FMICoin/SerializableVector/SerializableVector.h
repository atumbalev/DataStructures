#pragma once

#include <fstream>
#include <stdexcept>

// Template Vector that can initialize its elements from a Binary file that contains only elements of the given Type
template <class T>
class SerializableVector
{
public:
    //initializes an empty vector and doesn't allocate any memory in the heap
    SerializableVector();
    //Initializes the vector to be able to contain at least <size> number of elements,
    //its capacity is set tot the closest power of 2 bigger then size
    //if size is zero it will be set to 1
    //thorws bad_alloc if it fails
    explicit SerializableVector(unsigned size);

    //Initializes the vectors contents from a file
    //Takes a filename to a Binary file
    //Binary file that must contain only elements of the given Type
    //sets its size to the number of elements of type T in the binary file
    //sets its capacity to the closest power of 2 larger then its size
    //allocates capacity * sizeof(T) bytes of memory
    //thorws bad_alloc if it fails
    explicit SerializableVector(const char* fileName);
    SerializableVector(const SerializableVector& other);
    SerializableVector<T>& operator=(const SerializableVector& other);
    ~SerializableVector();

    //element access operator for const and non-const use
    //if the given index is out of the bound of the vector it throws a index_out_of_range exception
    T& operator[](unsigned i);
    const T& operator[](unsigned i) const;

    //inserts given element/s to the back of the vector
    //if the vector would be filled during any stage of that operation it preemptively resizes the vector
    //throws bad_alloc if it fails
    void insert(const T& elem);
    void bulkInsert(const SerializableVector<T>& other);

    //finds and removes given element from the vector
    //it keeps order
    void remove(const T& elem);

    //assures that vector has enough space to fit atleast <space> number of elements
    //if vector has enough space it does nothing
    //if vector does not it resizes it so it has enough space to fit elements
    //throws bad_alloc if it fails
    void reserve(unsigned space);

    //writes all the contents of the vector to a given file
    void writeToBinaryFile(const char* fileName) const;

    //returns true if the vector has 0 elements
    bool empty() const;
    //returns the number of elements in the vector
    unsigned size() const;
    //returns a const or non-const reference to the first/last element
    T& last();
    const T& last() const;
    T& first();
    const T& first() const;

private:
    void copy(const SerializableVector& other);
    void resize();
    void m_resize(unsigned space);

    void readFromBinaryFile(const char* fileName);
    unsigned inline newCapacity() const;

    //returns the closest power of 2 grater than the given unsigned integer
    unsigned inline getClosestPowerOf2(unsigned num);

    T* m_data;
    unsigned m_size;
    unsigned m_capacity;
};

#include "SerializableVector.inl"

