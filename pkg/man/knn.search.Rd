\name{knn.search}
\alias{knn.search}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Search Nearest Neighbors
}
\description{
Return index and distance for the \emph{k} nearest neighbors of each observation. Neighbors are obtained using the canonical Euclidian distance.
}
\usage{
knn.search(data, k =1)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{data}{
an input data.frame or matrix Where each line corresponds to an observation.
}

  \item{k}{
the maximum number of nearest neighbors to search.
}
}
\details{
Neighbors are found using the \code{kd-tree} algorithm.
}
\value{
 \item{index}{an \emph{n x k} matrix of nearest neighbor indices.}
 \item{dist}{  
an \emph{n x k} matrix of nearest neighbor distances.} 
}
\author{
The function has been implemented by Kai Li.
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\seealso{
\code{knn.emp} for empirical estimation of the risk, \code{knn.boot} for an exact bootstrap estimation, and \code{knn.cv} for cross-validated estimation for the \emph{k}NN algorithm. 
}

\examples{
data(Spam)
spam.data <- Spam[,-58]
knn.search(data=spam.data,k=7)
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
%\keyword{ ~kwd1 }
%\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
