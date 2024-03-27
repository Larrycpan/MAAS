#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
using namespace arma;
using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
List MAAS(const arma::mat& A1, const arma::mat& A2, const arma::mat& A3,arma::vec& dims) {
  
  double alpha = 1e-6,i;
  arma::vec loss(2);
  arma::mat W,H1,H2,H3,up, down, Z01, Z02, Z03;
  arma::mat parameter;
  List result(dims.size()+1);
  
  for (int j = 0; j < dims.size(); j++) {
    int k = dims(j);
    Rcpp::Rcout << "Training when k=" << k << std::endl;
    arma::arma_rng::set_seed(1234);
    W = arma::randu<arma::mat>(A1.n_rows, k);
    H1 = arma::diagmat(arma::randu<arma::vec>(k));
    H2 = arma::diagmat(arma::randu<arma::vec>(k));
    H3 = arma::diagmat(arma::randu<arma::vec>(k));
    
    arma::mat A11 = A1 * A1;
    arma::mat A22 = A2 * A2;
    arma::mat A33 = A3 * A3;
    arma::mat t_W=W.t();
    
    loss(0)=1;
    i=0.0;
    while (true) {
      i += 1;
      arma::mat WH1=W * H1, WH2=W * H2, WH3=W * H3;
      up = (A11 * WH1) + (A22 * WH2) + (A33 * WH3);
      
      down = (A11 * WH1 * t_W + WH1 * t_W * A11) * WH1 + 
        (A22 * WH2 * t_W + WH2 * t_W * A22) * WH2 + 
        (A33 * WH3 * t_W + WH3 * t_W * A33) * WH3;	
      
      W = 2 * W % (up / down); // 
      t_W=W.t();	  
      Z01 = A1 * W;
      Z02 = A2 * W;
      Z03 = A3 * W;
      
      H1 = H1 % ((Z01.t() * A1 * W) / (Z01.t() * (Z01 * H1 * t_W) * W));
      H2 = H2 % ((Z02.t() * A2 * W) / (Z02.t() * (Z02 * H2 * t_W) * W));
      H3 = H3 % ((Z03.t() * A3 * W) / (Z03.t() * (Z03 * H3 * t_W) * W));
      
      loss(1)    = 0.5 * (arma::accu(arma::square(A1 - A1 * W * H1 * t_W)) + 
        arma::accu(arma::square(A2 - A2 * W * H2 * t_W)) + 
        arma::accu(arma::square(A3 - A3 * W * H3 * t_W)));  
      
      arma::mat new_col=arma::mat({k+0.0,i+1,loss(1)});
      parameter=join_cols(parameter,new_col);	
      
      
      if(((loss(0) - loss(1)) / loss(0)) < alpha & ((loss(0) - loss(1)) / loss(0)) > 0){	
        result[j]=List::create(Named("W")=W, 
                               Named("H1")=H1, 
                               Named("H2")=H2, 
                               Named("H3")=H3);	
        break;					   
      }
      loss(0)=loss(1);	
    }
  }
  result[dims.size()]=List::create(Named("parameter")=parameter);
  
  return result;
}
