#include <Rcpp.h>
using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
NumericMatrix adjustPeak(NumericMatrix pp, NumericMatrix cc, DataFrame overlapRegion, double eta = 0.2) {
  double pp_overlap_val;
  double cc_overlap_val;
  int p_ndims = overlapRegion.nrows();
  int q_ndims = pp.nrow();
  NumericMatrix pp1 = pp;
  
  StringVector pp_overlap_region = overlapRegion["Peak_Region"];
  StringVector cc_overlap_region = overlapRegion["CNV_Region"];
  StringVector pp_colnames = colnames(pp);
  StringVector cc_colnames = colnames(cc);
  
  IntegerVector pp_match = match(pp_overlap_region, pp_colnames) - 1;
  IntegerVector cc_match = match(cc_overlap_region, cc_colnames) - 1;
  
  for (int p = 0; p < p_ndims; p++) {
    for (int q = 0; q < q_ndims; q++) {
      pp_overlap_val = pp(q, pp_match[p]);
      cc_overlap_val = cc(q, cc_match[p]);
      
      if (!isnan(pp_overlap_val) && !isnan(cc_overlap_val)) {
        if (pp_overlap_val > 1 && cc_overlap_val > 2) {
          pp1(q, pp_match[p]) = pp_overlap_val - eta * (cc_overlap_val - 2) * pp_overlap_val;
        } else if (pp_overlap_val > 0 && cc_overlap_val < 2) {
          pp1(q, pp_match[p]) = pp_overlap_val + eta * (2 - cc_overlap_val) * pp_overlap_val;
        }
      }
    }
  }
  return (pp1);
}
