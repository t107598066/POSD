#ifndef SORT_H
#define SORT_H

#include <vector>
#include <algorithm>
#include "shape.h"

class Sort
{
  public:
    Sort(std::vector<Shape*>* v): _v(v)
    {

    }

    template <class comparison>
    void sortArea(comparison compare1)
    {
      std::sort(_v->begin(),_v->end(),compare1);
    }

    template <class comparison>
    void sortPerimeter(comparison compare2)
    {
      std::sort(_v->begin(),_v->end(),compare2);
    }

    template <class comparison>
    void sortCompactness(comparison compare3)
    {
      std::sort(_v->begin(),_v->end(),compare3);
    }

  private:
      std::vector<Shape*>* _v;
};

bool perimeterAscendingComparison(Shape *a, Shape *b)
{
  return (a->perimeter() < b->perimeter());
}

bool perimeterDescendingComparison(Shape *a, Shape *b)
{
  return (a->perimeter() > b->perimeter());
};

class CompactnessAscendingComparison
{
  public:
    bool operator()(Shape *a, Shape *b)
    {
      return (a->compactness() < b->compactness());
    }
};

class CompactnessDescendingComparison
{
  public:
    bool operator()(Shape *a, Shape *b)
    {
      return (a->compactness() > b->compactness());
    }
};

#endif
