# Conway's Game of Life

---

![Conways_Game_of_Life_SparkVideo.gif](Conway's%20Game%20of%20Life%209a87649a184648c3bc54268466710fa8/Conways_Game_of_Life_SparkVideo.gif)

Conway's Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970.

## Table of Contents

---

1. Project Overview
2. How to compile and run

## Project Overview

---

Conway's Game of Life, made with C++ and SDL. 

### How does the game work?

Conway's Game of Life follows 4 unique rules.

1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

```cpp
for(int i = 0;i < row;i++){
        for(int j = 0;j < col;j++){
            
            int state = CalculateCellState(j,i);

            if(m_Gameworld[j + i * col] == 0){

                if(state == 3) 
                    m_Gameworldbuffer[j + i * col] = 1;

            } else if(m_Gameworld[j + i * col] == 1) {

                        if(state < 2 || state > 3)
                            m_Gameworldbuffer[j + i * col] = 0;
                        else 
                            m_Gameworldbuffer[j + i * col] = 1;
            
                    }
           
         }
}
```

Each cell could be seen as an element of a 2d array we call the game world and a buffer world a Gameworld buffer. The rules are applied with the game world and the buffer world is updated based on it. 

How to determine " how to update "? 

```cpp
	int sum = 0;
    for(int i = -1;i < 2;i++){

        for(int j = - 1;j < 2;j++){

            int x_pos = (j + x_worldPosition);
            int y_pos = (i + y_worldPosition);

            if((x_pos >= 0 && x_pos <= col - 1) && (y_pos >= 0 && y_pos <= row - 1) ){
                sum += m_Gameworld[x_pos + col * y_pos];
            }
        }

    }
        
    sum -= m_Gameworld[x_worldPosition + y_worldPosition * col];

	  return sum;
```

This system calculates a "state" variable that is like a penalty system that would determine how to update the squares around. 

Got the idea from the Coding train, link to the video for that is below.

[https://www.youtube.com/watch?v=FWSR_7kZuYg](https://www.youtube.com/watch?v=FWSR_7kZuYg)

### The Application

The application is implemented by the state machine. The application has 4 states.

1. Enter 
2. Run
3. Pause
4. Exit

**Enter State** 

- Enter state is the state the application enters by default.
- Here the 'game world' is set initially

**Run**

- The Run state is the state that runs 'Conway's Game of Life.

**Pause**

- In the Pause state, it pauses the application
- allows tinker with the 'game world' by setting new cells.

**Exit**

- Exit state quits the application.

![State diagram.drawio.png](Conway's%20Game%20of%20Life%209a87649a184648c3bc54268466710fa8/State_diagram.drawio.png)

## How to Compile and Run

---

Makefile is used to compile the code 

```makefile
make bin/applicationname
```

To compile and line the files.

```makefile
make applicationame
```

To run the code.