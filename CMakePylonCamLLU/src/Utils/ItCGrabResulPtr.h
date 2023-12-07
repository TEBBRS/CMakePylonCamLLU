#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t
#include <pylon/PylonIncludes.h>

class ItCGrabResultPtr
{
    public:
    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = uint8_t;
        using pointer = uint8_t*;  // or also value_type*
        using reference = uint8_t&;  // or also value_type&
        Iterator(pointer ptr) : m_ptr(ptr) {}
        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        // Prefix increment
        Iterator& operator++() { m_ptr++; return *this; }

        // Postfix increment
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

        private:
            pointer m_ptr;
    };
    Iterator begin(); 
    Iterator end();
    ItCGrabResultPtr(Pylon::CGrabResultPtr ptr);
private:
    Pylon::CGrabResultPtr grabResult;
};