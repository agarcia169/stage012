//Alex Garcia && Adebolanle Balogun
//Stage 0



#include <ctime>
#include <iostream> 
#include <cctype>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stage0.h>
#include <iomanip>
#include <set>

using namespace std;


Compiler::Compiler(char **argv) // constructor
   {
      sourceFile.open(argv[1]);
      listingFile.open(argv[2]);
      objectFile.open(argv[3]);
   }
   
Compiler::~Compiler() // destructor
   {
      sourceFile.close();
      listingFile.close();
      objectFile.close();
   }

void Compiler::createListingHeader()
   {
      time_t now = time (NULL);
      listingFile << "STAGE0:  Alex Garcia & Adebolanle Balogun" << ctime(&now) << "\n";
      listingFile << "LINE NO:               " << "SOURCE STATEMENT\n";
   }

void Compiler::parser()
   {
      nextChar();
      cout << "enter parser zone\n";
      if (nextToken() != "program")
         processError("keyword \"program\" expected");
      prog();

   }
void Compiler::createListingTrailer()
   {
      //possible right needed to justify right
      listingFile << "COMPILATION TERMINATED " << errorCount <<  " ERRORS ENCOUNTERED\n";
   }

void Compiler::processError(string err)
   {
      errorCount++;
      listingFile << "Error: " << "Line "<< lineNo << ". " << err << "\n";
      createListingTrailer();
      exit(1);
   }

void Compiler::insert(string externalName,storeTypes inType, modes inMode, string inValue,
allocation inAlloc, int inUnits)

{
   cout << "you just entered the insert zone\n";
   
   string name = externalName;
   while (name != "")
   {
      if (symbolTable.count(name) != 0)
         processError("multiple name definition");
      else if (isKeyword(name))
         processError("illegal use of keyword");
      else //create table entry
         {
            if (isupper(name[0]))
               symbolTable.insert(pair<string, SymbolTableEntry>(name, SymbolTableEntry(name,inType,inMode,inValue,inAlloc,inUnits)));
            else
            //does this:                                 
               symbolTable.insert(pair<string, SymbolTableEntry>(name, SymbolTableEntry(genInternalName(inType),inType,inMode,inValue,
                                 inAlloc,inUnits)));
            // need to be this?:
            // symbolTable[name] = SymbolTableEntry.SymbolTableEntry(genInternalName(inType),inType,inMode,inValue,inAlloc,inUnits)
         }
   }
}


storeTypes Compiler::whichType(string name) //tells which data type a name has
   {
      storeTypes dataType;
      if (isLiteral(name))
         if (isBoolean(name))
            dataType = BOOLEAN;
         else
            dataType = INTEGER;
      else {
         if (symbolTable.count(name) != 0)
            dataType = symbolTable.find(name)->second.getDataType();
         else
            processError("reference to undefined constant");
      }
      return dataType;
   }


string Compiler::whichValue(string name) //tells which value a name has
   {
      cout << "You just entered the value zone" << endl;
      string value;
      if (isLiteral(name))
         value = name;
      else //name is an identifier and hopefully a constant
         if (symbolTable.count(name) != 0 && symbolTable.find(name)->second.getValue() != "")
            {value = symbolTable.find(name)->second.getValue();}
         else
            {processError("reference to undefined constant");}
      return value;
   }


//FIXME
void Compiler::code(string op, string operand1, string operand2)
   {
      if (op == "program")
         emitPrologue(operand1);
      else if (op == "end")
         emitEpilogue();
      else if (op == "read")
         emit read code
      else if (op == "write")
         emit write code
      else if (op == "+") // this must be binary '+'
         emit addition code
      else if (op == "-") // this must be binary '-'
         emit subtraction code
      else if (op == "neg") // this must be unary '-'
         emit negation code;
      else if (op == "not")
         emit not code
      else if (op == "*")
         emit multiplication code
      else if (op == "div")
         emit division code
      else if (op == "mod")
         emit modulo code
      else if (op == "and")
         emit and code
      ...
      else if (op == "=")
         emit equality code
      else if (op == ":=")
         emit assignment code
      else
         processError("compiler error since function code should not be called with illegal arguments")
   }



