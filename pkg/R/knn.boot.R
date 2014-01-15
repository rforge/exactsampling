knn.boot <-
function(data=numeric(),label, k=numeric(),epsilon=0){
  data=as.matrix(data)
  nrows<-dim(data)[1]
  ncols<-dim(data)[2]
  if (sum(apply(data,2,is.numeric))!=ncols)
  {
    stop("Data must be numeric.")
  }
  if (k < 0)
  {
    stop("Parameter k  must be positive.")
  }
  if (k >= nrows){
    stop("Wrong choice of parameters : k should be smaller than the number of observations.")
  }
  if (nrows != length(label)){
    stop("The number of labels must be same as the number of observations in 'data'")
  }
  if (length(unique(label)) != 2){stop('Labels must be binary.')}
  labelA<-label[1]
  i<-1
  while (labelA == label[i])
  {
    i=i+1
  }
  label01=label
  labelB<-label[i]
  label01[which(label==labelA)]=1
  label01[which(label==labelB)]=0
 
  risque<-0
  data1<-as.vector(t(data),mode="numeric")
  label1<-as.vector(label01,mode="numeric")
  error<-as.vector(rep(1,nrows),"numeric")
  r<- .C("EBootstrap",l = as.double(data1), lab = as.double(label1), taille = as.integer(nrows), 
         dimension= as.integer(ncols), knb = as.integer(k), eps=as.double(epsilon),Risque=as.double(risque), 
         err=as.double(error), package="ExactSampling")
  list("risk"=r$Risque,"error.ind"=t(r$err))
}
