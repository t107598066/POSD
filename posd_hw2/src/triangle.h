#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "shape.h"
#include <math.h>

class Triangle: public Shape
{
  public:
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3):_x1(x1), _x2(x2), _x3(x3), _y1(y1), _y2(y2), _y3(y3)
    {
        isTriangle();
    }

    double area() const
    {
      double s1 = sqrt(pow((_x1 - _x2),2)+pow((_y1 - _y2),2));
      double s2 = sqrt(pow((_x2 - _x3),2)+pow((_y2 - _y3),2));
      double s3 = sqrt(pow((_x1 - _x3),2)+pow((_y1 - _y3),2));
      double s = (s1 + s2 + s3) / 2;
      return sqrt(s * (s - s1) * (s - s2) * (s - s3));
    }

    double perimeter() const
    {
      return sqrt(pow((_x1 - _x2),2)+pow((_y1 - _y2),2))
      +sqrt(pow(_x2 - _x3,2)+pow(_y2 - _y3,2))
      +sqrt(pow(_x1 - _x3,2)+pow(_y1 - _y3,2));
    }

    double compactness() const
    {
      try
      {
        if(isTriangle()==false)
        {
          throw std::string("Division by zero");
          return 0;
        }
        return (perimeter() * perimeter() ) / area();
      }
      catch(const char* str)
      {
        std::cerr << "trouble " << str;
      }
    }

    bool isTriangle() const
    {
        double s1 = sqrt(pow((_x1 - _x2),2)+pow((_y1 - _y2),2));
        double s2 = sqrt(pow((_x2 - _x3),2)+pow((_y2 - _y3),2));
        double s3 = sqrt(pow((_x1 - _x3),2)+pow((_y1 - _y3),2));

          if((s1+s2)<=s3 || (s2+s3)<=s1 || (s1+s3)<=s2)
          {
            throw std::string("Not a triangle.");
            return false;
          }
          else
          {
            return true;
          }
    }

  private:
    double _x1,_x2,_x3,_y1,_y2,_y3;
};

#endif
