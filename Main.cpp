#include "Factory.h"
#include "Factory_Sphere.h"
#include "Factory_Box.h"
#include "Figure.h"
#include "Sphere.h"
#include "Functions.h"
//#include "functions.cpp"
#include "Box.h"
#include "Header.h"
#include <map>
//o#include <omp.h>
int main() {
    const std::string FileName = "Data.txt";
    const std::string FileName_2 = "Objects.txt";
    std::ifstream inputFile(FileName);
    if (!inputFile.is_open()) {
        std::cout << "File was not opened!";
        exit(0);
    }
    std::ifstream inputFile_2(FileName_2);
    if (!inputFile_2.is_open()) {
        std::cout << "File_2 was not opened!";
        exit(0);
    }
    std::vector<double> cam(3);
    std::vector<double> normal(3);
    std::vector<double> up(3);
    double screen; double limit;
    double alpha;
    int height;
    int width;
    std::vector<double> light(3);
    while (!inputFile.eof()) {
        std::string line;
        inputFile >> line;
        //std::cout<<line;
        if (line == "cam") {
            double x, y, z;
            inputFile >> x >> y >> z;
            cam = { x,y,z };
        }
        if (line == "normal") {
            double x, y, z;
            inputFile >> x >> y >> z;
            normal = { x,y,z };
        }
        if (line == "up") {
            double x, y, z;
            inputFile >> x >> y >> z;
            up = { x,y,z };
        }
        if (line == "screen") {
            double x;
            inputFile >> x;
            screen = x;
        }
        if (line == "limit") {
            double x;
            inputFile >> x;
            limit = x;
        }
        if (line == "alpha") {
            double x;
            inputFile >> x;
            alpha = x;
        }
        if (line == "width") {
            int x;
            inputFile >> x;
            width = x;
        }
        if (line == "height") {
            int x;
            inputFile >> x;
            height = x;

        }
        if (line == "light") {
            double x, y, z;
            inputFile >> x >> y >> z;
            light = { x,y,z };
        }
    }
    inputFile.close();
    std::map<std::string, Factory*> Our_map;
    Our_map["sphere"] = new Factory_Sphere;
    Our_map["box"] = new Factory_box;
  //  Our_map["tetra"] = new Factory_tetra;
    std::vector<Figure*> Figures;

    while (!inputFile_2.eof()) {
        std::string line;
        inputFile_2 >> line;
        //std::cout<<line;
        auto curFactory = Our_map.find(line);
        if (!line.empty()) {
            if (curFactory == Our_map.end()) {
                std::cout << "Error! Wrong type of vector in file input2.txt!\n" << line;
                exit(0);
            }
        }
        if (line == "sphere") {
            double x, y, z, R;
            inputFile_2 >> x >> y >> z >> R;
            if (abs(x) > limit || abs(y) > limit || abs(z) > limit) {
                std::cout << "wrong data in sphere!";
                exit(0);
            }
            std::vector<double> centre = { x,y,z };

            Figures.push_back(curFactory->second->Create(R, centre));
        }
        if (line == "box") {
            double x_min, y_min, z_min, x_max, y_max, z_max;
            inputFile_2 >> x_min >> y_min >> z_min >> x_max >> y_max >> z_max;
            if (x_min >= x_max || y_min >= y_max || z_min >= z_max) {
                std::cout << "wrong data in box!";
                exit(0);
            }
            if (abs(x_min) > limit || abs(y_min) > limit || abs(z_min) > limit || abs(x_max) > limit || abs(y_max) > limit || abs(z_max) > limit) {
                std::cout << "wrong data in box limit!";
                exit(1);
            }
            std::vector<double> min = { x_min,y_min,z_min };
            std::vector<double> max = { x_max,y_max,z_max };

            Figures.push_back(curFactory->second->Create(min, max));
        }
    }

    inputFile_2.close();
    for (std::vector<double>::iterator i = normal.begin(); i != normal.end(); ++i) {
        *i = *i / sqrt(scalar_product(normal, normal));
    }

    for (std::vector<double>::iterator i = up.begin(); i != up.end(); ++i) {
        *i = *i / sqrt(scalar_product(up, up));
    }
    double pixel_size = (2 * screen * tan(3.14 * (alpha / 180) / 2)) / height;
    std::vector<double> left(3);
    vector_product(&left, up, normal);
    std::vector<double> lowest(3);

    for (size_t j = 0; j < 3; ++j) {
        lowest[j] = cam[j] + screen * (normal[j]) - (height / 2) * pixel_size * (up[j]) + (width / 2) * pixel_size * (left[j]);
    }
    //  std::cout << lowest[0] << "  " << lowest[1]<<"  " << lowest[2];
    int w = width;
    int h = height;

    unsigned char* img = NULL;
    int filesize = 54 + 3 * w * h;

    img = (unsigned char*)malloc(3 * w * h);
    memset(img, 0, 3 * w * h);

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            unsigned char r = 255;
            unsigned char g = 255;
            unsigned char b = 255;
            img[(j + i * w) * 3 + 2] = r;
            img[(j + i * w) * 3 + 1] = g;
            img[(j + i * w) * 3 + 0] = b;
        }
    }

    unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
    unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
    unsigned char bmppad[3] = { 0,0,0 };

    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize >> 8);
    bmpfileheader[4] = (unsigned char)(filesize >> 16);
    bmpfileheader[5] = (unsigned char)(filesize >> 24);

    bmpinfoheader[4] = (unsigned char)(w);
    bmpinfoheader[5] = (unsigned char)(w >> 8);
    bmpinfoheader[6] = (unsigned char)(w >> 16);
    bmpinfoheader[7] = (unsigned char)(w >> 24);
    bmpinfoheader[8] = (unsigned char)(h);
    bmpinfoheader[9] = (unsigned char)(h >> 8);
    bmpinfoheader[10] = (unsigned char)(h >> 16);
    bmpinfoheader[11] = (unsigned char)(h >> 24);

    FILE* f = fopen("Image.bmp", "wb");
    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);
    for (int i = 0; i < h; ++i) {
        fwrite(img + (w * (h - 1 - i) * 3), 3, w, f);
        fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f);
    }
    free(img);
    fclose(f);
    RGB_Image image;
    strcpy(image.file_name, "Image.bmp");
    load_image(&image);
    double x, y, z;
    for (size_t i = 0; i < Figures.size(); ++i) {
        for (size_t j = 0; j < Figures.size(); ++j) {
            if (Figures[j]->distance(cam) > Figures[i]->distance(cam)) {
                Figure* a = Figures[i];
                Figures[i] = Figures[j];
                Figures[j] = a;
            }
        }
    }
    unsigned char min = 255; unsigned char k = 60;
    std::vector<std::vector<unsigned char>> color(Figures.size());
    for (size_t i = 0; i < color.size();i++) {
        color[i].resize(3);
    }
    if (Figures.size() != 1) {
        for (size_t i = 0; i < Figures.size(); ++i) {
            if (i == 0) {
                color[i] = { 255,0,0 };
                
            }
            else if (i + 1 == Figures.size()) {
                color[i] = { 0,255,0 };
            }
            else {
                color[i] = { (unsigned char)(min - k),(unsigned char)(k),0};
                k+=40;
            }
        }
    }
    else color[0] = { 255,0,0 };

    auto start1 = std::chrono::system_clock::now();
