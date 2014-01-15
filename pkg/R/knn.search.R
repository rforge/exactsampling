knn.search <-
function(data=numeric(),k=1)
{
  if (is.numeric(k))
  {
    data=as.matrix(data)
    nrow=dim(data)[1]
    ncol=dim(data)[2]
    if (k >= nrow)
      {
        stop("Wrong choice of parameters : k should be smaller than the number of observations.")
      }
    if (k < 0)
      {
        stop("Parameter k  must be positive.")
      }
    dataV=as.vector(t(data),"numeric")
    listindex=rep(1,nrow*k)
    listdist=rep(1,nrow*k)
    index<-.C("knn_index",l = as.double(dataV), taille=as.integer(nrow)
              ,dimension=as.integer(ncol) ,kn=as.integer(k),lindex=as.integer(listindex),
              ldist=as.double(listdist),
              package="ExactSampling")
    Mdist=matrix(index$ldist,byrow=T,ncol=k)
    Mindex=matrix(index$lindex,byrow=T,ncol=k)
    list("index"=Mindex,"dist"=Mdist)
  }
  else if (is.numeric(k)){stop("Parameter k must be integer")}
}
