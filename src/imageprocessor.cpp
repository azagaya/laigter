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
    gradient_end = 1;
    normal_bisel_soft = true;
    normalInvertX = normalInvertY = normalInvertZ = 1;
    tileable = false;
    busy = false;

    parallax_max = 140;
    parallax_min = 0;
    parallax_invert = false;
    parallax_focus = 3;
    parallax_soft = 10;
    parallax_quantization = 1;
    parallax_type = ParallaxType::Binary;
    parallax_brightness = 0;
    parallax_contrast = 1;
    parallax_erode_dilate = 1;

    specular_blur = 10;
    specular_bright = 0;
    specular_contrast = 1;
    specular_thresh = 127;
    specular_invert = false;

    settings.tileable = &tileable;
    settings.gradient_end = &gradient_end;
    settings.parallax_max = &parallax_max;
    settings.parallax_min = &parallax_min;
    settings.parallax_soft = &parallax_soft;
    settings.parallax_type = &parallax_type;
    settings.parallax_focus = &parallax_focus;
    settings.parallax_invert = &parallax_invert;
    settings.parallax_contrast = &parallax_contrast;
    settings.parallax_brightness = &parallax_brightness;
    settings.parallax_erode_dilate = &parallax_erode_dilate;
    settings.parallax_quantization = &parallax_quantization;

    settings.normal_depth = &normal_depth;
    settings.normalInvertX = &normalInvertX;
    settings.normalInvertY = &normalInvertY;
    settings.normalInvertZ = &normalInvertZ;
    settings.normal_bisel_soft = &normal_bisel_soft;
    settings.normal_bisel_depth = &normal_bisel_depth;
    settings.normal_blur_radius = &normal_blur_radius;
    settings.normal_bisel_distance = &normal_bisel_distance;
    settings.normal_bisel_blur_radius = &normal_bisel_blur_radius;

    settings.specular_blur = &specular_blur;
    settings.specular_bright = &specular_bright;
    settings.specular_invert = &specular_invert;
    settings.specular_thresh = &specular_thresh;
    settings.specular_contrast = &specular_contrast;

}

int ImageProcessor::loadImage(QString fileName, QImage image){
    m_fileName = fileName;
    m_name = fileName;
    //m_img = imread(fileName.toStdString(),-1);
    m_img = Mat(image.height(),image.width(),CV_8UC4,image.scanLine(0));
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


    set_current_heightmap();


    fill_neighbours(m_heightmap,neighbours);

    return 0;
}

void ImageProcessor::set_current_heightmap(){
    current_heightmap = tileable ? neighbours : m_heightmap;
    cvtColor(current_heightmap,m_parallax, CV_RGBA2GRAY);
}

void ImageProcessor::calculate(){

    set_current_heightmap();

    calculate_distance();

    calculate_heightmap();

    generate_normal_map();

    calculate_parallax();

    calculate_specular();


}

void ImageProcessor::calculate_parallax(){
    Mat p = modify_parallax();

    Rect rect(m_img.cols,m_img.rows,m_img.cols,m_img.rows);
    if(tileable && p.rows == m_img.rows*3){
        p(rect).copyTo(current_parallax);
    }else{
        p.copyTo(current_parallax);
    }

    switch (current_parallax.channels()) {
    case 3:
        cvtColor(current_parallax,current_parallax,COLOR_RGB2GRAY);
        break;
    case 4:
        cvtColor(current_parallax,current_parallax,COLOR_RGBA2GRAY);
        break;

    }

    QImage pa = QImage(static_cast<unsigned char *>(current_parallax.data),
                       current_parallax.cols,current_parallax.rows,current_parallax.step,QImage::Format_Grayscale8);
    processed(pa,ProcessedImage::Parallax);
}

