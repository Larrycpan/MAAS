## MAAS

### Overview
Model-based Analysis of scATAC-Seq (MAAS) is a method for idenfication of tumor subpopulations based on single-cell
chromatin data. MAAS is easy to use, which includes peak adjusting and multimodal integration.

To use MAAS functions for integration, please source the Rcpp code.
```
for (i in list.files("./function/", pattern=".cpp$")) {
  sourceCpp(paste0("./function/", i))
}
```

Documentation and tutorials (data preparation and integration) can be found at <xxx>.

### Getting help

If you encounter a bug or have a feature request, please open an [issue](https://github.com/Larrycpan/MAAS/issues).

If you would like to discuss questions related to single-cell analysis,
you can open a [discussion](https://github.com/Larrycpan/MAAS/discussions).

### Citation

If you use data preparation schemes or MAAS in your work, please cite <xxx>.

### Related packages
-   [ArchR](https://www.archrproject.com/)
-   [epiAneufinder](https://github.com/colomemaria/epiAneufinder)
