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

### edit php.ini
```
extension="opencv.so路径"
```


##开发计划


## 结构
- OpenCV(namespace)
    - CV(class)
    - Mat(class)
        - __construct 
