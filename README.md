# DSA_MNIST-Data-Processing-and-k-Nearest-Neighbors-kNN-Optimization-using-k-D-Tree

**Introduction:**

This project is an assignment for the Data Structures and Algorithms course at Ho Chi Minh University of Technology. The goal is to optimize the k-Nearest Neighbors (kNN) algorithm using the k-D Tree data structure to improve processing speed, especially on high-dimensional data, such as MNIST.


**Project Overview:** Here are they

k-D Tree:
+ A k-D Tree is an extension of a binary search tree designed for multidimensional data.
+ It splits data by dimensions, alternating between dimensions at each tree level.
+ The k-D Tree enables efficient nearest-neighbor searches by reducing the number of points to evaluate.
  
k-Nearest Neighbors (kNN):
+ kNN is a simple classification algorithm that assigns labels based on the k closest points in a dataset.
+ This assignment requires implementing kNN with a k-D Tree to optimize search time.

**Requirements:** Here are they

Class kDTree
+ Implements the k-D Tree data structure, with operations such as insertion, deletion, and nearest-neighbor search.
+ Contains methods to build a balanced k-D Tree from a list of points.

Class kNN
+ Uses k-D Tree to classify data points based on k-nearest neighbors.
+ Provides a fit method for training data, a predict method for classification, and a score method to evaluate accuracy.
Dataset Class
+ Handles loading, processing, and managing the MNIST dataset.
+ The class has methods to load data from CSV, print dataset samples, and split data for training and testing.

**Instruction:**

To compile and run the program, you first need to set up an environment with a C++ compiler installed (specifically g++ with C++11 standard). After preparing the environment, you can compile the program by using the following command in the terminal:
bash
g++ -o main main.cpp kNN.cpp -I . -std=c++11

This command will create an executable file named main. After successfully compiling, you can run the program by typing the command:
bash
./main
