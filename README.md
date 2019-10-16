# grid_a_star
This is a graphical app implementing a_star algorithm to find the sortest path in a grid between two nodes.
## usage
  #### I. Drawing mode
    a: set start point (colored green) and end point (colored yellow)
    backspace: clear screen
    r: clear path
    enter: start path finding
    mouse 1: draws obstacle
    mouse 2: clears obstacle
  #### II. Path finding mode
    esc: cancel path finding
    
## flags
  #### syntax: ./main -w1920 -h1080 -n10 -r30 -d2 -f
  - **w**: window width
    - default: 800
  - **h**: window height
    - default: 600
  - **n**: node size in pixels
    - default: 15
  - **r**: render / open node discovered
    - default: 20
  - **d**: delay after every discovered openn node
    - default: 0
  - **f**: fps
    - default: 30
