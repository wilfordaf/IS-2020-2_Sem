#ifndef PREDICATE_HPP_INCLUDED
#define PREDICATE_HPP_INCLUDED

template<class Iterator, class Predicate>
bool allOf(Iterator begin, Iterator end, Predicate pred)
{
    for (Iterator current = begin; current != end; current++)
    {
        if (!pred(*current))
        {
            return false;
        }
    }
    return true;
}

template<class Iterator, class Predicate>
bool anyOf(Iterator begin, Iterator end, Predicate pred)
{
    for (Iterator current = begin; current != end; current++)
    {
        if (pred(*current))
        {
            return true;
        }
    }
    return false;
}

template<class Iterator, class Predicate>
bool noneOf(Iterator begin, Iterator end, Predicate pred)
{
    for (Iterator current = begin; current != end; current++)
    {
        if (pred(*current))
        {
            return false;
        }
    }
    return true;
}

template<class Iterator, class Predicate>
bool oneOf(Iterator begin, Iterator end, Predicate pred)
{
    bool answer = false;
    for (Iterator current = begin; current != end; current++)
    {
        if (pred(*current))
        {
            if (answer)
            {
                return false;
            }
            answer = true;
        }
    }
    return answer;
}

template<class Iterator, class Predicate>
bool isSorted(Iterator begin, Iterator end, Predicate pred)
{
    Iterator newEnd = end;
    newEnd--;
    for (Iterator current = begin; current != newEnd; current++)
    {
        Iterator next = current;
        next++;
        if (!pred(*current, *next))
        {
            return false;
        }
    }
    return true;
}

template<class Iterator>
bool isSorted(Iterator begin, Iterator end)
{
    Iterator newEnd = end;
    newEnd--;
    for (Iterator current = begin; current != newEnd; current++)
    {
        Iterator next = current;
        next++;
        if (*current > *next)
        {
            return false;
        }
    }
    return true;
}

template<class Iterator, class Number>
Iterator findNot(Iterator begin, Iterator end, const Number& num)
{
    for (Iterator current = begin; current != end; current++)
    {
        if (*current != num)
        {
            return current;
        }
    }
    return end;
}

template<class Iterator, class Number>
Iterator findBackward(Iterator begin, Iterator end, const Number& num)
{
    Iterator answer = end;
    for (Iterator current = begin; current != end; current++)
    {
        if (*current == num)
        {
            answer = current;
        }
    }
    return answer;
}

template<class Iterator, class Predicate>
bool isPartitioned(Iterator begin, Iterator end, Predicate pred)
{
    Iterator newEnd = end;
    newEnd--;
    bool F = pred(*begin);
    bool L = pred(*newEnd);
    if (F != L)
    {
        bool secondHalf = false;
        Iterator newBeg = begin;
        newBeg++;
        for (Iterator current = newBeg; current != newEnd; current++)
        {
            if (secondHalf && pred(*current) != L)
            {
                return false;
            }
            if (!secondHalf && pred(*current) != F)
            {
                secondHalf = true;
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

template<class Iterator, class Predicate>
bool isPalindrome(Iterator begin, Iterator end, Predicate pred)
{
    Iterator currentEnd = end;
    currentEnd--;
    for (Iterator currentBeg = begin; currentBeg != end; currentBeg++)
    {
        if (currentBeg == currentEnd)
        {
            return true;
        }
        if (!pred(*currentBeg, *currentEnd))
        {
            return false;
        }
        currentEnd--;
        if (currentBeg == currentEnd)
        {
            return true;
        }
    }
    return true;
}
#endif // PREDICATE_HPP_INCLUDED
