# Terminal Fruit Catcher — ncurses Roadmap

> Goal: Learn `ncurses` by building a small terminal game where the player catches falling fruit while avoiding bombs.

**Rule:** Don't copy implementations from the roadmap. Use documentation/man pages when you don't know how something works.

---

## 0. Project Setup

* [ ] Create the project directory
* [ ] Create `main.c`
* [ ] Create this `roadmap.md`
* [ ] Compile a completely empty C program
* [ ] Figure out how to link `ncurses` when compiling
* [ ] Run the program from the terminal

### Learn

* What `ncurses` is
* Why it needs to be linked separately
* What header provides its functions
* How your compiler finds the library

---

# 1. Start ncurses

### Goal

Get a program that starts and exits cleanly using ncurses.

* [ ] Initialize ncurses
* [ ] Understand what initialization changes about the terminal
* [ ] Restore the terminal when the program exits
* [ ] Experiment with exiting using different keys

### Learn

* `initscr`
* `endwin`
* `getch`
* Basic ncurses lifecycle

---

# 2. Keyboard Input

### Goal

Make the program react to keys.

* [ ] Read a key press
* [ ] Determine which key was pressed
* [ ] Make the program react to `A`
* [ ] Make it react to `D`
* [ ] Add a quit key
* [ ] Make input work without requiring Enter
* [ ] Make input non-blocking so the game can continue while no key is pressed

### Learn

* `getch`
* `cbreak`
* `raw`
* `nodelay`
* `keypad`

Don't use every option blindly. Understand what each one changes.

---

# 3. Drawing

### Goal

Display a character at a chosen position.

* [ ] Print one character
* [ ] Put a character at a specific row/column
* [ ] Move the player horizontally
* [ ] Clear the previous frame
* [ ] Draw the new frame
* [ ] Refresh the terminal

### Learn

* Screen coordinates
* `move`
* `addch`
* `mvaddch`
* `clear`
* `refresh`

### Experiment

Try different coordinates and determine:

* Which direction is X?
* Which direction is Y?
* Where is `(0,0)`?
* What happens when you draw outside the screen?

---

# 4. Build the Player

### Goal

Create the catching platform.

Decide what information the game needs to remember.

For example, think about:

* Horizontal position
* Vertical position
* Width

Then:

* [ ] Draw the player
* [ ] Move left
* [ ] Move right
* [ ] Prevent leaving the screen
* [ ] Make movement feel reasonable

Don't create a complicated player system.

---

# 5. Create the Game Loop

### Goal

Make the game continuously update.

Think about the loop as:

```text
INPUT
  ↓
UPDATE
  ↓
DRAW
  ↓
WAIT
  ↓
INPUT
```

* [ ] Make the game continuously redraw
* [ ] Process keyboard input
* [ ] Update positions
* [ ] Draw the current state
* [ ] Add a small delay
* [ ] Make the game quit cleanly

### Learn

* Why a game needs a loop
* Why input cannot block the loop
* Why the screen needs refreshing
* How timing affects game speed

---

# 6. Add Falling Fruit

### Goal

Make one piece of fruit fall from the top.

Decide:

* [ ] Starting X position
* [ ] Starting Y position
* [ ] Falling speed
* [ ] When the fruit reaches the bottom
* [ ] What happens after it reaches the bottom

Then:

* [ ] Draw the fruit
* [ ] Move it downward
* [ ] Reset it when necessary
* [ ] Give it a random starting X position

### Learn

* `rand`
* `srand`
* Random numbers within a range
* Game coordinates
* Timing

---

# 7. Collision Detection

### Goal

Determine whether the player caught the fruit.

Think about the geometry before writing anything.

You need to answer:

> At what point should the game consider the fruit "caught"?

* [ ] Define the catching area
* [ ] Detect a collision
* [ ] Increase the score when caught
* [ ] Reset the fruit
* [ ] Detect when the fruit is missed

Keep this simple.

---

# 8. Add Bombs

### Goal

Introduce a second falling object.

