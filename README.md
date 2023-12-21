## MAAS

### Overview
Model-based Analysis of scATAC-Seq (MAAS) is a method for idenfication of tumor subpopulations based on single-cell
chromatin data.

To use MAAS functions for integration, please run the following commands in __R__.
```
for (i in list.files("./function/", pattern=".cpp$")) {
  sourceCpp(paste0("./function/", i))
}
```

The key step of MAAS is integration, which is applied in a one-line-command
```
maas_res <- MAAS(peak.similarity, cnv.similarity, snv.similarity, dims = 2:5)
```
Documentation and tutorials (full data preparation and integration) can be found at <xxx>. The example data has been uploaded to [Zenodo](https://zenodo.org/)(doi: 10.5281/zenodo.10355916)

We provide the source code of SNV calling and MAAS in the github repository, including peak adjusting and multimodal integration.
To perform SNV RPCA analysis, you should install [Matlab](https://www.mathworks.com/products/matlab.html) in advance, which always finishes in a few seconds. 
This step is optional for users that raw SNV matrix is also adopted by MAAS.

In addition, we highly recommend installing [openBLAS](https://github.com/OpenMathLib/OpenBLAS) to speed matrix operations, before starting your MAAS analysis.

| :boom:| If you choose to install openBLAS, MAAS integration may take lots of memories of your system.|
|---------------|:------------------------|

### Getting help

If you encounter a bug or have a feature request, please open an [Issues](https://github.com/Larrycpan/MAAS/issues).

If you would like to discuss questions related to single-cell analysis,
you can open a [Discussions](https://github.com/Larrycpan/MAAS/discussions).

### Citation

If you use data preparation schemes or MAAS in your work, please cite <xxx>.

### Related packages
-   [ArchR](https://www.archrproject.com/)
-   [epiAneufinder](https://github.com/colomemaria/epiAneufinder)
