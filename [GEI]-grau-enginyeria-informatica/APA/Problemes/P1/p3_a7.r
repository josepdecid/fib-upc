M <- 1000
N <- 50
mu <- 42
sigma <- 0.42
sigma.square <- sigma ^ 2

gaussian.generator <- function() {
  return(rnorm(n = N, mean = mu, sd = sigma))
}
l <- replicate(n = M, expr = gaussian.generator(), simplify = F)

l.mu <- sapply(X = l, FUN = "mean")
l.sigma.square <- sapply(X = l, FUN = "var")

mu.bias <- mean(l.mu) - mu
mu.var <- var(l.mu)

sigma.square.bias <- mean(l.sigma.square) - sigma.square
sigma.square.var <- var(l.sigma.square)
