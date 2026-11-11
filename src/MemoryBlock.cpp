#include "MemoryBlock.h"

// constructor
MemoryBlock::MemoryBlock(size_t size) : size(size), refCount(0), data(new int[size]()) {}

// destructor
MemoryBlock::~MemoryBlock()
{
    delete[] data;
}
// copy constructor
MemoryBlock::MemoryBlock(const MemoryBlock &other)
    : size(other.size), refCount(0), data(new int[other.size])
{
    std::copy(other.data, other.data + other.size, data);
}

// assignment operator
MemoryBlock &MemoryBlock::operator=(const MemoryBlock &other)
{
    if (this != &other)
    {
        delete[] data;
        size = other.size;
        refCount = 0;
        data = new int[size];
        std::copy(other.data, other.data + other.size, data);
    }
    return *this;
}

// move constructor
MemoryBlock::MemoryBlock(MemoryBlock &&other)
    : size(other.size), refCount(other.refCount), data(other.data)
{
    other.data = nullptr;
    other.refCount = 0;
    other.size = 0;
}

// move assignment operator
MemoryBlock &MemoryBlock::operator=(MemoryBlock &&other)
{
    if (this != &other)
    {
        delete[] data;
        size = other.size;
        refCount = other.refCount;
        data = other.data;
        other.data = nullptr;
        other.size = 0;
        other.refCount = 0;
    }
    return *this;
}

int MemoryBlock::readFromBlock(std::size_t offset) const
{
    return data[offset];
}

void MemoryBlock::writeToBlock(std::size_t offset, int value)
{
    data[offset] = value;
}

void MemoryBlock::acquire()
{
    refCount++;
}

IdleAction MemoryBlock::release()
{
    refCount--;
    if (refCount = 0)
    {
        return onLastRelease();
    }
    return IdleAction::KeepCached;
}