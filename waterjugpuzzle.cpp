//header
/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Patrick Besser, Matthew Jacobsen
 * Date        : October 11, 2019 
 * Description : Solves the famous water jug puzzle using breadth-first search 
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
// imports
#include <iostream>
#include <sstream>
#include <vector>
//#include <algorith>
#include <stdlib.h>
#include <queue>

using namespace std;
// state
 struct State
{
    int a, b, c;
    vector<string> directions;

    State(int _a, int _b, int _c, vector<string> _directions) : a(_a), b(_b), c(_c), directions(_directions) {}

    // String representation of state in tuple form.
    string to_string()
    {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";  
        return oss.str();
    }
    // to compare different states to one another which will eventually be used to check if we have reached an asnwer
      int compareTo(State &temp){
          if(a == temp.getA() &&  b == temp.getB() && c == temp.getC()){
                return 0;
      }
          else{
                return 1;
          }
      }

    void out(){
        for(unsigned int x = 0; x < directions.size();x++){
            cout << directions[x] << endl; 
        }
    }
    
      int getA(){
            return a;
      }
      int getB(){
          return b; 
      }
      int getC(){
          return c; 
      }
};

// breadth first search
 State paths( State top,  State currentCap,  State finish, bool** map){
// BFS for our jugs
queue<State> directions; // initalize temp array(queue) to store directions
top.directions.push_back("Inital state. "+top.to_string()); //put inital inion in the directions vector
map[top.a][top.b] = true;
directions.push(top); // push initial state to the queue 
while(!(directions.empty())){
    top = directions.front();
    directions.pop();

     if (top.a == finish.a && top.b == finish.b && top.c == finish.c){
            return top;
        }//checks if C can pour into A
    //1) Pour from C to A
    if(top.c > 0 && (currentCap.a - top.a) > 0){
        State currentMove = top; //variable used to hold the current move, while we decide to push it, or get rid of it
        int drain = currentCap.getA() - currentMove.getA(); //drain is the difference between the current capacity of jug A - the state of jug A
        if(drain > currentMove.c){
            currentMove.a = (currentMove.a + top.c); // if the difference between the two jugs 
            currentMove.c = 0;
        }
    else{
        currentMove.c = (currentMove.c - drain); // actually make the move 
        currentMove.a = currentCap.a; 
    }
    // check if we have been here before 
    if(map[currentMove.getA()][currentMove.getB()] == false){
        map[currentMove.getA()][currentMove.getB()] = true;
        if(drain == 1 || top.c == 1){ // check if the move has one gallon 
            // add direction to our queue Condition: 1 gallon moving 
            currentMove.directions.push_back("Pour 1 gallon from C to A. " + currentMove.to_string());
            directions.push(currentMove);
        }
        else{
            // add direction to our queue, Condition : more than one gallon
            currentMove.directions.push_back("Pour " + to_string(min(drain, top.c)) + " gallons from C to A. " + currentMove.to_string());
            directions.push(currentMove);
    }
    }
} 


//2) Pour from B to A
    if(top.b > 0 && (currentCap.a - top.a) > 0){
        State currentMove = top; //variable used to hold the current move, while we decide to push it, or get rid of it
        int drain = currentCap.getA() - currentMove.getA(); //drain is the difference between the current capacity of jug A - the state of jug A
        if(drain > currentMove.b){
            currentMove.a = (currentMove.a + top.b); // if the difference between the two jugs
            currentMove.b = 0;
        }
    else{
        currentMove.b = (currentMove.b - drain); // actually make the move 
        currentMove.a = currentCap.a; 
    }
    // check if we have been here before 
    if(map[currentMove.getA()][currentMove.getB()] == false){
        map[currentMove.getA()][currentMove.getB()] = true;
        if(drain == 1 || top.b == 1){ // check if the move has one gallon 
            // add direction to our queue Condition: 1 gallon moving 
            currentMove.directions.push_back("Pour 1 gallon from C to A. " + currentMove.to_string());
            directions.push(currentMove);
        }
        else{
            // add direction to our queue, Condition : more than one gallon
            currentMove.directions.push_back("Pour " + to_string(min(drain, top.b)) + " gallons from C to A. " + currentMove.to_string());
            directions.push(currentMove);
    }
    }
}


//a=b
//keep c
//3) Pour from C to B
    if(top.c > 0 && (currentCap.b - top.b) > 0){
        State currentMove = top; //variable used to hold the current move, while we decide to push it, or get rid of it
        int drain = currentCap.getB() - currentMove.getB(); //drain is the difference between the current capacity of jug A - the state of jug A
        if(drain > currentMove.c){
            currentMove.b = (currentMove.b + top.c); // if the difference between the two jugs
            currentMove.c = 0;
        }
    else{
        currentMove.c = (currentMove.c - drain); // actually make the move 
        currentMove.b = currentCap.b; 
    }
    // check if we have been here before 
    if(map[currentMove.getA()][currentMove.getB()] == false){
        map[currentMove.getA()][currentMove.getB()] = true;
        if(drain == 1 || top.c == 1){ // check if the move has one gallon 
            // add direction to our queue Condition: 1 gallon moving 
            currentMove.directions.push_back("Pour 1 gallon from C to A. " + currentMove.to_string());
            directions.push(currentMove);
        }
        else{
            // add direction to our queue, Condition : more than one gallon
            currentMove.directions.push_back("Pour " + to_string(min(drain, top.c)) + " gallons from C to A. " + currentMove.to_string());
            directions.push(currentMove);
    }
    }

//C.A    :   A.B
//c=a
//a=b
//4) Pour from A to B
    if(top.c > 0 && (currentCap.b - top.b) > 0){
        State currentMove = top; //variable used to hold the current move, while we decide to push it, or get rid of it
        int drain = currentCap.b - currentMove.b; //drain is the difference between the current capacity of jug A - the state of jug A
        if(drain > currentMove.a){
            currentMove.b = (currentMove.b + top.a); // if the difference between the two jugs
            currentMove.a = 0;
        }
    else{
        currentMove.a = (currentMove.a - drain); // actually make the move 
        currentMove.b = currentCap.b; 
    }
    // check if we have been here before 
    if(map[currentMove.getA()][currentMove.getB()] == false){
        map[currentMove.getA()][currentMove.getB()] = true;
        if(drain == 1 || top.a == 1){ // check if the move has one gallon 
            // add direction to our queue Condition: 1 gallon moving 
            currentMove.directions.push_back("Pour 1 gallon from C to A. " + currentMove.to_string());
            directions.push(currentMove);
        }
        else{
            // add direction to our queue, Condition : more than one gallon
            currentMove.directions.push_back("Pour " + to_string(min(drain, top.a)) + " gallons from C to A. " + currentMove.to_string());
            directions.push(currentMove);
    }
    }
}
//C.A    :   B.C
//c=b
//a=c
//5) Pour from B to C
    if(top.b > 0 && (currentCap.c - top.c) > 0){
        State currentMove = top; //variable used to hold the current move, while we decide to push it, or get rid of it
        int drain = currentCap.c - currentMove.c; //drain is the difference between the current capacity of jug A - the state of jug A
        if(drain > currentMove.b){
            currentMove.c = (currentMove.c + top.b); // if the difference between the two jugs
            currentMove.b = 0;
        }
    else{
        currentMove.b = (currentMove.b - drain); // actually make the move 
        currentMove.a = currentCap.c; 
    }
    // check if we have been here before 
    if(map[currentMove.getA()][currentMove.getB()] == false){
        map[currentMove.getA()][currentMove.getB()] = true;
        if(drain == 1 || top.b == 1){ // check if the move has one gallon 
            // add direction to our queue Condition: 1 gallon moving 
            currentMove.directions.push_back("Pour 1 gallon from C to A. " + currentMove.to_string());
            directions.push(currentMove);
        }
        else{
            // add direction to our queue, Condition : more than one gallon
            currentMove.directions.push_back("Pour " + to_string(min(drain, top.b)) + " gallons from C to A. " + currentMove.to_string());
            directions.push(currentMove);
    }
    }
}
//B.C    :   A.C
//b=a
//c=c
//6) Pour from A to C
    if(top.a > 0 && (currentCap.c - top.c) > 0){
        State currentMove = top; //variable used to hold the current move, while we decide to push it, or get rid of it
        int drain = currentCap.c - currentMove.c; //drain is the difference between the current capacity of jug A - the state of jug A
        if(drain > currentMove.a){
            currentMove.c = (currentMove.c + top.a); // if the difference between the two jugs
            currentMove.a = 0;
        }
    else{
        currentMove.a = (currentMove.a - drain); // actually make the move 
        currentMove.a = currentCap.c; 
    }
    // check if we have been here before 
    if(map[currentMove.getA()][currentMove.getB()] == false){
        map[currentMove.getA()][currentMove.getB()] = true;
        if(drain == 1 || top.a == 1){ // check if the move has one gallon 
            // add direction to our queue Condition: 1 gallon moving 
            currentMove.directions.push_back("Pour 1 gallon from C to A. " + currentMove.to_string());
            directions.push(currentMove);
        }
        else{
            // add direction to our queue, Condition : more than one gallon
            currentMove.directions.push_back("Pour " + to_string(min(drain, top.a)) + " gallons from C to A. " + currentMove.to_string());
            directions.push(currentMove);
    }
    }
}

}
}
    top.directions.clear();
    top.directions.push_back("No solution.");
    return top;
}

