//
// Created by zander on 18-10-13.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int display_dst(int);



int main(void)
{
    Mat src_image_ = imread("/home/zander/work/zuru_test/cv_a/zuru.png");   // 读取图片
    imshow("src_image_", src_image_);   // 打开图片文件
    waitKey(0);     // 停留

    // 平滑
    int DELAY_BLUR = 100;
    int MAX_KERNEL_LENGTH = 31;

    Mat dst = src_image_.clone();
    Mat element = getStructuringElement(MORPH_RECT, Size(15,15));
    erode(src_image_, dst, element);

    imshow("[腐蚀效果]", dst);
    waitKey(0);


    return 0;
}
