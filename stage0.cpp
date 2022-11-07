//Alex Garcia && Adebolanle Balogun
//Stage 0



//dont forget the fuckton of include we'll need -bola
#include <ctime>
#include <iostream>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
// test 

using namespace std;

END_OF_FILE = '$'


//FIXME
// needs definitions for processError
// specifically : processError(unexpected end of file);
//                processError(illegal symbol)
//                processError('}' cannot begin token);
// if the pascallite helper functions need to be written, relook at 
// all the case statements
// @ createListingHeader() do SOURCESTATEMENT need to be literal or a var?
// #ofErrors var needed



Compiler(char **argv) // constructor
   {
      sourceFile.open(argv[1]);
      listingFile.open(argv[2]);
      objectFile.open(argv[3]);
   }
   
~Compiler() // destructor
   {
      sourceFile.close();
      listingFile.close();
      objectFile.close();
   }

void createListingHeader()
   {
      time_t now = time (NULL);
      cout << "STAGE0:  Alex Garcia & Adebolanle Balogun" << ctime(&now) << "\n";
      cout << "LINE NO:               " << "SOURCE STATEMENT\n";
      //line numbers and source statements should be aligned under the headings
   }

void parser()
   {
      nextChar();
      //FIXME HERE
      ch must be initialized to the first character of the source file
      if (nextToken() != "program")
         processError("keyword \"program\" expected")
            //a call to nextToken() has two effects
            // (1) the variable, token, is assigned the value of the next token
            // (2) the next token is read from the source file in order to make
            // the assignment. The value returned by nextToken() is also
            // the next token.
      prog();
         //parser implements the grammar rules, calling first rule
   }
void createListingTrailer()
   {
      cout << "COMPILATION TERMINATED " << #ofErrors <<  " ERRORS ENCOUNTERED\n";
   }

void processError(string err)
   {
      Output err to listingFile
      Call exit() to terminate program
   }

void insert(string externalName,storeType inType, modes inMode, string inValue,
allocation inAlloc, int inUnits)

{
   cout << "you just entered the prog zone\n";
   
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


storeTypes whichType(string name) //tells which data type a name has
   {
      if (name is a literal)
         if (name is a boolean literal)
            data type = BOOLEAN
         else
            data type = INTEGER
      else //name is an identifier and hopefully a constant
         if (symbolTable[name] is defined)
            data type = type of symbolTable[name]
         else
            processError(reference to undefined constant)
      return data type
   }


string whichValue(string name) //tells which value a name has
   {
      if (name is a literal)
         value = name
      else //name is an identifier and hopefully a constant
         if (symbolTable[name] is defined and has a value)
            value = value of symbolTable[name]
         else
            processError(reference to undefined constant)
      return value
   }



void code(string op, string operand1, string operand2)
   {
      if (op == "program")
         emitPrologue(operand1);
      else if (op == "end")
         emitEpilogue();
      else
         processError("compiler error since function code should not be called with illegal arguments");
   }



//prog() - production 1
void prog() //token should be "program"
{
   cout << "you just entered the prog zone\n";
   if (token != "program")
      processError("keyword \"program\" expected");
   progStmt();
   if (token == "const")
      consts();
   if (token == "var")
      vars();
   if (token != "begin")
      processError("keyword \"begin\" expected");
   beginEndStmt();
   if (token != END_OF_FILE)
      processError("no text may follow \"end\"");
}

// progStmt() - production 2
void progStmt() //token should be "program"
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
void consts() //token should be "const"
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
void vars() //token should be "var"
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
void beginEndStmt() //token should be "begin"
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
void constStmts() //token should be NON_KEY_ID
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
void varStmts() //token should be NON_KEY_ID
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
string ids() //token should be NON_KEY_ID
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
            tempString = temp + "," + ids();
         }
      return tempString;
   }




string nextToken() //returns the next token or end of file marker
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
               // I might be fucking up here idk if this is the proper way to do it
               String s = nextChar();
               while (//fixme)
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
char nextChar() //returns the next character or end of file marker ¯\_(ツ)_/¯
{
   get the next character
   if (ch =='$') {
         ch = END_OF_FILE    
   } else {
      ch = getchar();
               str[i + 1] = c;
               i++;
               listingFile << ch << '\n'
               return ch;
            } 
}


void emit(string label, string instruction, string operands, string comment)
   {
      //Turn on left justification in objectFile should probably just use setw() for these
      objectFile << '{0: <9}'.format(label);
      objectFile << '{0: <9}'.format(instruction);
      objectFile << '{0: <25}'.format(operands);
      objectFile << comment << endl;
      // probs not right idk wtf is goin on
   }

void emitPrologue(string progName, string operand2) // might be right idk  ¯\_(ツ)_/¯
   {
      //Output identifying comments at beginning of objectFile
      objectFile << "Alex Garcia && Adebolanle Balogun" <<endl;
      // ^ idk where to start here v
      //Output the %INCLUDE directives
      objectFile << "#include <iostream>:" << endl;
      objectFile << "#include <fstream>" << endl;
      objectFile << "#include <string>"<< endl;
      objectFile << "#include <map>"<< endl;
      emit("SECTION", ".text")
      emit("global", "_start", "", "; program" + progName)
      emit("\n_start:")
   }


void emitEpilogue(string operand1, string operand2)
   {
      emit("","Exit", "{0}");
      emitStorage();
   }


void emitStorage()
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

bool isKeyword(string s) // determines if s is a keyword idk if this is what he wants
   { // took all keywords and put them in a set to test against the string s
      set<string> keywords = { "program",  // set is a  data structure that conatains the same types of data
"begin",
"end",
"var",
"const",
"integer",
"boolean",
"true",
"false",
"not"};
 
      if (keywords.count(s)) {return true};// should count the occurences of s in the keywords set hopefully returns true if s is one of those keywords
      return false 
   }

bool isSpecialSymbol(char c) // determines if c is a special symbol
   {// not sure if this is what is meant by special symbol
      switch (c) {
         case ';':
         return true
         break;
         case ':':
         return true
         break;
         case ',':
         return true
         break;
         case '.':
         return true
         break;
         case '-':
         return true
         break;      
         case '+':
         return true
         break;
         case '=':
         return true
         break;
         default:
         return false // if it is not a special symbol   
         break;   

      }
   }

bool isNonKeyId(string s) // determines if s is a non_key_id
   {
      if (!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z') || s[0] == ' ')) { //checking if the first character is valid
         
         return false
      }
      //run through rest of string
      for (int i = 1; i < s.length(); i++) {
         if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9') || s[i] == ' ')) { //checking if the first character is valid
         
         return false
      }
      }
      return true; //should return true if s is a nonkeyid
   }

bool isInteger(string s) // determines if s is an integer
   {
      if (isdigit(s[i]) == false) {
         return false
      } else{return true}  
   }   
      
   

bool isBoolean(string s) const // determines if s is a boolean
   {
      if (s == "true" || s == "false") { // idk what to put here i looked up some examples and a lot of them pointed to this way
         //code here... maybe
         return true
      }
      return false;
   }

bool isLiteral(string s) // determines if s is a literal
   {
      switch (s) {
         case isInteger(s):
         return true
         break;
         case 'false':
         return true
         break;
         case 'true':
         return true
         break;
         case 'not':
         return true
         break;
         case '-':
         return true
         break;      
         case '+':
         return true
         break;
         default:
         return false // s is not a literal
         break;   

      }
   }
