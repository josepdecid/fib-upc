library(datasets)
library(caTools)
library(ggplot2)
library(caret)
library(doMC)

registerDoMC(cores = 4)

data(rock)
rock.df <- data.frame(area  = scale(rock$area),
                      perim = scale(rock$peri),
                      shape = scale(rock$shape),
                      perm  = log(rock$perm))

split = sample.split(rock.df$perm, SplitRatio = 0.8)
training.set = subset(rock.df, split == TRUE)
test.set = subset(rock.df, split == FALSE)

trc <- trainControl(method = 'LOOCV')
sizes <- seq(1, 15, by = 1)
decays <- 10^seq(-3, 0, by = 0.2)
nnet.model <- train(perm ~ .,
                    data = training.set,
                    linout = TRUE, trace = FALSE,
                    method = 'nnet', metric = 'RMSE',
                    trControl = trc, maxit = 2000,
                    tuneGrid = expand.grid(.size = sizes,
                                           .decay = decays))
pred <- predict(nnet.model, newdata = test.set)

(best <- nnet.model$bestTune)
(rmse <- nnet.model$results[as.numeric(row.names(best)),]$RMSE)

ggplot(test.set, aes(x = perm, y = pred)) +
  geom_point() +
  geom_smooth(method = 'lm', col = 'darkred') + 
  ggtitle('Actual vs Predicted (NN)') +
  theme(legend.position="none") +
  xlab('Actual') + ylab('Predicted')
