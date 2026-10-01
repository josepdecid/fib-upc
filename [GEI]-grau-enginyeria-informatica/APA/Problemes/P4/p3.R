energy = c(2.899, 3.484, 3.984, 4.444, 4.831, 5.376, 6.211, 7.576, 11.905, 16.667 )
st = c(367 ,311 ,295, 268, 253, 239, 220, 213, 193, 192)
sd = c(17, 9, 9, 7, 7, 6, 6, 6, 5, 5)

energy.inv = 1 / energy
w = 1 / sd^2

df = data.frame(energy.inv, st)
model.weighted = glm(formula = st ~ energy.inv, weights = w, data = df, family = gaussian)
model.unweight = glm(formula = st ~ energy.inv, data = df, family = gaussian)

plot(energy.inv, st, xlab = 'Inversa energia', ylab = 'Seccio transversal')
abline(model.weighted$coefficients[1], model.weighted$coefficients[2], col = "green")
abline(model.unweight$coefficients[1], model.unweight$coefficients[2], col = "blue")
