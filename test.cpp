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

int callPerson1(string name, int phoneNum, string message1); //the static analysis would issue a warning on the terminal for this function, because it has more than 3 parameters
int callPerson2(string name, int phoneNum, string message2, int count, int); //the static analysis would issue a warning on the terminal for this function, because it has more than 3 parameters
int callPerson3(string name, int phoneNum, string message3, abc dcf); //the static analysis would issue a warning on the terminal for this function, because it has more than 3 parameters
int callPerson4(string name, int phoneNum, string message4, int count); //the static analysis would issue a warning on the terminal for this function, because it has more than 3 parameters
int callPerson4(string name, int phoneNum); 
