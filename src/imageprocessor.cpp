#include "imageprocessor.h"
#include <QDebug>
#include <QApplication>
#include <cmath>
ImageProcessor::ImageProcessor(QObject *parent) : QObject(parent)
{
    normal_bisel_depth = 1000;
    normal_bisel_distance = 60;
    normal_depth = 100;
    normal_blur_radius = 5;
    normal_bisel_blur_radius = 10;
    gradient_end = 255;
    normal_bisel_soft = true;
    normalInvertX = normalInvertY = normalInvertZ = 1;
    tileable = false;
    busy = false;
}

int ImageProcessor::loadImage(QString fileName){
    m_fileName = fileName;
    m_name = fileName;
    m_img = imread(fileName.toStdString(),-1);
    int aux = m_img.depth();
    switch (aux) {
    case CV_8S:
        m_img.convertTo(m_img,CV_8U,0,128);
        break;
    case CV_16U:
        m_img.convertTo(m_img,CV_8U,1/255.0);
        break;
    case CV_16S:
        m_img.convertTo(m_img,CV_8U,1/255.0,128);
        break;
    case CV_32S:
        m_img.convertTo(m_img,CV_8U,1/255.0/255.0,128);
        break;
    case CV_32F:
    case CV_64F:
        m_img.convertTo(m_img,CV_8U,255);
        break;
    }

    if (m_img.channels() < 4){
        if (m_img.channels() == 3){
            cvtColor(m_img,m_img,COLOR_RGB2RGBA);
        }
        else{
            cvtColor(m_img,m_img,COLOR_GRAY2RGBA);
        }
    }

    neighbours = Mat::zeros(m_img.rows*3,m_img.cols*3,m_img.type());

    m_img.copyTo(m_heightmap);



    current_heightmap = tileable ? neighbours : m_heightmap;

    fill_neighbours(m_heightmap,neighbours);

    return 0;
}

void ImageProcessor::calculate(){
//    calculate_heightmap();

//    calculate_distance();
//    new_distance = modify_distance();

//    m_emboss_normal =(calculate_normal(m_gray,normal_depth,normal_blur_radius));
//    m_distance_normal = calculate_normal(new_distance,normal_bisel_depth*normal_bisel_distance
//                                         ,normal_bisel_blur_radius);
//    generate_normal_map();

    current_heightmap = tileable ? neighbours : m_heightmap;

    calculate_distance();
    m_distance.copyTo(new_distance);
    new_distance = modify_distance();
    m_distance_normal = calculate_normal(new_distance,normal_bisel_depth*normal_bisel_distance
                                         ,normal_bisel_blur_radius);

    calculate_heightmap();
    Mat gray;
    m_gray.copyTo(gray);
    m_emboss_normal = calculate_normal(gray,normal_depth,normal_blur_radius);
    generate_normal_map();
}

void ImageProcessor::calculate_heightmap(){
    cvtColor(current_heightmap, m_gray,COLOR_RGBA2GRAY);
    if(m_gray.type() != CV_32FC1)
        m_gray.convertTo(m_gray, CV_32FC1);
}

int ImageProcessor::fill_neighbours(Mat src, Mat dst){
    if (src.cols != dst.cols/3 || src.rows != dst.rows/3)
        return -1;
    Rect rect;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            rect = Rect(i*src.cols,j*src.rows,src.cols,src.rows);
            src.copyTo(dst(rect));
        }
    }
    calculate();
    return 0;
}

void ImageProcessor::reset_neighbours(){
    fill_neighbours(m_heightmap,neighbours);
}

int ImageProcessor::empty_neighbour(int x, int y){
    Mat n = Mat::zeros(m_heightmap.rows,m_heightmap.cols,m_heightmap.type());
    set_neighbour(n,neighbours,x,y);
    return 0;
}

int ImageProcessor::set_neighbour(Mat src, Mat dst, int x, int y){
    if (src.cols != dst.cols/3 || src.rows != dst.rows/3)
        return -1;
    Rect rect(y*src.cols,x*src.rows,src.cols,src.rows);
    src.copyTo(dst(rect));
    return 0;
}

