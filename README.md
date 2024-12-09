# RGBFilters

To run the comparison of each one of the filters: `GrayscaleFilter`. `GaussianBlurFilter`, `MedianFilter` & `SoftEdgeDetectionFilter`, we must use their respective 'main' files. 
- We first compile the `Pixel` and `Image` fies:
```bash
g++ Pixel.cpp Image.cpp
```
- Now we compile the respective filter with its respective 'main' file. We will use the GaussianBlur filter for this purpose. IMPORTANT -> You must have the OpenMP library installed in your respective C++ compiler:
```bash
g++ -fopenmp Pixel.cpp Image.cpp GaussianBlur.cpp GaussianBlurMain.cpp -o gaussian-blur-main
```
- We run the program we have compiled:
```bash
./gaussian-blur-main
```
- The output we get will depend on the filter used and the filtered images will be sent to an ouput folder. You will have to create the /ouput folder in the current working directory where you run the command:
```bash
Processing: images/large.ppm
Sequential: 1432ms
Parallel: 395ms
Speedup: 3.62226x
Writing to file: output/blurred_large.ppm

Processing: images/medium.ppm
Sequential: 191ms
Parallel: 73ms
Speedup: 2.61634x
Writing to file: output/blurred_medium.ppm

Processing: images/really_large.ppm
Sequential: 2286ms
Parallel: 674ms
Speedup: 3.38895x
Writing to file: output/blurred_really_large.ppm

Processing: images/small.ppm
Sequential: 224ms
Parallel: 43ms
Speedup: 5.1692x
Writing to file: output/blurred_small.ppm

Median Speedup: 3.50561x
```

```bash
output
├── blurred_large.ppm
├── blurred_medium.ppm
├── blurred_really_large.ppm
└── blurred_small.ppm
```