#pragma omp parallel for private(x,y,z)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::vector<double> direction(3);
            x = lowest[0] + (pixel_size / 2) * (up[0]) - (pixel_size / 2) * left[0] + i * (pixel_size) * (up[0]) - j * (pixel_size)*left[0];
            y = lowest[1] + (pixel_size / 2) * (up[1]) - (pixel_size / 2) * left[1] + i * (pixel_size) * (up[1]) - j * (pixel_size)*left[1];
            z = lowest[2] + (pixel_size / 2) * (up[2]) - (pixel_size / 2) * left[2] + i * (pixel_size) * (up[2]) - j * (pixel_size)*left[2];
            direction[0] = x - cam[0];
            direction[1] = y - cam[1];
            direction[2] = z - cam[2];

            std::vector<unsigned char> col = ray_trace(cam, direction, Figures, light, color);
            image.pixels[i][j].red = col[0];
            image.pixels[i][j].green = col[1];
            image.pixels[i][j].blue = col[2];
        }
    }
    auto end1 = std::chrono::system_clock::now();
    int elapsed_ms_1 = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count());
    std::cout << "runtime is " << elapsed_ms_1 << "s\n";

    for (auto it : Figures)
        delete it;
    delete Our_map["sphere"];
    delete Our_map["box"];
    delete Our_map["tetra"];
    save_image(image);
    free_pixels(image);
    return 0;
}
int load_image(RGB_Image* image_ptr)
{
    FILE* fptr;
    strcpy(image_ptr->file_name, "Image.bmp");
    fptr = fopen(image_ptr->file_name, "rb");

    if (NULL == fptr)
    {
        printf("\n File cannot be opened.");
        return 1;
    }

    fseek(fptr, 2, SEEK_SET);
    fread(&(image_ptr->size), 4, 1, fptr);
    fseek(fptr, 12, SEEK_CUR);
    fread(&(image_ptr->width), 4, 1, fptr);
    fread(&(image_ptr->height), 4, 1, fptr);
    fseek(fptr, 28, SEEK_CUR);

    image_ptr->pixels = (Pixel**)malloc((image_ptr->height) * sizeof(Pixel*));

    for (unsigned i = 0; i < (image_ptr->height); ++i)
        image_ptr->pixels[i] = (Pixel*)malloc((image_ptr->width) * sizeof(Pixel));

    for (unsigned i = 0; i < image_ptr->height; ++i)
    {
        for (unsigned j = 0; j < image_ptr->width; ++j)
        {
            image_ptr->pixels[i][j].red = 0;
            image_ptr->pixels[i][j].green = 0;
            image_ptr->pixels[i][j].blue = 0;
        }
    }

    for (unsigned i = 0; i < image_ptr->height; ++i)
    {
        for (unsigned j = 0; j < image_ptr->width; ++j)
        {
            fread(&(image_ptr->pixels[i][j].blue), 1, 1, fptr);
            fread(&(image_ptr->pixels[i][j].green), 1, 1, fptr);
            fread(&(image_ptr->pixels[i][j].red), 1, 1, fptr);
        }
    }
    fclose(fptr);

    return 0;
}

