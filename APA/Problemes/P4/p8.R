data <- matrix(c(1970:1979, 9, 9, 10, 10, 8, 6, 6, 4, 6, 4), nrow = 10)
data[,2] <- data[,2] * 1000

sample <- data.frame(x = phi, t = data[,1])
model <- glm(t ~ x.2 + x.1 - 1, data = sample, family = gaussian)