void ImageProcessor::calculate_specular(){
    Mat p = modify_specular();

    Rect rect(m_img.cols,m_img.rows,m_img.cols,m_img.rows);
    if(tileable && p.rows == m_img.rows*3){
        p(rect).copyTo(current_specular);
    }else{
        p.copyTo(current_specular);
    }

    switch (current_specular.channels()) {
    case 3:
        cvtColor(current_specular,current_specular,COLOR_RGB2GRAY);
        break;
    case 4:
        cvtColor(current_specular,current_specular,COLOR_RGBA2GRAY);
        break;

    }

    QImage pa = QImage(static_cast<unsigned char *>(current_specular.data),
                       current_specular.cols,current_specular.rows,current_specular.step,QImage::Format_Grayscale8);
    processed(pa,ProcessedImage::Specular);
}

void ImageProcessor::calculate_heightmap(){
    cvtColor(current_heightmap, m_gray,COLOR_RGBA2GRAY);
    if(m_gray.type() != CV_32FC1)
        m_gray.convertTo(m_gray, CV_32FC1);


    Mat gray;
    m_gray.copyTo(gray);
    m_emboss_normal = calculate_normal(gray,normal_depth,normal_blur_radius);
}

int ImageProcessor::fill_neighbours(Mat src, Mat dst){
    if (src.cols != dst.cols/3 || src.rows != dst.rows/3){
        return -1;
    }
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
    if (src.cols != dst.cols/3 || src.rows != dst.rows/3){
        return -1;
    }
    Rect rect(y*src.cols,x*src.rows,src.cols,src.rows);
    src.copyTo(dst(rect));
    return 0;
}

int ImageProcessor::set_neighbour_image(QString fileName, QImage image, int x, int y){

    Mat n = Mat(image.height(),image.width(),CV_8UC4,image.scanLine(0));

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
    //cvtColor(n,n,COLOR_RGBA2BGRA);
    cv::resize(n,n,m_img.size()*2);
    cv::resize(n,n,m_img.size());

    set_neighbour(n,neighbours,x,y);

    return 0;
}

QImage ImageProcessor::get_neighbour(int x, int y){
    Rect rect(y*m_img.cols,x*m_img.rows,m_img.cols,m_img.rows);
    neighbours(rect).copyTo(m_aux);
    //cvtColor(m_aux,m_aux,CV_BGRA2RGBA);
    QImage p =QImage(static_cast<unsigned char *>(m_aux.data),
                     m_aux.cols,m_aux.rows,m_aux.step,QImage::Format_RGBA8888);
    return p;

}

int ImageProcessor::loadHeightMap(QString fileName, QImage height){

    //m_heightmap = imread(fileName.toStdString(),-1);
    m_heightmap = Mat(height.height(),height.width(),CV_8UC4,height.scanLine(0));

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
    //cvtColor(m_heightmap,m_heightmap,COLOR_RGBA2BGRA);
    cv::resize(m_heightmap,m_heightmap,m_img.size()*2);
    cv::resize(m_heightmap,m_heightmap,m_img.size());

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

    m_distance.copyTo(new_distance);
    new_distance = modify_distance();
    m_distance_normal = calculate_normal(new_distance,normal_bisel_depth*normal_bisel_distance
                                         ,normal_bisel_blur_radius);
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
    calculate();
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
                *pixel = 0;
            }
            else{
                *pixel *= 255.0/normal_bisel_distance;
                if (*pixel > 1)
                    *pixel = 1;
                if (normal_bisel_soft){
                    double d = *pixel;
                    *pixel = sqrt(1-pow((d-1),2));
                }
            }
            pixel ++;
        }
    }
    return m;
}

