/**
 * Author: Ralph
 * Description: 
 */
struct Point {
  long long x, y;
} verts[MAXN];

int n;
// checks if a point is enclosed within a polygon
// returns -1 if on boundary, 0 if outside, 1 if enclosed
// polygon given as a list of consecutive vertices with the last one equal to
// the first

int isEnclosed(Point p) {
  int intersectCount = 0;

  // extend ray vertically and count intersections
  for (int i = 0; i < n; i++) {
    // point.x must be >= l.first and < r.first
    Point l, r;
    if (verts[i].x < verts[i + 1].x)
      l = verts[i], r = verts[i + 1];
    else if (verts[i].x > verts[i + 1].x)
      l = verts[i + 1], r = verts[i];
    // if line is vertical, we can ignore (can be proven to work))
    else {
      if (verts[i].x == p.x && p.y >= min(verts[i].y, verts[i + 1].y) &&
          p.y <= max(verts[i].y, verts[i + 1].y))
        return -1;
      continue;
    }

    if (p.x >= l.x && p.x < r.x) {
      long long cross = (r.y - l.y) * (p.x - l.x) - (p.y - l.y) * (r.x - l.x);
      if (cross == 0)
        return -1;
      intersectCount += cross > 0;
    }
  }
  return intersectCount % 2;
}
