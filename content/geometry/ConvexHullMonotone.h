/**
 * Author: Ralph
 * Description: 
 */
struct Point {
  long long x, y;

  const bool operator<(const Point &r) const {
    return x < r.x || (x == r.x && y < r.y);
  }
} pts[MAXN], hull[MAXN];

// includes points on the side of a hull
// to exclude, change > to >=
bool ccw(Point p1, Point p2, Point p3) {
  return (p1.x - p2.x) * (p3.y - p2.y) > (p3.x - p2.x) * (p1.y - p2.y);
}

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> pts[i].x >> pts[i].y;
  }

  sort(pts, pts + n);

  int sz = 0;
  for (int i = 0; i < n; i++) {
    while (sz > 1 && ccw(hull[sz - 2], hull[sz - 1], pts[i]))
      sz--;
    hull[sz++] = pts[i];
  }

  int botSz = --sz;
  for (int i = n - 1; i >= 0; i--) {
    while (sz - botSz > 1 && ccw(hull[sz - 2], hull[sz - 1], pts[i]))
      sz--;
    hull[sz++] = pts[i];
  }

  sz--;

  cout << sz << endl;
  for (int i = 0; i < sz; i++) {
    cout << hull[i].x << " " << hull[i].y << endl;
  }
}