#include<iostream> 
#include<vector>
using namespace std;
typedef vector<int> lnum;

lnum sumLong(string a, string b)
{
	lnum num1, num2;
	lnum sum; int i, tempSum = 0;

	for (int i = a.size() - 1; i >= 0; --i)
		num1.push_back(a[i] - '0');

	for (int i = b.size() - 1; i >= 0; --i)
		num2.push_back(b[i] - '0');

	for (i = 0; i < num1.size() || i < num2.size(); ++i)
	{
		if (i < num1.size()) tempSum += num1[i];
		if (i < num2.size()) tempSum += num2[i];
		sum.push_back(tempSum % 10);
		tempSum /= 10;
	}
	if (tempSum == 1) sum.push_back(tempSum);
	return sum;

}

void writeLong(lnum a)
{
	for (int i = a.size() - 1; i >= 0; --i) cout << a[i];
}

int main()
{
	int n, i;
	string a, b;
	cin >> n;
	for (i = 0; i < n; ++i)
	{
		cin >> a >> b;
		cout << "Case " << i + 1 << ":\n";
		cout << a << " + " << b << " = ";
		writeLong(sumLong(a, b));
		cout << "\n";
	}
	return 0;
}