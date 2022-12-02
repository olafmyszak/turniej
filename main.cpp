#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Warrior
{
  unsigned int id;
  unsigned int x;
  unsigned int y;
  unsigned int strength;
};

bool compareByX(const Warrior& a, const Warrior& b)
{
	return (a.x < b.x);
}

Warrior calculateLoss(const Warrior& a, const Warrior& b)
{
	if(a.strength < b.strength)
	{
		return a;
	}

	if(a.strength > b.strength)
	{
		return b;
	}

	if(a.id > b.id)
	{
		return a;
	}

	return b;
}

void printWarrior(const Warrior& warrior)
{
	cout<<warrior.x<<" "<<warrior.y;
}

Warrior whoDies(const vector<Warrior>& warriors)
{
	size_t size = warriors.size();

	if(size == 1)
	{
		return warriors[0];
	}

	if(size == 2)
	{
		return calculateLoss(warriors[0], warriors[1]);
	}


}

int main()
{
	unsigned short n, t;
	cin>>n>>t;

	vector<Warrior> warriors (n);

	for(unsigned int i = 0; i<n; ++i)
	{
		cin >> warriors[i].x >> warriors[i].y >> warriors[i].strength;
		warriors[i].id = i;
	}

	std::sort(warriors.begin(), warriors.end(), &compareByX);

	return 0;
}