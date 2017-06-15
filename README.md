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



## Development plan
- Mat类（存放图片结构）
- CV基本方法

## Structure
- OpenCV(namespace)
    - CV(class)
        - imread
        - imshow
        - imwrite
        - waitKey
    - Mat(class)
        - __construct
        - print
