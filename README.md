## MAAS
### Overview
Multimodel-based Analysis of scATAC-Seq (MAAS) is a method for idenfication of tumor subpopulations based on single-cell
chromatin data.

<p align="center">
<img src="https://github.com/Larrycpan/MAAS/blob/main/docs/figure/Figure%201.png" width="500", height = 600>
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