Mat ImageProcessor::modify_parallax(){
    Mat m;

    int threshType = !parallax_invert ? THRESH_BINARY_INV : THRESH_BINARY;
    Mat shape = getStructuringElement(MORPH_RECT,Size(abs(parallax_erode_dilate)*2+1,abs(parallax_erode_dilate)*2+1));

    switch (parallax_type){
    case ParallaxType::Binary:
        m_parallax.copyTo(m);
        GaussianBlur(m,m,Size(parallax_focus*2+1,parallax_focus*2+1),0,0);
        threshold(m,m,parallax_max,255,threshType);
        m -= parallax_min;
        if (parallax_erode_dilate > 0){
            dilate(m,m,shape);
        } else {
            erode(m,m,shape);
        }
        GaussianBlur(m,m,Size(parallax_soft*2+1,parallax_soft*2+1),0,0);
        break;
    case ParallaxType::HeightMap:
        current_heightmap.copyTo(m);
        cvtColor(m,m,CV_RGBA2GRAY);
        m.convertTo(m,CV_32F,1/255.0,-0.5);
        m.convertTo(m,-1,parallax_contrast,0.5);
        m.convertTo(m,CV_8U,255,parallax_brightness);
        GaussianBlur(m,m,Size(parallax_soft*2+1,parallax_soft*2+1),0,0);
        if (threshType == THRESH_BINARY_INV){
            subtract(Scalar::all(255),m,m) ;
        }
        break;
    case ParallaxType::Intervals:
        break;
    case ParallaxType::Quantization:
        current_heightmap.copyTo(m);

        GaussianBlur(m,m,Size(parallax_focus*2+1,parallax_focus*2+1),0,0);
        m /= (parallax_quantization/255.0);
        m *= (255.0/parallax_quantization);
        GaussianBlur(m,m,Size(parallax_soft*2+1,parallax_soft*2+1),0,0);

        m = -255/(parallax_max-parallax_min+1)*parallax_min+255/(parallax_max-parallax_min+1)*m;

        if (threshType == THRESH_BINARY_INV){
            subtract(Scalar::all(255),m,m) ;
        }
        break;
    }
    return m;
}

