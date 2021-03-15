#include <gtest/gtest.h>
#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/sort.h"
#include <algorithm>

TEST(SortTest, AreaAscendingSorting)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
  {
    new Circle(1.0), new Circle(0.5), new Rectangle(5, 6), new Rectangle(0.5, 1.5)
  };

  Sort* sort = new Sort(shapes);
  sort->sortArea([](Shape *a,Shape *b)
  {
    return a->area() < b->area();
  });
    ASSERT_NEAR(0.75, (*shapes)[0]->area(), 0.001);
    ASSERT_NEAR(0.25*3.1415, (*shapes)[1]->area(), 0.001);
    ASSERT_NEAR(3.1415, (*shapes)[2]->area(), 0.001);
    ASSERT_NEAR(30, (*shapes)[3]->area(), 0.001);
}

TEST(SortTest, AreaDescendingSorting)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
  {
    new Circle(1.0), new Circle(0.5), new Rectangle(5, 6), new Rectangle(0.5, 1.5)
  };

  Sort* sort = new Sort(shapes);
  sort->sortArea([](Shape *a,Shape *b)
  {
    return a->area() > b->area();
  });
    ASSERT_NEAR(30, (*shapes)[0]->area(), 0.001);
    ASSERT_NEAR(3.1415, (*shapes)[1]->area(), 0.001);
    ASSERT_NEAR(0.25*3.1415, (*shapes)[2]->area(), 0.001);
    ASSERT_NEAR(0.75, (*shapes)[3]->area(), 0.001);
}

TEST(SortTest, PerimeterAscendingSorting)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
  {
    new Circle(1.0), new Circle(0.5), new Rectangle(5, 6), new Rectangle(0.5, 1.5)
  };

  Sort* sort = new Sort(shapes);
  sort->sortPerimeter(perimeterAscendingComparison);
  ASSERT_NEAR(3.14159, (*shapes)[0]->perimeter(), 0.001);
  ASSERT_NEAR(4, (*shapes)[1]->perimeter(), 0.001);
  ASSERT_NEAR(6.283, (*shapes)[2]->perimeter(), 0.001);
  ASSERT_NEAR(22, (*shapes)[3]->perimeter(), 0.001);
}

TEST(SortTest, PerimeterDescendingSorting)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
  {
    new Circle(1.0), new Circle(0.5), new Rectangle(5, 6), new Rectangle(0.5, 1.5)
  };
  Sort* sort = new Sort(shapes);
  sort->sortPerimeter(perimeterDescendingComparison);
  ASSERT_NEAR(22, (*shapes)[0]->perimeter(), 0.001);
  ASSERT_NEAR(6.283, (*shapes)[1]->perimeter(), 0.001);
  ASSERT_NEAR(4, (*shapes)[2]->perimeter(), 0.001);
  ASSERT_NEAR(3.14159, (*shapes)[3]->perimeter(), 0.001);
}

TEST(SortTest, CompactnessAscendingSorting)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
  {
    new Circle(1.0), new Circle(0.3), new Rectangle(5, 6), new Rectangle(0.5, 1.5)
  };
  std::sort(shapes->begin(),shapes->end(),CompactnessAscendingComparison());
  ASSERT_NEAR(12.566370, (*shapes)[0]->compactness(), 0.001);
  ASSERT_NEAR(12.566370, (*shapes)[1]->compactness(), 0.001);
  ASSERT_NEAR(16.133333, (*shapes)[2]->compactness(), 0.001);
  ASSERT_NEAR(21.333333, (*shapes)[3]->compactness(), 0.001);
}

TEST(SortTest, CompactnessDescendingSorting)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
  {
    new Circle(1.0), new Circle(0.3), new Rectangle(5, 6), new Rectangle(0.5, 1.5)
  };
  std::sort(shapes->begin(),shapes->end(),CompactnessDescendingComparison());
  ASSERT_NEAR(21.333333, (*shapes)[0]->compactness(), 0.001);
  ASSERT_NEAR(16.133333, (*shapes)[1]->compactness(), 0.001);
  ASSERT_NEAR(12.566370, (*shapes)[2]->compactness(), 0.001);
  ASSERT_NEAR(12.566370, (*shapes)[3]->compactness(), 0.001);
}