* [ ] Give objects a type
* [ ] Make some objects fruit
* [ ] Make some objects bombs
* [ ] Catching fruit increases score
* [ ] Catching a bomb costs a life
* [ ] Missing fruit does something appropriate
* [ ] Decide what happens when lives reach zero

### Think

Do you actually need a `struct` yet?

If the answer is no, don't use one.

If the game starts becoming difficult to organize, that's when you can reconsider your data structure.

---

# 9. Multiple Objects

### Goal

Have several objects falling simultaneously.

* [ ] Decide how many objects can exist
* [ ] Store their positions
* [ ] Store their types
* [ ] Update every object
* [ ] Draw every object
* [ ] Check every object for collision
* [ ] Remove/reset objects when necessary

### Important

This is where your data representation starts becoming interesting.

Before writing anything, decide:

> "What information does ONE falling object need?"

Then:

> "How do I represent MANY of them?"

---

# 10. Terminal Boundaries

### Goal

Make the game work on different terminal sizes.

* [ ] Find the terminal width
* [ ] Find the terminal height
* [ ] Keep the player inside the screen
* [ ] Spawn objects inside the screen
* [ ] Handle resizing
* [ ] Decide what happens if the terminal is too small

### Learn

* `getmaxyx`
* `resize_term` / resize handling
* `KEY_RESIZE`

---

# 11. Colors

### Goal

Make the game visually readable.

Possible scheme:

* Player → one color

* Fruit → another

* Bomb → another

* Score/UI → another

* [ ] Initialize colors

* [ ] Create color pairs

* [ ] Apply colors to characters

* [ ] Experiment with bold/reverse attributes

### Learn

* `start_color`
* `init_pair`
* `attron`
* `attroff`

---

# 12. UI

Add:

* [ ] Score
* [ ] Lives
* [ ] Game title
* [ ] Controls
* [ ] Game-over screen
* [ ] Restart option

Keep the UI separate conceptually from the game world.

---

# 13. Difficulty

Make the game progressively harder.

Ideas:

* [ ] Faster objects
* [ ] More simultaneous objects
* [ ] More bombs
* [ ] Smaller catching platform
* [ ] Increasing spawn rate

Don't add everything at once.

---

# 14. Polish

Only after the game works:

* [ ] Better symbols
* [ ] Better colors
* [ ] Start screen
* [ ] Pause system
* [ ] High score
* [ ] Sound if you want to experiment
* [ ] Different fruit types
* [ ] Different bomb behavior

---

# 15. Refactoring

Now look at the code you actually wrote.

Ask yourself:

* Are any functions enormous?
* Are variables confusingly named?
* Am I repeating the same logic?
* Would a struct make something easier?
* Are there unnecessary abstractions?
* Can I separate input, game logic, and rendering?

**Don't refactor just because someone says "good C code needs X."**

Refactor because the existing code is becoming difficult to work with.

---

# 16. Optional Experiments

After the basic game works, use the project as an ncurses playground.

Try:

* [ ] Arrow keys
* [ ] WASD
* [ ] Unicode characters
* [ ] Borders
* [ ] Multiple windows
* [ ] Menus
* [ ] Text input
* [ ] Terminal resizing
* [ ] Different refresh rates
* [ ] Non-blocking input
* [ ] Mouse input
* [ ] Colored backgrounds
* [ ] Scrolling
* [ ] Randomly generated levels

---

# Final Goal

The finished game doesn't need to be impressive.

The actual goal is to reach the point where you understand:

```text
C program
    ↓
ncurses
    ↓
terminal
    ↓
input
    ↓
game state
    ↓
update
    ↓
render
    ↓
repeat
```

Once you understand that pipeline, you can reuse the knowledge for **other terminal programs and games**, not just this one.

---

## Rules for This Project

1. **Don't use AI to write the game for you.**
2. Use `man` pages and ncurses documentation when stuck.
3. Search Stack Overflow/Reddit when you need to understand a problem.
4. Don't add a feature until you understand the previous one.
5. Don't introduce structs/malloc/etc. just to make the project look sophisticated.
6. If the prototype becomes garbage, that's fine.
7. If it becomes good enough, move it from `RIdeas` into `mainProjects`.
8. If you abandon it, **you still learned something.**

