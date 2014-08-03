/*
  Project Euler Problem 39
  Mikael Fors 2014

  "If p is the perimeter of a right angle triangle with integral length sides,
   {a,b,c}, there are exactly three solutions for p = 120.

   For which value of p ≤ 1000, is the number of solutions maximised?"
*/

#include <iostream>
#include <cmath>
#include <unordered_map>

/*
    a ^ 2 + b ^ 2 = c ^ 3, where a + b c = 1000 at most means that
    a,b must be less than 293 because math.sqrt(2 * 293 ^ 2) + 2 * 293 = 1000

    This means roughly 85k potential side combinations (291 * 292), which is
    clearly low enough for brute force.

    We could generalize the function below by performing the calculation step
    done on the input argument, but depending on the roof-value for p, brute
    force might become a less than ideal approach.

*/

int sideSumWhichMaximizesRightTriangles() {
  std::unordered_map<int, int> triangleMap;
  double hypotenuse = 0;
  int p = 0, maxVal = -1, maxP = -1;
  for (int a = 2; a < 293; ++a) {
    for (int b = a + 1; b < 293; ++b) {
      hypotenuse = std::sqrt(a * a + b * b);
      if ((int)hypotenuse == hypotenuse) {
        p = a + b + hypotenuse;
        if (triangleMap.find(p) != triangleMap.end()) {
          triangleMap[p] += 1;
          if (triangleMap[p] > maxVal)
            maxP = p;
        } else {
          triangleMap[p] = 1;
        }
      }
    }
  }
  return maxP;
}

int main() {
  std::cout << "The answer is "
            << sideSumWhichMaximizesRightTriangles() << std::endl;
  return 0;
}