int ImageProcessor::set_neighbour_image(QString fileName, int x, int y){
    Mat n = imread(fileName.toStdString(),-1);

    int aux = n.depth();
    switch (aux) {
    case CV_8S:
        n.convertTo(n,CV_8U,0,128);
        break;
    case CV_16U:
        n.convertTo(n,CV_8U,1/255.0);
        break;
    case CV_16S:
        n.convertTo(n,CV_8U,1/255.0,128);
        break;
    case CV_32S:
        n.convertTo(n,CV_8U,1/255.0/255.0,128);
        break;
    case CV_32F:
    case CV_64F:
        n.convertTo(n,CV_8U,255);
        break;
    }

    if (n.channels() < 4){
        if (n.channels() == 3){
            cvtColor(n,n,COLOR_RGB2RGBA);
        }
        else{
            cvtColor(n,n,COLOR_GRAY2RGBA);
        }
    }


    cv::resize(n,n,Size(m_img.size()));

    set_neighbour(n,neighbours,x,y);

    return 0;
}

QImage ImageProcessor::get_neighbour(int x, int y){
    Rect rect(y*m_img.cols,x*m_img.rows,m_img.cols,m_img.rows);
    neighbours(rect).copyTo(m_aux);
    cvtColor(m_aux,m_aux,CV_BGRA2RGBA);
    QImage p =QImage(static_cast<unsigned char *>(m_aux.data),
                     m_aux.cols,m_aux.rows,m_aux.step,QImage::Format_RGBA8888);
    return p;

}

int ImageProcessor::loadHeightMap(QString fileName){

    m_heightmap = imread(fileName.toStdString(),-1);

    int aux = m_heightmap.depth();
    switch (aux) {
    case CV_8S:
        m_heightmap.convertTo(m_heightmap,CV_8U,0,128);
        break;
    case CV_16U:
        m_heightmap.convertTo(m_heightmap,CV_8U,1/255.0);
        break;
    case CV_16S:
        m_heightmap.convertTo(m_heightmap,CV_8U,1/255.0,128);
        break;
    case CV_32S:
        m_heightmap.convertTo(m_heightmap,CV_8U,1/255.0/255.0,128);
        break;
    case CV_32F:
    case CV_64F:
        m_heightmap.convertTo(m_heightmap,CV_8U,255);
        break;
    }

    if (m_heightmap.channels() < 4){
        if (m_heightmap.channels() == 3){
            cvtColor(m_heightmap,m_heightmap,COLOR_RGB2RGBA);
        }
        else{
            cvtColor(m_heightmap,m_heightmap,COLOR_GRAY2RGBA);
        }
    }


    cv::resize(m_heightmap,m_heightmap,Size(m_img.size()));
    cvtColor(m_heightmap, m_gray,COLOR_RGBA2GRAY);

    set_neighbour(m_heightmap,neighbours,1,1);

    if(m_gray.type() != CV_32FC1)
        m_gray.convertTo(m_gray, CV_32FC1);

    calculate();

    return 0;
}

void ImageProcessor::set_name(QString name){
    m_name = name;
}

QString ImageProcessor::get_name(){
    return m_name;
}
void ImageProcessor::calculate_gradient(){


}

void ImageProcessor::calculate_distance(){

    if (!current_heightmap.ptr<int>(0)) return;

    cvtColor(current_heightmap, m_distance,COLOR_RGBA2GRAY,1);

    for(int x = 0; x < m_distance.rows; ++x)
    {
        uchar * pixel = m_distance.ptr<uchar>(x);
        for(int y = 0; y < m_distance.cols; ++y)
        {
            if (!tileable && (x == 0 || y == 0
                              || x == m_distance.rows-1
                              || y == m_distance.cols-1))
            {
                //m_distance.at<unsigned char>(x,y) = 0;
                *pixel = 0;
            }else if (current_heightmap.at<Vec4b>(x,y)[3] == 0.0){
                //m_distance.at<unsigned char>(x,y) = 0;
                *pixel = 0;
            } else {
                m_distance.at<unsigned char>(x,y) = 255;
                *pixel = 255;
            }
            pixel ++;
        }
    }
    threshold(m_distance,m_distance,0,255,THRESH_BINARY);

    distanceTransform(m_distance,m_distance,CV_DIST_L2,5);
    m_distance.convertTo(m_distance,CV_32FC1,1.0/255);
}

