#include "cs225/PNG.h"
#include <list>
#include <iostream>
#include <vector>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;
using  namespace std;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  png_ = png;
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  ImageTraversal* add1 = &traversal;
  ColorPicker* add2 = &colorPicker;
  traversal_.push_back(add1);
  color_.push_back(add2);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) {
  Animation animation;
  /** @todo [Part 2] */
  int count = 0;
  //PNG copy = png_;
  animation.addFrame(png_);
  //std::cout << "traversal size: " << traversal_.size() << endl;
  for (unsigned int i = 0; i < traversal_.size();i++) {
    int count = 0;
    for (auto it = traversal_[i]->begin(); it != traversal_[i]->end(); ++it) {
      
      HSLAPixel& change = png_.getPixel((*it).x,(*it).y);
      change = color_[i]->getColor((*it).x,(*it).y);
      count++;
      if(count == int(frameInterval)) {
       animation.addFrame(png_);
       count = 0;
     }
     
      
     
    }
  }
  animation.addFrame(png_);
  return animation;
}