//makes visited array 
    bool** makeMatrix(int a, int b) {
    bool ** map = new bool*[a];
    for (int i = 0; i < a; i++){
        map[i] = new bool[b];
        fill(map[i], map[i] + b,false);
    }
    return map;
}
    
//find solution function
void solve(vector<int> input){
    vector<string> directions;



    State finish(input[3], input[4], input[5], directions);
    State begin(0, 0, input[2], directions);
    State currentCap(input[0], input[1], input[2], directions);
    bool ** map = makeMatrix(input[0] + 1, input[1] + 1);
    
    //call BFS for all the given peramaters
    //then print the output;
    //error: could not convert ‘map’ from ‘bool**’ to ‘std::vector<std::__cxx11::basic_string<char> >’  
    finish = paths(begin,currentCap,finish,map);
    finish.out(); 
    //deletes the visted array
    for(int i=0; i<currentCap.getB();i++){
        delete[] map[i];
    }
    delete[] map; 
}

//main method that does input validation and calls solution function

int main(int argc, char *const argv[])
{ //MAIN METHOD

    int compare;

    if (argc != 7)
    { //check for correct number of arguments
        cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"
             << endl; //print the corresponding error message
        return 1;     //return integer to satasify the definition of the main
    }

    istringstream iss; //define i string stream
    for (int i = 1; i < 7; i++)
    {
        iss.str(argv[i]); //update istringstream
        if (i >= 1 && i <= 3)
        { // capacity cases
            if (i == 1)
            { //jug A
                if (!(iss >> compare) || (compare < 0) || (compare == 0 && i == 3))
                {
                    cerr << "Error: Invalid capacity '" << argv[i] << "' for jug A." << endl;
                    return 1;
                }
            }
            if (i == 2)
            { //Jug B
                if (!(iss >> compare) || (compare < 0) || (compare == 0 && i == 3))
                {
                    cerr << "Error: Invalid capacity '" << argv[i] << "' for jug B." << endl;
                    return 1;
                }
            }
            if (i == 3)
            { //Jug C
                if (!(iss >> compare) || (compare < 0) || (compare == 0 && i == 3))
                {
                    cerr << "Error: Invalid capacity '" << argv[i] << "' for jug C." << endl;
                    return 1;
                }
            }
            iss.clear();
        }
        if (i > 3)
        { //goal cases
            if (i == 4)
            { //jug A
                if (!(iss >> compare) || (compare < 0) || (compare == 0 && i == 3))
                {
                    cerr << "Error: Invalid goal '" << argv[i] << "' for jug A." << endl;
                    return 1;
                }
            }
            if (i == 5)
            { //Jug B
                if (!(iss >> compare) || (compare < 0) || (compare == 0 && i == 3))
                {
                    cerr << "Error: Invalid goal '" << argv[i] << "' for jug B." << endl;
                    return 1;
                }
            }
            if (i == 6)
            { //Jug C
                if (!(iss >> compare) || (compare < 0) || (compare == 0 && i == 3))
                {
                    cerr << "Error: Invalid goal '" << argv[i] << "' for jug C." << endl;
                    return 1;
                }
            }
            iss.clear();
        }
    }

    //convert inputs to ints bc we already know that they are valid, non-negative integers
    int cA = atoi(argv[1]);
    int cB = atoi(argv[2]);
    int cC = atoi(argv[3]);
    int gA = atoi(argv[4]);
    int gB = atoi(argv[5]);
    int gC = atoi(argv[6]);

    // compare 1 to 4 aka A to A
    if (cA < gA)
    {
        cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    //compare 2 to 5 aka B to B
    if (cB < gB)
    {
        cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    //compare 3 to 6 aka C to C
    if (cC < gC)
    {
        cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }

    // is goal A + goal B + goal C = Cap C
    if ((gA + gB + gC) == cC)
    {
        vector<string> directs;
        //call waterjug
        //top by initalizing our 3 states. Where we start. What our capacities are and our final goal to fulfill
        // State *top = new State(0, 0, stoi(argv[3]));                              // top
        //  State currentCap = new  State(stoi(argv[1]), stoi(argv[2]), stoi(argv[3]),directs); //cap of jugs
        //  State finish = new  State(stoi(argv[4]), stoi(argv[5]), stoi(argv[6]),directs);     // goals to find
        //call methods
        //as said in class we need to find all possible paths to find the answer and then BFS to get the solution
        vector<int> input = {cA,cB,cC,gA,gB,gC};
        solve(input);
        cout << "works" << endl;
        return 0;
    }
    else
    { // if not then the gal in state isnt equal to the capacity of jug C so throw error and return
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }
}
