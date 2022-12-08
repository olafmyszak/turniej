#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>

using namespace std;

struct Warrior
{
  unsigned int id{};
  unsigned int x{};
  unsigned int y{};
  unsigned int strength{};
  bool isAlive{true};
};


bool compareByX(const Warrior& a, const Warrior& b)
{
	return (a.x < b.x);
}

bool compareByY(const Warrior& a, const Warrior& b)
{
	return (a.y < b.y);
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
	cout<<warrior.x<<" "<<warrior.y<<endl;
}


double distance(const Warrior& a, const Warrior& b)
{
	return sqrt((a.x - b.x) * (a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

pair<Warrior, Warrior> findClosestMiddle(const vector<Warrior>& middleStrip, double min)
{
	pair<Warrior, Warrior> pair (middleStrip[0], middleStrip[1]);
	size_t size = middleStrip.size();

	for(size_t i = 0; i<size; ++i)
	{
		//printWarrior(middleStrip[i]);
		for(size_t j = i+1; j<size && (middleStrip[j].y - middleStrip[i].y) < min; ++j)
		{
			if(distance(middleStrip[i], middleStrip[j]) < min)
			{
				pair.first = middleStrip[i];
				pair.second = middleStrip[j];
			}
		}
	}

	return pair;
}

void killWarrior(Warrior *warrior)
{
	printWarrior(*warrior);

	warrior->isAlive = false;
}

pair<Warrior, Warrior> minDistanceTwoPairs(const pair<Warrior, Warrior>& a, const pair<Warrior, Warrior>& b)
{
//	printWarrior(a.first);
//	printWarrior(a.second);
//	printWarrior(b.first);
//	printWarrior(b.second);

	if(distance(a.first, a.second) < distance(b.first, b.second))
	{
		return a;
	}

	return b;
}

pair<Warrior, Warrior> minDistanceThreeWarriors(Warrior warriors[], size_t size)
{
	double min = 9999;

	pair<Warrior, Warrior> pair (warriors[0], warriors[1]);

	for(unsigned int i=0; i<size; ++i)
	{
		for(unsigned int j=i+1; j<size; ++j)
		{
			double dist = distance(warriors[i], warriors[j]);
			if(dist < min)
			{
				min = dist;
				pair.first = warriors[i];
				pair.second =warriors[j];

			}
		}
	}

	return pair;
}

pair<Warrior, Warrior> findClosestPair(Warrior warriors[], size_t n)
{
	if(n == 2)
	{
		return {warriors[0], warriors[1]};
	}

	if(n == 3)
	{
		return minDistanceThreeWarriors(warriors, n);
	}

	size_t midPoint = n/2;
	Warrior middle = warriors[midPoint];

	pair<Warrior, Warrior> left = findClosestPair(warriors, midPoint);
	//printWarrior(left.first);
	//printWarrior(left.second);

	pair<Warrior, Warrior> right = findClosestPair(warriors + midPoint, n-midPoint);
	//printWarrior(right.first);
	//printWarrior(right.second);


	pair<Warrior, Warrior> min = minDistanceTwoPairs(left, right);

	//printWarrior(min.first);
	//printWarrior(min.second);

	double minDist = distance(min.first, min.second);

	vector<Warrior> strip;

	sort(strip.begin(), strip.end(), &compareByX);

	for(size_t i=0; i<n; ++i)
	{
		if(abs(double(warriors[i].x - middle.x)) < minDist)
		{
			strip.push_back(warriors[i]);
		}
	}

	for(auto&& el : strip)
	{
		//printWarrior(el);
	}

	return minDistanceTwoPairs(min, findClosestMiddle(strip, minDist));
}

void fight();


int main()
{
	unsigned short n, t;
	cin>>n>>t;

	auto *warriors = new Warrior[n];

	for(unsigned int i = 0; i<n; ++i)
	{
		cin >> warriors[i].x >> warriors[i].y >> warriors[i].strength;
		warriors[i].id = i;
	}

	std::sort(warriors, warriors+n, &compareByX);

	pair<Warrior, Warrior> pair = findClosestPair(warriors, n);



	delete [] warriors;

	return 0;
}