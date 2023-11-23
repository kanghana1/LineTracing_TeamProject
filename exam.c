#include <stdio.h>

typedef struct Point {
   int r;
   int c;
} Point;

int minPoint(Point point1, Point point2) // using in findDt method
{
   return min(point1.r, point2.r), min(point1.c, point2.c);
}

int maxPoint(Point point1, Point point2) // using in findDt method
{
   return max(point1.r, point2.r), max(point1.c, point2.c);
}

int main()
{
    printf("%d", min(3, 4));
}