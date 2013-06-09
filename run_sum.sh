#!/bin/sh

source=../data/blog_gbk.txt
datapath=only.txt
respath=result.txt


./OnlyChinese ${source} ${datapath}
./SuffixCompute ${datapath} |piconv -f gbk -t utf8 > res.txt

sort -n -k 2 res.txt -r -o res.txt

awk '{if($3!=0 && $4!=0) print $0;}'  res.txt > $respath
