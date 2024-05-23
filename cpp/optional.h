#ifndef OPTIONAL_H
#define OPTIONAL_H

/// <summary>
/// Represents an optional value.
/// </summary>
template <typename T>
struct Optional {
private:
    bool is_present;
    T value;
public:
    Optional();
    Optional(T value);
    void set_value(T value);
    void set_empty();
    T get_value();
    bool has_value();
};

#include "optional.cpp"

#endif
