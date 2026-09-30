N <- 1000
Mu <- c(0, 5, 2)
Sigma <- cbind(
  c(25, -1, 7),
  c(-1, 4, -4),
  c(7, -4, 10)
)

library('MASS')
X <- mvrnorm(n = 1000, mu = Mu, Sigma = Sigma)

# install.packages('rgl')
library('rgl')
plot3d(X)

ev <- eigen(Sigma)
eigenvalues <- ev$values
eigenvectors <- ev$vectors

PCA <- prcomp(X)

PCA.PC1 <- PCA$x[,1]
PCA.slope1 <- PCA$rotation[2,1] / PCA$rotation[1,1]

PCA.PC2 <- PCA$x[,2]
PCA.slope2 <- PCA$rotation[2,2] / PCA$rotation[1,2]

PCA.PC3 <- PCA$x[,3]
PCA.slope3 <- PCA$rotation[2,3] / PCA$rotation[1,3]

plot(x = PCA.PC1, xlab = "PC1", y = PCA.PC2, ylab = "PC2")
plot(x = PCA.PC1, xlab = "PC1", y = PCA.PC3, ylab = "PC3")
plot(x = PCA.PC2, xlab = "PC2", y = PCA.PC3, ylab = "PC3")