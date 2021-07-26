#include "mat.h"

namespace scnn
{
    Mat::~Mat()
    {
        if (sizeof(data) > 0)
            free(data);
    }

    Mat::Mat(const Mat &input_mat)
    {
        wid = input_mat.wid;
        data = input_mat.data;
        cha = input_mat.cha;
        hgt = input_mat.hgt;
        bat = input_mat.bat;
        len = input_mat.len;
    }

    Mat::Mat(int batch, int channel, int width, int height)
    {
        wid = width;
        hgt = height;
        cha = channel;
        bat = batch;
        len = wid * hgt * bat * cha;
        data = new double[len];
    }

    Mat::Mat(int width, int height)
    {
        wid = width;
        hgt = height;
        cha = 1;
        bat = 1;
        len = wid * hgt * 1 * 1;
        data = new double[len];
    }

    double inline Mat::GetElement(int x, int y)
    {
        return data[y * wid + x];
    }

    double inline Mat::GetElement(int b, int c, int x, int y)
    {
        return data[b * bat * c * cha * y * wid + x];
    }

    void inline Mat::SetElement(double v, int x, int y)
    {
        data[y * wid + x] = v;
    }

    void inline Mat::SetElement(double v, int b, int c, int x, int y)
    {
        data[b * bat * c * cha * y * wid + x] = v;
    }

    double &Mat::operator[](int i)
    {
        return data[i];
    }

    Mat Mat::operator+(Mat &b)
    {
        Mat dst(b);
        if (len == b.len)
        {
            for (int i = 0; i < len; i++)
            {
                dst[i] = b[i] + this->data[i];
            }
        }
        else
        {
            throw "the len of two mats are not equal!";
        }
        return dst;
    }

    Mat Mat::operator+(double v)
    {
        Mat dst(bat, cha, wid, hgt);
        dst.data = this->data;
        for (int i = 0; i < len; i++)
        {
            dst[i] = data[i] + v;
        }
        return dst;
    }

    Mat Mat::operator*(Mat &b)
    {
        Mat dst(b);
        if (len == b.len)
        {
            for (int i = 0; i < len; i++)
            {
                dst[i] = b[i] * this->data[i];
            }
        }
        else
        {
            throw "the len of two mats are not equal!";
        }
        return dst;
    }

    Mat Mat::operator+(double v)
    {
        Mat dst(bat, cha, wid, hgt);
        dst.data = this->data;
        for (int i = 0; i < len; i++)
        {
            dst[i] = data[i] * v;
        }
        return dst;
    }

    Mat Mat::operator-(Mat &b)
    {
        Mat dst(b);
        if (len == b.len)
        {
            for (int i = 0; i < len; i++)
            {
                dst[i] = b[i] - this->data[i];
            }
        }
        else
        {
            throw "the len of two mats are not equal!";
        }
        return dst;
    }

    Mat Mat::operator-(double v)
    {
        Mat dst(bat, cha, wid, hgt);
        dst.data = this->data;
        for (int i = 0; i < len; i++)
        {
            dst[i] = data[i] - v;
        }
        return dst;
    }

    Mat Mat::operator-(double *v)
    {
        if (bat != sizeof(v) / sizeof(v[0]))
        {
            throw "batchsize is error!";
        }

        Mat dst(bat, cha, wid, hgt);

        int lent = cha * wid * hgt;

        for (int i = 0; i < bat; i++)
        {
            for (int j = 0; j < lent; j++)
            {
                dst[i * lent + j] = this->data[i * lent + j] - v[i];
            }
        }

        return dst;
    }

    Mat Mat::operator/(double *v)
    {
        if (bat != sizeof(v) / sizeof(v[0]))
        {
            throw "batchsize is error!";
        }

        Mat dst(bat, cha, wid, hgt);

        int lent = cha * wid * hgt;

        for (int i = 0; i < bat; i++)
        {
            for (int j = 0; j < lent; j++)
            {
                dst[i * lent + j] = this->data[i * lent + j] / v[i];
            }
        }

        return dst;
    }



    Mat Mat::operator-()
    {
        Mat dst(bat, cha, wid, hgt);
        dst.data = this->data;
        for (int i = 0; i < len; i++)
        {
            dst[i] = -data[i];
        }
        return dst;
    }

    Mat Mat::operator/(Mat &b)
    {
        Mat dst(b);
        if (len == b.len)
        {
            for (int i = 0; i < len; i++)
            {
                if (abs(this->data[i]) < 1e-7)
                {
                    throw "the v is equal 0!";
                }

                dst[i] = b[i] / this->data[i];
            }
        }
        else
        {
            throw "the len of two mats are not equal!";
        }
        return dst;
    }

    Mat Mat::operator/(double v)
    {
        if (abs(v) < 1e-7)
        {
            throw "the v is equal 0!";
        }

        Mat dst(bat, cha, wid, hgt);
        dst.data = this->data;
        for (int i = 0; i < len; i++)
        {
            dst[i] = data[i] / v;
        }
        return dst;
    }

    static double Max(Mat &input_mat, int b, int c, int ind)
    {
        int lent = input_mat.wid * input_mat.hgt;

        double m = -1.79769313486231570E+308;

        for (int i = 0; i < lent; i++)
        {
            if (input_mat.GetElement(b * c * ind + i) > m)
                m = input_mat.GetElement(b * c * ind + i);
        }

        return m;
    }

    double Mat::Max(int dim)
    {
        double m = -1.79769313486231570E+308;
        if (cha == 1 && bat == 1)
        {
            return 0;
        }
        else
        {
            int lent = wid * hgt * cha;
            for (int j = 0; j < lent; j++)
            {
                if (data[lent * dim + j] > m)
                    m = data[lent * dim + j];
            }
        }
        return m;
    }

    double Mat::Min(int dim)
    {
        double m = 1.79769313486231570E+308;
        if (cha == 1 && bat == 1)
        {
            return 0;
        }
        else
        {
            int lent = wid * hgt * cha;
            for (int j = 0; j < lent; j++)
            {
                if (data[lent * dim + j] < m)
                    m = data[lent * dim + j];
            }
        }
        return m;
    }

    static double Min(Mat &input_mat, int b, int c, int ind)
    {
        int lent = input_mat.wid * input_mat.hgt;

        double m = 1.79769313486231570E+308;

        for (int i = 0; i < lent; i++)
        {
            if (input_mat.GetElement(b * c * ind + i) < m)
                m = input_mat.GetElement(b * c * ind + i);
        }

        return m;
    }

    Mat Mat::Clone()
    {
        Mat output(bat, cha, wid, hgt);

        memcpy(output.data, data, sizeof(data));

        return output;
    }

    void Mat::Normalize()
    {

        int lent = wid * hgt * cha;
        for (int i = 0; i < bat; i++)
        {
            double ma = Max(i);
            double mi = Min(i);
            for (int j = 0; j < lent; j++)
            {
                data[i * lent + j] = (data[i * lent + j] - mi) / (ma - mi);
            }
        }
    }

} // namespace name
