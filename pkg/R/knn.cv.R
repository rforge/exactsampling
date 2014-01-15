knn.cv <-
function(data=numeric(),label,k, p=1, method=character())
{
  data=as.matrix(data)
  nrows<-dim(data)[1]
  ncols<-dim(data)[2]
  if (sum(apply(data,2,is.numeric))!=ncols){stop("Data must be numeric.")}
      
   
  if( nrows < ( k + p - 1))
     {
        stop("Wrong choice of parameters : k + p - 1 should be smaller than the number of observations.")
      }
  
  if ((k < 0))
      {
        stop("Parameter k must be positive.")
      }
  
  if ((p < 0))
      {
        stop("Parameter p must be positive.")
      }  
  
  if ((method != "classification") & ( method != "regression") )
      {
        stop("Model should be 'classification' or 'regression'.")
      }
  label=as.vector(label)
  if (nrows != length(label))
      {
        stop("The number of labels must be same as the number of observations in 'data'")
      }
  
  error=rep(0,nrows)
  
  if ( method == "classification")
    {
      labelA<-label[1]
      i<-1
      if (length(unique(label))==2)
        {
          while (labelA == label[i]){i=i+1}
          label01=1:length(label)
          labelB<-label[i]
          label01[which(label==labelA)]=1
          label01[which(label==labelB)]=0
        }
      else{stop("Labels must be binary.")}
      risque<-0
      data1<-as.vector(t(data),mode="numeric")
      label1<-as.vector(label01,mode="numeric")
      error=rep(0,nrows)
      r<- .C("knn_NP_binaire",l = as.double(data1), lab = as.double(label1), taille = as.integer(nrows), 
             dimension= as.integer(ncols), knb = as.integer(k),  pnb = as.integer(p), Risque=as.double(risque),
             err=as.double(error), package="ExactSampling") 
    }
  else # regression
    {
      if (is.numeric(label)){}
      else {stop('Labels must be numeric.')}
      risque<-0
      data1<-as.vector(t(data),mode="numeric")
      label1<-as.vector(label,mode="numeric")
      error=rep(0,nrows)
      r<- .C("knn_NP_regression",l = as.double(data1), lab = as.double(label1),taille = as.integer(nrows), 
      dimension= as.integer(ncols), knb = as.integer(k),  pnb = as.integer(p),Risque=as.double(risque), 
      err=as.double(error),package="ExactSampling") 
    }
   list("risk"=r$Risque,"error.ind"=matrix(r$err,byrow=T,nrow=nrows))
}
