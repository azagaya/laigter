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
#include "src/imageloader.h"

using namespace cv;

enum class ProcessedImage
{
    Raw,
    Normal,
    Parallax
};

enum class ParallaxType
{
    Binary,
    HeightMap,
    Quantization,
    Intervals
};

class ProcessorSettings
{
public:
    ProcessorSettings& operator=( ProcessorSettings other);
    int *parallax_min;
    int *parallax_max;
    int *parallax_focus;
    int *parallax_soft;
    int *parallax_quantization;
    int *parallax_brightness;
    double *parallax_contrast;
    int *parallax_erode_dilate;
    ParallaxType *parallax_type;

    int *normal_depth;
    int *normal_bisel_depth;
    int *normal_bisel_distance;
    int *normal_blur_radius;
    int *normal_bisel_blur_radius;
    bool *normal_bisel_soft, *tileable, *parallax_invert;
    int *normalInvertX, *normalInvertY, *normalInvertZ;
    char *gradient_end;
};

class ImageProcessor : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessor(QObject *parent = nullptr);
    int loadImage(QString fileName, QImage image);
    int loadHeightMap(QString fileName, QImage height);
    void generate_normal_map();
    Mat calculate_normal(Mat mat, int depth, int blur_radius);
    void calculate_gradient();
    void calculate_distance();
    void calculate_heightmap();
    Mat modify_distance();
    Mat modify_parallax();
    void set_name(QString name);
    QString get_name();
    bool busy;
    QString m_fileName;
    QImage get_texture();
    QImage get_normal();
    QImage get_parallax();
    void update();
    void calculate();
    void calculate_parallax();

signals:
    void processed(QImage image, ProcessedImage type);
    void on_idle();
public slots:
    void copy_settings(ProcessorSettings s);
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

    void set_parallax_invert(bool invert);
    bool get_parallax_invert();
    void set_parallax_focus(int focus);
    int get_parallax_focus();
    void set_parallax_soft(int soft);
    int get_parallax_soft();
    void set_parallax_thresh(int thresh);
    int get_parallax_thresh();
    void set_parallax_min(int min);
    int get_parallax_min();
    void set_parallax_type(ParallaxType ptype);
    int get_parallax_quantization();
    void set_parallax_quantization(int q);
    int get_parallax_erode_dilate();
    void set_parallax_erode_dilate(int value);
    int get_parallax_brightness();
    void set_parallax_brightness(int brightness);
    double get_parallax_contrast();
    void set_parallax_contrast(int contrast);

    ProcessorSettings get_settings();

    ParallaxType get_parallax_type();




    int fill_neighbours(Mat src, Mat dst);
    int set_neighbour(Mat src, Mat dst, int x, int y);
    int set_neighbour_image(QString fileName, QImage image, int x, int y);
    int empty_neighbour(int x, int y);
    void reset_neighbours();
    void set_current_heightmap();
    QImage get_neighbour(int x, int y);

private:
    ProcessorSettings settings;

    ImageLoader il;
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
    Mat m_parallax;
    Mat current_heightmap;
    Mat neighbours;
    Mat m_aux;

    Mat current_parallax;
    int parallax_min;
    int parallax_max;
    int parallax_focus;
    int parallax_soft;
    int parallax_quantization;
    int parallax_brightness;
    double parallax_contrast;
    int parallax_erode_dilate;
    ParallaxType parallax_type;

    int normal_depth;
    int normal_bisel_depth;
    int normal_bisel_distance;
    int normal_blur_radius;
    int normal_bisel_blur_radius;
    bool normal_bisel_soft, tileable, parallax_invert;
    int normalInvertX, normalInvertY, normalInvertZ;
    char gradient_end;

};

#endif // IMAGEPROCESSOR_H
