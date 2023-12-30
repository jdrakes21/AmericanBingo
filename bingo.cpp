/*****************************************
** File:    bingo.cpp
** Project: CMSC 341 Project 0, Fall 2023
** Author:  Jervon Drakes
** Date:    9/10/2023
** E-mail:  jdrakes1@umbc.edu
** 
**
** This file contains the bingo.cpp file for Project 0.
** This program reads the bingo.h file and its functions and
** executes those functions for implementation
**
**
**
***********************************************/
// UMBC - CMSC 341 - Fall 2023 - Proj0

#include "bingo.h"


// Bingo( default constructor)
// Creates a bingo object 
Bingo::Bingo(){

  // initialize member variables with default values
  m_numRows = 0;
  m_minBallVal = 0;
  
  m_maxBallVal = 0;
  m_helperSize = 0;
  
  m_numCols = 0;
  m_trackCols = nullptr;

  m_trackRows = nullptr;
  m_helper = nullptr;
  
  m_card = nullptr;
}

// Bingo(copy constructor)
// Creates a bingo object with the respective default values
Bingo::Bingo(int rows, int columns, int min, int max){

  // conditional which ensures that the min value is within valid bounds
  if( min >= MINVAL && min <= MAXVAL){
    
    m_minBallVal = min;

  } else {

    
    m_minBallVal = 0; // set to a default value if out of bounds

  }

  // conditional which ensures that the max value ois within valid bounds
  if(max <= MAXVAL && max >= MINVAL){
    
    m_maxBallVal = max;

  } else {

    
    m_maxBallVal = 0; // set to a default value if out of bounds

  }
  
   // Ensure that rows are within a valid range
  if(rows >= 2 && rows <= 15){

    m_numRows = rows;

  } else {

    m_numRows = CARDROWS; // set to a default value if out of bounds

  }

  // Ensure that columns are set to 5
  if(columns == 5){

    m_numCols = columns;

  } else {

    m_numCols = CARDCOLS; // set to a default value if not 5

  }

  int range = max - min; // calculates the range for each column

  int boardSize = m_numRows * m_numCols; // calculates the size of the board

  if(range < boardSize){

    min = MINVAL; // reset min to a default value if range is not enough
    max = MAXVAL; // reset max toa default value if range is not enough

  }
    
  // initializes other member variables
  m_helperSize = BALLS;
  m_trackCols = new int[m_numCols];

  m_trackRows = new int[m_numRows];
  m_helper = new Cell[m_helperSize];

  m_card = new Cell*[m_numRows];

  for(int i = 0; i < m_numRows; i++){

    m_card[i] = new Cell[m_numCols]; // creates a 2D array for the card
  }

}

//reCreateCard(int rows, int columns, int min, int max)
//This function initializes a new card with randomly generated numbers
bool Bingo::reCreateCard(int rows, int columns, int min, int max){

  // conditional which checks that the provided parameters are valid
  if(rows < 2 || rows > 15 || columns != CARDCOLS || min < MINVAL || max > MAXVAL || (max - min +1 ) % columns != 0){

    // clears the exisiting card
    clear();
    return false;

  }

  // clear any exisiting data
  clear();

  // initializes member variables with new values from the parameters
  m_numRows = rows;
  m_numCols = columns;
  m_minBallVal = min;
  m_maxBallVal = max;

  // allocates memory for the new card created
  m_trackCols = new int[m_numCols];
  m_trackRows = new int[m_numRows];

  
  int numCells = (max - min) + 1; // calculates the number of cellts in the Bingo card
  m_helperSize = numCells;
  m_helper = new Cell[m_helperSize];

  // allocates memory for the 2D array
  m_card = new Cell*[m_numRows];
  

  for(int i = 0; i < m_numRows; i++){

    // allocates memory for each row within the card
    m_card[i] = new Cell[m_numCols];

  }

  // initilaizes the card created 
  initCard();

  // indicates the recreation was successful
  return true;
}

