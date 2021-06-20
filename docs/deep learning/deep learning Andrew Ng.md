# Basics of Neural Network programming  

## Binary Classification  

## Logistic Regression

Logistic regression is a learning algorithm used in a supervised learning problem when the output y are all either zero or one. The goal of logistic regression is to minimize the error between its predictions and training data.

Example: Cat vs No -cat

Given an image represented by a feature vector x, the algorithm will evaluate the probability of a cat being in that image.

​                   $Given\ x, \hat y =P(y=1|x), \ where \ 0\le\hat y \le 1$

The parameters used in Logistic regression are:

- The input features vector: $x\in \mathbb R^{n_x}$, where  $n_x$ is the number of features
- The training label: $y \in 0,1$
- The weights: $w\in \mathbb R^{n_x}$, where  $n_x$ is the number of features
- The threshold：$b \in \mathbb R$
- The output: $\hat y = \sigma(w^Tx + b)=\sigma(z)=\frac {1}{1+e^{-z}}$

![SigmoidFunction](.\images\SigmoidFunction.PNG)

$(w^Tx + b)$ is a linear function (ax + b), but since we are looking for a probability constraint between [0,1], the sigmoid function is used. The function is bounded between [0,1] as show in the graph abve.

Some observations form the graph:

- if z is a large positive number, the $\sigma(x)=1$
- if z is small or large negative number, then $\sigma(x)=0$
- if z = 0, then $\sigma(x)=0.5$

## Logistic Regression: Cost Function

![](.\images\LogisticRegression-CostFunction.PNG)

## Gradient Descent  

![GradienDescent](.\images\GradienDescent.PNG)

## Computation Graph  

