 
  参考：http://www.matrix67.com/blog/archives/5044

  实现思想：   
  主要是通过c++ map容器进行频度统计
  在计算左自由度时，方法比较old，将字符整体翻转后再按照计算右自由度的方法（后缀数组，注意判重）计算，最后保存子串时注意
在翻转过来

  程序执行已经整合到 run_sum.sh (首先去掉非中文符)

