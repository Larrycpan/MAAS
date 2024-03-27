#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
DataFrame intersectRegions(CharacterVector peaks, CharacterVector cnvs) {
  
  int n_peaks = peaks.size();
  int n_cnvs = cnvs.size();
  
  // initialize vectors to store chromosome, start, and end positions
  std::vector<std::string> peak_chr(n_peaks), cnv_chr(n_cnvs);
  std::vector<int> peak_start(n_peaks), peak_end(n_peaks), cnv_start(n_cnvs), cnv_end(n_cnvs);
  
  // parse peak regions into chromosome, start, and end positions
  for(int i = 0; i < n_peaks; i++) {
    try {
      std::string peak = Rcpp::as<std::string>(peaks[i]);
      std::size_t pos1 = peak.find(":");
      std::size_t pos2 = peak.find("-");
      peak_chr[i] = peak.substr(0, pos1);
      peak_start[i] = std::stoi(peak.substr(pos1+1, pos2-pos1-1));
      peak_end[i] = std::stoi(peak.substr(pos2+1));
    } catch (const std::exception& e) {
    Rcpp::stop("Error parsing peak region " + Rcpp::as<std::string>(peaks[i]) + ": " + e.what());
      }
    }
  
  // parse cnv regions into chromosome, start, and end positions
  for(int i = 0; i < n_cnvs; i++) {
    try {
      std::string cnv = Rcpp::as<std::string>(cnvs[i]);
      std::size_t pos1 = cnv.find(":");
      std::size_t pos2 = cnv.find("-");
      cnv_chr[i] = cnv.substr(0, pos1);
      cnv_start[i] = std::stoi(cnv.substr(pos1+1, pos2-pos1-1));
      cnv_end[i] = std::stoi(cnv.substr(pos2+1));
    } catch (const std::exception& e) {
      Rcpp::stop("Error parsing CNV region " + Rcpp::as<std::string>(cnvs[i]) + ": " + e.what());
    }
  }
  
  // initialize vectors to store overlapping regions
  std::vector<std::string> peak_overlap, cnv_overlap;
  
  // find overlapping regions
  for(int i = 0; i < n_peaks; i++) {
    for(int j = 0; j < n_cnvs; j++) {
      if(peak_chr[i] == cnv_chr[j] && peak_start[i] <= cnv_end[j] && peak_end[i] >= cnv_start[j]) {
        peak_overlap.push_back(Rcpp::as<std::string>(peaks[i]));
        cnv_overlap.push_back(Rcpp::as<std::string>(cnvs[j]));
      }
    }
  }
  
  // create data frame with overlapping regions
  DataFrame result = DataFrame::create(Named("Peak_Region") = peak_overlap, Named("CNV_Region") = cnv_overlap);
  return result;
}
