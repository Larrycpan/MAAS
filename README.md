## MAAS
### Overview
Single-cell multimodal analysis enables highly accurate delineation of clinically relevant tumor cell subpopulations

<p align="center">



<img src="http://bioinfo.szbl.ac.cn/share/MAAS_data/Figure 1.png" alt="Flowchart" style="width: 70%">

<p align="center">

### Quick start
To use MAAS functions for integration, please run the following commands in __R__. We provide example data of cell similarities for the three modalities formatted as `list` R object.
```
library(Rcpp)
for (i in list.files("./src/", pattern="MAAS*")) {
  sourceCpp(paste0("./src/", i))
}

data <- readRDS("example.data/example.similarity.rds")
maas.test <- MAAS(data$Peak, df$CNV, df$SNV, dims = 2:5)
saveRDS(maas.test, "maas.res.all.rds")
```

```
# Then we can do clustering based on the consensus latent factors
#### Determine the optimal clustering strategy
maas.res <- readRDS("maas.res.test.rds")
barcode.list <- rownames(data$Peak)
set.seed(1)
barcode.list <- sample(barcode.list, 400)

#### Using the optimal clustering strategy
clusPerformance <- data.frame(matrix(nrow = length(maas.res)-1, ncol = 5),
                              row.names = paste0("dims=", 2:length(maas.res)))
colnames(clusPerformance) <- paste0("k=", 2:6)
for(i in 1:(length(maas.res)-1)){
  for(j in 2:6){
    df <- as.data.frame(maas.res[[i]]$W)
    rownames(df) <- barcode.list
    maas.tmp.clu <- withr::with_seed(2, kmeans(df, centers = j)$cluster)
    clusPerformance[i,j-1] <- clusteringMetric(maas.res[[i]]$W, clu = maas.tmp.clu, disMethod = "cosine")
  }
}

#### Re-running clustering with the optimal performance
df <- as.data.frame(maas.res[[4]]$W)
rownames(df) <- barcode.list
maas.clu <- data.frame(Cluster = withr::with_seed(2, kmeans(df, centers = 2)$cluster))
maas.clu$Cluster <- as.factor(maas.clu$Cluster)
saveRDS(ataclone.clu, "example.MAAS.clu.rds")

#### Visualization
umap.axis <- withr::with_seed(2, uwot::umap(df, n_neighbors = 50, metric = "manhattan", min_dist = 0.1, n_threads = 30))
umap.axis <- as.data.frame(umap.axis); umap.axis$Cluster <- ataclone.clu$Cluster
colnames(umap.axis) <- c("UMAP-1", "UMAP-2", "Cluster")
ggplot(umap.axis, aes(`UMAP-1`, `UMAP-2`))+
  geom_point(aes(color = Cluster), size = 1.75)+
  scale_color_manual(values = my_color)+
  theme_dr()+
  labs(x = "UMAP-1", y = "UMAP-2")+
  theme(panel.grid = element_blank(),
        axis.title = element_text(size = 14),
        axis.text = element_blank(),
        legend.text = element_text(size = 12))
```

<img src="http://bioinfo.szbl.ac.cn/share/MAAS_data/HCC.MAAS.cluster.umap.png" alt="Flowchart" style="width: 70%">

Documentation and tutorials (full data preparation and integration) can be found at <https://larrycpan.github.io/MAAS/>. The example data has been uploaded to the folder example.data, which is the input for the [Running MAAS](https://larrycpan.github.io/MAAS/6.MAAS.html).

We provide the source code of SNV calling and MAAS in the github repository, including peak adjusting and multimodal integration.
To perform SNV RPCA analysis, you should install [Matlab](https://www.mathworks.com/products/matlab.html) in advance, which always finishes in a few seconds. 
This step is optional for users that raw SNV matrix is also adopted by MAAS.

In addition, we highly recommend installing [openBLAS](https://github.com/OpenMathLib/OpenBLAS) to speed matrix operations, before starting your MAAS analysis.

### Getting help

If you encounter a bug or have a feature request, please open an [Issues](https://github.com/Larrycpan/MAAS/issues).

If you would like to discuss questions related to single-cell analysis,
you can open a [Discussions](https://github.com/Larrycpan/MAAS/discussions).


### Related packages
-  [Signac](https://stuartlab.org/signac/)
-  [epiAneufinder](https://github.com/colomemaria/epiAneufinder)
-  [SComatic](https://github.com/cortes-ciriano-lab/SComatic)