//Bingo(destructor)
//This is the destructor and it deallocates the memory.
Bingo::~Bingo(){

  // cleans up allocated memory and sets the member variables to default values
  clear();
    
}

void Bingo::clear(){

  // deallocates memory for these arrays
  delete[] m_trackCols;
  delete[] m_trackRows;
  delete[] m_helper;
  
  // deallocates memory for the 2d array
  for(int i = 0; i < m_numRows; i++){

    delete[] m_card[i];

  }

  delete[] m_card;

  // pointers are set to nullptr to prevent loose pointers
  m_card = nullptr;
  m_trackCols = nullptr;
  m_trackRows = nullptr;
  m_helper = nullptr;
  
  // members variables are reset to initial values
  m_numRows = 0;
  m_numCols = 0;
  m_minBallVal = 0;
  m_maxBallVal = 0;
  m_helperSize = 0;
  
  
}

//initCard
//This function populates the card cells with random numbers. Moreover, it initializes other member variables that are used as helpers
bool Bingo::initCard(){

  double rangeHelperSize = 0.2;
  
  if(m_card == nullptr){

    return false;

  }

  // calculate the size of the helper array based on the minimum and maximm ball values
  m_helperSize = (m_maxBallVal - m_minBallVal + 1);

  int innerRange = m_helperSize * rangeHelperSize; // calculates the range for the inner loop(20% of the helper size)
  int innerMin = MINVAL; // assigns innerMin as the constant MINVAL
  int innerMax = MINVAL + innerRange - 1; // calculates the innerMax based on the innerMin and innerRange

  // initializes the m_trackRows array
  for(int i = 0; i < m_numRows; i++){

    m_trackRows[i] = 0;

  }

  // initializes the m_trackCols array
  for(int i = 0; i < m_numCols; i++){

    m_trackCols[i] = 0;

  }

  // initializes the m_helper array 
  for(int i = 0; i < m_helperSize; i++){

    m_helper[i] = Cell();

  }

  // loops through each column of the bingo card
  for( int col = 0; col < m_numCols; col++){

    int count = 0;

    innerRange = m_helperSize * rangeHelperSize; // updates the innerRange based on the column size

   
    Random genRandNum(innerMin, innerMax, SHUFFLE);

    vector <int> numbersShuffled; //vector numbersShuffled is initialized to store numbers which are shuffled

    genRandNum.getShuffle(numbersShuffled); // numbers shuffled is populated with random numbers that are shuffled

    // loops through each row of the current columns    
    for( int row = 0; row < m_numRows; row++){

      // sets the row, column and value for the current cell in m_card
      m_card[row][col].setRow(row);
      m_card[row][col].setCol(col);
      m_card[row][col].setVal(numbersShuffled[count]);

      // updates that particular entre in the m_helper array
      m_helper[numbersShuffled[count] - m_minBallVal] = m_card[row][col];
      count++;

    }

    
    innerMin = innerMin + innerRange;// updates the innerMin for the next column

    innerMax = innerMax + innerRange;// updates the innerMax for the next column

  }

  return true;
  
      
}

//drawBalls
//This function generates and returns a list containing randomly distributed ball numbers
vector<int> Bingo::drawBalls(){

  // vector created to store the balls
  vector<int> ballsDrawn; 

  Random genRandom(m_minBallVal, m_maxBallVal, SHUFFLE);

  genRandom.getShuffle(ballsDrawn); // populate the vector ballsDrawn with shuffled numbers

  return ballsDrawn;
}

