# Heritage

A group of families within a village of former landowners initiated a division process. This process is a
bit particular because each of the heirs does not seek to have more or equal surface of land than the
others, instead, they only seek to divide in equal parts the places that bring with them precious
mineral ores. The land of each of the former heirs is a plan of R rows and C columns, where each of
the cells represents one hectare of surface, which may or may not have an ore in it. The dividing
process will be carried out with a series of vertical and horizontal cuts to the plan. Thelawyers of each
of the families have the task of carrying out a peaceful and transparent process ensuring that each of
the heirs has the same amount of ores, regardless of the surface.

It helps the lawyers to carry out the separation.

__Inputs:__ <br/>
The first input is an integer P representing the number of test cases. For each test case you will
receive 3 integers: N, R and C where: N represents the number of heirs and where R and C represent
the dimensions of the plan. Then in the following "inputs" you will receive the information of each of
the rows of the plan, where each hectare with an ore is represented by "+" and each empty hectare is
represented by ".".

__Outputs:__ <br/>
For each test case you shall print the X coordinates of the vertical cuts (each separated by comma
(","), starting from 0) and space separated the Y coordinates of the horizontal cuts (each separated by
comma (","), starting from 0). In case there are no cuts (either vertical or horizontal) print a hyphen
("-"). In case it is impossible to make the division print the word: IMPOSSIBLE.

__Limits:__ <br/>
Maximum time per test case: 20s. <br/>
1 < R, C, N <= 1000 <br/>
P < 1000000

__Examples:__ <br/>

| 3                                                                           |               |
|:----------------------------------------------------------------------------|:-------------:|
| 4 5 5 <br/> + . + + . <br/> . . + . + <br/> . . . . + <br/> . . . . .       | 2, 3, 4 -     |
| 2 4 2 <br/> + . <br/> + . <br/> + + <br/> . +                               | __IMPOSIBLE__ |
| 4 5 4 <br/> . . + + <br/> . . + + <br/> . . . . <br/> + . . + <br/> + . . + | 3 2           |

<br/>

__Explanation:__

* In the first test case, we have: 4 heirs and a 5x5 plot of land. Here we simply count the
number of available ores and take the residue of the division with the number of heirs. When
we find that it is 0, we know that we have to give 2 ores to each one and we proceed with the
division. In this case there are only vertical cuts, so no dash is printed in the second space.

* In this case we mark that it is impossible because we only have two heirs and 5 ores, it is not
possible to do the division process in this case.

* In this case, it is possible to do the division process, since there are 4 heirs and there are 8
hectares with ores available, then we look for the cuts. In this case, unlike the first one, there
are vertical and horizontal cuts.
