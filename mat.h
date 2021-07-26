#include <math.h>

#include <string.h>

namespace scnn
{
     enum MAT_CAL_TYPE
     {
          ADD,
          SUBSTRACT,
          DIVISION,
          MULTIPLY,
          DOT
     };

     class Mat
     {
     private:
          double *data;

     public:
          int wid;
          int hgt;
          int cha;
          int bat;
          int len;

          Mat(int width, int height);
          Mat(const Mat &input_mat);
          Mat(int batch, int channel, int width, int height);

          Mat();
          ~Mat();
          double inline GetElement(int ind);
          double inline GetElement(int x, int y);
          double inline GetElement(int b, int c, int x, int y);

          void inline SetElement(double v, int ind);
          void inline SetElement(double v, int x, int y);
          void inline SetElement(double v, int b, int c, int x, int y);

          double &Mat::operator[](int i);

          Mat Mat::operator+(Mat &b);
          Mat Mat::operator+(double v);

          Mat Mat::operator-(Mat &b);
          Mat Mat::operator-(double v);
          Mat Mat::operator-();
          Mat Mat::operator-(double *v);


          Mat Mat::operator*(Mat &b);
          Mat Mat::operator*(double v);

          Mat Mat::operator/(Mat &b);
          Mat Mat::operator/(double v);
          Mat Mat::operator/(double *v);
          
          static double Max(Mat &input_mat);
          static double Min(Mat &input_mat);
          static double Max(Mat &input_mat, int dim);
          static double Min(Mat &input_mat, int dim);
          double Max();
          double Min();
          double Max(int dim);
          double Min(int dim);

          Mat Clone();
          void Normalize();
     };

}