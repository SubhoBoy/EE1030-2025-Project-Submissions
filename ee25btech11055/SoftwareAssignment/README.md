# Image Compression using Truncated SVD

This repo contains the source code, project report and instructions to run the software, for the Software Course Project for EE1030.
The idea is to perform rudimentary compression on an image by representing it as a matrix (or in the case of a colour image, 3 matrices) and applying SVD upon it. By keeping only the top _k_ singular values, a low rank approximation of the image matrix can be obtained, which upon conversion back to the source format results in a smaller file size due to the format's compressive algorithms.

# Project Features
- User configurable parameter setting
- Pure C implementation for program
- High-performance parallel processing
- Efficient truncated SVD instead of full SVD
- Efficient colour handling
- Flexible I/O formats
- Modular, memory managed code
- Comparison with standard libraries and error plots

## Project Structure
```
SoftwareAssignment
├── codes
│   ├── c_libs
│   │   ├── image.c
│   │   ├── image.h
│   │   ├── matrix.c
│   │   ├── matrix.h
│   │   ├── stb_image.h
│   │   ├── stb_image_write.h
│   │   ├── svd.c
│   │   └── svd.h
│   ├── c_main
│   │   ├── a.out
│   │   └── main.c
│   └── README_code.md
├── figs
│   ├── einstein_100.jpg
│   ├── einstein_10.jpg
│   ├── einstein_150.jpg
│   ├── einstein_15.jpg
│   ├── einstein_1.jpg
│   ├── einstein_200.jpg
│   ├── einstein_20.jpg
│   ├── einstein_25.jpg
│   ├── einstein_30.jpg
│   ├── einstein_50.jpg
│   ├── einstein_5.jpg
│   ├── einstein_75.jpg
│   ├── einstein.jpg
│   ├── globe_100.jpg
│   ├── globe_10.jpg
│   ├── globe_1.jpg
│   ├── globe_200.jpg
│   ├── globe_25.jpg
│   ├── globe_300.jpg
│   ├── globe_50.jpg
│   ├── globe_5.jpg
│   ├── globe.jpg
│   ├── greyscale_100.png
│   ├── greyscale_10.png
│   ├── greyscale_1.png
│   ├── greyscale_200.png
│   ├── greyscale_25.png
│   ├── greyscale_50.png
│   ├── greyscale_5.png
│   └── greyscale.png
├── gvv-book.sty
├── gvv.sty
├── README.md
├── report.pdf
├── report.synctex.gz
├── report.tex
└── tables
    ├── einstein.tex
    ├── globe.tex
    └── greyscale.tex
```
