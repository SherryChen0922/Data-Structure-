/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#include "cs225/PNG.h"
#include "Image.h"
#include <vector>
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_
class StickerSheet {
public:
     StickerSheet(const Image &picture, unsigned max);
     ~StickerSheet();
     StickerSheet (const StickerSheet &other);
     const StickerSheet & operator= (const StickerSheet &other);
     void changeMaxStickers (unsigned max);
     int addSticker(Image &sticker, unsigned x,unsigned y);
     bool translate(unsigned index, unsigned x, unsigned y);
     void removeSticker(unsigned index);
     Image* getSticker(unsigned index);
     Image render() const;
 private:
    unsigned max_;
    Image base;
    std::vector<Image*> stickersheet_;
    std::vector<unsigned> xlocation;
    std::vector<unsigned> ylocation;
    unsigned number;
 };
 #endif
 #pragma once