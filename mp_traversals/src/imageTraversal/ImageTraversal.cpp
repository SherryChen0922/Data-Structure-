#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  curr_.x = -2;
  curr_.y = -2;
  traversal_ = NULL;
}
ImageTraversal::Iterator::Iterator( ImageTraversal & traversal, Point start, double tolerance,PNG png) 
{
  /** @todo [Part 1] */
 curr_ = start;
 traversal_ = &traversal;
 start_ = start;
 tolerance_ = tolerance;
 png_ = png;
 visited.resize(png.width());
  for(unsigned i = 0; i < png.width();i++) {
    visited[i].resize(png.height());
  }
  for(unsigned i = 0; i < png.width();i++) {
    for(unsigned j = 0; j < png.height();j++) {
      visited[i][j] = 0;
    }
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //Point output;
  //if(!traversal_->empty()) {
  // curr_ = traversal_ -> pop();
  visited[curr_.x][curr_.y] = 1;
  //std::cout << curr_ << std::endl;
  if(curr_.x + 1 < png_.width()) {
     //std::cout << "in right" << std::endl;
     Point right(curr_.x + 1, curr_.y);
     if(visited[right.x][right.y] == 0 && calculateDelta(png_.getPixel(start_.x,start_.y), png_.getPixel(right.x,right.y)) <= tolerance_) {
      traversal_->add(right);
      //std::cout << "added" << std::endl;
     }
  }
  if(curr_.y + 1 < png_.height()) {
    // std::cout << "in down" << std::endl;
     Point down(curr_.x, curr_.y +1);
     if(visited[down.x][down.y] == 0 && calculateDelta(png_.getPixel(start_.x,start_.y), png_.getPixel(down.x,down.y)) <= tolerance_) {
      traversal_->add(down);
     // std::cout << "added" << std::endl;
     }
  }
  if(curr_.x > 0){
     //std::cout << "in left" << std::endl;
     Point left(curr_.x - 1, curr_.y);
     if(visited[left.x][left.y] == 0 && calculateDelta(png_.getPixel(start_.x,start_.y), png_.getPixel(left.x,left.y)) <= tolerance_) {
      traversal_->add(left);
      //std::cout << "added" << std::endl;
     }
  }
  if(curr_.y > 0) {
     //std::cout << "in above" << std::endl;
     Point up(curr_.x, curr_.y -1);
     if(visited[up.x][up.y] == 0 && calculateDelta(png_.getPixel(start_.x,start_.y), png_.getPixel(up.x,up.y)) <= tolerance_) {
      traversal_->add(up);
      //std::cout << "added" << std::endl;
     }
  }
  bool end = true;
  while(!traversal_->empty()) {
    curr_ = traversal_->pop();
    if(visited[curr_.x][curr_.y] == 0) {
      end = false;
      break;
    }
  }
  if(end == true) {
     traversal_ = NULL;
   curr_.x = -2;
   curr_.y = -2;
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  //return traversal_->peek();
  // std::cout << "reach" <<std::endl;
  return curr_; 
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (traversal_ == NULL && other.traversal_ == NULL) return false;
  else if (other.traversal_ == NULL && traversal_->empty()) return false;
  else if (traversal_ == NULL && other.traversal_->empty()) return false;
  else if (traversal_->empty() && other.traversal_->empty()) return false;
  else return true;
 
}

