//Alex Garcia && Adebolanle Balogun
//Stage 0



#include <ctime>
#include <iostream>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

END_OF_FILE = '$'
#ofErrors = 0;
lineNumber = 0;

Compiler::Compiler(char **argv) // constructor
   {
      sourceFile.open(argv[1]);
      listingFile.open(argv[2]);
      objectFile.open(argv[3]);
   }
   
~Compiler::Compiler() // destructor
   {
      sourceFile.close();
      listingFile.close();
      objectFile.close();
   }

void Compiler::createListingHeader()
   {
      time_t now = time (NULL);
      cout << "STAGE0:  Alex Garcia & Adebolanle Balogun" << ctime(&now) << "\n";
      cout << "LINE NO:               " << "SOURCE STATEMENT\n";
      //line numbers and source statements should be aligned under the headings
   }

void Compiler::parser()
   {
      nextChar();
      if (nextToken() != "program")
         processError("keyword \"program\" expected");
      prog();

   }
void Compiler::createListingTrailer()
   {
      //possible right needed to justify right
      cout << "COMPILATION TERMINATED " << #ofErrors <<  " ERRORS ENCOUNTERED\n";
   }

void Compiler::processError(string err)
   {
      #ofErrors++;
      listingFile << "Error: " << "Line "<< lineNumber << ": " << err << "\n";
      exit(1);
   }

void Compiler::insert(string externalName,storeType inType, modes inMode, string inValue,
allocation inAlloc, int inUnits)

