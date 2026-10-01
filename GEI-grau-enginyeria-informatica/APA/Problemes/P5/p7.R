library(caret)
library(doMC)

registerDoMC(cores = 4)

letters.df <- read.table('letters.txt')

corrupt <- function(bits) {
  rand.corrupt <- min(rpois(1, lambda = 1.01), 35)
  change.pos <- sample(35, size = rand.corrupt)
  mask <- rep(0, times = 35)
  mask[change.pos] <- 1
  changed.bits <- xor(as.numeric(bits[1:35]), mask)
  corrupted <- c(as.numeric(changed.bits), bits[36])
  return(corrupted)
}

generateCorrupt <- function(df, n) {
  idx <- sample(1:nrow(df), n, replace = TRUE)
  new.data <- t(apply(df[idx,], MARGIN = 1, FUN = corrupt))
  new.data <- data.frame(new.data)
  rownames(new.data) <- seq(1:n)
  colnames(new.data) <- c(1:35, "letter")
  new.data$letter <- as.factor(new.data$letter)
  return(new.data)
}

training.set <- generateCorrupt(letters.df, 1500)
test.set <- generateCorrupt(letters.df, 500)

sizes <- seq(1, 16, by = 1)
decays <- 10^seq(-3, 0, by = 0.2)
trc <- trainControl(method = 'repeatedcv',
                    number = 10,
                    repeats = 5)
nnet.model <- train(letter ~ .,
                    data = training.set, trace = FALSE,
                    method = 'nnet', metric = 'Accuracy',
                    trControl = trc, maxit = 500,
                    tuneGrid = expand.grid(.size = sizes, .decay = decays))
pred <- predict(nnet.model, newdata = test.set)

(best <- nnet.model$bestTune)
(conf <- confusionMatrix(test.set$letter, pred))
