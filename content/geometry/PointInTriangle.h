/**
 * Author: Ralph
 * Description: 
 */

struct Point {
  long long x, y;

  Point() { x = 0, y = 0; }
  Point(long long x, long long y) { this->x = x, this->y = y; }

  Point operator-(const Point &other) {
    return Point(this->x - other.x, this->y - other.y);
  }

  static long long crossProduct(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
  }

  bool operator==(const Point &other) {
    return this->x == other.x && this->y == other.y;
  }

  double length() { return sqrt(x * x + y * y); }
};

bool sameSign(long long a, long long b) {
  return (a > 0 && b > 0) || (a < 0 && b < 0);
}

bool sameSide(Point p1, Point p2, Point a, Point b) {
  long long first = Point::crossProduct(b - a, p1 - a);
  long long second = Point::crossProduct(b - a, p2 - a);
  return sameSign(first, second);
}

bool pointInTriangle(Point p, Point a, Point b, Point c) {
  return sameSide(p, a, b, c) && sameSide(p, b, a, c) && sameSide(p, c, a, b);
}

bool pointOnSegment(Point p, Point a, Point b) {
  return Point::crossProduct(b - a, p - a) == 0 &&
         ((sameSign(p.x - a.x, b.x - a.x) && (p.x - a.x) / (b.x - a.x) == 0) ||
          (sameSign(p.y - a.y, b.y - a.y) && (p.y - a.y) / (b.y - a.y) == 0));
}