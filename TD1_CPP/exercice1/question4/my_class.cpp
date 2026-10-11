#include "my_class.h"
#include <iostream>

my_class::my_class() : element("Hello World !") {}

my_class::my_class(std::string valeur) : element(valeur) {}

void my_class::print_my_element() const
{
    std::cout << element << std::endl;
}
