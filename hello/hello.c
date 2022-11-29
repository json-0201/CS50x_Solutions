#include <stdio.h>
#include <cs50.h>

string get_name(void);  // call a function

int main(void)
{
    string name = get_name();
    printf("hello, %s\n", name);
}

string get_name(void)   // return_type function_name(parameter)
{
    string user_name = get_string("Enter your name: ");
    return user_name;
}