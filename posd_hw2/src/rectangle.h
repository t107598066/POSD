#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"
#include <math.h>

class Rectangle: public Shape
{
  public:
    Rectangle(double l, double w):_l(l),_w(w)
    {

    }

    double area () const
    {
      return _l * _w;
    }

    double perimeter () const
    {
      return 2*(_l + _w);
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
    double _l,_w;
};

#endif
