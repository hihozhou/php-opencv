# PHP-OPENCV - PHP extension for Opencv

[![Minimum PHP Version](https://img.shields.io/badge/php-%3E%3D%207.0-8892BF.svg)](https://php.net/)

## Requirements

- OpenCV 3.2
- PHP7.0+



## Installation

```bash
git clone https://github.com/hihozhou/php-opencv.git
cd php-opencv
phpize
./configure --with-php-config=your php-config path
make
make install
```

## Configure

php.ini

```
extension="opencv.so path"
```
## Example

```php
//Obama.php
use function CV\{ imread, imshow, waitkey, namedWindow};

$im = imread('Obama.png');//load image
namedWindow('This is Obama id card',WINDOW_FULLSCREEN);//create window
imshow('This is Obama id card',$im);//show image on window

waitkey(0);

```

result:

![Obama](tests/Obama.png)

Load image by gray

```php
$gray = imread('Obama.png',IMREAD_GRAYSCALE);
//or
use  function CV\{ cvtColor};
$gray = cvtColor($im, COLOR_BGR2GRAY);

```

![Obama_gray](tests/Obama_gray.png)


You can draw something.  
e.g:  

```php
use CV\{Mat,Scalar, Point, Size};
use function CV\{ellipse, imwrite, waitKey};
use const CV\{CV_8UC3};

$windowWidth = 600;
$thickness = 2;
$lineType = 8;
$matScalar = new Scalar(0,0,0);
$mat = new Mat($windowWidth, $windowWidth, CV_8UC3, $matScalar);
$point=new Point($windowWidth/2, $windowWidth/2);
$size=new Size($windowWidth/4, $windowWidth/16);
$scalar=new Scalar(255, 129, 0);
for($i = 0; $i <= 360; $i += 45){
    ellipse($mat,$point,$size,$i,0,360,$scalar,$thickness,$lineType);
}
imwrite('./tests/ellipse.png',$mat);

```

result:

![ellipse](tests/ellipse.png)



## Features
- 1.calib3d
- 2.contrib
- 3.core
- 4.imgproc
- 5.features2d
- 6.flann
- 7.gpu
- 8.highgui
- 9.legacy
- 10.ml
- 11.nonfree
- 12.objdetect
- 13.ocl
- 14.photo
- 15.stitching
- 16.superres
- 17.ts
- 18.video
- 19.Videostab

## Structure
- CV(namespace)
    - Exception(class)
    - Mat(class)
        - __construct
        - print
        - zeros
        - type
        - depth
        - channels
        - isContinuous
        - row
        - col
    - Point(class)
        - __construct
        - print
    - Scalar(class)
        - __construct
        - print
    - Size(class)
        - __construct
        - print
    - Rect(class)
        - __construct
        - print
        - tl
        - br
        - size
        - area
    - imread(function)
    - imwrite(function)
    - namedWindow(function)
    - imshow(function)
    - waitKey(function)
    - cvtColor(function)
    - ellipse(function)
    - circle(function)
    - line(function)
    - rectangle(function)
    - rectangleByPoint(function)
    - rectangleByRect(function)
    - Formatter(class)
    
    
    
## 感谢

感谢[韩天峰](https://github.com/matyhtf)老大的指导，  
感谢[盘古大叔](https://github.com/pangudashu)的[php7-internal](https://github.com/pangudashu/php7-internal)项目以及平常的指导，  
感谢`木桶技术升级交流群`和`黑夜路人技术群`、以及`PHP内核交流`的群友对技术的帮助。