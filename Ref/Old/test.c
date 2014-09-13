#include <iostream>
int main()
{
  char *p = "Hello";
  while(*p)
   std::cout << *p++;//Increment the pointer here 
    return 0;
}