Mat ImageProcessor::modify_specular(){
    Mat m;

        current_heightmap.copyTo(m);
        cvtColor(m,m,CV_RGBA2GRAY);
        m.convertTo(m,CV_32F,1/255.0,-specular_thresh/255.0);
        m.convertTo(m,-1,specular_contrast,specular_thresh/255.0);
        m.convertTo(m,CV_8U,255,specular_bright);
        GaussianBlur(m,m,Size(specular_blur*2+1,specular_blur*2+1),0,0);

        if (specular_invert){
            subtract(Scalar::all(255),m,m) ;
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
    p = QImage(static_cast<unsigned char *>(current_parallax.data),
               current_parallax.cols,current_parallax.rows,current_parallax.step,QImage::Format_RGB888);
    processed(p,ProcessedImage::Parallax);
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
            if (heightMap.at<Vec4b>(y,x)[3] == 0.0 ){
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

void ImageProcessor::copy_settings(ProcessorSettings s){
    settings = s;
}

ProcessorSettings ImageProcessor::get_settings(){
    return settings;
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
    Mat image;
    cvtColor(m_img,m_aux,CV_BGRA2RGBA);
    return QImage(static_cast<unsigned char *>(m_aux.data),
                  m_aux.cols,m_aux.rows,m_aux.step,QImage::Format_RGBA8888);
}

QImage ImageProcessor::get_normal(){
    return QImage(static_cast<unsigned char *>(m_normal.data),
                  m_normal.cols,m_normal.rows,m_normal.step,QImage::Format_RGB888);
}

QImage ImageProcessor::get_parallax(){
    return QImage(static_cast<unsigned char *>(current_parallax.data),
                  current_parallax.cols,current_parallax.rows,current_parallax.step,QImage::Format_Grayscale8);
}

QImage ImageProcessor::get_specular(){
    return QImage(static_cast<unsigned char *>(current_specular.data),
                  current_specular.cols,current_specular.rows,current_specular.step,QImage::Format_Grayscale8);
}

bool ImageProcessor::get_parallax_invert(){
    return parallax_invert;
}

void ImageProcessor::set_parallax_invert(bool invert){
    parallax_invert = invert;
    calculate_parallax();
}

void ImageProcessor::set_parallax_focus(int focus){
    parallax_focus = focus;
    calculate_parallax();
}

int ImageProcessor::get_parallax_focus(){
    return parallax_focus;
}

void ImageProcessor::set_parallax_soft(int soft){
    parallax_soft = soft;
    calculate_parallax();
}

int ImageProcessor::get_parallax_soft(){
    return parallax_soft;
}

int ImageProcessor::get_parallax_thresh(){
    return parallax_max;
}

void ImageProcessor::set_parallax_thresh(int thresh){
    parallax_max = thresh;
    calculate_parallax();
}

int ImageProcessor::get_parallax_min(){
    return parallax_min;
}

void ImageProcessor::set_parallax_min(int min){
    parallax_min = min;
    calculate_parallax();
}

ParallaxType ImageProcessor::get_parallax_type(){
    return  parallax_type;
}

void ImageProcessor::set_parallax_type(ParallaxType ptype){
    parallax_type = ptype;
    calculate_parallax();
}

int ImageProcessor::get_parallax_quantization(){
    return  parallax_quantization;
}

void ImageProcessor::set_parallax_quantization(int q){
    parallax_quantization = q;
    calculate_parallax();
}

void ImageProcessor::set_parallax_erode_dilate(int value){
    parallax_erode_dilate = value;
    calculate_parallax();
}

int ImageProcessor::get_parallax_erode_dilate(){
    return parallax_erode_dilate;
}

void ImageProcessor::set_parallax_contrast(int contrast){
    parallax_contrast = contrast / 1000.0;
    calculate_parallax();
}

double ImageProcessor::get_parallax_contrast(){
    return  parallax_contrast;
}

void ImageProcessor::set_parallax_brightness(int brightness){
    parallax_brightness = brightness;
    calculate_parallax();
}

int ImageProcessor::get_parallax_brightness(){
    return parallax_brightness;
}

void ImageProcessor::set_specular_blur(int blur){
    specular_blur = blur;
    calculate_specular();
}
int ImageProcessor::get_specular_blur(){
    return specular_blur;
}

void ImageProcessor::set_specular_bright(int bright){
    specular_bright = bright;
    calculate_specular();
}
int ImageProcessor::get_specular_bright(){
    return specular_bright;
}

void ImageProcessor::set_specular_invert(bool invert){
    specular_invert = invert;
    calculate_specular();
}
bool ImageProcessor::get_specular_invert(){
    return  specular_invert;
}

void ImageProcessor::set_specular_thresh(int thresh){
    specular_thresh = thresh;
    calculate_specular();
}
int ImageProcessor::get_specular_trhesh(){
    return specular_thresh;
}

void ImageProcessor::set_specular_contrast(int contrast){
    specular_contrast = contrast/1000.0;
    calculate_specular();
}
double ImageProcessor::get_specular_contrast(){
    return specular_contrast;
}


ProcessorSettings& ProcessorSettings::operator=( ProcessorSettings other){
    *tileable = *(other.tileable);
    *gradient_end = *(other.gradient_end);
    *parallax_max = *(other.parallax_max);
    *parallax_min = *(other.parallax_min);
    *parallax_soft = *(other.parallax_soft);
    *parallax_type = *(other.parallax_type);
    *parallax_focus = *(other.parallax_focus);
    *parallax_invert = *(other.parallax_invert);
    *parallax_contrast = *(other.parallax_contrast);
    *parallax_brightness = *(other.parallax_brightness);
    *parallax_erode_dilate = *(other.parallax_erode_dilate);
    *parallax_quantization = *(other.parallax_quantization);

    *normal_depth = *(other.normal_depth);
    *normalInvertX = *(other.normalInvertX);
    *normalInvertY = *(other.normalInvertY);
    *normalInvertZ = *(other.normalInvertZ);
    *normal_bisel_soft = *(other.normal_bisel_soft);
    *normal_bisel_depth = *(other.normal_bisel_depth);
    *normal_blur_radius = *(other.normal_blur_radius);
    *normal_bisel_distance = *(other.normal_bisel_distance);
    *normal_bisel_blur_radius = *(other.normal_bisel_blur_radius);
    return *this;
}