void ImageProcessor::set_normal_invert_x(bool invert){
    normalInvertX = -invert*2+1;
    m_emboss_normal =(calculate_normal(m_gray,normal_depth,normal_blur_radius));
    m_distance_normal = calculate_normal(new_distance,normal_bisel_depth*normal_bisel_distance
                                         ,normal_bisel_blur_radius);
    generate_normal_map();

}
void ImageProcessor::set_normal_invert_y(bool invert){
    normalInvertY = -invert*2+1;
    m_emboss_normal =(calculate_normal(m_gray,normal_depth,normal_blur_radius));
    m_distance_normal = calculate_normal(new_distance,normal_bisel_depth*normal_bisel_distance
                                         ,normal_bisel_blur_radius);
    generate_normal_map();
}
void ImageProcessor::set_normal_invert_z(bool invert){
    normalInvertZ = -invert*2+1;
    m_emboss_normal =(calculate_normal(m_gray,normal_depth,normal_blur_radius));
    m_distance_normal = calculate_normal(new_distance,normal_bisel_depth*normal_bisel_distance
                                         ,normal_bisel_blur_radius);
    generate_normal_map();
}
void ImageProcessor::set_normal_depth(int depth){
    normal_depth = depth;
    Mat gray;
    m_gray.copyTo(gray);
    m_emboss_normal = calculate_normal(gray,normal_depth,normal_blur_radius);
    generate_normal_map();
}
void ImageProcessor::set_normal_bisel_soft(bool soft){
    normal_bisel_soft = soft;
    new_distance = modify_distance();
    m_distance_normal = calculate_normal(new_distance,normal_bisel_depth*normal_bisel_distance
                                         ,normal_bisel_blur_radius);
    generate_normal_map();
}
void ImageProcessor::set_normal_blur_radius(int radius){
    normal_blur_radius = radius;
    Mat gray;
    m_gray.copyTo(gray);
    m_emboss_normal = calculate_normal(gray,normal_depth,normal_blur_radius);
    generate_normal_map();
}

void ImageProcessor::set_normal_bisel_depth(int depth){
    normal_bisel_depth = depth;
    m_distance_normal = calculate_normal(new_distance,normal_bisel_depth*normal_bisel_distance
                                         ,normal_bisel_blur_radius);
    generate_normal_map();
}

void ImageProcessor::set_normal_bisel_distance(int distance){
    normal_bisel_distance = distance;
    new_distance = modify_distance();
    m_distance_normal = calculate_normal(new_distance,normal_bisel_depth*normal_bisel_distance
                                         ,normal_bisel_blur_radius);
    generate_normal_map();
}

void ImageProcessor::set_tileable(bool t){
    tileable = t;
    current_heightmap = t ? neighbours : m_heightmap;

    calculate_distance();
    m_distance.copyTo(new_distance);
    new_distance = modify_distance();
    m_distance_normal = calculate_normal(new_distance,normal_bisel_depth*normal_bisel_distance
                                         ,normal_bisel_blur_radius);

    calculate_heightmap();
    Mat gray;
    m_gray.copyTo(gray);
    m_emboss_normal = calculate_normal(gray,normal_depth,normal_blur_radius);
    generate_normal_map();

}

bool ImageProcessor::get_tileable(){
    return tileable;
}

Mat ImageProcessor::modify_distance(){
    Mat m;
    m_distance.copyTo(m);
    for(int x = 0; x < m.rows; ++x)
    {
        float *pixel = m.ptr<float>(x);
        for(int y = 0; y < m.cols; ++y)
        {
            if (normal_bisel_distance == 0){
                //m.at<float>(y,x) = 0;
                *pixel = 0;
            }
            else{
                //m.at<float>(x,y) *= 255.0/normal_bisel_distance;
                *pixel *= 255.0/normal_bisel_distance;
//                if (m.at<float>(x,y) > 1)
//                    m.at<float>(x,y) = 1;
                if (*pixel > 1)
                    *pixel = 1;
                if (normal_bisel_soft){
                    //double d = m.at<float>(x,y);
                    double d = *pixel;
                    //m.at<float>(x,y) = sqrt(1-pow((d-1),2));
                    *pixel = sqrt(1-pow((d-1),2));
                }
            }
            pixel ++;
        }
    }
    return m;
}

void ImageProcessor::set_normal_bisel_blur_radius(int radius){
    normal_bisel_blur_radius = radius;
    m_distance_normal = calculate_normal(new_distance,normal_bisel_depth*normal_bisel_distance
                                         ,normal_bisel_blur_radius);
    generate_normal_map();
}

