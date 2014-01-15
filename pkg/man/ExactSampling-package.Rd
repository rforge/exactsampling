\name{ExactSampling-package}
\alias{ExactSampling-package}
\alias{ExactSampling}
\docType{package}
\title{
ExactSampling: risk evaluation using exact resampling
methods for the k Nearest Neighbor algorithm
}
\description{
ExactSampling contains functions that estimate the risk associated to a \emph{k}NN prediction function (either in regression or binary classification) based on resampling method (leave-\emph{p}-out cross-validation or bootstrap). It also contain a function \code{knn.search} to obtain the list of \emph{k} nearest neighbors for each point in the sample, and a function to compute the empirical risk of a \emph{k}NN prediction function. 
}
\details{
\tabular{ll}{
Package: \tab ExactSampling\cr
Type: \tab Package\cr
Version: \tab 1.0\cr
Date: \tab 2013-01-22\cr
License: \tab GPL(>=2)\cr
}
% An overview of how to use the package, including the most important functions 
}
\author{
KAI LI
Maintainer: Koskas Michel<Michel.Koskas@agroparistech.fr>
}
\references{
Celisse, A.and Mary-Huard, T. (2011) Exact Cross-Validation for kNN and applications to passive and active learning in classification. \emph{Journal de la SFdS}, \bold{152, 3.}}

\keyword{ \emph{k}NN algorithm, cross-validation, bootstrap}
\seealso{
\code{knn.emp} for the empirical estimation of the risk, \code{knn.boot} for an exact bootstrap estimation, \code{knn.cv} for the cross-validated estimation for the \emph{k}NN algorithm, and \code{knn.search} to obtain the \emph{k} nearest neighbors. }

%\examples{
%~~ simple examples of the most important functions ~~
%}
