//Alex Garcia && Adebolanle Balogun
//




string nextToken() //returns the next token or end of file marker
{
	token = "";
	while (token == "")
	{
	switch(ch)
	{
	case '{' : //process comment
	while (nextChar() is not one of END_OF_FILE, '}'}
	{ //empty body }
	if (ch == END_OF_FILE)
	processError(unexpected end of file)
	else
	nextChar()
	case '}' : processError('}' cannot begin token)
	case isspace(ch) : nextChar()
	case isSpecialSymbol(ch): token = ch;
	nextChar()
	case islower(ch) : token = ch;
	while (nextChar() is one of letter, digit, or
	'_' but not END_OF_FILE)
	{
	token+=ch
	}	
	if (ch is END_OF_FILE)
	processError(unexpected end of file)
	case isdigit(ch) : token = ch;
	while (nextChar() is digit but not END_OF_FILE)
	{
	token+=ch
	}
	if (ch is END_OF_FILE)
	processError(unexpected end of file)
	case END_OF_FILE : token = ch
	default : processError(illegal symbol)
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
    cout << ch << 001.lst<<'\n'
    return ch;
} 
}