int save_image(RGB_Image image)
{
    char fileCopy[100];
    FILE* fptr;
    int data_size = image.size - 54;
    unsigned char bmp_header[] = {
              0x42,0x4D,
              (unsigned char)image.size, (unsigned char)(image.size >> 8), (unsigned char)(image.size >> 16),(unsigned char)(image.size >> 24),
              0x00,0x00,0x00,0x00,
              0x36,0x00,0x00,0x00,
              0x28,0x00,0x00,0x00,
              (unsigned char)image.width,(unsigned char)(image.width >> 8),  (unsigned char)(image.width >> 16),(unsigned char)(image.width >> 24),
              (unsigned char)image.height,(unsigned char)(image.height >> 8),  (unsigned char)(image.height >> 16),(unsigned char)(image.height >> 24),
              0x01,0x00,0x18,0x00,
              0x00,0x00,0x00,0x00,
              (unsigned char)data_size,(unsigned char)(data_size >> 8),(unsigned char)(data_size >> 16),(unsigned char)(data_size >> 24),
              0x00,0x00,0x00,0x00,
              0x00,0x00,0x00,0x00,
              0x00,0x00,0x00,0x00,
              0x00,0x00,0x00,0x00
    };
    strcpy(fileCopy, image.file_name);
    fptr = fopen(fileCopy, "wb");
    if (NULL == fptr)
    {
        printf("\n File cannot be saved.");
        return 1;
    }
    fwrite(bmp_header, 1, 54, fptr);
    for (unsigned i = 0; i < image.height; ++i)
    {
        for (unsigned j = 0; j < image.width; ++j)
        {
            fwrite(&(image.pixels[i][j].blue), 1, 1, fptr);
            fwrite(&(image.pixels[i][j].green), 1, 1, fptr);
            fwrite(&(image.pixels[i][j].red), 1, 1, fptr);
        }
    }

    fclose(fptr);
    return 0;
}

void free_pixels(RGB_Image image_ptr)
{
    for (unsigned i = 0; i < image_ptr.height; ++i)
    {
        free(image_ptr.pixels[i]);
    }
    free(image_ptr.pixels);
}