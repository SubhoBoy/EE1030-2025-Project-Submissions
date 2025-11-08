## Instructions
The project uses only standard libraries, along with stb_image.h which is included in the repo. To run the code, first ensure that your `gcc` version is greater than 4.2.0
```bash
gcc --version
```
If gcc is up to date, proceed to compile the project:
1. On UNIX based systems:
```bash
gcc c_main/main.c c_libs/matrix.c c_libs/image.c c_libs/svd.c -lm -o comp
```
2. On Windows:
```bash
gcc c_main/main.c c_libs/matrix.c c_libs/image.c c_libs/svd.c -lm -o comp.exe
```

The format for running the program is:
```bash
./comp input.img output.img k
```
where _k_ is the number of top singular values to keep.

To run the Python code for comparison with linalg libraries and plotting, first install the following Python libraries:
```
numpy Pillow matplotlib
```
Then, the Python code is self-contained:
```bash
python svdplot.py
```
