#include "batchnorm.h"

namespace scnn
{
    Batchnorm::Batchnorm(double eps, double *param_mean, double *param_var, double gamma, double beta)
    {
        m_beta = beta;
        m_eps = eps;
        m_gamma = gamma;
        m_running_mean = param_mean;
        m_running_var = param_var;
    }
    Batchnorm::~Batchnorm()
    {
        if (sizeof(m_running_var) > 0)
            free(m_running_var);

        if (sizeof(m_running_mean) > 0)
            free(m_running_mean);
    }

    Mat Batchnorm::forward(Mat &input_mat)
    {
        int lent = sizeof(m_running_var) / sizeof(double);

        for (int i = 0; i < lent; i++)
        {
            m_running_var[i] = sqrt(m_eps + m_running_var[i]);
        }
        Mat x = (input_mat - m_running_mean) / m_running_var;

        x = x * m_gamma + m_beta;

        return x;
    }

    double *Batchnorm::operator+(double v)
    {
        double *newdata = m_running_var;
        int lent = sizeof(m_running_var) / sizeof(double);
        for (int i = 0; i < lent; i++)
        {
            newdata[i] += m_eps;
        }

        return newdata;
    }

} // namespace scnn
