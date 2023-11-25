// imageTest - A program that performs some image processing.
//
// This program is an example use of the image8bit module,
// a programming project for the course AED, DETI / UA.PT
//
// You may freely use and modify this code, NO WARRANTY, blah blah,
// as long as you give proper credit to the original and subsequent authors.
//
// João Manuel Rodrigues <jmr@ua.pt>
// 2023

#include <assert.h>
#include <errno.h>
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image8bit.h"
#include "instrumentation.h"

int main(int argc, char* argv[]) {
  program_name = argv[0];
  if (argc != 3) {
    error(1, 0, "Usage: imageTest input.pgm output.pgm");
  }
                                                                                    //INICIALIZAÇÃO DE IMAGEM
  ImageInit();
  
  printf("# LOAD image");
                                                                                    //RESET À  INSTRUMENTAÇÃO
  InstrReset(); // to reset instrumentation                 
                                                                                    //LOAD DA IMAGEM 1
  Image img1 = ImageLoad(argv[1]);
  if (img1 == NULL) {
    error(2, errno, "Loading %s: %s", argv[1], ImageErrMsg());
  }
                                                                                    //PRINT DA INSTRUMENTAÇÃO
  InstrPrint(); // to print instrumentation                                         

  // Try changing the behaviour of the program by commenting/uncommenting
  // the appropriate lines.

                                                                                    //TESTE À FUNÇÃO DE IMAGECROP()
  Image img2 = ImageCrop(img1, ImageWidth(img1)/4, ImageHeight(img1)/4, ImageWidth(img1)/2, ImageHeight(img1)/2);

                                                                                    //TESTE À FUNÇÃO DE IMAGEROTATE()
  img2 = ImageRotate(img1);
  if (img2 == NULL) {
    error(2, errno, "Rotating img2: %s", ImageErrMsg());
  }

                                                                                    //TESTE À FUNÇÃO IMAGENEGATIVE()
  ImageNegative(img2);

                                                                                    //TESTE À FUNÇÃO IMAGETHRESHOLD()
  ImageThreshold(img2, 100);

                                                                                    //TESTE À FUNÇÃO IMAGEBRIGHTEN()
  ImageBrighten(img2, 1.3);

  if (ImageSave(img2, argv[2]) == 0) {
    error(2, errno, "%s: %s", argv[2], ImageErrMsg());
  }
  
  ImageDestroy(&img1);
  ImageDestroy(&img2);
  return 0;
}