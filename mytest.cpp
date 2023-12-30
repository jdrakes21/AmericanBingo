/*****************************************
** File:    mytest.cpp
** Project: CMSC 341 Project 0, Fall 2023
** Author:  Jervon Drakes
** Date:    9/10/2023
** E-mail:  jdrakes1@umbc.edu
** 
**
** This file contains the mytest.cpp file for Project 0.
** This program implements functions for the tester class to 
** implement numerous test cases for the functions in bingo.cpp
**
**
**
***********************************************/
#include "bingo.h"


class Tester{
    public:
    
    // Function: Bingo::Bingo(int row, int columns, int min, int max)
    // Case: Tests the constructor for an error case (negative rows or columns)
    // Expected Result: Creates an empty object if the user tries to create an object 
    // with either negative rows or columns
    bool constructorErrorTest(){

  
    // creates a Bingo object called gameBingo with invalid paramters (-5 and 5 for the numer of rows and columns respectively)
    Bingo gameObject(-5, 5, MINVAL, MAXVAL);

    // returns true if the number of rowx and columns in the object match CARDROWS AND CARDCOLS
    // This indicates that the constructor handles the invalid input correctly
    return gameObject.m_numRows == CARDROWS && gameObject.m_numCols == CARDCOLS;
  }

    // Function: Bingo::Bingo(int row, int columns, int min, int max)
    // Case: Tests the constructor of the Bingo class with normal input values
    // Expected result:  Creates memory and initializes all member variables with proper values if the user tries
    // create an bject with valid input values
    bool constructorTestNormal(){
      
      // creates a bingo objectwith normal input value
      Bingo Objectgame(10, 5, MINVAL, MAXVAL);

      // returns true if the rows, columns, minimum value and maximum value match
      // indicates the constructor correctly initialized the object
      return Objectgame.m_numRows == 10 && Objectgame.m_numCols == 5 && Objectgame.m_minBallVal == MINVAL && Objectgame.m_maxBallVal == MAXVAL;
    }

  // Function: Bingo::Bingo(int row, int columns, int min, int max)
  // Case: Test the constructor of the Bingo class with edge case input values
  // Expected Result: Creates memory and defaults the number of rows to CARDROWS and cols to CARDCOLS.
  // Also initializes member variables with valid input values 
  bool constructorTestEdgeCase(){
    
    // Create a bingo object with edge case input values
    Bingo bingoGame(1, 5, MINVAL, MAXVAL);
    
    // returns true if both the number of rows and columns match the expected default value
    // indicates that the constructor correctly handles the edge case input
    return bingoGame.m_numRows == CARDROWS && bingoGame.m_numCols == CARDCOLS;

  }

  // Function: Bingo::reCreateCard(int row, int column, int kin, int max)
  // Case: Tests the reCreateCard function of the bingo class with invalid input values
  // Expected result: Creates an empty object if the user tries to create an object 
  // with either negative rows or columns
  bool reCreateCardErrorTest(Bingo &bingoObject, int gameRows, int gameColumns){
     
    bool gameResult = false; // initialize gameResult to false

    gameResult = gameResult && (bingoObject.reCreateCard(gameRows, gameColumns, MINVAL, MAXVAL));// calls the reCreateCard function on the bingo Object

    return gameResult;
      

  }

  //Function: Bingo::reCreateCard(int row, int column, int kin, int max)
  //Case: Tests the reCreateCard function of the Bingo class with edge case input values
  //Expected result: This method will successfully recreate the bingoCard with the provided cardRows and cardCols
  //within the specified minimum and maximum ball value range
  bool reCreateCardEdgeCase(Bingo &game, int cardRows, int cardCols){

    bool edgeCaseResult = true; // initialize edgeCaseResult to true
    
    edgeCaseResult = edgeCaseResult && (game.reCreateCard(cardRows, cardCols, MINVAL, MAXVAL));

    // if the reCreateCard method succeeds the function will return true
    // indicating that the edge case was hadnled successfully
    return edgeCaseResult;
  }

