\name{knn.cv}
\alias{knn.cv}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Computing Cross-validated Risk for the kNN Algorithm
}
\description{
knn.cv is used to compute the Leave-\emph{p}-Out (L\emph{p}O) cross-validation estimator of the risk for the \emph{k}NN algorithm. Neighbors are obtained using the canonical Euclidian distance. In the classification case predicted labels are obtained by majority vote. The risk is computed using the 0/1 hard loss function, and when ties occur a value of 0.5 is returned.  In the regression case predicted labels are obtained by averaging. The risk is computed using the quadratic loss function. 
}
\usage{
knn.cv(data, label, k, p = 1, method)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{data}{
 an input data.frame or matrix Where each line corresponds to an observation.
}
  \item{label}{
a vector containing labels. If \code{method='regression'}  then \code{label} must be numeric. If \code{method='classification'} then \code{label} may be a factor, numeric or character variable with only 2 different values.
}
  \item{k}{
  the number of neighbors to be considered. 
}
  \item{p}{
leave-\emph{p}-out parameter. Each resampling splits the sample into a training sample of size \emph{n-p} and a validation sample of size \emph{p}. 
}
  \item{method}{
"classification" or "regression"
}
}
\value{
\code{knn.cv} returns a list containing the following two components:
\item{risk}{value of the risk evaluated by L-\emph{p}O cross-validation}
\item{error.ind}{vector containing the individual risk for each observation.}  
}
\references{
 Celisse, A.and Mary-Huard, T. (2011) Exact Cross-Validation for kNN and applications to passive and active learning in classification. \strong{Journal de la SFdS}, \bold{152}, 3. 
}

\author{
The function has been implemented by Kai Li, based on Celisse and Mary-Huard (2011).
}

\note{
For a given Value of parameter \emph{k}, only values of parameter \emph{p} satisfying \eqn{k+p \leq n} are admissible. 
}


%% ~Make other sections like Warning with \section{Warning }{....} ~

\seealso{
\code{knn.emp} for empirical estimation of the risk and \code{knn.boot} for an exact bootstrap estimation, and \code{knn.search} to obtain the \emph{k} nearest neighbors. }
\examples{
data(Spam)
spam.label <- Spam[,58]
spam.data <- Spam[,-58]

# Using the spam dataset
names(spam.data)
table(spam.label)

# LpO cross-validation
res.knn.cv <- knn.cv(data = spam.data, label = spam.label, k = 7, p = 12, method = "classification")
res.knn.cv$risk
head(res.knn.cv$error.ind)

}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
%\keyword{ ~kwd1 }
%\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
