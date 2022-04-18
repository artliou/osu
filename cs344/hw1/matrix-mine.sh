#!/bin/bash

#Author: Arthur Liou
#Assignment: Program 1 - matrices
#Class: CS344

operationName=$1

# Function: Calculates Size of a Single Matrix
# Usage: matrix dims [matrix]
# Description: Outputs a row vector to the terminal. This row vector contains
# the number of rows and columns of a single matrix.

dims(){
  data="$1"
  cat "$data" > tmp0$$
  # Stores the number of rows in tmp1
  wc -l < tmp0$$ > tmp1$$
  # Appends the number of rows to tmp2 by transposing tmp0 + counting the new lines
  head -1 tmp0$$ | tr '\t' '\n' |wc -l >> tmp1$$
  # Transposes tmp1 & Adds the result to tmp2
  cat tmp1$$ | tr '\n' '\t' > tmp2$$
  # Fulfill spaces requirement
  cat tmp2$$ | tr '\t' ' ' > tmp3$$
  # Clean up spaces 
  cat tmp3$$ | cut -d ' ' -f -2  > tmp4$$
  #Send to stdout
  cat tmp4$$
  TEMPS+=("tmp0$$" "tmp1$$" "tmp2$$" "tmp3$$" "tmp4$$")
  # See removeTempFiles Function Description for more detail
  removeTempFiles
  exit 0
}


# Function: Transposes a matrix
# Usage: matrix transpose [matrix]
# Description: Outputs to terminal the tranposition of an input matrix. 
# It will reflect elemtns of the matrix along the main diagonal. So MxN -> NxM matrix
# and values along the main diagonal will not be changed

transpose(){
  data="$1"
  cat "$data" > newRow0$$
  # Gather number of columns
  numberColumn="$(head -1 newRow0$$ | tr '\t' '\n' | wc -l)"
  # Gather number of row
  numberRow="$(wc -l < newRow0$$)"
  i=0
  while [ $i -lt $numberColumn ]; do
    i=$((i+1))
    cat newRow0$$ | cut -f "$i" | tr '\n' '\t' | cut -f -"$numberRow" >> newRow1$$
  done
  cat newRow1$$
  TEMPS+=("newRow0$$" "newRow1$$")
  # See removeTempFiles Function Description for more detail
  removeTempFiles
  exit 0
}


# Function: For a single matrix, calculates the mean of all values of each column
# Usage: matrix mean [matrix]
# Description: Outputs to terminal the mean values of each column of a matrix
# MxN matrix -> 1xN row vector, where first element is mean of column one, etc

mean(){
  data="$1"
  cat "$data" > mean0$$
  # Gather number of columns
  numberColumn="$(head -1 mean0$$ | tr '\t' '\n' | wc -l)" #count the number of columns
  # Gather number of row
  numberRow="$(wc -l < mean0$$)"
  i=0
  # While count is less than the number of columns in the matrix,
  # Find the mean of each column 
  while [ $i -lt $numberColumn ]; do
    i=$((i+1))
    cat mean0$$ | cut -f "$i" > mean1$$
    sum=0
    while read num; do
      sum=$(expr $sum + $num)
    done < mean1$$
    mean=$(( ($sum + ($numberRow/2)*(($sum>0)*2-1))/$numberRow ))
    echo "$mean" >> mean2$$
  done
  cat mean2$$ | ./matrix transpose > mean3$$
  cat mean3$$
  TEMPS+=("mean0$$" "mean1$$" "mean2$$" "mean3$$")
  # See removeTempFiles Function Description for more detail
  removeTempFiles
  exit 0
}


# Function: Add two matrices 
# Usage: matrix add [matrixLeft] [matrixRight]
# Description: Outputs to terminal the results of two matrices. 
# Will return error if the two matrices don't have same dimensions

add(){
  touch sumMatrix0$$
  # Dimensions gather
  numberColumnsLeft="$(head -1 $1 | tr '\t' '\n' | wc -l)"
  numberRowLeft="$(wc -l < $1)"
  numberColumnsRight="$(head -1 $2 | tr '\t' '\n' | wc -l)"
  numberRowRight="$(wc -l < $2)"
  # Dimension check
  if [ $numberColumnsLeft != $numberColumnsRight ] || [ $numberRowLeft != $numberRowRight ]
  then
    rm *$$
    echo "Matrices' dimensions aren't equal" >&2 && exit 1
  fi
  i=0
  # Two while loops; one for columns, another for rows
  while [ $i -lt $numberColumnsLeft ]; do
    i=$((i+1))
    num=$((i-1))
    #isolates ith column from both matrices
    cat $1 | cut -f "$i" > add2$$
    cat $2 | cut -f "$i" > add3$$
    TEMPS+=("add2$$" "add3$$")
    j=0
    while [ $j -lt $numberRowLeft ]; do
      j=$((j+1))
      # Grabs corresponding elements from both "column vectors"
      mat1Val="$(cat add2$$ | head -n "$j" | tail -n 1)"
      mat2Val="$(cat add3$$ | head -n "$j" | tail -n 1)"
      # Sum/Addition
      sum=$(($mat1Val + $mat2Val))
      # Inserts into tempFile as the ith column vector
      echo "$sum" >> add4$i$$
    done
    paste sumMatrix$num$$ add4$i$$ > sumMatrix$i$$
    TEMPS+=("sumMatrix$num$$" "sumMatrix$i$$" "add4$i$$")
  done
  lastColumn=$((numberColumnsLeft+1))
  cat sumMatrix$numberColumnsLeft$$ | cut -f 2-"$lastColumn" > finalMatrix$$
  TEMPS+=("finalMatrix$$")
  cat finalMatrix$$
  return 0
}

