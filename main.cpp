#include <cstdio>
#include "Signal.hpp"

class Foo
{
    public:

        void bar(int x, int y)
        {
            printf("Foo::bar(%d, %d)\n", x, y);
        }
};

void foobar(int x, int y)
{
    printf("foobar(%d, %d)\n", x, y);
}

int main(void)
{
    Foo foo;
    Signal<int, int> s;
	
    // Connect a function
    s.connect(foobar);
    
    // Connect a class method
    s.connect(&foo, &Foo::bar);
    
    // Create and connect some lambda expression
    s.connect([&foo](int x, int y){ 
        printf("lambda::"); foo.bar(x, y); 
    });
    
    // Emit the signal !
    s.emit(4, 2);
    
    return 0;
}
