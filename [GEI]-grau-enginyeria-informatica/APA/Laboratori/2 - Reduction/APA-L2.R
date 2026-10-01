#####################################
## APA Laboratori 2                ##
## Visualització (PCA/FDA)         ##
## version of October, 2017        ## 
#####################################

set.seed(222)
library(MASS)

###########################################################
## Example 1: Comparison between PCA and FDA on 2D toy data
###########################################################

## Fisher's discriminant analysis (FDA) is a method that finds a linear combination of features to project or separate two or more classes of objects

## If your goal is to perform (linear) dimensionality reduction for class discrimination, you should use FDA instead of PCA; PCA is useful for signal representation (but not necessarily for discrimination)

## Sigma is a 2x2 positive-definite symmetric matrix specifying the covariance matrix of two variables

N <- 200

(Sigma <- matrix(data=c(2,1.3,1.3,1),nrow=2,ncol=2,byrow=TRUE))

# these are the eigenvalues:

eigen (Sigma, only.values=TRUE)$values

# Let's create class 1 ('red' class)

mean.1 <- matrix(c(2,0),nrow=2,ncol=1)                         

X.red <- mvrnorm(N,mu=mean.1,Sigma=Sigma)

# Let's create class 2 ('green' class)

mean.2 <- -mean.1

X.green <- mvrnorm(N,mu=mean.2,Sigma=Sigma)

par(mfrow=c(2,2))

plot(c(X.red[,1],X.green[,1]), c(X.red[,2],X.green[,2]), 
     xlim=c(-6,6),ylim=c(-6,6),
     col=c(rep('red',N),rep('green',N)), main="Toy data", xlab="X1", ylab="X2")

# Now we glue both classes one after the other and create a dataframe

d <- data.frame(c(rep(1,N),rep(2,N)), c(X.red[,1], X.green[,1]), c(X.red[,2], X.green[,2]))
colnames(d) <- c("target", "X1", "X2")
d$target <- as.factor(d$target)
summary(d)

# call to FDA (also known as LDA, because it is linear)
myLDA <- lda(d[c(2,3)],d[,1])

# Now we show the best projection direction on the original space. This direction maximizes the separability of the classes. For that, we first need the slope:

LDAslope <- myLDA$scaling[2]/myLDA$scaling[1]

# And now we can perform the visualization:

plot(c(X.red[,1],X.green[,1]), c(X.red[,2],X.green[,2]), col=c(rep('red',N),rep('green',N)),
     xlim=c(-6,6),ylim=c(-6,6),
     main="Direction for projection using FDA", xlab="X1", ylab="X2")

abline(0,LDAslope,col='black',lwd=2)

# We can also compute the projections of the two classes

myLDA.proj <- d[,2] * myLDA$scaling[1] + d[,3] * myLDA$scaling[2]

plot(myLDA.proj, c(rep(0,N),rep(0,N)), col=c(rep('green',N),rep('red',N)),
     main='FDA projection as seen in 1D', xlab="Discriminant", ylab="")

# To understand what is going on, do:

myLDA

# of which ...

myLDA$scaling

# ... are the coefficients of the linear discriminant (w in class)

## So we are projecting the data into the direction that maximizes (linear) separability:

# projection(X) = X1*myLDA$scaling[1] + X2*myLDA$scaling[2]

# Now we compute PCA:
  
myPCA <- prcomp(d[c(2,3)],scale=TRUE)

# Now we need to project the data in the first principal component

d1PCA <- myPCA$x[,1]
PCAslope1 <- myPCA$rotation[2,1]/myPCA$rotation[1,1]

# And now we can perform the visualization:

plot(c(X.red[,1],X.green[,1]), c(X.red[,2],X.green[,2]), col=c(rep('red',N),rep('green',N)),
     xlim=c(-6,6),ylim=c(-6,6),
     main="Direction for projection using PCA", xlab="X1", ylab="X2")

abline(0,PCAslope1,col='black',lwd=2)

# We can see that the FDA projection maximices separability while the PCA projection maximices variability

####################################################################
## Example 2: Visualizing crabs with FDA
####################################################################

# Campbell studied rock crabs of the genus "Leptograpsus" in 1974. One
# species, Leptograpsus variegatus, had been split into two new species,
# previously grouped by colour (orange and blue). Preserved specimens
# lose their colour, so it was hoped that morphological differences
# would enable museum material to be classified.

# Data is available on 50 specimens of each sex of each species (so 200 in total),
# collected on sight at Fremantle, Western Australia. Each specimen has
# measurements on: the width of the frontal lobe (FL), the rear width (RW),
# the length along the carapace midline (CL), the maximum width (CW) of 
# the carapace, and the body depth (BD) in mm, in addition to
# colour (that is, species) and sex.

## the crabs data is also in the MASS package
data(crabs)

## look at data
?crabs
summary(crabs)
head(crabs)

