# GraphOps

**Installation**

***.sln usage recommended!!!***

If you want to use CMake, download and use in folder(boost 1.70 minimum required in PATH):

```
mkdir build
cd build
cmake ..
make
```

**How to use**

Choose .txt file with graph configuration.

Sample:

```
1,4
4,1
1,3
2,1
2,4
5,1
2,3
```
Where numbers are tops of graph for edge between them.


**Examples**

Graph info:

![image](https://github.com/user-attachments/assets/82e9d8dd-f3a0-45ac-bf4c-e733cd557a3b)

Current graph:

![starter_dia](https://github.com/user-attachments/assets/eb9526e3-57e6-4638-9bb2-5b1fd1024b1c)

Non-isomorphic graph:

![non_iso_dia](https://github.com/user-attachments/assets/2e2df8a2-a056-4e9d-853e-a61ae4d9101e)

Addition for graph:

![add_dia](https://github.com/user-attachments/assets/3f4c518e-d225-4a2c-be57-877c91541dd6)


***~~Features~~ BUGS:***

- Starting graph with 0 only!!!(boost library requirement). You can start file with any number, but all numbers before will exist in graph.
- Not tested at all, so maybe else....
