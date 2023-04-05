#include "StickerSheet.h"
#include "cs225/PNG.h"
using namespace cs225;
using namespace std;
StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base = picture;
    max_ = max;
    number = 0;
    stickersheet_ = vector<Image*>(max_,NULL);
    xlocation = vector<unsigned>(max_,0);
    ylocation = vector<unsigned>(max_,0);
}

StickerSheet::~StickerSheet() {
}

StickerSheet::StickerSheet (const StickerSheet &other) {
    base = other.base;
    max_ = other.max_;
    stickersheet_ = other.stickersheet_;
    xlocation = other.xlocation;
    ylocation = other.ylocation;
     number = other.number;
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other) {
    base = other.base;
    max_ = other.max_;
    stickersheet_ = other.stickersheet_;
    xlocation = other.xlocation;
    ylocation = other.ylocation;
     number = other.number;
        return *this;
    }

void StickerSheet::changeMaxStickers (unsigned max) {
    if(max_ == max) {
        return;
    }
    max_ = max;
    stickersheet_.resize(max_);
    xlocation.resize(max_);
    ylocation.resize(max_);
    }

    int StickerSheet::addSticker(Image &sticker, unsigned x,unsigned y) {
            for (unsigned i = 0; i < stickersheet_.size();i++){
            if(stickersheet_[i] == NULL) {
                stickersheet_[i] = &sticker;
                xlocation[i] = x;
                ylocation[i] = y;
                number = number + 1;
                return i;
            }
        }
    return -1;
    }

    bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
        if(stickersheet_[index] == NULL) {
            return false;
        } else{
            xlocation[index] = x;
            ylocation[index] = y;
            return true;
        }
    }
    void StickerSheet::removeSticker(unsigned index) {
        number = number - 1;
        stickersheet_[index] = NULL;
        
    }
    Image* StickerSheet::getSticker(unsigned index) {
        if (index > stickersheet_.size() - 1) {
            return NULL;
        } else {
            return stickersheet_[index];
        }
    }
    Image StickerSheet::render() const {
        Image returnImage = base;
        for(unsigned i = 0; i < stickersheet_.size(); i++) {
            if(stickersheet_[i] != NULL) {
                if(ylocation[i]+stickersheet_[i]->height() > returnImage.height()) {
                    returnImage.resize(returnImage.width(), ylocation[i]+stickersheet_[i]->height());
                } 
                if(xlocation[i]+stickersheet_[i]->width() > returnImage.width()) {
                    returnImage.resize(xlocation[i]+stickersheet_[i]->width(),returnImage.height());
                }
            for(unsigned int x = xlocation[i]; x < xlocation[i] + stickersheet_[i]->width();x++) {
                for(unsigned int y = ylocation[i]; y < ylocation[i] + stickersheet_[i]->height();y++) {
                    unsigned int w = x - xlocation[i];
                    unsigned int h = y - ylocation[i];
                    HSLAPixel & oldPixel = returnImage.getPixel(x, y);
                    HSLAPixel & newPixel = stickersheet_[i] ->getPixel(w,h);
                    if(newPixel.a != 0) {
                        oldPixel = newPixel;
                    }
                }
            }
            }
        }
        return returnImage;
    }