//prog() - production 1
void Compiler::prog() //token should be "program"
{
   cout << "you just entered the prog zone\n";
   if (token != "program")
      processError("keyword \"program\" expected");
   progStmt();
   cout << __LINE__ << endl;
   if (token == "const")
      consts();
   if (token == "var")
      vars();
   //seof check
   if (token != "begin")
      processError("keyword \"begin\" expected");
   beginEndStmt();
   if (token[0] != END_OF_FILE)
      processError("no text may follow \"end\"");
}

// progStmt() - production 2
void Compiler::progStmt() //token should be "program"
   {
      cout << "you just entered the progstmts zone\n";
      string x;
      if (token != "program")
         processError("keyword \"program\" expected");
      x = nextToken();
      if (!isNonKeyId(x))
      //FIXME dont know if PROG_NAME is the correct way to do this
         processError(PROG_NAME + " expected");
      nextToken();
      if (token != ";")
         processError("\";\" expected");
      nextToken();
      code("program", x);
      insert(x,PROG_NAME,CONSTANT,x,NO,0);
   }

//consts() - production 3
void Compiler::consts() //token should be "const"
{
   cout << "you just entered the consts zone\n";
   if (token != "const")
      processError("keyword \"const\" expected");
   nextToken();
   if (!isNonKeyId(token))
      processError("non-keyword identifier must follow \"const\"");
   constStmts();
}

// vars() - production 4
void Compiler::vars() //token should be "var"
{
   cout << "you just entered the vars zone\n";
   if (token != "var")
      processError("keyword \"var\" expected");
   string x = nextToken();
   if (!isNonKeyId(x))
      processError("non-keyword identifier must follow \"var\"");
   varStmts();
}

// beginEndStmt() - production 5 ¯\_(ツ)_/¯
void Compiler::beginEndStmt() //token should be "begin"
{
   cout << "you just entered the beginEndStmt zone\n";
   if (token != "begin")
      processError("keyword \"begin\" expected");
   if (nextToken() != "end")
      processError("keyword \"end\" expected");
   if (nextToken() != ".")
      processError("period expected");
   nextToken();
   code("end", ".");
}

//constStmts() - production 6
void Compiler::constStmts() //token should be NON_KEY_ID
   {
      cout << "you just entered the constStmts zone\n";
      string x,y;
      if (!isNonKeyId(token))
         processError("non-keyword identifier expected");
      x = token;
      if (nextToken() != "=")
         processError("\"=\" expected");
      y = nextToken();
      if (y != "+" || y !=  "-" || y != "not" || !isNonKeyId(y) || y != "true" || y != "false" || !isInteger(y))
         processError("token to right of \"=\" illegal");
      if (y == "+" || y == "-")
         {
            if (!isInteger(nextToken()))
               processError("integer expected after sign");
            y = y + token;
         }
      if (y == "not")
         {
            if (!isBoolean(nextToken()))
               processError("boolean expected after \"not\"");
            if (token == "true")
               y = "false";
            else
               y = "true";
         }
      if (nextToken() != ";")
         processError("semicolon expected");
      if (!isInteger(y) || !isBoolean(y))
         processError("data type of token on the right-hand side must be INTEGER or BOOLEAN");
      insert(x,whichType(y),CONSTANT,whichValue(y),YES,1);
      x = nextToken();
      if (x != "begin" || x != "var" || !isNonKeyId(x))
         processError("non-keyword identifier, \"begin\", or \"var\" expected");
      if (isNonKeyId(x))
         constStmts();
   }

//varStmts() - production 7 
void Compiler::varStmts() //token should be NON_KEY_ID
   {
      cout << "you just entered the varStmts zone\n";
      string x,y;
      if (!isNonKeyId(token))
         processError("non-keyword identifier expected  ");
      //FIXME?? 
      x = ids();
      if (token != ":")
         processError("\":\" expected");
      if (nextToken() != "integer" || nextToken() != "boolean")
         processError("illegal type follows \":\"");
      y = token;
      if (nextToken() != ";")
         processError("semicolon expected");
      insert(x,whichType(y),VARIABLE,"",YES,1);
      //Double Check here to the pseudocode
      if (nextToken() != "begin" || !isNonKeyId(nextToken()))
         processError("non-keyword identifier or \"begin\" expected");
      if (isNonKeyId(token))
         varStmts();
   }

