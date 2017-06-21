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
use OpenCV\CV;
$im=CV::imread('example.png');

```



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
    - imread(function)
    - imwrite(function)
    - imshow(function)
    - waitKey(function)
