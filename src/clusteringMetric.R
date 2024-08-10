clusteringMetric <- function(D, clu, disMethod = c("cosine", "hamming", "euclidean")){
  
  require(clusterSim)
  require(parallelDist)
  require(fpc)
  require(clValid)
  
  dis <- parDist(as.matrix(D), method = disMethod, threads = 40)
  
  silwidth_c <- fpc::cluster.stats(d = dis, clustering= clu)$avg.silwidth
  dbi_c <- clusterSim::index.DB(x = D, cl = clu, d = dis, centrotypes = "medoids")$DB
  dvi_c <- clValid::dunn(distance = dis, clusters = clu)

  chi <- function(X, clusters){
    clusters_n <- length(unique(clusters))
    samples_n <- nrow(X)
    X_mean <- apply(X, 2, mean)
    ex_disp <- c()
    in_disp <- c()
    for (i in c(1:clusters_n)){
      cluster_k <- X[which(clusters == i),]
      mean_k <- apply(cluster_k, 2, mean)
      a1 <- nrow(cluster_k) * sum((mean_k - X_mean)^2)
      ex_disp <- c(ex_disp, a1)
      a2 <- sum((t(t(cluster_k) - mean_k))^2)
      in_disp <- c(in_disp, a2)
    }

    k1 <- sum(ex_disp)
    k2 <- sum(in_disp)
    if (k2 == 0){
      return(1)
    }
    else{
      return((k1 * (samples_n - clusters_n))/(k2 * (clusters_n - 1)))
    }
  }

  chi_c <- chi(D, clusters = clu)

  Comb_index <- (silwidth_c / dbi_c) * dvi_c * chi_c
  # Comb_index <- silwidth_c * dvi_c / dbi_c
  
  return(Comb_index)
}