  //Function: Bingo::reCreateCard(int row, int column, int kin, int max)
  //Case: Tests the reCreateCard function of the Bingo class with valid input values
  //Expected result: Creaes a new Card with memory and initializes all member variables with proper values
  bool reCreateCardNormalTest(Bingo &boardObject, int boardRows, int boardCols){

    boardObject.clear(); // clears the Bingo object before recreating the card

    bool boardResult = boardObject.reCreateCard(boardRows, boardCols, MINVAL, MAXVAL);
    
    // determines if the methods fails
    // if it has then false is returned which indicated the test case failed
    if(!boardResult){

      return false;
    }

    // determines if the number of rows and columns in the object
    // matches the provided boardRows and boardCols
    // returns true if that is the case which indicates the method worked successfully
    return boardObject.m_numRows == boardRows && boardObject.m_numCols == boardCols;
  }
  
  //Function: Bingo::clear()
  //Case: Test the clear function of the bingo class given valid input values for a Binog object
  //Expected Result: All dynamically memory is properly deallocated and the object's
  // attributes are set to default values
  bool testClearNormal(){
    
    // Creates a bingo object with specified parameter values
    Bingo testObj(5, 5, 1, 25);
    
    // clears the object
    testObj.clear(); 

    // check if all member variables are set to default values
    // if so then the case has passed
    return (testObj.m_numRows == 0 && testObj.m_numCols == 0 && testObj.m_minBallVal == 0 && testObj.m_maxBallVal == 0 && testObj.m_helperSize == 0
    && testObj.m_trackCols == nullptr && testObj.m_trackRows == nullptr && testObj.m_helper == nullptr && testObj.m_card == nullptr);
    
  }
  //Function: Bingo::initCard
  //Case: Tests the initCard function if it were to be called on an empty object
  //Expected Result: The object will stay an empty object once the call is finished 
  bool initCardTestError(Bingo &bingo){


    bingo.clear(); // clear the Bingo object before the card is initalized

    bool result = bingo.initCard(); // call the initCard function on the object

    // returns the inervse of the result
    // (true if initCard failed, or false if succeeded)
    // indicates that the test passes if the initCard function returns false
    return !result;
  }

  //Function: Bingo::initCard
  //Case: Tests the iniCard function of the bingo Class if the object has a 5x5 card
  //Expected Result:  The cells in m_card are initialized to the correct value as the value in every column
  // fall within the correct range 
  bool initCardTestNormal(Bingo &bingoBoard){

    // creates a temporary bingo object
    Bingo bingo(CARDROWS, CARDCOLS, MINVAL, MAXVAL);

    bool validResult = bingo.initCard(); // initializes the card of the temporary object

    // if the initialization fails, then a test failure occurs
    if(!validResult){
      
      return false;
    }

    int gameCol;
    int gameRow;

    // Iterates through each columns of the card and verifies
    // that the values in each column is within the expected range
    for(gameCol = 0; gameCol < CARDCOLS; gameCol++){

      int expectedMin = MINVAL + (gameCol * ((MAXVAL - MINVAL + 1) / CARDCOLS));// calculate the expected minimum value
      int expectedMax = MINVAL + (gameCol + 1) * ((MAXVAL - MINVAL +1) / CARDCOLS) - 1;// calculate the expected maximum value

      // iterate through each row in t corresponding column of the object
      for(gameRow = 0; gameRow < bingoBoard.m_numRows; gameRow++){

	int bingoValue = bingoBoard.m_card[gameRow][gameCol].getVal();

          // determines if the bingoValue falls within that range for this column  
	if(bingoValue < expectedMin || bingoValue > expectedMax){
            
            // returns false if it does not which means the test has failed
	  return false;
	} 
      }
    }

    // returns true and the test has passed if the values
    // meet the expected ranges for reach column
    return true;
  }


  //Function: Bingo::play(int numDraws, vector<int> rndBalls)
  //Case: Tests the play function of the bingo class with invalid inputs
  //Expected Result: An error should occur due to the presence of invalid ball values
  bool playTestError(Bingo &bingoGame){

    bingoGame.clear(); // clears the Bingo object before the simulation begins

    vector<int> bingoBalls = {0, 75, 50, -20}; // initializes a vector which includes an invalid value

    int bingoResult = bingoGame.play(bingoBalls.size(), bingoBalls); // calls the play function on the object

    // determines if the result is -1 which would indicate
    // that an error occurred and the test case passed
    return bingoResult == -1; 
  }
  
