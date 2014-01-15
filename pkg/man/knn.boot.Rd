\name{knn.boot}
\alias{knn.boot}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Computing Exact or Epsilon- Bootstrap Risk Estimator for the kNN Algorithm.
}
\description{
knn.boot is used to compute the exact or Epsilon- bootstrap estimator of the risk for the \emph{k}NN algorithm in binary classification. Neighbors are obtained using the canonical Euclidian distance. Predicted labels are obtained by majority vote. The risk is computed using the 0/1 hard loss function, and when ties occur a value of 0.5 is returned.    
}
\usage{
knn.boot(data = numeric(), label, k = numeric(), epsilon = 0)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{data}{
an input data.frame or matrix Where each line corresponds to an observation.
}
  \item{label}{
a vector containing labels. \code{label} may be a factor, numeric or character variable with at most 2 different values.
}
  \item{k}{
the number of neighbors to be considered. 
}
  \item{epsilon}{
required precision level for the bootstrap approximation. If \code{epsilon=0} (default) the exact bootstrap is computed.
}
}

\details{
 knn.boot computes the "exact" bootstrap estimator, meaning that all resamplings with replacement of the initial dataset are considered. The epsilon-bootstrap provides an approximated value of the previous "exact" estimator by discarding resamplings with associated low probabilities. This last strategy is recommended for large sets of data for which exact resampling may be time consumming.
}

\value{
\code{knn.cv} returns a list containing the following two components:
\item{risk}{value of the risk evaluated by exact or approximated bootstrap} 
\item{error.ind}{vector containing the individual risk for each observation}
}

\author{
The function has been implemented by Kai Li, based on Celisse and Mary-Huard (2011).
}

\section{warning}{
Exact bootstrap requires intensive computational time and should be applied to small datasets only (\emph{n<200})
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\seealso{
\code{knn.emp} for empirical estimation of the risk and \code{knn.cv} for an exact cross-validated estimation, and \code{knn.search} to obtain the \emph{k} nearest neighbors.
}

\examples{
data(Spam)
spam.label <- Spam[1:20,58]
spam.data <- Spam[1:20,-58]

# Using the spam dataset
names(spam.data)
table(spam.label)

# Exact bootstrap
knn.boot(data = spam.data, label = spam.label, k = 7)

# epsilon-bootstrap
knn.boot(data = spam.data, label = spam.label, k = 7, epsilon = 0.01)
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
%\keyword{ ~kwd1 }
%\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
