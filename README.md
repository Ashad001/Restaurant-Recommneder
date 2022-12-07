
<div align="center">

#  ***P**roject **R**eport*

</div>


## Delish Advocacy: A Restaurant Recommender 
#### using  **Decision Tree**

*5/11/2022 - 4/12/2022*

## **Introduction and Background**
A crowdsourced restaurant recommendation system that filters out a restaurant from a myriad of preset ones purely based on the user preferences after a series of dichotomous questions explicitly designed to target precisely what the user desires. The decision tree uses cuisine preferred, pricing, time of the day, and reservation availability, to filter the restaurant out.


## **Implementation Of Decision Tree Classification**
Decision trees are a simple machine learning algorithm that uses a series of features of observation to create a prediction of a target outcome class. In our case, it is helping us classify various circumstances of user adoption and predict whether that restaurant is advocated or not. The decision tree is trained using a series of observations (training data) to create a tree that best fits the training data. This tree can then be used to make predictions on a series of observations without knowing the target outcome. In our case, the target outcome is the whether the restaurant is recommended or not.

The Data Set For out model consist of these features/questions.

1. Is the reservation available
1. The price range for that restaurant
1. Cuisine style
1. Timing of choice

Providing that, the data set of our model looked like this:
_____________________________________________________________________________
| Name           | Recommended   | Reservations | Pricing  | Cuissine | Timing |
| -------------- | -----------   | ------------ | -------- | -------- | ------ |
| No Lies Fries  |   NO          | no           | below 5k | American | Dinner |
| Ghalib         |   YES         | yes          | above 5k | Desi     | Lunch  |
| Xander's       |   YES         | yes          | below 5k | American | Lunch  |
| Xander's       |   NO          | yes          | above 5k | American | Dinner |
| Coconut Grove  |   YES         | yes          | below 5k | Desi     | Lunch  |
| Coconut Grove  |   NO          | yes          | above 5k | Desi     | Dinner |
| SAGKH          |   YES         | no           | below 5k | Desi     | Dinner |
| Dominos        |   YES         | no           | below 5k | American | Lunch  |
| Dominos        |   YES         | no           | below 5k | American | Dinner |
| Al Kabab       |   YES         | no           | below 5k | Desi     | Dinner |
| Lal Qila       |   NO          | yes          | above 5k | Desi     | Dinner |
| Burger o'clock |   NO          | no           | below 5k | American | Lunch  |
| Burger o'clock |   YES         | no           | above 5k | American | Dinner |
| Oh my Grill    |   YES         | no           | below 5k | American | Lunch  |
| Oh my Grill    |   YES         | yes          | above 5k | American | Dinner |
| Aussies        |   YES         | no           | above 5k | American | Lunch  |
| Aussies        |   YES         | no           | below 5k | American | Dinner |
_____________________________________________________________________________
- At first glance, out data looked like this:

![](Aspose.Words.752761b4-ea88-41a1-9e4e-389491422841.004.png)

- But after breaking the data into various categories recursively, the data transformed like this (first recursion)

![](Aspose.Words.752761b4-ea88-41a1-9e4e-389491422841.005.png)
![](Aspose.Words.752761b4-ea88-41a1-9e4e-389491422841.006.png)
![](Aspose.Words.752761b4-ea88-41a1-9e4e-389491422841.007.png)
![](Aspose.Words.752761b4-ea88-41a1-9e4e-389491422841.008.png)


