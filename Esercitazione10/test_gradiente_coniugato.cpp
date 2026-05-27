#include <iostream>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/SVD>
#include "gradiente_coniugato.hpp"

double condA(const Eigen::MatrixXd& A)
{
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
  Eigen::VectorXd singularValuesA = svd.singularValues();
  return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}

int main(int argc, char **argv) 
{
  const double tol = 1.0e-15;
  unsigned int n = 20;

  Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);

  if (abs(B.determinant()) < tol) {
    
    std::cout<<"La matrice B ha determinante troppo piccolo!";
    return EXIT_FAILURE;
  }

  Eigen::MatrixXd A = B.transpose() * B;
  Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);

  Eigen::VectorXd b = A * x_ex;

  Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n);
  Eigen::VectorXd res = b - A * x0;
  double res_norm_0 = res.norm();

  const unsigned int it_max = 10000;
  unsigned int it = 0;
  const double res_tol = 1.0e-12;

  std::cout.precision(2);
  std::cout<< std::scientific<< "Matrix Cond: "<< condA(A)<< std::endl;

  Eigen::VectorXd x=gradiente_coniugato(A,b,x0,tol,it_max);

  double err_rel; 

  if (x_ex.norm() == 0.0) {
    // Se la soluzione esatta è un vettore nullo, calcoliamo l'errore assoluto
    err_rel = (x - x_ex).norm();
  } else {
    // Altrimenti calcoliamo l'errore relativo standard
    err_rel = (x - x_ex).norm() / x_ex.norm();
  }

  std::cout.precision(4);
  std::cout<< std::scientific<< "res"<< "/"<< "res_tol"<< std::endl;
  std::cout<< std::scientific<< res.norm() / res_norm_0<< "/"<< res_tol<< std::endl;
  std::cout<< std::scientific<< "err_rel"<< std::endl;
  std::cout<< std::scientific<< err_rel<< std::endl;
  std::cout<< std::scientific<< "soluzione"<< std::endl;
  std::cout<< std::scientific<< x << std::endl;


  if (err_rel<res_tol) {
    return EXIT_SUCCESS;
  }
  else {
    return EXIT_FAILURE;
  }
}