//ids() - production 8
string Compiler::ids() //token should be NON_KEY_ID
   {
      
      string temp,tempString;
      if (!isNonKeyId(token))
         processError("non-keyword identifier expected");
      tempString = token;
      temp = token;
      if (nextToken() == ",")
         {
            if (!isNonKeyId(nextToken()))
               processError("non-keyword identifier expected");
            tempString = temp + "," + ids();
         }
      return tempString;
   }
//FIXME check whether or not the remaining 5 prods need creation

void Compiler::execStmts(); // stage 1, production 2
{
   cout << "you just entered the execStmts zone\n";
   
   
}

void Compiler::execStmt(); // stage 1, production 3
{
   cout << "you just entered the execStmt zone\n";

}

void Compiler::assignStmt(); // stage 1, production 4
{
   cout << "you just entered the assignStmt zone\n";

}

void Compiler::readStmt(); // stage 1, production 5
{
   cout << "you just entered the readStmt zone\n";


}

void Compiler::writeStmt(); // stage 1, production 7
{
   cout << "you just entered the writeStmt zone\n";

}

void Compiler::express(); // stage 1, production 9
{
   cout << "you just entered the express zone\n";

}

void Compiler::expresses(); // stage 1, production 10
{
   cout << "you just entered the expresses zone\n";

}

void Compiler::term(); // stage 1, production 11
{
   cout << "you just entered the term zone\n";

}

void Compiler::terms(); // stage 1, production 12
{
   cout << "you just entered the terms zone\n";

}

void Compiler::factor(); // stage 1, production 13
{
   cout << "you just entered the factor zone\n";

}

void Compiler::factors(); // stage 1, production 14
{
   cout << "you just entered the factors zone\n";

}

void Compiler::part(); // stage 1, production 15
{
   cout << "you just entered the part zone\n";

}


string Compiler::nextToken() //returns the next token or end of file marker
{
   cout << "entered the nextToken zone\n";
	token = "";
	while (token == "")
	{
      cout << __LINE__ << endl;
      cout << token << endl;
      if (ch == '{') 
         {
         while (nextChar() != sourceFile.eof() || nextChar() != '}')
            {
               if (ch == sourceFile.eof())
                         processError("unexpected end of file");
						else
                         nextChar();
            }
         }
      else if (ch == '}') 
         {
            processError("\'}\' cannot begin token");
         }
      else if (isspace(ch)) 
         {
            cout << __LINE__ << endl;
            nextChar();
         }
      else if (isSpecialSymbol(ch))
         {
            cout << __LINE__ << endl;
            token = ch;
				nextChar();
         }
      else if (islower(ch)) 
         {
            cout << __LINE__ << endl;
            //string n(1, ch);
            while ((islower(ch) || isdigit(ch) || ch == '_') && ch != END_OF_FILE)
               {
                  cout << __LINE__ << endl;
                  token+=ch;
                  nextChar();
                  cout << token << endl;
					}	
            if (ch == sourceFile.eof())
               processError("unexpected end of file");
         }
      else if (isdigit(ch))
         {
            token = ch;
            string d(1, ch);
            while (isInteger(d) && ch != sourceFile.eof())
               {
                  token+=ch;
               }
            if (ch == sourceFile.eof())
               processError("unexpected end of file");
         }
      else if (ch == sourceFile.eof())
         {
            cout << __LINE__ << endl;
            token = ch;
         }
      else {
            processError("illegal symbol");
      }
    }
    cout << __LINE__ << endl;
    cout << token << endl;
    return token;
}
char Compiler::nextChar()
{
   sourceFile.get(ch);
   if (sourceFile.eof()) {
      ch = '$';  
      return ch;
   }
   if (lineNo == 0){
      lineNo++;
      listingFile << right << setw(5) << lineNo << '|';
   } 
   listingFile << ch;
   if (ch == '\n') {
      cout << __LINE__ << endl;
      lineNo++;
      listingFile << right << setw(5) << lineNo << '|';
   }
   return ch;
}


