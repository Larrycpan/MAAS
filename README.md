## MAAS

### Overview
Model-based Analysis of scATAC-Seq (MAAS) is a method for idenfication of tumor subpopulations based on single-cell
chromatin data.

To use MAAS functions for integration, please run the following code in __R__.
```
for (i in list.files("./function/", pattern=".cpp$")) {
  sourceCpp(paste0("./function/", i))
}
```
We provide the source code of SNV calling and MAAS in the github repository, including peak adjusting and multimodal integration. 
In addition, we highly recommend installing [openBLAS](https://github.com/OpenMathLib/OpenBLAS) to speed matrix operations, before starting your MAAS analysis.
> [!CAUTION] 
> If you choose to install openBLAS, MAAS integration may take lots of memories of your system. 

Documentation and tutorials (full data preparation and integration) can be found at <xxx>.

### Getting help

If you encounter a bug or have a feature request, please open an [Issues](https://github.com/Larrycpan/MAAS/issues).

If you would like to discuss questions related to single-cell analysis,
you can open a [Discussions](https://github.com/Larrycpan/MAAS/discussions).

### Citation

If you use data preparation schemes or MAAS in your work, please cite <xxx>.

### Related packages
-   [ArchR](https://www.archrproject.com/)
-   [epiAneufinder](https://github.com/colomemaria/epiAneufinder)
