/*
Copyright(c) 2024 Roman Koshchei

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

//= INCLUDES ===================
#include <optional>
//==============================

template <typename TItem, typename TSize = uint32_t>
class CircularStack {
    static_assert(std::is_unsigned<TSize>::value, "Circular Stack TSize must be an unsigned integral type."); 

private:
    TSize top_item_index;
    TSize items_count;

    TSize buffer_capacity;
    TItem* buffer_start;

public:
    CircularStack(TSize capacity);
    ~CircularStack();

    void Push(TItem item);
    std::optional<TItem> Pop();
    void Clear();
};

template <typename TItem, typename TSize>
CircularStack<TItem, TSize>::CircularStack(TSize capacity): buffer_capacity(capacity), items_count(0) {
    this->buffer_start = new TItem[capacity];
    this->top_item_index = capacity - 1;
}

template <typename TItem, typename TSize>
CircularStack<TItem, TSize>::~CircularStack() {
    delete[] buffer_start;
}

template <typename TItem, typename TSize>
void CircularStack<TItem, TSize>::Push(TItem item) {
    top_item_index += 1;
    if (top_item_index == buffer_capacity) {
        top_item_index = 0;
    }

    buffer_start[top_item_index] = item;

    if (items_count < buffer_capacity) {
        items_count += 1;
    }
}

template <typename TItem, typename TSize>
std::optional<TItem> CircularStack<TItem, TSize>::Pop() {
    if (items_count == 0) {
        return std::nullopt;
    }

    TItem item = buffer_start[top_item_index];

    if (top_item_index == 0) {
        top_item_index = buffer_capacity - 1;
    }
    else {
        top_item_index -= 1;
    }

    items_count -= 1;

    return item;
}

template <typename TItem, typename TSize>
void CircularStack<TItem, TSize>::Clear() {
    this->items_count = 0;
    this->top_item_index = this->buffer_capacity - 1;
}