# Function: Multiply two matrices together
# Usage: matrix multiply [matrixLeft] [matrixRight]
# Description: 
#   Takes an MxN and NxP matrices and multiplies them together by taking the ith row
#   of the first matrix and transposed ith column of the second matrix, mutliplying
#   each corresponding element and then summing the results.
multiply(){
  touch element0$$
  numberColumnsLeftM="$(head -1 $1 | tr '\t' '\n' | wc -l)" #count the number of columns
  numberRowLeftM="$(wc -l < $1)" #count the number of columns
  numberColumnsRightM="$(head -1 $2 | tr '\t' '\n' | wc -l)" #count the number of columns
  numberRowRightM="$(wc -l < $2)" #count the number of columns
  if [ $numberColumnsLeftM != $numberRowRightM ]
  then
    rm *$$
    echo "Matrices' dimensions do not match. Sorry." >&2 && exit 1
  fi
  i=0
  # While loop to multiply the corresponding elements
  while [ $i -lt $numberColumnsRightM ]; do
    i=$((i+1))
    num=$((i-1))
    # Grab ith column from second matrix
    cat $2 | cut -f "$i" > mult3$$ 
    # Use Transpose
    cat mult3$$ | ./matrix transpose > mult4$$
    j=0
    while [ $j -lt $numberRowLeftM ]; do
      j=$((j+1))
      # Grab the jth row from first matric
      cat $1 | head -"$j" | tail -1 > mult5$$
      k=0
      sum=0
      while [ $k -lt $numberColumnsLeftM ]; do
        k=$((k+1))
        #gets corresponding elements from matrices
        productValue1="$(cat mult5$$ | cut -f "$k")"
        productValue2="$(cat mult4$$ | cut -f "$k")"
        sum=$(($productValue1 * $productValue2 + $sum))
      done
      #insert sum into tempFile creating a column vector
      echo $sum >> mult6$i$$ 
    done
    paste element$num$$ mult6$i$$ > element$i$$
    TEMPS+=("element$num$$" "element$i$$" "mult6$i$$")
  done
  TEMPS+=("mult3$$" "mult4$$" "mult5$$")
  lastColumn=$((numberColumnsRightM+1))
  cat element$i$$ | cut -f 2-"$lastColumn" > finalMatrix$$
  cat finalMatrix$$
  TEMPS+=("finalMatrix$$")
  return 0
}

# Function: removes all temporary files (hence removeTempFiles)
# Description: You may notice I executed this function at the end of each operation. At the beginning of the main part
# of the program, an array was declared. All temp variables were added there. Now, it's
# time to "erase the whiteboard" so to speak.
removeTempFiles(){
  for t in "${TEMPS[@]}"; do rm -f "$t"; done
  return
}

# Function: Run Program Main
# Usage: ./matrix OPERATION [ARGUMENT]
# Description: Checks for the number of arguments (and edges cases, etc) before attempting
# to execute an operation. It will only go through if the arguments are readable and present.
# If any of the checks fail, then program will exit with status 1 and output to stderr
# Otherwise, it'll output to stdout

trap "rm -f *$$; echo 'CTRL+C received, exiting'; exit 1" INT HUP TERM
#array for temporary files.
TEMPS=("${TEMPS[@]}") 
if [ $operationName == "dims" ] || [ $operationName == "transpose" ] || [ $operationName == "mean" ]
then
  [ $# -gt 2 ] && echo "Invalid number of arguments" >&2 && exit 1
  if [ $# -eq 2 ]
  then
    if [ -r $2 ]
    then
      $operationName $2
    else
      echo "Unreadable file" >&2 && exit 1
    fi
  else
    data="/dev/stdin"
    $operationName $data
  fi
else
  [ $# -ne 3 ] && echo "Invalid number of arguments" >&2 && exit 1
  if [ -r $2 ] && [ -r $3 ]
  then
    $operationName $2 $3
    # See removeTempFiles Function Description for more detail
    removeTempFiles
    exit 0
  else
    echo "Unreadable file(s)" >&2 && exit 1
  fi
fi