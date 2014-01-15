\name{knn.emp}
\alias{knn.emp}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
 Computing Empirical Risk for the kNN Algorithm
}
\description{
knn.emp is used to compute the empirical estimator of the risk for the \emph{k}NN and weighted \emph{k}NN algorithms. Neighbors are obtained using the canonical Euclidian distance. In the classification case predicted labels are obtained by (possibly weighted) majority vote. The risk is computed using the 0/1 hard loss function. When ties occur a value of 0.5 is returned for the risk. In the regression case predicted labels are obtained by (possibly weighted) averaging. The risk is computed using the quadratic loss function. 
}
\usage{
knn.emp(data, label, k, weight = NULL, alpha = NULL, method)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{data}{
an input data.frame or matrix where each line corresponds to an observation.
}
  \item{label}{
a column vector containing the labels. If \code{method='regression'} \code{label} must be numeric. If \code{method='classification'} \code{label} may be a factor, numeric or character variable with only 2 different values.
}
  \item{k}{
the number of neighbors to be considered.
}
  \item{weight}{
an optional matrix containing positive weights. For each observation, the corresponding list of weights is given in row, according to the ordering of the sample. 
}
 
  \item{alpha}{
an optional parameter. If given, the weighted \emph{k}NN algorithm is performed, where the weight of observation \emph{j} in the prediction rule to predict the label of point \emph{i} is 0 if \emph{j} does not belong to the \emph{k} nearest neighbors of \emph{i}, and is inversely proportional to the Euclidian distance between \emph{i} and \emph{j} to the power alpha otherwise. Only available when \code{weight=NULL}.
}
  \item{method}{
\code{"classification"} or \code{"regression"}
}

}

\value{
\code{knn.emp} returns a list containing the following two components:
\item{risk}{value of the empirical risk} 
\item{error.ind}{vector containing the individual empirical risk for each observation}
}

\references{
 Celisse, A.and Mary-Huard, T. (2011) Exact Cross-Validation for kNN and applications to passive and active learning in classification. \emph{Journal de la SFdS}, \bold{152, 3.}
}

\author{
The function has been implemented by Kai Li, based on Celisse and Mary-Huard (2011).
}

\seealso{
\code{knn.cv} for a cross-validated estimation of the risk, \code{knn.boot} for an exact bootstrap estimation, and \code{knn.search} to obtain the \emph{k} nearest neighbors.
}
\examples{
data(Spam)
# Empirical risk, classification case
spam.label <- Spam[,58]
spam.data <- Spam[,-58]
res.knn.emp <- knn.emp(data = spam.data, label = spam.label, k = 7, method = "classification")

}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
%\keyword{ ~kwd1 }
%\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
