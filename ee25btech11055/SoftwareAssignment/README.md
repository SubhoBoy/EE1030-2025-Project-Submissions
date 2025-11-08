# Image Compression using Truncated SVD

This repo contains the source code, project report and instructions to run the software, for the Software Course Project for EE1030.
The idea is to perform rudimentary compression on an image by representing it as a matrix (or in the case of a colour image, 3 matrices) and applying SVD upon it. By keeping only the top _k_ singular values, a low rank approximation of the image matrix can be obtained, which upon conversion back to the source format results in a smaller file size due to the format's compressive algorithms.

## Instructions
The project uses only standard libraries, along with stb_image.h which is included in the repo. To run the code, first ensure that your `gcc` version is greater than 4.2.0
```bash
gcc --version
```
If gcc is up to date, proceed to compile the project:
1. On UNIX based systems:
```bash
gcc main.c matrix.c image.c svd.c -lm -o comp
```
2. On Windows:
```bash
gcc main.c matrix.c image.c svd.c -lm -o comp.exe
```

The format for running the program is:
```bash
./comp input.img output.img k
```
where _k_ is the number of top singular values to keep 
