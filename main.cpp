#include "print_ip.h"

int main() {
    PrintIp( char{-1} ); // 255
    PrintIp( short{0} ); // 0.0
    PrintIp( int{2130706433} ); // 127.0.0.1
    PrintIp( long{8875824491850138409} ); // 123.45.67.89.101.112.131.41
    PrintIp( std::string{"Hello, World!"} ); // Hello, World!
    PrintIp( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    PrintIp( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    PrintIp( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
    PrintIp( std::make_tuple("123", "456", "789", "0") ); // 123.456.789.0
    // compile error
    // PrintIp( std::make_tuple(123, 456, "789", "123") );
    return 0;
}
