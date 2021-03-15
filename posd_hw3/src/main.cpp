#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include "shape.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"
#include "sort.h"

std::vector<double> splitValueIntoVector(std::string waitToSplitString, char comma)
{
    std::stringstream stream(waitToSplitString);
    std::vector<double> vectorValue;
    std::string buffer;
    //一個是输入流，一個是string buffer,第三個参数是讀取的分割符
    //從输入流中讀入字符，存到string變量
    while(std::getline(stream, buffer, comma))
    {
        vectorValue.push_back(std::stod(buffer));
    }
    return vectorValue;
}

void addShapeIntoVector(std::vector<std::string> inputContent, std::vector<Shape*> &shapes)
{
  for(std::string inputShapeVector:inputContent)
  {
    if(inputShapeVector.substr(0,6)=="Circle")
    {
      inputShapeVector.erase(inputShapeVector.end()-1);
      std::string value = inputShapeVector.substr(8);
      shapes.push_back(new Circle(std::stod(value)));
    }
    else if(inputShapeVector.substr(0,9)=="Rectangle")
    {
      inputShapeVector.erase(inputShapeVector.end() - 1);
      std::string splitShapeString = inputShapeVector.substr(11);
      std::vector<double> value = splitValueIntoVector(splitShapeString,',');
      shapes.push_back(new Rectangle(value[0], value[1]));
    }
    else if(inputShapeVector.substr(0,8)=="Triangle")
    {
      inputShapeVector.erase(inputShapeVector.end() - 1);
      std::string splitShapeString = inputShapeVector.substr(10);
      std::vector<double> value = splitValueIntoVector(splitShapeString,',');
      shapes.push_back(new Triangle(value[0], value[1], value[2], value[3], value[4], value[5]));
    }
  }
}


void outputFile(std::string outputFilePath, std::vector<Shape*> shapes)
{
  std::ofstream outfile;
  outfile.open(outputFilePath, std::ios::out);
  outfile << '[';
  for (Shape* shape : shapes)
      {
        if (shape != shapes.back())
        {
          outfile << shape << ',';
        }
        else
        {
          outfile << shape << ']';
        }
      }
  outfile.close();
}

int main(int argc, char *argv[]){
  std::ifstream infile;
  std::string inputStr;
  std::vector<std::string> inputContent; //save txt parameter in verctor
  std::vector<Shape*> shapes; //construct shapes parameter in verctor
  Sort* sort = new Sort(&shapes);

  infile.open(argv[1], std::ios::in);
  while(getline(infile, inputStr))
  {
        inputContent.push_back(inputStr);
  }
  infile.close();

  addShapeIntoVector(inputContent, shapes);

  //判斷面積或周長,遞增或遞減
  if(std::string(argv[3])=="area")
  {
    if(std::string(argv[4])=="inc")
    {
      sort->sortArea([](Shape *a,Shape *b)
      {
        return a->area() < b->area();
      });
    }
    else if(std::string(argv[4])=="dec")
    {
      sort->sortArea([](Shape *a,Shape *b)
      {
        return a->area() > b->area();
      });
    }
    outputFile(argv[2], shapes);
  }
  else if(std::string(argv[3])=="perimeter")
  {
    if(std::string(argv[4])=="inc")
    {
      sort->sortArea([](Shape *a,Shape *b)
      {
        return a->perimeter() < b->perimeter();
      });
    }
    else if(std::string(argv[4])=="dec")
    {
      sort->sortArea([](Shape *a,Shape *b)
      {
        return a->perimeter() > b->perimeter();
      });
    }
    outputFile(argv[2], shapes);
  }
  return 0;
}