  //Function: Bingo::play(int numDraws, vector<int> rndBalls)
  // Case: Tests the play function of the Bingo class with valid input values
  //Expected Result: The balls are successfully played and the card is empty at the end of the game
  bool playTestNormalCase(Bingo &gameBingo){

    gameBingo.clear(); // the object is cleared before play is simulated


    // loops and initialized the card with numbers and set row and col values 
    for(int i =0; i < gameBingo.m_numRows; i++){
      for(int j = 0; j < gameBingo.m_numCols; j++){

	gameBingo.m_card[i][j].setVal(i * gameBingo.m_numCols + j + 1);
	gameBingo.m_card[i][j].setRow(i);
	gameBingo.m_card[i][j].setCol(j);
      }

    }

    // vector created to simulate balls being drawm
    vector<int>bingoBalls;
 
    // balls are drawn and the result is checked 
    for(int i = 1; i <= gameBingo.m_numRows * gameBingo.m_numCols; i++){
      
      bingoBalls.push_back(i);

      int ballResult = gameBingo.play(i, bingoBalls);

      // if the result does not match the ball drawn then there
      // is a test failure
      if(ballResult != i){

	return false;

      }
    }

    // Determines if the cells on the card are empty once all 
    // balls are drawm
    for(int i = 0; i < gameBingo.m_numRows; i++){
      for(int j = 0; j < gameBingo.m_numCols; j++){

	if(gameBingo.m_card[i][j].getVal() != EMPTYCELL){
	      
	  return false;
	}
      }
    }
    
    // returns ture and the case has passed oncethe balls are played successfully and the card is empty  
    return true;
  }
  
  //Function: Bingo::play(int numDraws, vector<int> rndBalls)
  //Case: Tests the play function of the bingo Class if there are no balls to be drawm
  //Expected Result: No balls are drawn and the play method would return 0 as there is 
  // an empty set of bingo balls 
  bool playTestEdgeCase(Bingo &board){
    
    //clear the object before play commences
    board.clear(); 

    // empty vector created
    vector<int> emptyBalls; 

    int edgeCaseResult = board.play(emptyBalls.size(), emptyBalls); // play function is called on the object
    
    // determines if the result is 0 which indicates that no balls were drawn
    // indicating a successful case
    return edgeCaseResult == 0; 

  }

  //Function: const Bingo & operator=(const Bingo & rhs)
  //Case: Tests the assignment operator of the bingo Class with an edge
  //(Assigning an empty object to an object with regular data)
  //Expected Result: The attributes of lhs should be set to 0
  bool assignmentOperatorEdgeCase(Bingo &lhs, Bingo &rhs){

  // object is cleared 
  rhs.clear(); 

  lhs = rhs; // the rhs obect is assigned to the lhs object
  
  // determines if the attributed of lhs match the expected values
  // if all attributes set to 0 then the case has passed
  return lhs.m_numRows == 0 && lhs.m_numCols == 0 && lhs.m_minBallVal == 0 && lhs.m_maxBallVal == 0;

  }

   //Function: const Bingo & operator=(const Bingo & rhs)
   //Case: Tests the assignment operator for the bingo Class on objects that  both contain data
   //Expected Result: The objects should be exact copies of each. 
   // Their attributes are to be identical
   bool assignmentNormal(Bingo & lhs, Bingo & rhs){

     // lhs = rhs;
        // we expect that lhs object is an exact copy of rhs object
     bool result = true;
        // we expect that the corresponding cells in lhs and rhs
        //      cards carry the same cell information (exact same copy)
     for (int i = 0; i<rhs.m_numRows;i++){
       for (int j=0;j<rhs.m_numCols;j++){
	 result = result && (lhs.m_card[i][j] == rhs.m_card[i][j]);
       }
     }
        // we expect that the corresponding cells in lhs and rhs
        //      m_helper carry the same cell information (exact same copy)
     for (int i=0;i<rhs.m_helperSize;i++){
       result = result && (lhs.m_helper[i] == rhs.m_helper[i]);
     }
        // we expect that the corresponding cells in lhs and rhs
        //      m_trackRows carry the same cell information (exact same copy)
     for (int i=0;i<rhs.m_numRows;i++){
       result = result && (lhs.m_trackRows[i] == rhs.m_trackRows[i]);
     }
        // we expect that the corresponding cells in lhs and rhs
        //      m_trackCols carry the same cell information (exact same copy)
     for (int i=0;i<rhs.m_numCols;i++){
       result = result && (lhs.m_trackCols[i] == rhs.m_trackCols[i]);
     }
     result = result && (lhs.m_minBallVal == rhs.m_minBallVal);
     result = result && (lhs.m_maxBallVal == rhs.m_maxBallVal);
     return result;
   }

  
    private:
    
