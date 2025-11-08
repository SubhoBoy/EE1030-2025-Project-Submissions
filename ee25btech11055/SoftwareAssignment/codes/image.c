#include "image.h"
#include <stdio.h>
//#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void read_img(const char *inp, const char *out) {
    int x,y,n;
    
    unsigned char *data; 

    if ((data = stbi_load(inp,&x,&y,&n,3)) == NULL) {
        printf("Could not load input image");
        return;
    }


    FILE *mid;
    if ((mid = fopen(out,"w")) == NULL) {
        printf("Error: Could not create ppm file");
        stbi_image_free(data);
        return;
    }

    // 255 is max value for reference
    fprintf(mid, "P3\n# format\n%d %d\n255\n", x, y); //TODO write format i got from here

    int count = 0;
    long long len= (long long)x * y * 3; 
    
    for (long long i = 0; i < len; i++) {
        fprintf(mid, "%d", data[i]);

        count++;
        if (count % 15 == 0 ){
             fprintf(mid, "\n");
        } else {
             fprintf(mid, " ");
        }
    }

    fclose(mid);
    stbi_image_free(data); 

    return;
}

//void write_img(const char *inp, const char *out, int format, int quality) {
//    int x,y,n;
//
//    unsigned char *data;
//    if ((data = stbi_load(inp,&x,&y,&n,3)) == NULL) {
//        printf("Error in opening intermediate file.");
//        return;
//    }
//
//    if (format) {
//        if(stbi_write_png(out,x,y,n,data,x*n)) printf("Image written to file");
//        else printf("Could not write to png"); 
//    } else {
//        if(stbi_write_jpg(out,x,y,n,data,quality)) printf("Image written to file");
//        else printf("Could not write to jpg");
//    }
//    stbi_image_free(data);
//
//}
void write_img(const double *r, const double *g, const double *b, 
               int x, int y, const char *out, int format, int quality) {
    
    unsigned char *output_data = (unsigned char *) malloc(x*y*3 * sizeof(unsigned char));
    if (output_data == NULL) {
        printf("Error: Could not allocate memory for output image buffer.");
        return;
    }

    long long i = 0;
    for (long long p = 0; p < x; p++) {
        for (long long q = 0; q < y; q++) {
            double rv = r[p*y+q];
            double gv = g[p*y+q];
            double bv = b[p*y+q];

            // Need clamp cuz AVD gives weird results
            output_data[i++] = (rv < 0.0) ? 0 : (rv > 255.0) ? 255 : (unsigned char)rv;
            output_data[i++] = (gv < 0.0) ? 0 : (gv > 255.0) ? 255 : (unsigned char)gv;
            output_data[i++] = (bv < 0.0) ? 0 : (bv > 255.0) ? 255 : (unsigned char)bv;
        }
    }
    
    if (format) {
        if(stbi_write_png(out, x, y, 3, output_data, x * 3)) {
             printf("Image written to file\n");
        } else {
             printf("Could not write to png");
        }
    } else {
        if(stbi_write_jpg(out, x, y, 3, output_data, quality)) {
            printf("Image written to file\n");
        } else {
            printf("Could not write to jpg");
        }
    }
    
    free(output_data);
}

//int main(int argc, char **argv) {
//    if (argc != 3) {
//        fprintf(stderr, "Usage: %s <input.img> <output.ppm>\n", argv[0]);
//        return 1;
//    }
//    read_img(argv[1], argv[2]);
//    return 0;
//}
