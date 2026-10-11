#ifndef MY_CLASS_H
#define MY_CLASS_H
#include <string>

class my_class
{
private:
    std::string element;
public:
    my_class();
    my_class(std::string valeur);
    void print_my_element() const;
};

#endif
