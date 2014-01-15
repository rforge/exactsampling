\name{Spam}
\alias{Spam}
\docType{data}
\title{
Spam Example Dataset
}
\description{
The spam dataset is available and fully described on the UCI spambase directory, and has been used for instance in Hastie et al. (2001). The dataset is a collection of 4601 spam and non-spam e-mails, described by 57 continuous variables (and the nominal class label).
}
\usage{
data(Spam)
}

\details{ 
 A data frame with 4601 observations on the following 58 variables:\cr
 \itemize{
 \item{\code{[,1:57]}}{ numeric Descriptors of the email contents, mostly word or character appearance percentage. See the UCI spambase directory for more information. }
 \item{\code{[,58]}}{ factor  Labels: regular (0) or spam (1) email.}
  }
}
%\details{
%%  ~~ If necessary, more details than the __description__ above ~~
%}
\source{
UCI spambase directory : \cr
\url{ftp://ftp.ics.uci.edu/pub/machine-learning-databases/spambase/}
}
\references{
 Hastie, T. Tibshirani, R. and Friedman, J. (2001) Chapter 9 of \emph{The Elements of Statistical Learning: Data Mining, Inference, and Prediction}, eds Springer, New York
}
\examples{
data(Spam)
}
\keyword{datasets}