void Compiler::emit(string label, string instruction, string operands, string comment)
   {
      objectFile << left;
      objectFile << setw(8) << label;
      objectFile << setw(8) << instruction;
      objectFile << setw(24) << operands ;
      objectFile << comment << endl;
   }

void Compiler::emitPrologue(string progName, string operand2)
   {
      time_t now = time (NULL);
      objectFile << "Alex Garcia && Adebolanle Balogun" << ctime(&now) <<endl;
      objectFile << "%INCLUDE Along32.inc:" << endl;
      objectFile << "%INCLUDE Macros_Along.inc" << endl;
      emit("SECTION", ".text");
      emit("global", "_start", "", "; program" + progName);
      emit("\n_start:");
   }

void Compiler::emitEpilogue(string operand1, string operand2)
   {
      emit("","Exit", "{0}");
      emitStorage();
   }


void Compiler::emitStorage()
{
   emit("SECTION", ".data");
	for (auto it = symbolTable.begin(); it != symbolTable.end(); ++it){
		if(it->second.getAlloc() == YES && it->second.getMode() == CONSTANT){
			emit(it->second.getInternalName());
		}
	}
	emit("SECTION", ".bss");
	for (auto it = symbolTable.begin(); it != symbolTable.end(); ++it){
		if(it->second.getAlloc() == YES && it->second.getMode() == VARIABLE){
			emit(it->second.getInternalName());
		}
	}
}
bool Compiler::isKeyword(string s) const
   { 
      set<string> keywords = { "program", "begin", "end", "var", "const", "integer", "boolean", "true", "false", "not"};
      if (keywords.count(s)) {return true;};
      return false; 
   }

bool Compiler::isSpecialSymbol(char c) const // determines if c is a special symbol
   {// not sure if this is what is meant by special symbol
      if (c == ';')
         return true;
      else if (c == ':')
         return true;
      else if (c == ',')
         return true;
      else if (c == '.')
         return true;
      else if (c == '-')
         return true;
      else if (c == '+')
         return true;
      else if (c == '=')
         return true;
      else
         return false;
        
      /*switch (c) {
         case ';':
         return true;
         break;
         case ':':
         return true;
         break;
         case ',':
         return true;
         break;
         case '.':
         return true;
         break;
         case '-':
         return true;
         break;      
         case '+':
         return true;
         break;
         case '=':
         return true;
         break;
         default:
         return false; // if it is not a special symbol   
         break;   
*/
      }
   //}
bool Compiler::isNonKeyId(string s)const // determines if s is a non_key_id
   {
      // need to find out whether or not _ can be in the beginning or just at any other space besides the beginning
      if (isalpha(s[0])) {
      //run through rest of string
      cout << __LINE__ << endl;
         for (uint i = 1; i < s.length(); i++) {
            if (!isalnum(s[i])) {
            cout << __LINE__ << endl;
            return false;
            }
         }
      }
      cout << __LINE__ << endl;
      return true; 
   }

bool Compiler::isInteger(string s) const// determines if s is an integer
   {
      for (uint i = 1; i < s.length(); i++) {
         if (s[i] == '0' || s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9') {
            return true;
         }
      }
      return false;
   }   
      
   

bool Compiler::isBoolean(string s) const // determines if s is a boolean
   {
      if (s == "true" || s == "false") { 
         return true;
      }
      return false;
   }

bool Compiler::isLiteral(string s) const // determines if s is a literal
   {
      if (isInteger(s))
         return true;
      else if (s == "false")
         return true;
      else if (s == "true")
         return true;
      else if (s == "not")
         return true;
      else if (s == "-")
         return true;
      else if (s == "+")
         return true;
      return false;
   }

//STAGE 1 ADDITION   
void Compiler::pushOperator(string name) //push name onto operatorStk
   {
      operatorStk.push(name);
   }

//STAGE 1 ADDITION
//FIXME
void Compiler::pushOperand(string name) //push name onto operandStk
   //if name is a literal, also create a symbol table entry for it
   {
      if (isLiteral(name) && has no symbol table entry)
         insert symbol table entry, call whichType to determine the data type of the literal
      operandStk.push(name);
   }

