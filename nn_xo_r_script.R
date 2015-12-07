## Neural network project, fall 2016
## Marie Drabkova
#setwd("~/School/neuralnetwork/experimenty")

#--------------------------------------------------------------------------------------------
# 1) success rate / pocet vnitrnich neuronu pro 1/2/3 vrstvou sit -> 3 krivky / rady v 1 grafu -> vyber vhodne organizace


#--------------------------------------------------------------------------------------------
# 2) pro jednu organizaci chyba / n kroku uceni

plotAccurancy <-function(input, output) {
  my_data=read.csv(input, header=FALSE, sep=",")
  png(filename=output)
  par(adj=1, pty='m')
  xg<-seq(0,length(my_data$V1) - 1,1)
  plot(xg,my_data$V1, type='l', lty=1, ylim=c(0,1), col=c(2), xlab="t (epocha)", ylab="accurancy (%)")
  lines(xg, my_data$V2, type='l', lty=2, col=c(3))
  legend("bottomright",legend=c("training data","validation data"),lty=c(1,2), col=c(2,3))
  dev.off()
}
plotAccurancy2 <-function(input) {
  my_data=read.csv(input, header=FALSE, sep=",")
  par(adj=1, pty='m')
  xg<-seq(0,length(my_data$V1) - 1,1)
  plot(xg,my_data$V1, type='l', lty=1, ylim=c(0,1), col=c(2), xlab="t (epocha)", ylab="accurancy (%)")
  lines(xg, my_data$V2, type='l', lty=2, col=c(3))
  legend("bottomright",legend=c("training data","validation data"),lty=c(1,2), col=c(2,3))
}

plotCost <-function(input, output) {
  my_data=read.csv(input, header=FALSE, sep=",")
  png(filename=output)
  par(adj=1, pty='m')
  xg<-seq(0,length(my_data$V1) - 1,1)
  plot(xg,my_data$V1, type='l', lty=1, ylim=c(0,1), col=c(2), xlab="t (epocha)", ylab="cost (%)")
  lines(xg, my_data$V2, type='l', lty=2, col=c(3))
  legend("topright",legend=c("training data","validation data"),lty=c(1,2), col=c(2,3))
  dev.off()
}
plotCost2 <-function(input) {
  my_data=read.csv(input, header=FALSE, sep=",")
  par(adj=1, pty='m')
  xg<-seq(0,length(my_data$V1) - 1,1)
  plot(xg,my_data$V1, type='l', lty=1, ylim=c(0,1), col=c(2), xlab="t (epocha)", ylab="cost (%)")
  lines(xg, my_data$V2, type='l', lty=2, col=c(3))
  legend("topright",legend=c("training data","validation data"),lty=c(1,2), col=c(2,3))
}

plotAccurancy("accurancy.csv","a")
plotCost("cost.csv", "c")


#--------------------------------------------------------------------------------------------
# 3) pro jednu viteznou organizace matice zmatenosti

