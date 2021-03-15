#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"
#include <math.h>

class Circle: public Shape
{
  public:
      Circle(double r):_r(r)
      {

      }

      double area() const
      {
        return M_PI * _r * _r;

      }

      double perimeter() const
      {
        return 2 * M_PI * _r;
      }

      double compactness() const
      {
        try
        {
          if(area()==0)
          {
            throw std::string("Division by zero");
          }
          return (perimeter() * perimeter() ) / area();
        }
        catch(const char* str)
        {
          std::cerr << "trouble " << str;
        }
      }

  private:
      double _r;
};

#endif
