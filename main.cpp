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

bool compareByX(const Warrior &a, const Warrior &b)
{
	return (a.x < b.x);
}

bool compareByY(const Warrior &a, const Warrior &b)
{
	return (a.y < b.y);
}

Warrior calculateLoss(const Warrior &a, const Warrior &b)
{
	if (a.strength < b.strength)
	{
		return a;
	}

	if (a.strength > b.strength)
	{
		return b;
	}

	if (a.id > b.id)
	{
		return a;
	}

	return b;
}

void printWarrior(const Warrior &warrior)
{
	cout << warrior.x << " " << warrior.y << endl;
}

double distance(const Warrior &a, const Warrior &b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

pair<Warrior, Warrior> findClosestMiddle(const vector<Warrior> &middleStrip, double min)
{
	pair<Warrior, Warrior> pair(middleStrip[0], middleStrip[1]);
	size_t size = middleStrip.size();

	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = i + 1; j < size && (middleStrip[j].y - middleStrip[i].y) < min; ++j)
		{
			if (distance(middleStrip[i], middleStrip[j]) < min)
			{
				pair.first = middleStrip[i];
				pair.second = middleStrip[j];
			}
		}
	}

	return pair;
}

void killWarrior(vector<Warrior> &warriors, Warrior warrior)
{
	printWarrior(warrior);

	for (auto it = warriors.begin(); it!=warriors.end(); ++it)
	{
		if (it->x==warrior.id)
		{
			warriors.erase(it);
			return;
		}
	}
}

void killWarrior(Warrior *warrior)
{
	printWarrior(*warrior);

	warrior->isAlive = false;
}

pair<Warrior, Warrior> minDistanceTwoPairs(const pair<Warrior, Warrior> &a, const pair<Warrior, Warrior> &b)
{
	if (distance(a.first, a.second) < distance(b.first, b.second))
	{
		return a;
	}

	return b;
}

pair<Warrior, Warrior> minDistanceThreeWarriors(vector<Warrior>::iterator begin, vector<Warrior>::iterator end)
{
	double min = 999999999999999;

	pair<Warrior, Warrior> pair(*begin, *(begin + 1));

	for(auto i=begin; i != end; ++i)
	{
		for(auto j=i+1; j != end; ++j)
		{
			double dist = distance(*i, *j);

			if(dist < min)
			{
				min = dist;
				pair.first = *i;
				pair.second = *j;
			}
		}
	}

	return pair;
}

pair<Warrior, Warrior> findClosestPair(vector<Warrior>::iterator begin, vector<Warrior>::iterator end)
{
	vector<Warrior>::difference_type n = end - begin;

	if (n<=3)
	{
		return minDistanceThreeWarriors(begin, end);
	}

	vector<Warrior>::difference_type midPoint = n/2;
	Warrior middle = *(begin + midPoint);

	pair<Warrior, Warrior> left = findClosestPair(begin, begin + midPoint - 1);

	pair<Warrior, Warrior> right = findClosestPair(begin + midPoint, end);

	pair<Warrior, Warrior> min = minDistanceTwoPairs(left, right);

	double minDist = distance(min.first, min.second);

	vector<Warrior> strip;

	sort(strip.begin(), strip.end(), &compareByY);

	for (vector<Warrior>::difference_type i = 0; i < n; ++i)
	{
		if (abs(double((begin + i)->x - middle.x)) < minDist)
		{
			strip.push_back(*(begin + i));
		}
	}

	return minDistanceTwoPairs(min, findClosestMiddle(strip, minDist));
}

void fight(vector<Warrior> &warriors, pair<Warrior, Warrior> &&pair)
{
	Warrior victim = calculateLoss(pair.first, pair.second);

	killWarrior(warriors, victim);
}

int main()
{
	unsigned short n, t;
	cin >> n >> t;

	vector<Warrior> warriors(n);

	for (unsigned int i = 0; i < n; ++i)
	{
		cin >> warriors[i].x >> warriors[i].y >> warriors[i].strength;
		warriors[i].id = i;
	}

	std::sort(warriors.begin(), warriors.end(), &compareByX);

	findClosestPair(warriors.begin(), warriors.end());

	for (unsigned int i = 0; i < t; ++i)
	{
		fight(warriors, findClosestPair(warriors.begin(), warriors.end()));
	}

	return 0;
}