void ImageProcessor::generate_normal_map(){
    if (!current_heightmap.ptr<int>(0) || busy) return;
    busy = true;
    Mat normals;
    normals =(m_emboss_normal
              + m_distance_normal);
    for(int x = 0; x < normals.cols; ++x)
    {
        for(int y = 0; y < normals.rows; ++y)
        {
            Vec3f n = normalize(normals.at<Vec3f>(y,x));
            normals.at<Vec3f>(y,x) = n*0.5+Vec3f(0.5,0.5,0.5);
        }
    }

    normals.convertTo(normals,CV_8UC3,255);
    normals.copyTo(m_normal);
    QImage p =QImage(static_cast<unsigned char *>(m_normal.data),
                     m_normal.cols,m_normal.rows,m_normal.step,QImage::Format_RGB888);
    processed(p, ProcessedImage::Normal);
    busy = false;
    on_idle();
}

void ImageProcessor::update(){
    QImage p =QImage(static_cast<unsigned char *>(m_normal.data),
                     m_normal.cols,m_normal.rows,m_normal.step,QImage::Format_RGB888);
    processed(p, ProcessedImage::Normal);
}

Mat ImageProcessor::calculate_normal(Mat mat, int depth, int blur_radius){

    Mat aux, heightMap;
    Mat mdx,mdy,mg;
    Rect rect(m_img.cols,m_img.rows,m_img.cols,m_img.rows);
    float dx, dy;
    GaussianBlur(mat,aux,Size(blur_radius*2+1,blur_radius*2+1),0);
    if(tileable && aux.rows == m_img.rows*3){
        aux(rect).copyTo(aux);
        current_heightmap(rect).copyTo(heightMap);
    }else{
        m_heightmap.copyTo(heightMap);
    }
    Mat normals(aux.size(), CV_32FC3);
    for(int x = 0; x < aux.cols; ++x)
    {
        for(int y = 0; y < aux.rows; ++y)
        {
            if (heightMap.at<Vec4b>(y,x)[3] == 0.0){
                normals.at<Vec3f>(y,x) = Vec3f(0,0,1);
                continue;
            }

            dx = -aux.at<float>(y,(x-1+aux.cols)%aux.cols) + aux.at<float>(y,(x+1+aux.cols)%aux.cols);
            dy = -aux.at<float>((y-1+aux.rows)%aux.rows,x) + aux.at<float>((y+1+aux.rows)%aux.rows,x);


            Vec3f n = Vec3f(-dx*(depth/1000.0)*normalInvertX,
                            dy*(depth/1000.0)*normalInvertY,
                            1*normalInvertZ);
            normals.at<Vec3f>(y,x) = n;

        }
    }
    return normals;
}

void ImageProcessor::copy_settings(ImageProcessor *p){
    normal_depth = p->get_normal_depth();
    normal_blur_radius = p->get_normal_blur_radius();
    normal_bisel_soft = p->get_normal_bisel_soft();
    normal_bisel_depth = p->get_normal_bisel_depth();
    normal_bisel_distance = p->get_normal_bisel_distance();
    normal_bisel_blur_radius = p->get_normal_bisel_blur_radius();
    normalInvertX = p->get_normal_invert_x();
    normalInvertY = p->get_normal_invert_y();
    tileable = p->get_tileable();
}

int ImageProcessor::get_normal_depth(){
    return normal_depth;
}

int ImageProcessor::get_normal_blur_radius(){
    return normal_blur_radius;
}

bool ImageProcessor::get_normal_bisel_soft(){
    return normal_bisel_soft;
}

int ImageProcessor::get_normal_bisel_depth(){
    return normal_bisel_depth;
}

int ImageProcessor::get_normal_bisel_distance(){
    return  normal_bisel_distance;
}

int ImageProcessor::get_normal_bisel_blur_radius(){
    return normal_bisel_blur_radius;
}

int ImageProcessor::get_normal_invert_x(){
    return normalInvertX;
}

int ImageProcessor::get_normal_invert_y(){
    return normalInvertY;
}

QImage ImageProcessor::get_texture(){
    return QImage(static_cast<unsigned char *>(m_img.data),
                  m_img.cols,m_img.rows,m_img.step,QImage::Format_RGB888);;
}

QImage ImageProcessor::get_normal(){
    return QImage(static_cast<unsigned char *>(m_normal.data),
                  m_normal.cols,m_normal.rows,m_normal.step,QImage::Format_RGB888);
}


