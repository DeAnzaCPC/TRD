/**
 * Author: Sunho
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem, so that an expression of the type $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$ becomes true, or reports that it is unsatisfiable.
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.either(0, \tilde3); // Var 0 is true or var 3 is false
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 * Status: stress-tested
 */
#pragma once

#include "SCC.h"

struct two_sat {
  int n;
  vector<int> res;
  sc_components scc;
 
  two_sat(int n) : n(n), scc(2*n) {}
 
  int inv(int v) {
    if (v < n)
      return n + v;
    else
      return v - n;
  }
 
  int norm(int v){
    if (v >= n)
      return v - n;
    return v;
  }
 
  // a or b <=> (~b => a and ~a => b)
  void either(int a, int b) {
    scc.add(inv(a), b);
    scc.add(inv(b), a);
  }
 
  bool run() {
    scc.run();
  
    res.assign(n, -1);
    for (int i=scc.num_comp-1;i>=0;i--){
      for (int a : scc.comps[i]) {
        if (scc.comp_ids[a] == scc.comp_ids[inv(a)]) {
          return false;
        }
        if (res[norm(a)] == -1)
          res[norm(a)] = a < n;
      }
    }
    return true;
  }
};