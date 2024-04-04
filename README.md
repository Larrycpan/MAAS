## MAAS
### Overview
Multimodal-based Analysis of scATAC-Seq (MAAS) is a method for idenfication of tumor subpopulations based on single-cell
chromatin data.

<p align="center">



<img src="https://private-user-images.githubusercontent.com/27127316/319435747-c192b126-2414-47d6-b603-e5234b370b43.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MTIyMDMyMjksIm5iZiI6MTcxMjIwMjkyOSwicGF0aCI6Ii8yNzEyNzMxNi8zMTk0MzU3NDctYzE5MmIxMjYtMjQxNC00N2Q2LWI2MDMtZTUyMzRiMzcwYjQzLnBuZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNDA0MDQlMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjQwNDA0VDAzNTUyOVomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPTk4NmJmNjYzNTkzZGFmMzA5NTk3NDdhNTZkMjQyNWY4YjY0YmZlZDc5NzBkN2U3ZTc3YTVjYjk3ZTVlYzRmY2EmWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0JmFjdG9yX2lkPTAma2V5X2lkPTAmcmVwb19pZD0wIn0.H3ze3ZEcy8RQKYu933c-efOqbHRQTFMFNVuesSjPBcc" alt="Flowchart" width="500", height = 600>

<p align="center">

To use MAAS functions for integration, please run the following commands in __R__.
```
library(Rcpp)
for (i in list.files("./src/", pattern="MAAS*")) {
  sourceCpp(paste0("./src/", i))
}
```

The key step of MAAS is integration, which is applied in a one-line-command
```
maas_res <- MAAS(peak.similarity, cnv.similarity, snv.similarity, dims = 2:5)
```
Documentation and tutorials (full data preparation and integration) can be found at <https://larrycpan.github.io/MAAS/>. The example data has been uploaded to the folder example.data, which is the input for the [Running MAAS](https://larrycpan.github.io/MAAS/6.MAAS.html). If you would like to go through the whole analysis including data preparation, you can download data from [Zenodo](https://zenodo.org/) (doi: 10.5281/zenodo.10355916).

We provide the source code of SNV calling and MAAS in the github repository, including peak adjusting and multimodal integration.
To perform SNV RPCA analysis, you should install [Matlab](https://www.mathworks.com/products/matlab.html) in advance, which always finishes in a few seconds. 
This step is optional for users that raw SNV matrix is also adopted by MAAS.

In addition, we highly recommend installing [openBLAS](https://github.com/OpenMathLib/OpenBLAS) to speed matrix operations, before starting your MAAS analysis.

### Getting help

If you encounter a bug or have a feature request, please open an [Issues](https://github.com/Larrycpan/MAAS/issues).

If you would like to discuss questions related to single-cell analysis,
you can open a [Discussions](https://github.com/Larrycpan/MAAS/discussions).

### Citation

If you use data preparation schemes or MAAS in your work, please cite <xxx>.

### Related packages
-   [ArchR](https://www.archrproject.com/)
-   [epiAneufinder](https://github.com/colomemaria/epiAneufinder)
