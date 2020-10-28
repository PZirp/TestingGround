#pragma once
#include <vector> 
class Point
{

private:
	//int x;
	//int y;
	//int coords[2];
	std::vector<int> c;

public:
	Point(int x, int y);
	
	void setX(int newX);

	void setY(int newY);

	int getX();

	int getY();

	/*int**/ std::vector<int> getCoordinates();

};

