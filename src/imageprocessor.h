#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <QImage>
#include <opencv2/opencv.hpp>
#if defined(Q_OS_WIN)
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#endif
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
    int loadHeightMap(QString fileName);
    void generate_normal_map();
    Mat calculate_normal(Mat mat, int depth, int blur_radius);
    void calculate_gradient();
    void calculate_distance();
    void calculate_heightmap();
    Mat modify_distance();
    void set_name(QString name);
    QString get_name();
    bool busy;
    QString m_fileName;
    QImage get_texture();
    QImage get_normal();
    void update();
    void calculate();

signals:
    void processed(QImage image, ProcessedImage type);
    void on_idle();
public slots:
    void copy_settings(ImageProcessor *p);
    void set_normal_depth(int depth);
    int get_normal_depth();
    void set_normal_blur_radius(int radius);
    int get_normal_blur_radius();
    void set_normal_bisel_depth(int depth);
    int get_normal_bisel_depth();
    void set_normal_bisel_distance(int distance);
    int get_normal_bisel_distance();
    void set_normal_bisel_blur_radius(int radius);
    int get_normal_bisel_blur_radius();
    void set_normal_bisel_soft(bool soft);
    bool get_normal_bisel_soft();
    void set_normal_invert_x(bool invert);
    int get_normal_invert_x();
    void set_normal_invert_y(bool invert);
    int get_normal_invert_y();
    void set_normal_invert_z(bool invert);
    bool get_tileable();
    void set_tileable(bool t);
    int fill_neighbours(Mat src, Mat dst);
    int set_neighbour(Mat src, Mat dst, int x, int y);
    int set_neighbour_image(QString fileName, int x, int y);
    int empty_neighbour(int x, int y);
    void reset_neighbours();
    QImage get_neighbour(int x, int y);

private:
    QString m_name;
    Mat m_img;
    Mat m_gray;
    Mat m_gradient;
    Mat m_distance;
    Mat aux_distance;
    Mat m_normal;
    Mat m_emboss_normal;
    Mat m_distance_normal;
    Mat new_distance;
    Mat m_heightmap;
    Mat current_heightmap;
    Mat neighbours;
    Mat m_aux;
    int normal_depth;
    int normal_bisel_depth;
    int normal_bisel_distance;
    int normal_blur_radius;
    int normal_bisel_blur_radius;
    bool normal_bisel_soft, tileable;
    int normalInvertX, normalInvertY, normalInvertZ;
    char gradient_end;
};

#endif // IMAGEPROCESSOR_H
