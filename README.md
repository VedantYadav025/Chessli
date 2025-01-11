# Chessly
This  is a Chess game written in C++


## I am writing my plan on how I am going about this. 

* We have made the basic structure of the board. Now, need to do move generation.
* First, let us make move generation for non-sliding pieces (King, Knight, Pawn)
* We are ignoring castling, checks and checkmates here. Just figuring out which are squares each piece can go to. 
* Done with Pawns, Knights and Kings. (En-pessant, Checks, Checkmates and promotion ignore for now)
* Started with Rooks, seems much more difficult than non-sliding pieces. Will have to look at Magic BitBoards

* Really need to re-do the file structure of the project. 


* Writing function to print the board which a human can understand (basically, repping chess pieces by text)
* Using convention of FEN strings (Black pieces by small letter, White by capital)
* Also, need to write a constructor where a FEN string is an input (first, resturcture the project)
