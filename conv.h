#include "mat.h"

namespace scnn
{

    class Conv
    {

    public:
        Mat conv_kernels;
        int m_stride;
        int m_pad;
        int outc;
        int kernelsize;

        Conv(int inputc, int outputc, int kernelsize, int stride = 1, int pad = 0);
        ~Conv();

        virtual Mat forward(Mat &input_mat);
    };

    class Conv3:public Conv
    {
        private:
            double per_conv(Mat &input_mat, Mat &kernel, int b, int c, int oc, int x, int y, int pad);

        public:
            Mat forward(Mat &input_mat);
            ~Conv3();
            Conv3();
        };
}
