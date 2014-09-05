#include <iostream>
using std::cerr;
using std::endl;
using namespace std;

void g1(int& b){b += 3;}
void f1(int const& a){
g1(a);
cout << "\nEl valor de a es " << a << endl;

}

int main()
{
   int first = 1;
   f1(first);
   cout << first << endl;
 
}
