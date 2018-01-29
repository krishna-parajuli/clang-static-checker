#include <string>
using namespace std;
class Person {
	public:
		Person(string, int);
		int callPerson(string name, int phoneNum, string message, int count); //the static analysis would issue a warning on the terminal for this function, because it has more than 3 parameters

	private:
		string name;
		int age;
};

void a();

int main(int argc, char* argv[]) { 
   return 0;

   for(int i=222; i<3; i++){} 
}
