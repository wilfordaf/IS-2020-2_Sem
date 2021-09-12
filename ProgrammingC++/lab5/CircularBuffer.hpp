#ifndef CIRCULARBUFFER_HPP_INCLUDED
#define CIRCULARBUFFER_HPP_INCLUDED

#include <iterator>
#include <string.h>

template <class T>
class Iterator
{
private:
    T* buffer;
    int bufBegin, bufCapacity, index;
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = int;
    using reference = T&;
    using pointer = T*;
    Iterator(T* buffer_, int bufBegin_, int bufCapacity_, int index_)
    {
        buffer = buffer_;
        bufBegin = bufBegin_;
        bufCapacity = bufCapacity_;
        index = index_;
    }
    bool operator == (const Iterator& other) const
    {
        return index == other.index;
    }
    bool operator != (const Iterator& other) const
    {
        return !(*this == other);
    }
    Iterator& operator ++ ()
    {
        index++;
        return *this;
    }
    Iterator& operator -- ()
    {
        index--;
        return *this;
    }
    Iterator& operator += (difference_type d)
    {
        index += d;
        return *this;
    }
    Iterator& operator -= (difference_type d)
    {
        index -= d;
        return *this;
    }
    bool operator < (const Iterator& other)
    {
        return index < other.index;
    }
    bool operator <= (const Iterator& other)
    {
        return index <= other.index;
    }
    bool operator > (const Iterator& other)
    {
        return !(*this <= other);
    }
    bool operator >= (const Iterator& other)
    {
        return !(*this < other);
    }
    reference operator * () const
    {
        return buffer[(bufBegin + index) % bufCapacity];
    }
    friend Iterator operator + (Iterator i, difference_type d)
    {
        i += d;
        return i;
    }
    friend Iterator operator + (difference_type d, Iterator& i)
    {
        return i + d;
    }
    friend Iterator operator - (Iterator i, difference_type d)
    {
        i -= d;
        return i;
    }
    friend Iterator operator - (difference_type d, Iterator& i)
    {
       return i - d;
    }
    friend difference_type operator - (Iterator& i, Iterator& other)
    {
        return i.index - other.index;
    }
};

template <class T>
class CircularBuffer
{
private:
    int bufCapacity, bufSize, bufBegin;
    T* buffer;
public:
    CircularBuffer(int C)
    {
        bufCapacity = C;
        bufSize = 0;
        bufBegin = 0;
        buffer = new T[bufCapacity];
    }
    ~CircularBuffer()
    {
        delete[] buffer;
    }
    Iterator<T> begin() const
    {
        return Iterator<T>(buffer, bufBegin, bufCapacity, 0);
    }
    Iterator<T> end() const
    {
        return Iterator<T>(buffer, bufBegin, bufCapacity, bufSize);
    }
    void addFirst(const T& value)
    {
        bufBegin--;
        if (bufBegin == -1)
        {
            bufBegin = bufCapacity - 1;
        }
        buffer[bufBegin] = value;
        if (bufSize != bufCapacity)
        {
            bufSize++;
        }
    }
    void addLast(const T& value)
    {
        int bufEnd = (bufBegin + bufSize) % bufCapacity;
        buffer[bufEnd] = value;
        if (bufSize != bufCapacity)
        {
            bufSize++;
        }
    }
    T first()
    {
        return buffer[bufBegin];
    }
    T last()
    {
        int bufEnd = (bufBegin + bufSize - 1) % bufCapacity;
        return buffer[bufEnd];
    }
    T& operator[] (int index)
    {
        if (index >= bufSize || index < 0)
        {
            std::string error = "Trying to access the " + std::to_string(index) + " element, but the size is " + std::to_string(bufSize) + ".";
            throw std::out_of_range(error);
        }
        int curIndex = (bufBegin + index) % bufCapacity;
        return buffer[curIndex];

    }
    T& operator[] (int index) const
    {
        if (index >= bufSize || index < 0)
        {
            std::string error = "Trying to access the " + std::to_string(index) + " element, but the size is " + std::to_string(bufSize) + ".";
            throw std::out_of_range(error);
        }
        int curIndex = (bufBegin + index) % bufCapacity;
        return buffer[curIndex];
    }
    void delFirst()
    {
        if (bufSize != 0)
        {
            bufBegin = (bufBegin + 1) % bufCapacity;
            bufSize--;
        }

    }
    void delLast()
    {
        if (bufSize != 0)
        {
            bufSize--;
        }
    }
    void changeCapacity(int newCapacity)
    {
        T* newBuffer = new T[newCapacity];
        bufSize = std::min(bufSize, newCapacity);
        for (int i = 0; i < bufSize; i++)
        {
            newBuffer[i] = buffer[(bufBegin + i) % bufCapacity];
        }
        delete[] buffer;
        buffer = newBuffer;
        bufBegin = 0;
        bufCapacity = newCapacity;
    }
};

#endif // CIRCULARBUFFER_HPP_INCLUDED
