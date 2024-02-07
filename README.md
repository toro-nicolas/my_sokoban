# my_sokoban 📦



### Table of contents 📑
- [Project goal](https://github.com/toro-nicolas/my_sokoban#project-goal-)
- [How to compile it ?](https://github.com/toro-nicolas/my_sokoban#how-to-compile-it--)
- [How to use it ?](https://github.com/toro-nicolas/my_sokoban#how-to-use-it--)
- [Final result on my.epitech.eu](https://github.com/toro-nicolas/my_sokoban#final-result-on-myepitecheu-)

### Project goal 🎯
Reproduction of the sokoban game in C with ncurses.    
The sokoban is a game in which you play as a player whose aim is to put boxes into holes.    
The game is won when all the holes are filled, and lost when all the boxes are blocked.     

### How to compile it ? 🛠️
Make the game :
```shell
make
```

Make the libs :
```shell
make libs
```

Re make the game :
```shell
# This command will deleted all the compiled files
make re
```

Remove all compiled files (*.o) :
```shell
make clean
```

<p>Remove all compiled files (*.o), all compiled libs (*.a), all unit tests and program executable  :</p>

```shell
make fclean
```

Make a unit_tests file :
```shell
make unit_tests
```

Make and run a unit_tests file with the coverage :
```shell
make tests_run
```

### How to use it ? 💻
Usage :
```Shell
./my_sokoban [map]
```

A map must have the same number of holes as boxes, and must include a box, a hole and a player.    
Walls must be marked with '#'.

Map example :
```Shell
############
#        O #
#   P   ####
#          #
#######    #
#  O ##    #
#    ##    #
#          #
#       XX #
#       #  #
############
```

### Final result on my.epitech.eu 🚩
|                   Test name                    | Status |
|:----------------------------------------------:|:------:|
|   Call with an argument which is not a file    |   ✅    |
|            Call with an invalid map            |   ✅    |
|             Call with no argument              |   ✅    |
|                 Display usage                  |   ✅    |
| Mini Map : '#####\n#PXO#\n#####\n' (Free test) |   ✅    |
|         Move around a map (Free test)          |   ✅    |
|                 Other mini Map                 |   ✅    |
|                Simple move only                |   ✅    |
|              Move box on a target              |   ✅    |
|        Move box on a target (Free test)        |   ✅    |
|               Try move over wall               |   ✅    |
|         Try move over wall (Free test)         |   ✅    |
|                     Move 1                     |   ✅    |
|                     Move 2                     |   ✅    |
|                     Move 3                     |   ✅    |
|                     Move 4                     |   ✅    |
|               Play in simple map               |   ✅    |
|     Play in simple map and try go outside      |   ✅    |
|                   Double map                   |   ✅    |
|         Map with lot of box and target         |   ✅    |
|                 No square map                  |   ✅    |
|                Star shaped map                 |   ✅    |
|                 Losing a game                  |   ✅    |
|                 Winning a game                 |   ✅    |
|                 Move 1 - final                 |   ✅    |
|                 Move 2 - final                 |   ✅    |
|                 Move 3 - final                 |   ✅    |
|                 Move 4 - final                 |   ✅    |
|           Play in simple map - final           |   ✅    |
| Play in simple map and try go outside - final  |   ✅    |
|               Double map - final               |   ❌    |
|     Map with lot of box and target - final     |   ✅    |
|             No square map - final              |   ✅    |
|            Star shaped map - final             |   ✅    |
|             Losing a game - final              |   ✅    |
|             Winning a game - final             |   ✅    |

I obtained **97.2%** with **99% lines** and **90%** branches in the last test.
