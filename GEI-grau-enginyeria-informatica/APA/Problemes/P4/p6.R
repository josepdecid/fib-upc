N <- 5
data <- matrix(c(2.70, 48, 2.00, 67, 1.61, 83, 1.20, 108, 1.02, 126),
               nrow = N, byrow = TRUE)
r <- data[,1]
phi <- data[,2] * pi / 180

# 1*p
Phi.p <- rep(1, N)
# r*cos(phi)*e
Phi.e <- r * cos(phi)

Phi <- matrix(c(Phi.p, Phi.e), nrow = N, byrow = FALSE)

df <- data.frame(data = Phi, r = r)
names(df)[1:2] <- c('p', 'e')
# r ~ e ≡ r ~ e + p - 1 
(model <- glm(formula = r ~ e, data = df, family = gaussian))

# Plot the data
p <- model$coefficients[1]
e <- model$coefficients[2]
data.plot <- cbind(data[,2], r)
plot(data.plot, xlab = 'phi', ylab = 'r')
curve(expr = p / (1 - e*cos(x * pi / 180)), add = TRUE,
      col = "violet", lwd = 2, from = 40, to = 130)
grid()

# Moore-Penrose inverse
# MP <- ginv(Phi, tol = sqrt(.Machine$double.eps))
# (w <- MP %*% r)
# Same result!
