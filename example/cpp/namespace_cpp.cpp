#include <iostream>
using namespace std;

namespace savitch1
{
    void greeting( );
}

namespace savitch2
{
    void greeting( );
}

void big_greeting( );

int main( )
{
    {
        using namespace savitch2;
        greeting( );
    }

    {
        using namespace savitch1;
        greeting( );
    }

    big_greeting( );

    return 0;
}

namespace savitch1
{
    void greeting( )
    {
        cout << "Hello from namespace savitch1.\n";
    }
}

namespace savitch2
{
    void greeting( )
    {
        cout << "Greetings from namespace savitch2.\n";
    }
}

void big_greeting( )
{
    cout << "A Big Global Hello!\n";
}


/*
output:
Greetings from namespace savitch2.
Hello from namespace savitch1.
A Big Global Hello!

*/
