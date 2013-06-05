recursiverm() {
  for d in $(find * -name '*.dat') 
  do
    /home/wnoizumi/Repositorios/PAA/Debug/PPH 4 $d >> results.csv
  done
}

(recursiverm)
