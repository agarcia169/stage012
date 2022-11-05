//Alex Garcia && Adebolanle Balogun
//Stage 0



//dont forget the fuckton of include we'll need -bola


END_OF_FILE = '$'


//FIXME
// needs definitions for processError
// specifically : processError(unexpected end of file);
//                processError(illegal symbol)
//                processError('}' cannot begin token);
// if the pascallite helper functions need to be written, relook at 
// all the case statements




Compiler(char **argv) // constructor
{
open sourceFile using argv[1]
open listingFile using argv[2]
open objectFile using argv[3]
}
~Compiler() // destructor
{
close all open files
}
void createListingHeader()
{
print "STAGE0:", name(s), DATE, TIME OF DAY
print "LINE NO:", "SOURCE STATEMENT"
//line numbers and source statements should be aligned under the headings
}
void parser()
{
nextChar()
//ch must be initialized to the first character of the source file
if (nextToken() != "program")
processError(keyword "program" expected)
//a call to nextToken() has two effects
// (1) the variable, token, is assigned the value of the next token
// (2) the next token is read from the source file in order to make
// the assignment. The value returned by nextToken() is also
// the next token.
prog()
//parser implements the grammar rules, calling first rule
}
void createListingTrailer()
{
print "COMPILATION TERMINATED", "# ERRORS ENCOUNTERED"
}
Void processError(string err)
{
Output err to listingFile
Call exit() to terminate program
}


