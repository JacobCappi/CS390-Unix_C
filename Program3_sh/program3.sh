#!/bin/bash

# *************************************************
# ----- Author: Jacob Cappi
# ----- Email : jc0199@uah.edu
# ----- Programming Assignment 3
# ----- Date : 04.13.2021
# ----- Searches and Replaces primitive values with new Values
# ----- Example usage : 
# ----- tar -xzf program3_sed_project.tgz && find testapp/ -type f \( -name *.h -o -
# *************************************************


while read line
do
# ----- This check is project specific, tar'd project file relies on this header file for defs
# ------ so, this file should not be modified
    if [ $line != "testapp/PrimitiveDefs.h" ]; then
# ----- Replacing Chars
        sed -i 's/\sunsigned char\s/ CS390_UCHAR /g' $line 
        sed -i 's/\schar\s/ CS390_CHAR /g' $line 

# ----- Replacing Shorts 
        sed -i 's/\sunsigned short\s/ CS390_UINT16 /g' $line 
        sed -i 's/\sshort\s/ CS390_INT16 /g' $line 

# ----- Replacing Ints 
        sed -i 's/\sunsigned int\s/ CS390_UINT32 /g' $line 
        sed -i 's/\sint\s/ CS390_INT32 /g' $line # should take unsigned int to CS390 Uint32

# ----- Replacing Floating point 
        sed -i 's/\sfloat\s/ CS390_FLOAT32 /g' $line 
        sed -i 's/\sdouble\s/ CS390_FlOAT64 /g' $line 

# ----- Replacing booleans 
        sed -i 's/\sbool\s/ CS390_BOOL /g' $line 
   fi 

done
exit
