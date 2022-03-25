#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

class CNonCopyable
{
public:
    CNonCopyable() = default;
    virtual ~CNonCopyable() = default;

public:
    CNonCopyable(const CNonCopyable& other) = delete;
    CNonCopyable& operator=(const CNonCopyable& other) = delete;
};

#endif // NONCOPYABLE_H
