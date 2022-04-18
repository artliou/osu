#!/bin/bash

#NAME
#   Program 1 - matrices
#AUTHOR
#   Written by Everett Williams (williaev@oregonstate.edu)
#DATE
#   29 Jan 2018
#CLASS
#   CS344

opName=$1

# NAME
#   dims - calculates the size of a single matrix
# SYNOPSIS
#   dims [matrix]
# DESCRIPTION
#   Outputs to the terminal a row vector containing the number of rows and columns.
#   Rows are determined by counting the number of lines and columns are counted
#   by taking the leading row and counting how many tab deliniated columns it contains.
# AUTHOR
#   Written by Everett Williams (williaev@oregonstate.edu)
dims(){
  data="$1"
  cat "$data" > tmp0$$
  wc -l < tmp0$$ > tmp1$$ #determines number of rows and stores in tmp1
  head -1 tmp0$$ | tr '\t' '\n' |wc -l >> tmp1$$ #determines number of columns and appends to tmp1 by tranposing tmp0 and counting newlines
  cat tmp1$$ | tr '\n' '\t' > tmp2$$ #transpose tmp1 and place result in tmp2
  cat tmp2$$ | tr '\t' ' ' > tmp3$$ #replace tabs with spaces
  cat tmp3$$ | cut -d ' ' -f -2  > tmp4$$ #remove additional space at the end.
  cat tmp4$$ #send to stdout
  TEMPS+=("tmp0$$" "tmp1$$" "tmp2$$" "tmp3$$" "tmp4$$")
  removeTemp
  exit 0
}

# NAME
#   transpose - transposes a matrix
# SYNOPSIS
#   transpose [matrix]
# DESCRIPTION
#   Outputs to the terminal the transpose of the input matrix.  The transpose matrix
#   is formed by cutting the ith column of a matrix and transposing it by changing
#   each newline to a tap and appending to a file.
# AUTHOR
#   Written by Everett Williams (williaev@oregonstate.edu)
transpose(){
  data="$1"
  cat "$data" > newRow0$$
  numCol="$(head -1 newRow0$$ | tr '\t' '\n' | wc -l)" #count the number of columns
  numRow="$(wc -l < newRow0$$)" #count the number of columns
  i=0
  while [ $i -lt $numCol ]; do
    i=$((i+1))
    cat newRow0$$ | cut -f "$i" | tr '\n' '\t' | cut -f -"$numRow" >> newRow1$$
  done
  cat newRow1$$
  TEMPS+=("newRow0$$" "newRow1$$")
  removeTemp
  exit 0
}

# NAME
#   mean - calculates the mean of all the values in the each columun of the input matrix
# SYNOPSIS
#   mean [matrix]
# DESCRIPTION
#   Outputs to the terminal the mean values of each column of a matrix.  The means
#   are formed by cutting each column, summing each element, and calculating the mean
#   using the round half away from zero technique.
# AUTHOR
#   Written by Everett Williams (williaev@oregonstate.edu)
mean(){
  data="$1"
  cat "$data" > mean0$$
  numCol="$(head -1 mean0$$ | tr '\t' '\n' | wc -l)" #count the number of columns
  numRow="$(wc -l < mean0$$)" #count the number of columns
  i=0
  while [ $i -lt $numCol ]; do
    i=$((i+1))
    cat mean0$$ | cut -f "$i" > mean1$$
    sum=0
    while read num; do
      sum=$(expr $sum + $num)
    done < mean1$$
    mean=$(( ($sum + ($numRow/2)*(($sum>0)*2-1))/$numRow ))
    echo "$mean" >> mean2$$
  done
  cat mean2$$ | ./matrix transpose > mean3$$
  cat mean3$$
  TEMPS+=("mean0$$" "mean1$$" "mean2$$" "mean3$$")
  removeTemp
  exit 0
}

# NAME
#   add - add two matrices element-wise.
# SYNOPSIS
#   add [matrix1] [matrix2]
# DESCRIPTION
#   Outputs the result of two matrices being added element-wise.  The addition of
#   the two matrices is performed by cutting the ith column of each matrix then
#   adding the two columns together element-wise.
# AUTHOR
#   Written by Everett Williams (williaev@oregonstate.edu)
add(){
  touch sumMatrix0$$
  numCol="$(head -1 $1 | tr '\t' '\n' | wc -l)" #count the number of columns
  numRow="$(wc -l < $1)" #count the number of columns
  numCol2="$(head -1 $2 | tr '\t' '\n' | wc -l)" #count the number of columns
  numRow2="$(wc -l < $2)" #count the number of columns
  if [ $numCol != $numCol2 ] || [ $numRow != $numRow2 ]  #ensure dimensions of matrices are same.
  then
    rm *$$
    echo "the dimensions of the matrices do not match" >&2 && exit 1
  fi
  i=0
  while [ $i -lt $numCol ]; do
    i=$((i+1))
    num=$((i-1))
    cat $1 | cut -f "$i" > add2$$ #cuts ith column from matrix 1
    cat $2 | cut -f "$i" > add3$$ #cuts ith column from matrix 2
    TEMPS+=("add2$$" "add3$$")
    j=0
    while [ $j -lt $numRow ]; do
      j=$((j+1))
      mat1Val="$(cat add2$$ | head -n "$j" | tail -n 1)" #gets corresponding elements from matrices
      mat2Val="$(cat add3$$ | head -n "$j" | tail -n 1)"
      sum=$(($mat1Val + $mat2Val)) #adds them together
      echo "$sum" >> add4$i$$ #inserts into temporary file as column vector (ith column)
    done
    paste sumMatrix$num$$ add4$i$$ > sumMatrix$i$$
    TEMPS+=("sumMatrix$num$$" "sumMatrix$i$$" "add4$i$$")
  done
  lastCol=$((numCol+1))
  cat sumMatrix$numCol$$ | cut -f 2-"$lastCol" > finalMatrix$$ #remove additional space at the end.
  TEMPS+=("finalMatrix$$")
  cat finalMatrix$$
  return 0
}