    /**********************************************
    * If we need helper functions to be reused in *
    *   test functions they can be declared here!
    **********************************************/
};


int main() {
  
  // creates a Tester object for test case purposes
  Tester tester;

  // creates a bingo object with specified values
  Bingo obj(CARDROWS, CARDCOLS, MINVAL, MAXVAL);

  Bingo obj1;
  
  // outputs whether the error case for the constructor passed or failed
  cout << "Testing Constructor Error Case: " << (tester.constructorErrorTest() ? "passed" : "failed") << endl;

  cout << "                                " << endl;
  
  // outputs whther the edge case for the constructor passed or failed
  cout << "Testing Constructor Edge Case: " << (tester.constructorTestEdgeCase() ? "passed" : "failed") << endl;

  cout << "                                " << endl;
  
  // outputs whether the normal case for the constructor passed or failed
  cout << "Testing Constructor Normal Case: " << (tester.constructorTestNormal() ? "passed" : "failed") << endl;

  cout << "                                " << endl;
  
  cout << "Testing reCreateCard Error case: " << endl;

  //perfoms the error case method and determines if it passed or failed
  if(tester.reCreateCardErrorTest(obj, -5 , 10) == true){
    
    cout << "Error Case failed " << endl;
    
  } else {

    cout << "Error Case passed " << endl;

  }

  cout << "                                " << endl;

  cout << "Testing reCreatCard Normal Case: " << endl;

  // performs the normal case method for reCreateCard and determines if it passed or failed
  if(tester.reCreateCardNormalTest(obj, 10, 5)){

    cout << "Normal Case passed " << endl;

  } else { 

    cout << "Normal Case failed " << endl;

  }

  cout << "                                " << endl;

  cout << "Testing reCreateCard Edge Case: " << endl;
  
  // determines if the edge case for reCreateCard passed or failed
  if(tester.reCreateCardEdgeCase(obj, 2, 5)){

    cout << "Edge Case passed" << endl;

  } else {

    cout << "Edge Case failed" << endl;

  }

  cout << "                                " << endl;

  cout << "Testing Clear Normal Case: " << endl;

  if(tester.testClearNormal()){

    cout << "Normal Case passed" << endl;

  }else{

    cout << "Normal Case failes" << endl;

  }
  

  cout << "                                " << endl;

  cout << "Testing initCard Error Case: " << endl;

  // determines if the error case for initCard passed or failed
  if(tester.initCardTestError(obj)){

    cout << "Error Case passed " << endl;

  } else {

    cout << "Error Case failed " << endl;
  }

  cout << "                                " << endl;

  cout << "Testing initCard Normal Case: " << endl;
  
  // determines if the normal case for initCard passed or failed
  if(tester.initCardTestNormal(obj)){

    cout << "Normal Case passed " << endl;

  } else {

    cout << "Normal Test failed " << endl;

  }

  cout << "                                " << endl;

  cout << "Testing play Error Case: " << endl;
  
  // determines if the error case for play passed or failed
  if(tester.playTestError(obj)){

    cout << "Error Case passed " << endl;

  } else {

    cout << "Error Case failed " << endl;
  }

  cout << "                                " << endl;

  cout << "Testing play Normal Case: " << endl;
  
  // determines if the normal case for play passed or failed
  if(tester.playTestNormalCase(obj)){

    cout << "Normal Case passed " << endl;

  } else {

    cout << "Normal Test failed " << endl;

  }

  cout << "                                " << endl;

  cout << "Testing play Edge Case: " << endl;
  
  // determines if the edge case for play passed or failed
  if(tester.playTestEdgeCase(obj)){

    cout << "Edge Case passed " << endl;

  } else {

    cout << "Edge Case failed " << endl;

  }

  cout << "                                " << endl;

  cout << "Testing Assignment Operator Normal Case: " << endl;
  
  // determines if the normal case for the assignment operator passed or failed
  if(tester.assignmentNormal(obj1, obj)){

    cout << "Normal Case passed " << endl;

  } else {

    cout << "Normal Test failed " << endl;

  }

  cout << "                                " << endl;

  cout << "Testing Assignment Operator Edge Case: " << endl;
  
  // determines if the edge case for the assignment operator passed or failed
  if(tester.assignmentOperatorEdgeCase(obj, obj1)){

    cout << "Edge Case passed " << endl;

  } else {

    cout << "Edge Case failed " << endl;

  }


  return 0;
  

}						
