#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
Image base; 
       base.readFromFile("/workspaces/cs225/mp_stickers/alma.png");
StickerSheet add(base, 3);
Image one;
one.readFromFile("/workspaces/cs225/mp_stickers/i.png");
add.addSticker(one,1,1);
add.addSticker(one, 20,20);
add.addSticker(one, 40,40); 
  Image output = add.render();
  output.writeToFile("/workspaces/cs225/mp_stickers/myImage.png");
  return 0;

}
