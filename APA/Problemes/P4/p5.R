library('MASS')

N <- 5
data <- matrix(c(-1, 2, 1, 1, 2, 1, 3, 0, 5, 3), nrow = N, byrow = TRUE)
x <- data[,1]
t <- data[,2]

# Phi_j = x^j
Phi <- matrix(c(x^0, x^1, x^2), nrow = N)

# Tolerancy as the smallest positive floating-point number
MP <- ginv(Phi, tol = sqrt(.Machine$double.eps))

# Weights w0 w1 and w2
(w <- MP %*% t)

# Plot the data
plot(data, xlab = 'x', ylab = 't')
curve(expr = w[1] + w[2]*x + w[3]*x^2, add = TRUE, col = "violet",
      lwd = 2, from = -2, to = 6)
grid()