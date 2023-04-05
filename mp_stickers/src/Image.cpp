#include "Image.h"
using namespace cs225;

void Image::lighten() {
    Image::lighten(0.1);
}
    void Image::lighten(double amount) {
        for(unsigned int x = 0; x < width(); x++) {
        for(unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).l + amount < 1.0) {
                getPixel(x,y).l = getPixel(x,y).l + amount;
            } else {
                getPixel(x,y).l = 1.0;
            }
        }
    }
    }
    void Image::darken() {
    for(unsigned int x = 0; x < width(); x++) {
        for(unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).l > 0.1) {
                getPixel(x,y).l = getPixel(x,y).l - 0.1;
            } else {
                getPixel(x,y).l = 0.0;
            }
        }
    }
    }
    void Image::darken(double amount) {
    for(unsigned int x = 0; x < width(); x++) {
        for(unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).l - amount > 0.0) {
                getPixel(x,y).l = getPixel(x,y).l - amount;
            } else {
                getPixel(x,y).l = 0.0;
            }
        }
    }
    }
    void Image::saturate() {
        for(unsigned int x = 0; x < width(); x++) {
        for(unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).s < 0.9) {
                getPixel(x,y).s = getPixel(x,y).s + 0.1;
            } else {
                getPixel(x,y).s = 0.0;
            }
        }
    }
    }
    void Image::saturate(double amount) {
        for(unsigned int x = 0; x < width(); x++) {
        for(unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).s + amount < 1.0) {
                getPixel(x,y).s = getPixel(x,y).s + amount;
            } else {
                getPixel(x,y).s = 1.0;
            }
        }
    }
    }
    void Image::desaturate() {
        for(unsigned int x = 0; x < width(); x++) {
        for(unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).s > 0.1) {
                getPixel(x,y).s = getPixel(x,y).s - 0.1;
            } else {
                getPixel(x,y).s = 0.0;
            }
        }
    }
    }
    void Image::desaturate(double amount) {
        for(unsigned int x = 0; x < width(); x++) {
        for(unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).s - amount > 0.0) {
                getPixel(x,y).s = getPixel(x,y).s - amount;
            } else {
                getPixel(x,y).s = 0.0;
            }
        }
    }
    }
    void Image::grayscale() {
        for(unsigned int x = 0; x < width(); x++) {
        for(unsigned int y = 0; y < height(); y++) {
                getPixel(x,y).s = 0;
        }
    }
    }
    void Image::rotateColor(double degrees) {
        for(unsigned int x = 0; x < width(); x++) {
        for(unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).h + degrees < 360.0 && getPixel(x,y).h + degrees > 0) {
                getPixel(x,y).h = getPixel(x,y).h + degrees;
            } else if (getPixel(x,y).h + degrees > 360.0) {
                getPixel(x,y).h = getPixel(x,y).h + degrees -360;
            } else {
                getPixel(x,y).h = getPixel(x,y).h + degrees + 360;
            }
        }
    }
    }
    void Image::illinify() {
       for(unsigned int x = 0; x < width(); x++) {
        for(unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).h > 102.5 ||getPixel(x,y).h < 293.5) {
                getPixel(x,y).h = 216.0;
            } else {
                getPixel(x,y).h = 11.0;
            }
        }
    } 
    }
    void Image::scale(double factor) {
PNG *temp = new PNG(width(), height());
for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & newPixel = temp ->getPixel(x, y);
         newPixel =  this->getPixel(x, y);
      }
    }
unsigned int newWidth_ = width() * factor;
unsigned int newHeight_ = height() *factor;
resize(newWidth_, newHeight_);
for (unsigned x = 0; x < newWidth_; x++) {
      for (unsigned y = 0; y < newHeight_; y++) {
         HSLAPixel & oldPixel = temp->getPixel(x/factor, y/factor);
         HSLAPixel & newPixel = this ->getPixel(x, y);
         newPixel =  oldPixel;
      }
    }
    delete temp;
    }

    void Image::scale(unsigned w, unsigned h) {
        double factor1 = (double)w/width();
        double factor2 = (double)h/height();
        double factor = 0.0;
        if(factor1 > factor2) {
  factor = factor2;
        }else {
            factor = factor1;
        }
        std::cout<< factor << std::endl;
        PNG *temp = new PNG(width(), height());
for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & newPixel = temp ->getPixel(x, y);
         newPixel =  this->getPixel(x, y);
      }
    }
unsigned int newWidth_ = width() * factor;
unsigned int newHeight_ = height() *factor;
resize(newWidth_, newHeight_);
for (unsigned x = 0; x < newWidth_; x++) {
      for (unsigned y = 0; y < newHeight_; y++) {
         HSLAPixel & oldPixel = temp->getPixel(x/factor, y/factor);
         HSLAPixel & newPixel = this ->getPixel(x, y);
         newPixel =  oldPixel;
      }
    }
    delete temp;
    }