//STAGE 1 ADDITION   
string Compiler::popOperator() //pop name from operatorStk
   {
      if (!operatorStk.empty())
         {
            //FIXME maybe... not sure about auto here
            auto item = operatorStk.top();
            operatorStk.pop();
            return item;
         }
      else
         processError("compiler error; operator stack underflow");
   }

//STAGE 1 ADDITION
string Compiler::popOperand() //pop name from operandStk
   {
      if (!operandStk.empty())
         {
            //FIXME maybe... not sure about auto here
            auto item = operandStk.top();
            operandStk.pop();
            return item;
         }
      else
         processError("compiler error; operand stack underflow")
   }

   string Compiler::genInternalName(storeTypes stype) const// determines if s is a literal
      {
         string newName;
         static int numBool, numInt, numProg = 0;
         if (stype == BOOLEAN){
            newName = "B";
            newName += to_string(numBool);
            numBool++;
         }
      
         if (stype == INTEGER){
            newName = "I";
            newName += to_string(numInt);
            numInt++;
         }
         
         if (stype == PROG_NAME){
            newName = "P";
            newName += to_string(numProg);
            numProg++;
         }
         
         return newName;
      }

//STAGE 1 ADDITION
void Compiler::emitAdditionCode(string operand1,string operand2) //add operand1 to operand2
   {
      if (!isInteger(operand1) || !isInteger(operand2))
         processError("illegal type")
      if (contentsOfAReg[0] == 'T') // the A Register holds a temp not operand1 nor operand2 
         {
            //then emit code to store that temp into memory 
            //change the allocate entry for the temp in the symbol table to yes 
            //deassign the temp
         }
      if () //the A register holds a non-temp not operand1 nor operand2 
         // then deassign it
      if () //neither operand is in the A register then
         {
            //emit code to load operand2 into the A register
            //emit code to perform register-memory addition
            //deassign all temporaries involved in the addition and free those names for reuse
            //A Register = next available temporary name and change type of its symbol table entry to integer
            //push the name of the result onto operandStk
         }
   }
//STAGE 1 ADDITION  
void Compiler::emitSubtractionCode(string operand1,string operand2) 
   {
      if (!isInteger(operand1) || !isInteger(operand2))
         processError("illegal type")
   }
  
void Compiler::emitMultiplicationCode(string operand1,string operand2) 
   {
      if (!isInteger(operand1) || !isInteger(operand2))
         processError("illegal type")
   }

void Compiler::emitModuloCode(string operand1, string operand2)
   {
      if (!isInteger(operand1) || !isInteger(operand2))
         processError("illegal type")
   }
   
void Compiler::emitDivisionCode(string operand1,string operand2) //divide operand2 by operand1
   {
      if (!isInteger(operand1) || !isInteger(operand2))
         processError("illegal type")
      if the A Register holds a temp not operand2 then
      emit code to store that temp into memory
      change the allocate entry for it in the symbol table to yes
      deassign it
      if the A register holds a non-temp not operand2 then deassign it
      if operand2 is not in the A register
      emit instruction to do a register-memory load of operand2 into the A register
      emit code to extend sign of dividend from the A register to edx:eax
      emit code to perform a register-memory division
      deassign all temporaries involved and free those names for reuse
      A Register = next available temporary name and change type of its symbol table entry to integer
      push the name of the result onto operandStk
   }
   
void Compiler::emitAndCode(string operand1,string operand2) //and operand1 to operand2
   {
      if (!isBoolean(operand1) || !isBoolean(operand2))
         processError("illegal type")
      if the A Register holds a temp not operand1 nor operand2 then
      emit code to store that temp into memory
      change the allocate entry for the temp in the symbol table to yes
      deassign it
      if the A register holds a non-temp not operand1 nor operand2 then deassign it
      if neither operand is in the A register then
      emit code to load operand2 into the A register
      emit code to perform register-memory and
      deassign all temporaries involved in the and operation and free those names for reuse
      A Register = next available temporary name and change type of its symbol table entry to boolean
      push the name of the result onto operandStk
   }
   
void Compiler::emitOrCode(string operand1,string operand2) //and operand1 to operand2
   {
      if (!isBoolean(operand1) || !isBoolean(operand2))
         processError("illegal type")
   }
   
