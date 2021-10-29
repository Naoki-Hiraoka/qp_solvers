#include <qpswifteigen/qpswifteigen.h>
#include <iostream>

namespace qpswifteigen{
  solver::~solver(){
    if(this->qp_) QP_CLEANUP(this->qp_);
  }

  bool solver::initialize(const Eigen::SparseMatrix<double,Eigen::ColMajor>& P,
                          const Eigen::MatrixXd& c,
                          const Eigen::SparseMatrix<double,Eigen::ColMajor>& A,
                          const Eigen::MatrixXd& b,
                          const Eigen::SparseMatrix<double,Eigen::ColMajor>& G,
                          const Eigen::MatrixXd& h){
    this->P_ = P;
    this->c_ = c;
    this->A_ = A;
    this->b_ = b;
    this->G_ = G;
    this->h_ = h;

    if(this->qp_) QP_CLEANUP(this->qp_);
    this->qp_ = QP_SETUP(P_.cols(), G_.rows(), A_.rows(),
                         P_.outerIndexPtr(),P_.innerIndexPtr(),P_.valuePtr(),
                         A_.outerIndexPtr(),A_.innerIndexPtr(),A_.valuePtr(),
                         G_.outerIndexPtr(),G_.innerIndexPtr(),G_.valuePtr(),
                         c_.data(), h_.data(), b_.data(),
                         0.0, NULL);
    this->qp_->options->verbose = this->setting_.verbose;
    this->qp_->options->reltol = this->setting_.reltol;
    this->qp_->options->abstol = this->setting_.abstol;
    this->qp_->options->sigma = this->setting_.sigma;
    this->qp_->options->maxit = this->setting_.maxit;

    this->initialized_ = true;
  }

  bool solver::solve(){
    if(!this->qp_){
      std::cerr << "[qpswifteigen::solver::solve()] qp is not initialized"<<std::endl;
      return false;
    }

    qp_int ExitCode = QP_SOLVE(this->qp_);
    // switch(ExitCode){
    // case QP_OPTIMAL:
    //   std::cerr << "[qpswifteigen::solver::solve()] QP_OPTIMAL"<<std::endl;
    //   break;
    // case QP_MAXIT:
    //   std::cerr << "[qpswifteigen::solver::solve()] QP_MAXIT"<<std::endl;
    //   break;
    // case QP_FATAL:
    //   std::cerr << "[qpswifteigen::solver::solve()] QP_FATAL"<<std::endl;
    //   break;
    // case QP_KKTFAIL:
    //   std::cerr << "[qpswifteigen::solver::solve()] QP_KKTFAIL"<<std::endl;
    //   break;
    // default:
    //   break;
    // }
    return QP_OPTIMAL==ExitCode;
  }

  bool solver::getSolution(Eigen::VectorXd& solution){
    if(!this->qp_) return false;
    solution.resize(this->P_.rows());
    for(size_t i=0;i<this->P_.rows();i++){
      solution[i]=this->qp_->x[i];
    }
    return true;
  }
}
