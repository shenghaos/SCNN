#include "relu.h"


namespace scnn
{

    Mat Relu::forward(Mat &input)
    {

        Mat dst = Mat(input);
        for (int i = 0; i < input.len; i++)
        {
            dst[i] = dst[i] > 0 ? dst[i] : 0;
        }

        return dst;
    }





}