# NAME
#   multiply - multiply two matrices together.
# SYNOPSIS
#   multiply [matrix1] [matrix2]
# DESCRIPTION
#   Takes an MxN and NxP matrices and multiplies them together by taking the ith row
#   of the first matrix and transposed ith column of the second matrix, mutliplying
#   each corresponding element and then summing the results.
# AUTHOR
#   Written by Everett Williams (williaev@oregonstate.edu)
multiply(){
  touch element0$$
  numColM1="$(head -1 $1 | tr '\t' '\n' | wc -l)" #count the number of columns
  numRowM1="$(wc -l < $1)" #count the number of columns
  numColM2="$(head -1 $2 | tr '\t' '\n' | wc -l)" #count the number of columns
  numRowM2="$(wc -l < $2)" #count the number of columns
  if [ $numColM1 != $numRowM2 ]
  then
    rm *$$
    echo "the dimensions of the matrices are not compatible" >&2 && exit 1
  fi
  i=0
  while [ $i -lt $numColM2 ]; do
    i=$((i+1))
    num=$((i-1))
    cat $2 | cut -f "$i" > mult3$$ #grab ith column from second matrix CH
    cat mult3$$ | ./matrix transpose > mult4$$ #create a row vector from mult
    j=0
    while [ $j -lt $numRowM1 ]; do
      j=$((j+1))
      cat $1 | head -"$j" | tail -1 > mult5$$  #grab jth row from first matrix
      k=0
      sum=0
      while [ $k -lt $numColM1 ]; do
        k=$((k+1))
        mult1Val="$(cat mult5$$ | cut -f "$k")" #gets corresponding elements from matrices
        mult2Val="$(cat mult4$$ | cut -f "$k")"
        sum=$(($mult1Val * $mult2Val + $sum))
      done
      echo $sum >> mult6$i$$ #insert sum into file creating a column vector
    done
    paste element$num$$ mult6$i$$ > element$i$$
    TEMPS+=("element$num$$" "element$i$$" "mult6$i$$")
  done
  TEMPS+=("mult3$$" "mult4$$" "mult5$$")
  lastCol=$((numColM2+1))
  cat element$i$$ | cut -f 2-"$lastCol" > finalMatrix$$ #remove additional space at the end.
  cat finalMatrix$$
  TEMPS+=("finalMatrix$$")
  return 0
}

# NAME
#   removeTemp - cleans up temporary files.
# SYNOPSIS
#   removeTemp
# DESCRIPTION
#   Runs at the completion of each of the operation functions.  An array was declared
#   at the beginning of the main part of the program.  All temporary variables are
#   added to this array.  When removeTemp is called it removes all of the temporary
#   files in the array.  This method was suggested by Ryan Gambord.
# AUTHOR
#   Written by Everett Williams (williaev@oregonstate.edu)
removeTemp(){
  for t in "${TEMPS[@]}"; do rm -f "$t"; done
  return
}

# NAME
#   main - entry point for the matrix program.
# SYNOPSIS
#   Run the program using ./matrix OPERATION [argument]
# DESCRIPTION
#   Checks to ensure the number of arguments are correct before executing the operation
#   and that the arguments are readable and present, if not correct exit with a status 1.
#   This function uses a trap function to handle untimely ctrl-c interrupts, exiting with
#   a status 1 and removing remaining files by process number.  If there are no issues
#   main calls the corresponding functions.
# AUTHOR
#   Written by Everett Williams (williaev@oregonstate.edu)
trap "rm -f *$$; echo 'CTRL+C received, exiting'; exit 1" INT HUP TERM
TEMPS=("${TEMPS[@]}") #create array for temporary files.
if [ $opName == "dims" ] || [ $opName == "transpose" ] || [ $opName == "mean" ]
then
  [ $# -gt 2 ] && echo "invalid number of arguments" >&2 && exit 1
  if [ $# -eq 2 ]
  then
    if [ -r $2 ]
    then
      $opName $2
    else
      echo "file is not readable" >&2 && exit 1
    fi
  else
    data="/dev/stdin"
    $opName $data
  fi
else
  [ $# -ne 3 ] && echo "invalid number of arguments" >&2 && exit 1
  if [ -r $2 ] && [ -r $3 ]
  then
    $opName $2 $3
    removeTemp
    exit 0
  else
    echo "one of the files is not readable" >&2 && exit 1
  fi
fi