Technology Used: [sanddance](https://www.microsoft.com/en-us/garage/profiles/sanddance/) 

# **How the decision tree was made!**
To train a decision tree classifier,

- The model has a number of measurements of categorical feature vectors that keep control of the whole data for each node of a tree.
- We used [ID3](https://towardsdatascience.com/decision-trees-for-classification-id3-algorithm-explained-89df76e72df1) algorithm to make a decision tree.
- To make sure which feature stands out the most, we use entropy measurements

![](Aspose.Words.752761b4-ea88-41a1-9e4e-389491422841.009.png)

- For each feature, we calculated the info gain for every table.
- Selected the column/feature that maximizes the info gain, and assign that to the node.

![](Aspose.Words.752761b4-ea88-41a1-9e4e-389491422841.010.png)

- Split the data based on that feature to create two new sub-trees and two tables
- Repeat the splitting of nodes in each sub-tree until only one outcome is left (info gain = 0)
# **Inputs**
The data is imported using a CSV reader function which reads the data in strings and returns a 2D vector (string). Next to simplify the problem that the decision tree can be run on any data provided we converted whole data in integers/bits using bit\_masking: it encoded the strings to integers and that is input to the decision tree as training data

The first column of names is omitted from the input and each column will contain all the question user is asked, a column is representing a feature or an individual question. The second column (first column of training data) represents outcomes, whether the restaurant is recommended or not.
# **Output**
We asked the user several questions (features of our data) and predict the outcome for that user. NOTE: There will be one less column in the user data as the outcome would be unknown.
# **Data Structure used**
***Vectors***

A vector/dynamic array of pointers for all features, where every element points to an array with the value of that feature for each training observation.

We used several dimensions of vectors based on various purposes.

- For output, a 1-D vector is used
- For training data, the 2-D vector is used (named Matrix)
- For splitting the data, two 2-D vectors are used (named as TwoMatrix)

***Maps*** 

To keep track of counts: maps (like dictionaries) are used. Which helps us in BIt\_masking, column\_deletion, info\_gain, and entropy calculations.

NOTE: maps are self-balancing red-black trees that are sorted.

***Trees***

The binary tree is used for decision-making where every left node goes with higher info gain than that of the right node.

Decision Trees classify labels by sorting them down the tree from the root node to some leaf node. Each node specifies a test of some *attribute* of the instance, and each branch descending from that node corresponds to one of the possible values for this attribute.

Our basic algorithm learns the decision tree by constructing it top-down, beginning with the question, “Which attribute should be tested at the root of the tree?” To answer this question, each attribute is evaluated using a statistical test to determine how well it alone classifies the training examples. The best attribute is selected as the root of the tree. Our next task is to find which node will be next after the root. In this case, we would like to again choose the attribute which is most useful to classify training examples. Then repeat the process until we find the leaf node.

An example of the tree on the above data looked like this:

![](Aspose.Words.752761b4-ea88-41a1-9e4e-389491422841.011.png)
# **Architecture and Design**
Each Tree Node has the following attributes and methods:

1. *TrainData* - Specific table data for every node.
1. *bestSplit* - contains two variables: resEntropy and Feature of that node.
1. *leftChild* - pointer to a left node of the tree.
1. *rightChild* - pointer to the right node of the tree.
1. *CountResults()* - will give counts of every feature in the table.
1. *EntropyOfCol()* - will give the entropy of a specific column required for the counts of features.
1. *ColGain()* - will use the entropy of the column function to calculate the gain of the column.
1. *GetInfoGain()* - will calculate the info gain of the whole table by using the above methods.

Data\_Retreival class contains 2 methods:

1. *RETRIEVE\_DATA* - Fetch the data from a CSV file and save it in 2D vector.
1. *Bit\_Mask* - Encode the data to bits and omits the miscellaneous column.

decision tree class contains the following attributes and methods:

1. A Data retrieval object - used to retrieve data from CSV which will be used by the root Node
1. *Root* - A tree node object.
1. *DecisionTree()* - constructor to initialize and set attributes required for first use
1. *ConstructTree()* - Construct the tree using the training data.
1. *Predicts()* - will take the output data and returns 0/1, whether the restaurant is recommended or not.

Other attributes and functions:

1. *isIdentical()* - helper function for bit\_mask
1. *PrintData1()* - for printing 1-D vectors
1. *PritnData2()* - for printing 2-D vectors

The menu class contains various functions for user interaction. Every part is divided into many readable functions which make the interface very pleasing to the user.




