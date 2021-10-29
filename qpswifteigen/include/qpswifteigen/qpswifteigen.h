#ifndef QPSWIFTEIGEN_H
#define QPSWIFTEIGEN_H

#include <qpSWIFT.h>
#include <Eigen/Eigen>

namespace qpswifteigen{
  class solver{
  public:
    ~solver();
    /*
      objective:  mazimize 0.5 x' P x + c' x
      subject to: Ax = b; Gx <= h
     */
    bool initialize(const Eigen::SparseMatrix<double,Eigen::ColMajor>& P,
                    const Eigen::MatrixXd& c,
                    const Eigen::SparseMatrix<double,Eigen::ColMajor>& A,
                    const Eigen::MatrixXd& b,
                    const Eigen::SparseMatrix<double,Eigen::ColMajor>& G,
                    const Eigen::MatrixXd& h);

    bool solve();

    bool getSolution(Eigen::VectorXd& solution);

    bool is_initialized() {return initialized_;}

    // for option setting
    settings& setting() { return setting_;}
  private:
    QP* qp_;
    settings setting_;
    Eigen::SparseMatrix<double,Eigen::ColMajor,long> P_;
    Eigen::MatrixXd c_;
    Eigen::SparseMatrix<double,Eigen::ColMajor,long> A_;
    Eigen::MatrixXd b_;
    Eigen::SparseMatrix<double,Eigen::ColMajor,long> G_;
    Eigen::MatrixXd h_;

    bool initialized_=false;
  };
}

#endif
