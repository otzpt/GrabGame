# GRABGAME 
## My first ever TUI game
**grabgame** is a simple and fun TUI game made entierly in c using ncurses library

## How to build

First you do
```
git clone https://github.com/otzpt/GrabGame
```
then
```bash
cd GrabGame
```
now 
```bash
make
```
that compiles the game
```bash
./grabgame
```
and now this runs the game

## Limitations

The game is linux only and to adjust settings you have to mess with the ```GrabGame.c``` file directly

## How to adjust settings

To change the ammount of objects falling alter this line:
```C
#define MAX_OBJECT 5 /* to be more specific alter the value 5 default is 5 */
```
more specific line **10**

To change the speed at wich the object falls alter this line:
```C
if (object_timer >= 20) // being specific alter the value 20 default is 20
```
more specific line **175**

## LICENSE

This game is licensed under MIT