void insert(string externalName,storeType inType, modes inMode, string inValue,
allocation inAlloc, int inUnits)
//create symbol table entry for each identifier in list of external names
//Multiply inserted names are illegal
{
string name
while (name broken from list of external names and put into name != "")
{
if (symbolTable[name] is defined)
processError(multiple name definition)
else if (name is a keyword)
processError(illegal use of keyword)
else //create table entry
{
if (name begins with uppercase)
symbolTable[name]=(name,inType,inMode,inValue,inAlloc,inUnits)
else
symbolTable[name]=(genInternalName(inType),inType,inMode,inValue,
inAlloc,inUnits)
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
emitPrologue(operand1)
else if (op == "end")
emitEpilogue()
else
processError(compiler error since function code should not be called with
illegal arguments)
}



//prog() - production 1
void prog() //token should be "program"
{
if (token != "program")
processError(keyword "program" expected)
progStmt()
if (token == "const")
consts()
if (token == "var")
vars()
if (token != "begin")
processError(keyword "begin" expected)
beginEndStmt()
if (token != END_OF_FILE)
processError(no text may follow "end”)
}

// progStmt() - production 2
void progStmt() //token should be "program"
{
string x
if (token != "program")
processError(keyword "program" expected)
x = NextToken()
if (token is not a NON_KEY_ID)
processError(program name expected)
if (nextToken() != ";")
processError(semicolon expected)
nextToken()
code("program", x)
insert(x,PROG_NAME,CONSTANT,x,NO,0)
}

//consts() - production 3
void consts() //token should be "const"
{
if (token != "const")
processError(keyword "const" expected)
if (nextToken() is not a NON_KEY_ID)
processError(non-keyword identifier must follow "const")
constStmts()
}

// vars() - production 4
void vars() //token should be "var"
{
if (token != "var")
processError(keyword "var" expected)
if (nextToken() is not a NON_KEY_ID)
processError(non-keyword identifier must follow "var")
varStmts()
}

// beginEndStmt() - production 5
void beginEndStmt() //token should be "begin"
{
if (token != "begin")
procesError(keyword "begin" expected)
if (nextToken() != "end")
processError(keyword "end" expected)
if (nextToken() != ".")
processError(period expected)
nextToken()
code("end", ".")
}

//constStmts() - production 6
void constStmts() //token should be NON_KEY_ID
{
string x,y
if (token is not a NON_KEY_ID)
processError(non-keyword identifier expected)
x = token
if (nextToken() != "=")
processError("=" expected)
y = nextToken()
if (y is not one of "+","-","not",NON_KEY_ID,"true","false",INTEGER)
processError(token to right of "=" illegal)
if (y is one of "+","-")
{
if (nextToken() is not an INTEGER)
processError(integer expected after sign)
y = y + token;
}
if (y == "not")
{
if (nextToken() is not a BOOLEAN)
processError(boolean expected after “not”)
if (token == "true")
y = "false"
else
y = "true"
}
if (nextToken() != ";")
processError(semicolon expected)
if (the data type of y is not INTEGER or BOOLEAN)
processError(data type of token on the right-hand side must be INTEGER or
BOOLEAN)
insert(x,whichType(y),CONSTANT,whichValue(y),YES,1)
x = nextToken()
if (x is not one of "begin","var",NON_KEY_ID)
processError(non-keyword identifier, "begin", or "var" expected)
if (x is a NON_KEY_ID)
constStmts()
}

//varStmts() - production 7
void varStmts() //token should be NON_KEY_ID
{
string x,y
if (token is not a NON_KEY_ID)
processError(non-keyword identifier expected)
x = ids()
if (token != ":")
processError(":" expected)
if (nextToken() is not one of "integer","boolean")
processError(illegal type follows ":")
y = token
if (nextToken() != ";")
processError(semicolon expected)
insert(x,y,VARIABLE,"",YES,1)
if (nextToken() is not one of "begin",NON_KEY_ID)
processError(non-keyword identifier or "begin" expected)
if (token is a NON_KEY_ID)
varStmts()
}

//ids() - production 8
string ids() //token should be NON_KEY_ID
{
string temp,tempString
if (token is not a NON_KEY_ID)
processError(non-keyword identifier expected)
tempString = token
temp = token
If (nextToken() == ",")
{
if (nextToken() is not a NON_KEY_ID)
processError(non-keyword identifier expected)
tempString = temp + "," + ids()
}
return tempString
}




string nextToken() //returns the next token or end of file marker
{
	token = "";
	while (token == "")
	{
		switch(ch)
			{
				case '{' : //process comment
					while (nextChar() != END_OF_FILE || '}'}
					{
						if (ch == END_OF_FILE)
                         processError(unexpected end of file);
						else
                         nextChar()
               }
                   break;
				case '}' : 
               processError('}' cannot begin token);
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
               while (isNonKeyId(s) && != END_OF_FILE)
                  {
                     token+=ch
						}	
               if (ch == END_OF_FILE)
                  processError(unexpected end of file)
               break;
            case isdigit(ch) :
               token = ch;
               String s = nextChar();
               while (isInteger(s) && != END_OF_FILE)
                  {
                     token+=ch
                  }
               if (ch == END_OF_FILE)
               processError(unexpected end of file)
               break;
            case END_OF_FILE : 
               token = ch;
               break;
            default : 
               processError(illegal symbol);
            break; // this is a superstitous break, i know i probably dont need it 
    }
    return token
}
char nextChar() //returns the next character or end of file marker
{
   if (c =='$')
      {
         ch = END_OF_FILE    
      } else{
         c = getchar();
         str[i + 1] = c;
         i++;
         cout << ch << 001.lst <<'\n'
         return ch;
      } 
}


void emit(string label, string instruction, string operands, string comment)
{
//Turn on left justification in objectFile
cout << '{0: <9}'.format(label);
cout << '{0: <9}'.format(instruction);
cout << '{0: <25}'.format(operands);
cout << comment ;
// probs not right 
}

void emitPrologue(string progName, string operand2)
{
//Output identifying comments at beginning of objectFile
// ^ idk where to start here v
//Output the %INCLUDE directives
cout << "#include <iostream>:" ;
cout << "#include <fstream>";
cout << "#include <string>";
cout << "#include <map>";
emit("SECTION", ".text")
emit("global", "_start", "", "; program" + progName)
emit("_start:")
}


void emitEpilogue(string operand1, string operand2)
{
emit("","Exit", "{0}");
emitStorage();
}


void emitStorage()
{
emit("SECTION", ".data")
for those entries in the symbolTable that have
an allocation of YES and a storage mode of CONSTANT
{ call emit to output a line to objectFile }
emit("SECTION", ".bss")
for those entries in the symbolTable that have
an allocation of YES and a storage mode of VARIABLE
{ call emit to output a line to objectFile }
}
