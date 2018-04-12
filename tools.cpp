#include "tools.h"

#define min2(a,b) (a)<(b)?(a):(a)
#define min(a,b,c) (min2(a,b))<(c)?(min2(a,b)):(c)

//QImage Tools::ConnectedDomain(const QImage &origin)
//{

//}



QImage Tools::RGB2HSV(const QImage &origin, double *h_f, double *h_b, double *s_f, double *s_b, double *v_f, double *v_b)
{
    int width = origin.width();
    int height = origin.height();
    QImage newImg = QImage(width, height, QImage::Format_RGB888);

    for(int x=0; x<width; x++)
    {
        for(int y=0; y<height; y++)
        {
            QColor color = origin.pixel(x,y);
            double hue = color.hue();
            double saturation = color.saturation();
            double value = color.value();
            //int hue = 0;
            int max=0;
            int min=0;
            int flag_h = 0;
            int flag_s = 0;
            int flag_v = 0;
            int count_h = 0;
            int count_s = 0;
            int count_v = 0;
            for(int i = 0; i < 3; i++){
                if(h_f[i] < 0 || h_b[i] < 0){
                    count_h++;
                }
                else if(h_f[i] < h_b[i]){
                    min = h_f[i];
                    max = h_b[i];
                }
                else {
                    min = h_b[i];
                    max = h_f[i];
                }
                if(hue <= max && hue >= min){
                    flag_h = 1;
                }
               if(s_f[i] < 0 || s_b[i] < 0){
                    count_s++;
                }
                else if(s_f[i] < s_b[i]){
                    min = s_f[i];
                    max = s_b[i];
                }
                else {
                    min = s_b[i];
                    max = s_f[i];
                }
                if(saturation <= max && saturation >= min){
                    flag_s = 1;
                }
                if(v_f[i] < 0 || v_b[i] < 0){
                    count_v++;
                }
                else if(v_f[i] <  v_b[i]){
                    min = v_f[i];
                    max = v_b[i];
                }
                else {
                    min = v_b[i];
                    max = v_f[i];
                }
                if(value <= max && value >= min)
                    flag_v = 1;
            }
            if(count_h == 3)
                flag_h = 1;
            if(!flag_h)
                hue = 0;
            if(count_s == 3)
                flag_s = 1;
            if(!flag_s )
                saturation = 0;
            if(count_v == 3)
                flag_v = 1;
            if(!flag_v)
                value = 0;
            //printf("%d,%d,%d\n",count_h,count_s, count_v);
           // printf("%d,%d,%d\n",hue, saturation, value);
            color.setHsv(hue, saturation, value, color.alpha());
//            newImg.setPixelColor(x,y,color);
            newImg.setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
        }
    }
    return newImg;
}
