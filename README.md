Student Name: Alfonso Luis Del Rosario
Student ID: 1698802
Programming Assignment 4

                                                List.h 
-----------------------------------------------------------------------------------------------------------------------------------------
Provides function prototypes, parameter details, and function return types of the List ADT to the client. 
Briefly explains each functions' purpose and use cases.

                                                List.c 
-----------------------------------------------------------------------------------------------------------------------------------------
Implements the functions of the List ADT. Handles invalid and/or empty inputs appropriately. 
Defines the functionality of the tools provided by the List ADT
List ADT is a doubly linked list that provides client side users access to functions that can generate dynamically allocated lists.
These lists' data can be accessed and modified through the various function calls provided and listed in the List.h file. 

                                                Matrix.h
---------------------------------------------------------------------------------------------z--------------------------------------------
Provides function prototypes, parameter details, and function return types of the Matrix ADT to the client.
Briefly explains each functions' purpose and use cases.

                                                Matrix.c
-----------------------------------------------------------------------------------------------------------------------------------------
Implements functions of the Matrix ADT. Handles invalid and/or empty inputs appropriately.
Matrix ADT is a tool that allows the client user to create an nxn sized matrix and fill in each entry with a type double value. 
This Matrix ADT gives the client access to the basic matrix computations such as: sum, difference, matrix multiplication, etc. 

                                                MatrixTest.c
-----------------------------------------------------------------------------------------------------------------------------------------
MatrixTest is a program that tests the functions created for the Matrix ADT in an environment that's both optimal and non-optimal.
Consider it a stress test for every operation built in the Matrix ADT.

                                                ListTest.c
-----------------------------------------------------------------------------------------------------------------------------------------
ListTest is a program that tests the functions created for the List ADT in an environment that's both optimal and non-optimal.
Consider it a stress test for every operation built in the List ADT.

                                                Sparse.c
-----------------------------------------------------------------------------------------------------------------------------------------
Arguments: infile , outfile

Sparse.c is a program that parses through a file provided in its argument list, then creates and fills two matrices of given size and 
given entries. Sparse then outputs the resulting matrices of the ADT functions such as: sum, transpose, differece, product, etc.
Sparse outputs these values and statements along with these values into a output file provided as an argument as well.

                                                Makefile
-----------------------------------------------------------------------------------------------------------------------------------------
Provides easier command line expressions that make it easier to build and run each of the client side programs.

-----------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------
SAMPLE RUN:

/*---in.txt---*/                                      
      
      3 9 5                                                
                                                           
      1 1 1.0                                              
      1 2 2.0                                              
      1 3 3.0                                              
      2 1 4.0                                              
      2 2 5.0                                              
      2 3 6.0                                              
      3 1 7.0                                              
      3 2 8.0                                             
      3 3 9.0                                              
                                                            
      1 1 1.0                                               
      1 3 1.0                                               
      3 1 1.0                                               
      3 2 1.0                       
      3 3 1.0                                               
                                                            
              
/*---out.txt---*/

      A has 9 non-zero entries:
      1: (1, 1.0) (2, 2.0) (3, 3.0) 
      2: (1, 4.0) (2, 5.0) (3, 6.0) 
      3: (1, 7.0) (2, 8.0) (3, 9.0) 
  
      B has 5 non-zero entries:
      1: (1, 1.0) (3, 1.0) 
      3: (1, 1.0) (2, 1.0) (3, 1.0) 
  
      (1.5)*A = 
      1: (1, 1.5) (2, 3.0) (3, 4.5) 
      2: (1, 6.0) (2, 7.5) (3, 9.0) 
      3: (1, 10.5) (2, 12.0) (3, 13.5) 
  
      A+B = 
      1: (1, 2.0) (2, 2.0) (3, 4.0) 
      2: (1, 4.0) (2, 5.0) (3, 6.0) 
      3: (1, 8.0) (2, 9.0) (3, 10.0) 
  
      A+A = 
      1: (1, 2.0) (2, 4.0) (3, 6.0) 
      2: (1, 8.0) (2, 10.0) (3, 12.0) 
      3: (1, 14.0) (2, 16.0) (3, 18.0) 
  
      B-A = 
      1: (2, -2.0) (3, -2.0) 
      2: (1, -4.0) (2, -5.0) (3, -6.0) 
      3: (1, -6.0) (2, -7.0) (3, -8.0) 
  
      A-A = 
  
      Transpose(A) = 
      1: (1, 1.0) (2, 4.0) (3, 7.0) 
      2: (1, 2.0) (2, 5.0) (3, 8.0) 
      3: (1, 3.0) (2, 6.0) (3, 9.0) 
  
      A*B = 
      1: (1, 4.0) (2, 3.0) (3, 4.0) 
      2: (1, 10.0) (2, 6.0) (3, 10.0) 
      3: (1, 16.0) (2, 9.0) (3, 16.0) 
  
      B*B = 
      1: (1, 2.0) (2, 1.0) (3, 2.0) 
      3: (1, 2.0) (2, 1.0) (3, 2.0) 
  














