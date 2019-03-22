#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <QPixmap>


using namespace cv;

enum class ProcessedImage
  {
     Raw,
     Normal
  };

class ImageProcessor : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessor(QObject *parent = nullptr);
    int loadImage(QString fileName);
    void generate_normal_map();
    Mat calculate_normal(Mat mat, int depth, int blur_radius);
    void calculate_gradient();
    void calculate_distance();
    Mat modify_distance();
    bool busy;
    QString m_fileName;

signals:
    void processed(QImage image, ProcessedImage type);
    void on_idle();
public slots:
    void set_normal_depth(int depth);
    void set_normal_blur_radius(int radius);
    void set_normal_bisel_depth(int depth);
    void set_normal_bisel_distance(int distance);
    void set_normal_bisel_blur_radius(int radius);
    void set_normal_bisel_soft(bool soft);
    void set_normal_invert_x(bool invert);
    void set_normal_invert_y(bool invert);
    void set_normal_invert_z(bool invert);

private:
    Mat m_img;
    Mat m_gray;
    Mat m_gradient;
    Mat m_distance;
    Mat m_normal;
    Mat m_emboss_normal;
    Mat m_distance_normal;
    Mat new_distance;
    int normal_depth;
    int normal_bisel_depth;
    int normal_bisel_distance;
    int normal_blur_radius;
    int normal_bisel_blur_radius;
    bool normal_bisel_soft;
    int normalInvertX, normalInvertY, normalInvertZ;
    char gradient_end;
};

#endif // IMAGEPROCESSOR_H