## The goal is to separate the 200 crabs into four classes, given by the 2x2 configurations for sex (Male/Female) and species (Blue/Orange)

Crabs.class <- factor(paste(crabs[,1],crabs[,2],sep=""))

# Now 'BF' stands now for 'Blue Female', and so on
table(Crabs.class)

## using the rest of the variables as predictors (except 'index', which is only an index)
Crabs <- crabs[,4:8]

summary(Crabs)

## Various preliminary plots (notice all 5 predictors are continuous)

par(mfrow=c(1,1))
boxplot(Crabs)

hist(Crabs$FL,col='red',breaks=20,xlab="", main='Frontal Lobe Size (mm)')
hist(Crabs$RW,col='red',breaks=20,xlab="", main='Rear Width (mm)')
hist(Crabs$CL,col='red',breaks=20,xlab="", main='Carapace Length (mm)')
hist(Crabs$CW,col='red',breaks=20,xlab="", main='Carapace Width (mm)')
hist(Crabs$BD,col='red',breaks=20,xlab="", main='Body Depth (mm)')

## Now let's visualize data using FDA

(lda.model <- lda (x=Crabs, grouping=Crabs.class))

plot(lda.model)

## As there are four classes (called 'groups' in LDA), we get three linear discriminants (LDs) for projection (always the number of classes minus 1)
## We first compute the loadings (the 'loadings' are simply the projected data)

## This time we do it more generally, using matrix multiplication

loadings <- as.matrix(Crabs) %*% as.matrix(lda.model$scaling)

## We are performing dimensionality reduction 5D --> 3D, and plotting the projected data into the first two LDs (the 2 most important dimensions)

# We do our own plotting method, with color and legend:

colors.crabs <- c('blue', 'lightblue', 'orange', 'yellow')

crabs.plot <- function (myloadings)
{
  plot (myloadings[,1], myloadings[,2], type="n", xlab="LD1", ylab="LD2")
  text (myloadings[,1], myloadings[,2], labels=crabs$index, col=colors.crabs[unclass(Crabs.class)], cex=.55)
  legend('topright', c("B-M","B-F","O-M","O-F"), fill=colors.crabs, cex=.55)
}

crabs.plot (loadings)

# The result is quite satisfactory, right? We can see that the 5 continuous predictors do indeed represent 4 different crabs. 

# We can also see that crabs of the Blue "variety" are less different 
# (regarding males and females) than those in the Orange variety

## If you would like to keep this new representation for later use (maybe to build a classifier on it), simply do:

Crabs.new <- data.frame (New.feature = loadings, Target = Crabs.class)

summary(Crabs.new)

## Now let's analyze the numerical output of lda() in more detail:

lda.model

# "Prior probabilities of groups" is self-explanatory (these are estimated from the data, but can be overriden by the 'prior' parameter)

# "Group means" is also self-explanatory (these are our mu's)

# "Coefficients of linear discriminants" are the scaling factors we have been using to project data. These have been normalized so that the within-groups covariance matrix is spherical (a multiple of the identity). 

# This means that the larger the coefficient of a predictor,
# the more important the predictor is for the discrimination:

lda.model$scaling

# We can interpret our plot so that the horizontal axis (LD1) separates the groups mainly by using FL, CW and BD;
# the vertical axis (LD2) separates the groups mainly by using RW and some CL, etc

## The "Proportion of trace" is the proportion of between-class variance that is explained by successive discriminants (LDs)

# For instance, in our case LD1 explains 68.6% of the total between-class variance

## In this case, the first two LDs account for 98.56% of total between-class variance, fairly close to 100%

## This means that the third dimension adds but a little bit of discriminatory information. Let's visualize the crabs in 3D:

library(rgl)

# 3D scatterplot (can be rotated and zoomed in/out with the mouse)
plot3d(loadings[,1], loadings[,2], loadings[,3], "LD1", "LD2", "LD3",
       size = 4, col=colors.crabs[unclass(Crabs.class)], main="Crabs Data")

text3d(loadings[,1], loadings[,2], loadings[,3], color = "black", texts=rownames(Crabs.new), adj = c(0.85, 0.85), cex=0.6)
         
## As the measurements are lengths, it could be sensible to take logarithms

(lda.logmodel <- lda (x=log(Crabs), grouping=Crabs.class))

## The model looks a bit better, given that he first two LDs now account for 99.09% of total between-class variance, very good indeed, so a 3D plot does not add anything visual

## As an example, the first (log) LD is given by:
# LD1 = -31.2*log(FL) - 9.5*log(RW) - 9.8*log(CL) + 66*log(CW) - 18*log(BD)

## get the new loadings

logloadings <- as.matrix(log(Crabs)) %*% as.matrix(lda.logmodel$scaling)

## plot the projected data in the first two LDs

crabs.plot (logloadings)

## The first coordinate clearly expresses the difference between species, and the second the difference between sex!