// play(int numDraws, vector<int>rndBalls)
//This function gets ball numbers from the vector rndBalls. If the ball number exists in the card this function replaces the corresponding cell in the card with an empty cell,             //i.e. EMPTYCELL. The function counts the number of replacements and at the end returns it. Among multiple players who are playing with the same rndBalls vector, the                       // player who gets the lowercount is the winner
int Bingo::play(int numDraws, vector<int>rndBalls){

  
  int ballCount = 0;

  int maxNum = m_maxBallVal - m_minBallVal + 1; // determines the maximum number of balls that can be drawm

  int ballsSize = rndBalls.size();
  
  if(numDraws > maxNum || ballsSize > numDraws){

    return -1; // returns -1 if the number of draws is greater than the maximum number of balls or ballsSize is greater than the number of draws
  }
  
  for(int i = 0; i < numDraws; i++){

    // determine if the drawn ball is within the required range
    if(rndBalls[i] < m_minBallVal || rndBalls[i] > m_maxBallVal){

      return - 1; // return -1 if the ball is out of range
    }

    int ballBingo = rndBalls[i] - m_minBallVal; 

    // determine if the current ball that is drawn exists on the bingo card
    if(m_helper[ballBingo].getVal() == rndBalls[i]){

      int gameRow = m_helper[ballBingo].getRow(); // retrieves the row of the ball drawn 
      int gameCol = m_helper[ballBingo].getCol(); // retireves the column of the ball drawn
      m_card[gameRow][gameCol].setVal(EMPTYCELL); // sets that cell to an empty cell

      ballCount++;

      //determines if a row or colum is completed 
      if(++m_trackRows[gameRow] == m_numCols || ++m_trackCols[gameCol] == m_numRows){

	// if the condition is true the ballCount is returned
	return ballCount;
      }
    }
        
  }
  
  // the total count of replaced cells after all the balls have been drawn is returned
  return ballCount;
    
    
}
 

// Assignment Operator
// The assignment operator creates a deep copy of rhs
const Bingo & Bingo::operator=(const Bingo & rhs){

  // check for self-assignment
  if(this == &rhs){
    return *this;
  }

  
  
  // clear exisiting data within the card
  clear();

  //if(!rhs.m_card){

  // copies member variables from the object rhs
  m_numRows = rhs.m_numRows;
  m_numCols = rhs.m_numCols;
  m_minBallVal = rhs.m_minBallVal;
  m_maxBallVal = rhs.m_maxBallVal;
  m_helperSize = rhs.m_helperSize;

  // allocates memory for new arrays
  m_trackCols = new int[m_numCols];
  m_trackRows = new int[m_numRows];
  m_helper = new Cell[m_helperSize];
  m_card = new Cell*[m_numRows];

   
  
  // copies data from the m_trackCols array to the rhs object
  for(int i = 0; i < m_numCols; i++){
    m_trackCols[i] = rhs.m_trackCols[i];

  }

  // copies data from the m_trackRows array to the rhs object
  for(int i = 0; i < m_numRows; i++){
    m_trackRows[i] = rhs.m_trackRows[i];

  }

  // copies data from the m_helper array to the rhs object
  for(int i = 0; i < m_helperSize; i++){
    m_helper[i] = rhs.m_helper[i];

  }


  for(int i = 0; i < m_numRows; i++){
    m_card[i] = new Cell[m_numCols];
    for(int j = 0; j < m_numCols; j++){
      m_card[i][j] = rhs.m_card[i][j];
    }
   }

  
  return * this;
}

// The dump function renders the card in the terminal
// This function is provided to facilitate debugging
// Using this function as a test case will not be accepted
void Bingo::dumpCard(){
    cout << "  ";
    cout << "\033[1;35m B   I   N   G   O\033[0m";    
    cout << endl;
    for (int i=1;i <= m_numRows;i++){
        if ((i < 10))
            cout << "\033[1;35m" << "0" << i << " \033[0m";
        else
            cout << "\033[1;35m" << i << " \033[0m";
        for (int j=1;j<=m_numCols;j++){
            if (m_card[i-1][j-1].getVal() == EMPTYCELL)
                cout << "\033[1;31m" << m_card[i-1][j-1].getVal() << "\033[0m" << "  ";
            else
                cout << m_card[i-1][j-1].getVal() << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

// the overloaded equality operator for the Cell object
bool operator==(const Cell & lhs, const Cell & rhs){
    return ((lhs.m_col == rhs.m_col) &&
            (lhs.m_row == rhs.m_row) &&
            (lhs.m_value == rhs.m_value));
}
