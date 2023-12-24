#include <iostream>
using namespace std;

double divide(double a, double b){
	double result = 0;
	if (b != 0)
	{
		result = a/b;
	}
	else
	{
		cout << "Division by zero error!" << endl;
	}
	cout << result << endl;
	return result;
}

int main(){
	double a,b;
	cout << "a: ";
	cin >> a;
	cout << "b: ";
	cin >> b;
	divide(a,b);
	return 0;
}