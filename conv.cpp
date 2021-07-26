#include "conv.h"

namespace scnn
{

    Conv::Conv(int inputc, int ouputc, int kernelsize, int stride = 1, int pad = 0)
    {

        conv_kernels = Mat(inputc, ouputc, kernelsize, kernelsize);
        m_stride = stride;
        m_pad = pad;
        outc = ouputc;
    }

    Conv::~Conv()
    {
        conv_kernels.~Mat();
    }


    double Conv3::per_conv(Mat &input, Mat &kernel, int b, int c, int oc, int x, int y, int pad)
    {
        int w = input.wid;
        int h = input.hgt;

        double c1 =
            x >= pad && y >= pad && x <= w && y <= h ? input.GetElement(b, c, x, y) * kernel.GetElement(c, oc, 1, 1) : 0 + x - 1 >= pad && y >= pad && x - 1 <= w && y <= h       ? input.GetElement(b, c, x - 1, y) * kernel.GetElement(c, oc, 0, 1)
                                                                                                                   : 0 + x + 1 >= pad && y >= pad && x + 1 <= w && y <= h         ? input.GetElement(b, c, x + 1, y) * kernel.GetElement(c, oc, 2, 1)
                                                                                                                   : 0 + x >= pad && y - 1 >= pad && x <= w && y - 1 <= h         ? input.GetElement(b, c, x, y - 1) * kernel.GetElement(c, oc, 1, 0)
                                                                                                                   : 0 + x - 1 >= pad && y - 1 >= pad && x - 1 <= w && y - 1 <= h ? input.GetElement(b, c, x - 1, y - 1) * kernel.GetElement(c, oc, 0, 0)
                                                                                                                   : 0 + x + 1 >= pad && y - 1 >= pad && x + 1 <= w && y - 1 <= h ? input.GetElement(b, c, x + 1, y - 1) * kernel.GetElement(c, oc, 2, 0)
                                                                                                                   : 0 + x >= pad && y + 1 >= pad && x <= w && y + 1 <= h         ? input.GetElement(b, c, x, y + 1) * kernel.GetElement(c, oc, 1, 2)
                                                                                                                   : 0 + x - 1 >= pad && y + 1 >= pad && x - 1 <= w && y + 1 <= h ? input.GetElement(b, c, x - 1, y + 1) * kernel.GetElement(c, oc, 0, 2)
                                                                                                                   : 0 + x + 1 >= pad && y + 1 >= pad && x + 1 <= w && y + 1 <= h ? input.GetElement(b, c, x + 1, y + 1) * kernel.GetElement(c, oc, 2, 2)
                                                                                                                                                                                  : 0;
        return c1;
    }


    Conv3::~Conv3()
    {
        Conv::~Conv();
    }
    Mat Conv3::forward(Mat &input)
    {
        int out_w = int(floor((input.wid + 2 * m_pad + kernelsize) / m_stride + 1));
        int out_h = int(floor((input.hgt + 2 * m_pad + kernelsize) / m_stride + 1));

        Mat dst(input.bat, outc, out_w, out_h);

        for (int i = 0; i < input.bat; i++)
        {
            for (int j = 0; j < input.cha; j++)
            {
                for (int m = 0; m < outc; m++)
                {
                    for (int k = 1; k <= input.wid - 1; k += m_stride)
                    {
                        for (int l = 1; l <= input.hgt - 1; l += m_stride)
                        {
                            double c1 = per_conv(input, conv_kernels, i, j, m, k, l, m_pad);
                            dst.SetElement(c1, i, m, (k - 1) / m_stride, (l - 1) / m_stride);
                        }
                    }
                }
            }
        }

        return dst;
    }

}