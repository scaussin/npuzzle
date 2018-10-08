| Language | Field                            | Project | Grade |
| :------: |:--------------------------------:| :------:|:-----:|
| C/C++, C# | Algorithms & AI | Solo   |118/125|
---
# N-puzzle
This program is able to solve [15-puzzle](https://en.wikipedia.org/wiki/15_puzzle) of various sizes, as optimally as possible using an [A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm).

![Alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/f/ff/15-puzzle_magical.svg/220px-15-puzzle_magical.svg.png "demo")
### Demo
map:
```
2 3 4
1 8 0
7 6 5
```
solving:
```
./npuzzle map
solvable in 5 moves:

2 3 4
1 8 0
7 6 5

2 3 0
1 8 4
7 6 5

2 0 3
1 8 4
7 6 5

0 2 3
1 8 4
7 6 5

1 2 3
0 8 4
7 6 5

1 2 3
8 0 4
7 6 5
```
