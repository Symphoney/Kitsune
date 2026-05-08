//
// Adapter Design Pattern: vector_raster.h
//
/*
What is the Adapter Design Pattern?
The Adapter Design Pattern is a structural design pattern that allows incompatible interfaces to work together.
It acts as a bridge between two incompatible interfaces, enabling them to communicate and work together
without modifying their code.
 */

/*
 * Common real-world uses:
 * - SVG rendering
 * - GUI toolkits
 * - font rendering
 * - game engines converting geometry to pixels
 *
 * Vector vs Raster
 * Vector: Shapes defined by primitives (like lines, curves, polygons).
 * Scales without loss, ideal for illustrations and logos.
 * Raster: fixed grid of pixels. Rendering happens by setting pixel values (points)
 * Scales poorly, ideal for photographs and complex images.
 *
 * Why teh adapter - LineToPointAdapter
 * Raster code knows how to draw points/pixels. The adapter converts vector primitives (a Line)
 * into the sequence of Points the raster renderer expects. It bridges both representations
 * so you can keep vector models and reuse existing raster drawing code.
 */

#include <iostream>
#include <vector>
#include <memory>

struct Point
{
  int x; // x and y coordinates of a point
  int y;
};

struct Line
{
  Point start; // start and end points of a line
  Point end;
};

struct VectorObject
{
  typedef std::vector<Line> Lines; // a vector object is a collection of lines

  Lines lines;

  virtual std::vector<Line>::iterator begin() { return lines.begin();};
  virtual std::vector<Line>::iterator end() { return lines.end();}; // allow iteration over lines in a vector object
};

struct VectorRectangle : VectorObject {
  // constructor to create a rectangle defined by its top-left corner (x, y) and its width and height
  VectorRectangle(int x, int y, int width, int height) {
    lines.emplace_back(Line{ Point{x, y}, Point {x + width, y }});
    lines.emplace_back(Line{ Point{x + width, y}, Point{x + width, y}});
    lines.emplace_back(Line{ Point{x, y}, Point{x, y + height}});
    lines.emplace_back(Line{ Point{x, y + height}, Point{x + width, y + height}});
  }
};

// Create a vector of shared pointers to VectorObject, which includes two rectangles
std::vector<std::shared_ptr<VectorObject>> vectorObjects {
  std::make_shared<VectorRectangle>(10, 10, 100, 100),
  std::make_shared<VectorRectangle>(30, 30, 60, 60)
};

// LineToPointAdapter is an adapter that converts a Line into a collection of Points
class LineToPointAdapter {
public:
  using Points = std::vector<Point>;
private:
  Points points {};
public:
  explicit LineToPointAdapter(const Line &line) {
    points.reserve(2);
    points.push_back(line.start);
    points.push_back(line.end);
  }

  Points::const_iterator begin() const { return points.begin(); }
  Points::const_iterator end() const { return points.end(); }

};

/*
// Created by Rija on 4/14/2026.
//

#include <iostream>
#include "vector_raster.h"

int main() {
  // construct a line from (0, 0) to (3, 3)
  Line line{ Point{0, 0}, Point{3, 3} };

  LineToPointAdapter adapter(line);

  int idx = 0;
  for (const auto &p : adapter) {
    std::cout << "Point " << idx++ << ": " << p.x << ", " << p.y << '\n';
  }

  return 0;
}
*/