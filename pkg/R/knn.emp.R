knn.emp <-
  function(data=numeric(),label,k,weight=NULL,alpha=NULL, method=character())
  {
    data=as.matrix(data)    
    nrows<-dim(data)[1]
    ncols<-dim(data)[2]
    if (sum(apply(data,2,is.numeric))!=ncols)
    {
      stop(" Data must be numeric")
    }
    if (nrows != length(label))
    {
      stop("The number of labels must be same as the number of observations in 'data'")
    }
    if( nrows < k)
    {
      stop("Wrong choice of parameters : k should be smaller than the number of observations.")
    }
    if (k < 0)
    {
      stop("Parameter k  must be positive.")
    }
    if ((method != "classification") & ( method != "regression") )
    {
      stop("choose model=( 'classification' , 'Regression')")
    }
    if (nrows != length(label))
    {
      stop("The number of labels must be same as the number of observations in 'data'")
    }
    
    if ( method == "classification")
    {
      if (length(unique(label))!=2){stop('Labels must be binary.')}
      labelA<-label[1]
      i<-1
      while (labelA == label[i]){i=i+1}
      label01=1:length(label)
      labelB<-label[i]
      label01[which(label==labelA)]=1
      label01[which(label==labelB)]=0
      
      risque<-0
      data1<-as.vector(t(data),mode="numeric")
      label1<-as.vector(label01,mode="numeric")
      
      if (is.null(weight) & is.null(alpha))
      {
        error=as.vector(rep(0,nrows),"numeric")
        r <- .C("knn_NP_binaire_emp",l = as.double(data1), lab = as.double(label1), taille = as.integer(nrows), 
                dimension= as.integer(ncols), knb = as.integer(k), Risque=as.double(risque), 
                err=as.double(error),package="ExactSampling") 
      } # classification pondere 
      else if (is.numeric(weight)){
        weight=as.matrix(weight)
        if (dim(weight)[1]!=nrows || dim(weight)[2]!=nrows){
          stop("Incorrect dimensions for the weight matrix. Should be n*n.")
        }
        else{
          error=as.vector(rep(0,nrows),"numeric")
          data2<-as.vector(t(weight),mode="numeric")
          r<- .C("knn_Pondere_binaire_emp",l = as.double(data1), lab = as.double(label1),weights=as.double(data2), taille = as.integer(nrows), 
                 dimension= as.integer(ncols), knb = as.integer(k),Risque=as.double(risque), 
                 err=as.double(error),package="ExactSampling")
        } 
      }#classification pondere avec la puissance
      else if (is.numeric(alpha)){
        error=as.vector(rep(0,nrows),"numeric")
        r<- .C("knn_Puissance_binaire_emp",l = as.double(data1), lab = as.double(label1), Alpha=as.double(alpha),taille = as.integer(nrows), 
               dimension= as.integer(ncols), knb = as.integer(k), Risque=as.double(risque), 
               err=as.double(error),package="ExactSampling")
      } 
    }
    else
    {  # regression 
      risque<-0
      if (is.numeric(label)){}
      else{ stop('Labels must be numeric')}
      data1<-as.vector(t(data),mode="numeric")
      label1<-as.vector(label,mode="numeric")
      #regression non pondère
      if (is.null(weight) & is.null(alpha))
      {   
        error=as.vector(rep(0,nrows),"numeric")
        r<- .C("knn_NP_regression_emp",l = as.double(data1), lab = as.double(label1),taille = as.integer(nrows), 
               dimension= as.integer(ncols), knb = as.integer(k),Risque=as.double(risque), 
               err=as.double(error),package="ExactSampling") 
      }
      else
      {   
        if (is.numeric(alpha) & is.null(weight))
        { # regression puissance
          error=as.vector(rep(0,nrows),"numeric")
          r<- .C("knn_Puissance_regression_emp",l = as.double(data1), lab = as.double(label1), Alpha = as.double(alpha), taille = as.integer(nrows), 
                 dimension= as.integer(ncols), knb = as.integer(k),Risque=as.double(risque), 
                 err=as.double(error),package="ExactSampling")
        }
        else
        { 
          weight=as.matrix(weight)
          if (dim(weight)[1] != nrows || dim(weight)[2] != nrows) 
          {
            stop("Incorrect dimensions for the weight matrix. Should be n*n.")
          }    
          # regression pondère
          error=as.vector(rep(0,nrows),"numeric")
          data2<-as.vector(t(weight),mode="numeric")
          r <- .C("knn_P_regression_emp",l = as.double(data1), lab = as.double(label1), weights = as.double(data2), 
                  taille = as.integer(nrows),dimension= as.integer(ncols), knb = as.integer(k),Risque=as.double(risque),
                  err=as.double(error),package="ExactSampling")
        }
      } 
    } 
    list(risk.emp=r$Risque,error.ind=as.matrix(r$err))
  }
