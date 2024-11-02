# DSA_MNIST-Data-Processing-and-k-Nearest-Neighbors-kNN-Optimization-using-k-D-Tree

**Introduction**
This project is an assignment for the Data Structures and Algorithms course at Ho Chi Minh University of Technology. The goal is to optimize the k-Nearest Neighbors (kNN) algorithm using the k-D Tree data structure to improve processing speed, especially on high-dimensional data, such as MNIST.


**Project Overview**
k-D Tree:

+ A k-D Tree is an extension of a binary search tree designed for multidimensional data.
+ It splits data by dimensions, alternating between dimensions at each tree level.
+ The k-D Tree enables efficient nearest-neighbor searches by reducing the number of points to evaluate.
  
k-Nearest Neighbors (kNN):
+ kNN is a simple classification algorithm that assigns labels based on the k closest points in a dataset.
+ This assignment requires implementing kNN with a k-D Tree to optimize search time.

**Requirements**
Class kDTree
+ Implements the k-D Tree data structure, with operations such as insertion, deletion, and nearest-neighbor search.
+ Contains methods to build a balanced k-D Tree from a list of points.

Class kNN
+ Uses k-D Tree to classify data points based on k-nearest neighbors.
+ Provides a fit method for training data, a predict method for classification, and a score method to evaluate accuracy.
Dataset Class
+ Handles loading, processing, and managing the MNIST dataset.
+ The class has methods to load data from CSV, print dataset samples, and split data for training and testing.

**Instruction**
Để biên dịch và chạy chương trình, trước tiên bạn cần cài đặt môi trường có sẵn trình biên dịch C++ (cụ thể là g++ với chuẩn C++11). Sau khi đã chuẩn bị môi trường, bạn có thể biên dịch chương trình bằng cách sử dụng lệnh sau trong terminal:
bash
g++ -o main main.cpp kNN.cpp -I . -std=c++11

Lệnh này sẽ tạo ra một file thực thi có tên là main. Sau khi biên dịch thành công, bạn có thể chạy chương trình bằng cách gõ lệnh:
bash
./main
