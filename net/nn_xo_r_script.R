## Neural network project, fall 2016
## Marie Drabkova
setwd("~/net/out")

#--------------------------------------------------------------------------------------------
# 1) success rate / pocet vnitrnich neuronu pro 1/2/3 vrstvou sit -> 3 krivky / rady v 1 grafu -> vyber vhodne organizace


#--------------------------------------------------------------------------------------------
# 2) pro jednu organizaci chyba / n kroku uceni

showPlot <-function(filename, legendposition) {
  my_data=read.csv(filename, header=FALSE, sep=",")
  X11()
  par(adj=1, pty='m')
  xg<-seq(0,length(my_data$V1) - 1,1)
  plot(xg,my_data$V1, type='l', lty=1, ylim=c(0,1), col=c(2), xlab="t (epocha)", ylab="accurancy (%)")
  lines(xg, my_data$V2, type='l', lty=2, col=c(3))
  legend(legendposition,legend=c("training data","validation data"),lty=c(1,2), col=c(2,3))
}

showPlot("accurancy.csv", "bottomright")
showPlot("cost.csv", "topright")


#--------------------------------------------------------------------------------------------
# 3) pro jednu viteznou organizace matice zmatenosti
