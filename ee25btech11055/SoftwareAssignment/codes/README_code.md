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
