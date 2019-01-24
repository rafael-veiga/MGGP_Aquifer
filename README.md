# Multiobjective grammar-based genetic programming applied to Ecologic relations in metagenomic data.
The code originated from the project described in the article "Multiobjective grammar-based genetic programming applied to the study of asthma and allergy epidemiology, Autors: Veiga, et al. 2018, jornal:BMC Bioinformatics  DOI:10.1186/s12859-018-2233-z".

In this version, modifications were made to parallelize the code and to shuffle the relationships between variables for control group in each generation. The purpose of this shuffle is to create new relationships with each generation so that the algorithm is able to identify relationship that actually occur in the case group.

# Compilation
Compile with the preferred C ++ compiler and add the "-fopenmp" flag for parallelization in openMP. 

# Input data
- Grammar definition File
  Non-terminals are any word delimited by symbols \<>
  
  The symbols | separates the productions
  
  First line is the definition of the initial nonterminal, example : 
 
  \<exp>: \<exp> + \<exp> | \<count>
  
  More information on how to construct the grammars can be obtained in Veiga et al. 2018
  
- Table of metagenomic abundance File

- Group Definition File

# How to run (Parameters)
1) seed

2) grammar file

3) table file
4) group file
5) generations number
6) Models population size
7) max tree deep
8) output file

example: MGGP.exe 1 gram.txt soil.csv grupo.csv 50000 500 20 result.dat



