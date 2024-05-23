#ifndef OPTIONAL_CPP
#define OPTIONAL_CPP

#include "optional.h"

template <typename T>
Optional<T>::Optional() {
    this->is_present = false;
}

template <typename T>
Optional<T>::Optional(T value) {
    this->is_present = true;
    this->value = value;
}

template <typename T>
void Optional<T>::set_value(T value) {
    this->is_present = true;
    this->value = value;
}

template <typename T>
void Optional<T>::set_empty() {
    this->is_present = false;
}

template <typename T>
T Optional<T>::get_value() {
    return this->value;
}

template <typename T>
bool Optional<T>::has_value() {
    return this->is_present;
}

#endif