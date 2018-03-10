#include <iostream>
#include "common_ptr.h"
using namespace std;
using mypointer::common_ptr;

int main()
{
	{
		common_ptr<int> value1(new int(5));
		common_ptr<int> value2(value1);
		common_ptr<int> value3;

		value3 = value2;

		cout << *value1 << endl;
		cout << *value2 << endl;
		cout << *value3 << endl;
		cout << value1.get_count() << endl;
	}
	system("pause");
}