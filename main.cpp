#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Warrior
{
 public:
  unsigned int x;
  unsigned int y;
  unsigned int strength;
};

bool compareByX(const Warrior& a, const Warrior& b)
{
	return (a.x < b.x);
}


int main()
{
	unsigned short n, t;
	cin>>n>>t;

	vector<Warrior> warriors (n);

	for(unsigned int i = 0; i<n; ++i)
	{
		cin >> warriors[i].x >> warriors[i].y >> warriors[i].strength;
	}





	return 0;
}