{
   cout << "you just entered the insert zone\n";
   
   string name = externalName;
   while (name != "")
   {
      //symbolTable[name] is defined
      //so would this work?
      //also would the class name notation be correct
      //FIXME how do we compare external and internal names?
      if (SymbolTableEntry.getInternalName(name))
         processError("multiple name definition")
      else if (isKeyword(name))
         processError("illegal use of keyword")
      else //create table entry
         {
            if (isUpper(name[0]))
               symbolTable[name]=(name,inType,inMode,inValue,inAlloc,inUnits)
            else
            //does this:                                 
               symbolTable[name]=(genInternalName(inType),inType,inMode,inValue,
                                 inAlloc,inUnits)
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
      else //name is an identifier and hopefully a constant
         //FIXME
         if (symbolTable[name] is defined)
            dataType = type of symbolTable[name];
         else
            processError("reference to undefined constant");
      return dataType;
   }


string Compiler::whichValue(string name) //tells which value a name has
   {
      cout << "You just entered the value zone" << endl;
      string value;
      if (isLiteral(name))
         value = name;
      else //name is an identifier and hopefully a constant
         //FIXME
         if (symbolTable[name] is defined and has a value)
            value = value of symbolTable[name]
         else
            processError("reference to undefined constant");
      return value;
   }



void Compiler::code(string op, string operand1, string operand2)
   {
      if (op == "program")
         emitPrologue(operand1);
      else if (op == "end")
         emitEpilogue();
      else
         processError("compiler error since function code should not be called with illegal arguments");
   }



//prog() - production 1
void Compiler::prog() //token should be "program"
{
   cout << "you just entered the prog zone\n";
   if (token != "program")
      processError("keyword \"program\" expected");
   progStmt();
   if (token == "const")
      consts();
   if (token == "var")
      vars();
   //seof check
   if (token != "begin")
      processError("keyword \"begin\" expected");
   beginEndStmt();
   //seof check
   if (token != END_OF_FILE)
      processError("no text may follow \"end\"");
}

// progStmt() - production 2
void Compiler::progStmt() //token should be "program"
   {
      cout << "you just entered the progstmts zone\n";
      string x;
      if (token != "program")
         processError("keyword \"program\" expected");
      x = NextToken();
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
/*
string token()
for (string::iterator it = token.begin(); it != token.end; ++it)
   cout << *it << '\n'
   just realized this would just loop through the whole string but if edited will give you the begining of the string i hope
*/
{
   cout << "you just entered the beginEndStmt zone\n";
   if (token != "begin")
      procesError("keyword \"begin\" expected");
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
      insert(x,y,VARIABLE,"",YES,1);
      //Double Check here to the pseudocode
      if (nextToken() != "begin" || !isNonKeyId(nextToken()))
         processError("non-keyword identifier or \"begin\" expected");
      if (isNonKeyId(token))
         varStmts();
   }

//ids() - production 8
string Compiler::ids() //token should be NON_KEY_ID
   {
      cout << "you just entered the ids zone\n";
      string temp,tempString;
      if (!isNonKeyId(token))
         processError("non-keyword identifier expected");
      tempString = token;
      temp = token;
      if (nextToken() == ",")
         {
            if (!isNonKeyId(nextToken()))
               processError("non-keyword identifier expected")
            //check string concat rules here, idk if this works
            //FIXME
            tempString = temp + "," + ids();
         }
      return tempString;
   }




string Compiler::nextToken() //returns the next token or end of file marker
{
	token = "";
	while (token == "")
	{
		switch(ch)
			{
				case '{' : //process comment
					while (nextChar() != END_OF_FILE || nextChar() != '}'}
					{
						if (ch == END_OF_FILE)
                         processError("unexpected end of file");
						else
                         nextChar();
               }
                   break;
				case '}' : 
               processError("\'}\' cannot begin token");
               break;            
            
				case isspace(ch) : 
               nextChar();
               break;
				case isSpecialSymbol(ch): 
               token = ch;
					nextChar();
               break;
				case islower(ch) : 
               token = ch;
               String s = nextChar();
               while (isNonKeyId(s) && s != END_OF_FILE)
                  {
                     token+=ch;
						}	
               if (ch == END_OF_FILE)
                  processError("unexpected end of file");
               break;
            case isdigit(ch) :
               token = ch;
               String s = nextChar();
               while (isInteger(s) && s != END_OF_FILE)
                  {
                     token+=ch;
                  }
               if (ch == END_OF_FILE)
                  processError("unexpected end of file");
               break;
            case END_OF_FILE : 
               token = ch;
               break;
            default : 
               processError("illegal symbol");
            break; // this is a superstitous break, i know i probably dont need it 
    }
    return token
}
char Compiler::nextChar() //returns the next character or end of file marker ¯\_(ツ)_/¯
{
   sourceFile.get(ch);
   if (sourceFile.eof()) {
      ch = '$';  
      return ch;
   } else if (lineNumber == 0){
      lineNumber +=1;
      listingFile << right << setw(5) << lineNumber << '|';
   } 
   listingFile << ch;
   else if (ch == '\n') {
      lineNumber +=1;
      listingFile << right << setw(5) << lineNumber << '|';
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

void emitPrologue(string progName, string operand2) // might be right idk  ¯\_(ツ)_/¯
   {
      objectFile << "Alex Garcia && Adebolanle Balogun" << ctime(&now) <<endl;
      objectFile << "%INCLUDE Along32.inc:" << endl;
      objectFile << "%INCLUDE Macros_Along.inc" << endl;
      emit("SECTION", ".text")
      emit("global", "_start", "", "; program" + progName)
      emit("\n_start:")
   }


void Compiler::emitEpilogue(string operand1, string operand2)
   {
      emit("","Exit", "{0}");
      emitStorage();
   }


void Compiler::emitStorage()
// not sure if right but this is how the other longboard guy explained it to me
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

bool Compiler::isKeyword(string s)
   { 
      set<string> keywords = { "program", "begin", "end", "var", "const", "integer", "boolean", "true", "false", "not"};
      if (keywords.count(s)) {return true};
      return false 
   }

bool Compiler::isSpecialSymbol(char c) // determines if c is a special symbol
   {// not sure if this is what is meant by special symbol
      switch (c) {
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

      }
   }

bool Compiler::isNonKeyId(string s) // determines if s is a non_key_id
   {
      if (!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z') || s[0] == ' ')) {
         
         return false;
      }
      //run through rest of string
      for (int i = 1; i < s.length(); i++) {
         if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9') || s[i] == ' ')) {
         
         return false;
      }
      }
      return true; 
   }

bool Compiler::isInteger(string s) // determines if s is an integer
   {
      if (isdigit(s[i]) == false) {
         return false;
      } else{return true}  
   }   
      
   

bool Compiler::isBoolean(string s) const // determines if s is a boolean
   {
      if (s == "true" || s == "false") { 
         //code here... maybe
         return true;
      }
      return false;
   }

bool Compiler::isLiteral(string s) // determines if s is a literal
   {
      switch (s) {
         case isInteger(s):
         return true;
         break;
         case 'false':
         return true;
         break;
         case 'true':
         return true;
         break;
         case 'not':
         return true;
         break;
         case '-':
         return true;
         break;      
         case '+':
         return true;
         break;
         default:
         return false;
         break;   

      }
   }
bool Compiler::genInternalName(storeTypes s) // determines if s is a literal
   {
      cout << "enter genName" << endl;
	   string newName;
      //FIXME MAYBE
	   static int numBool, numInt, numProg;
	   if (s == BOOLEAN){
         newName = "B";
         newName += to_string(numBool);
         numBool++;
      }
	
      if (s == INTEGER){
         newName = "I";
         newName += to_string(numInt);
         numInt++;
      }
      
      if (s == PROG_NAME){
         newName = "P";
         newName += to_string(numProg);
         numProg++;
      }
      
      return newName;
   }
