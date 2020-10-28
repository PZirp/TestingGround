#include "Point.h"


		Point::Point(int x, int y)// :x{ x }, y{ y } {} 
		{
			/*coords[0] = x;
			coords[1] = y;*/
			c.push_back(x);
			c.push_back(y);
		}

		void Point::setX(int newX) {
			/*x*/ /*coords[0] = newX;*/ c[0] = newX;
		}

		void Point::setY(int newY) {
			/*y*/ /*coords[1] = newY;*/ c[1] = newY;
		}

		int Point::getX() {
			return /*coords[0];*/ c[0];
		}

		int Point::getY() {
			return /*coords[1];*/ c[1];
		}

		/*int**/ std::vector<int> Point::getCoordinates() {
			return /*coords*/c;
		}