void Compiler::emitEqualityCode(string operand1,string operand2) //test whether operand2 equals operand1
   {
      if () //types of operands are not the same
      processError(incompatible types)
      if the A Register holds a temp not operand1 nor operand2 then
      emit code to store that temp into memory
      change the allocate entry for it in the symbol table to yes
      deassign it
      if the A register holds a non-temp not operand2 nor operand1 then deassign it
      if neither operand is in the A register then
      emit code to load operand2 into the A register
      emit code to perform a register-memory compare
      emit code to jump if equal to the next available Ln (call getLabel)
      emit code to load FALSE into the A register
      insert FALSE in symbol table with value 0 and external name false
      emit code to perform an unconditional jump to the next label (call getLabel should be L(n+1))
      emit code to label the next instruction with the first acquired label Ln
      emit code to load TRUE into A register
      insert TRUE in symbol table with value -1 and external name true
      emit code to label the next instruction with the second acquired label L(n+1)
      deassign all temporaries involved and free those names for reuse
      A Register = next available temporary name and change type of its symbol table entry to boolean
      push the name of the result onto operandStk
   }
   
void Compiler::emitInequalityCode(string operand1, string operand2)
   {
      //adsf
   }

void Compiler::emitLessThanCode(string operand1, string operand2)
   {
      //adsf
   }
   
void Compiler::emitLessThanOrEqualToCode(string operand1, string operand2)
   {
      //adsf
   }
   
void Compiler::emitGreaterThanCode(string operand1, string operand2)
   {
      //sfdg
   }   

void Compiler::emitGreaterThanOrEqualToCode(string operand1, string operand2)
   {
      //dfg
   }   
      
void Compiler::emitNegationCode(string operand1, string = "")
   {
      //fsgs
   }
   
void Compiler::emitNotCode(string operand1, string = "")
   {
      //gfsdf
   }

void Compiler::emitAssignCode(string operand1,string operand2) //assign the value of operand1 to operand2
   {
      if types of operands are not the same
      processError(incompatible types)
      if storage mode of operand2 is not VARIABLE
      processError(symbol on left-hand side of assignment must have a storage mode of VARIABLE)
      if operand1 = operand2 return
      if operand1 is not in the A register then
      emit code to load operand1 into the A register
      emit code to store the contents of that register into the memory location pointed to by
      operand2
      set the contentsOfAReg = operand2
      if operand1 is a temp then free its name for reuse
      //operand2 can never be a temporary since it is to the left of ':='
    }
    
void Compiler::emitReadCode(string operand, string operand2)
   {
      string name
      while (name is broken from list (operand) and put in name != "")
      {
      if () //name is not in symbol table
         processError("reference to undefined symbol")
      if () //data type of name is not INTEGER
         processError("can\'t read variables of this type")
      if () //storage mode of name is not VARIABLE
         processError("attempting to read to a read-only location")
      emit code to call the Irvine ReadInt function
      emit code to store the contents of the A register at name
      set the contentsOfAReg = name
      }
   }
   
void Compiler::emitWriteCode(string operand, string operand2)
   {
      string name
      static bool definedStorage = false
      while (name is broken from list (operand) and put in name != "")
      {
      if name is not in symbol table
      processError(reference to undefined symbol)
      if name is not in the A register
      emit the code to load name in the A register
      set the contentsOfAReg = name
      if data type of name is INTEGER or BOOLEAN
      emit code to call the Irvine WriteInt function
      emit code to call the Irvine Crlf function
      } // end while
   }
     
void Compiler::freeTemp()
   {
      currentTempNo--;
      if (currentTempNo < -1)
         processError("compiler error, currentTempNo should be ≥ –1")
   }
   
   
string Compiler::getTemp()
   {
      string temp;
      currentTempNo++;
      temp = "T" + currentTempNo;
      if (currentTempNo > maxTempNo)
         {
            insert(temp, UNKNOWN, VARIABLE, "", NO, 1)
            maxTempNo++;
            return temp;
         }
   }
   
//FIXME
string Compiler::getLabel()
   {
      //what the actual fuck goes here?
   }


bool Compiler::isTemporary(string s) const //determines if s represents a temporary
   {
      //adsfa
   }