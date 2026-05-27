#include <vector>
#include <eigen3/Eigen/SVD>
#include <eigen3/Eigen/Dense>


using namespace std;



Eigen::VectorXd gradiente_coniugato(const Eigen::MatrixXd& A,const Eigen::VectorXd& b,Eigen::VectorXd& x0,double tol,int it_max) {
    Eigen::VectorXd r_k=b-(A*x0);
    Eigen::VectorXd p_k=r_k;
    Eigen::VectorXd x_k=x0;
    double res_norm_0 = r_k.norm();
    int k=0;
    
    while (k < it_max && r_k.norm() > tol * res_norm_0) {
        const double alpha_k=((p_k.transpose()*r_k)/(p_k.transpose()*A*p_k)).value();
        x_k=x_k+(alpha_k*p_k);
        r_k=b-(A*x_k);
        const double beta_k=((p_k.transpose()*A*r_k)/(p_k.transpose()*A*p_k)).value();
        p_k=r_k-(beta_k*p_k);
        k++;

    }
    return x_k;
}