# Tetris-Redux
modified version of tetris


## A high-level description of each of your public member functions in my classes
### Class Well

+ **Well** – Constructor
+ **~Well** – Destructor (unnecessary) 
+ **emptyWell** – this function is to restart the tetris board once a level is complete, it clears the board and allows for the new game to begin. I placed this in Well class because it dealt directly with the well object
+ **updateTet** – updates the coordinate with a given character, placed in the Well class because it directly modified the well behavior.
+ **viewTet** – This function allows the user to view the coordinate of the tetris board without modifying it, which is why it is constant
+ **floors** – deals with the most important part of the game, removing of completed floors. It tracks how many floors have been filled and returns the amount to be removed.

### Class Game
+	**Game** – Constructor, initialized almost everything
+	**~Game** – for pointer destruction
+	**Play** - work horse of the game. Starts a timer which is what the entire function is revolving around, if a certain time elapses from a moment when time is measured, a piece drops. This function waits on key inputs and is in charge of updating variables revolving around playing individual levels.
+	**playOneLevel** – rather unnecessary, behaves as a helper function. Returns true if the player has removed the required level count.
+	**DisplayPrompt** – instructs user on what to do next, displays string
+	**displayStatus** – displays level, rows left, and score
+	**getRandPiece** – assigns a random piece type to a pointer

###	Class Piece & Children
+	**Piece** – initializer for drop location and orientation
+	**pDisplay** – made virtual because each child displays something different
+	**PieceInWell** – places a tetris piece into the game at X=3, Y=0, with default orientation.
+	**nextPieceDisplay** – used only for the display portion of the game, prints the next tetris piece in line.
+	**Rotate** – changes the orientation of the tetris piece
+	**pieceFall** – moves the tetris piece down one coordinate if it is allowable. This function determines if it can move into the position or not.
+	**moveLeft** – moves the tetris piece to the left, if allowable. Virtual because the crazy piece moves to the right
+	**moveRight** – moves the tetris piece to right, if allowable. Virtual because the crazy piece moves to left.
+	**placePiece** – virtual function because of the foam piece and the vapor piece. Otherwise it turns the tetris piece into bricks once it has reached a lower bound.

## Design decisions and assumptions made
+	I assumed that the tetris board cannot be changed. It will remain the dimensions specified in the spec. I used vectors for my first 3 attempts. But I bit off more than I could chew and made my code more complicated than it had to be. I’m pretty happy with the final result though. Given another couple of hours. I think I could have worked out the foam bomb and any potential bugs I didn’t catch. I also assumed the play another level function was simply a helper function. It was kind of redundant to use it when a simple if statement did the same thing. Testing it was time consuming because I had to play tetris.

+	Side Note :I had an interesting bug where the right most of my well wasn’t being cleared. I didn’t realize because when I play tetris. The right most column is where I place my I pieces for clearing the board. I fixed it.
