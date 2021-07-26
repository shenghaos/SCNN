#include "mat.h"


namespace scnn
{

    class Batchnorm
    {

        public:
            double m_gamma;
            double m_beta;
            double *m_running_mean;
            double *m_running_var;
            double m_eps;

            Batchnorm(double eps, double* param_mean, double* param_var, double gamma, double beta);
            ~Batchnorm();
            Mat forward(Mat &input_mat);
            double *operator+(double v);
    };

}