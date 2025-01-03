#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector> 
#include <array>
#include <map>
#include <regex> 
#include <algorithm>
#include <set>
#include <memory>
#include <stack>
#include <queue>

enum TokenType {
    NUL,
    END,
    OPERATOR,
    ASSIGN, 
    INT,
    FLOAT,
    CHAR,
    IDENTIFIER,
    KEYWORD,
    BRACKET_OPEN,
    BRACKET_CLOSE,
    QUESTIONMARK,
    COMMA,
    COLON,
    DOT,
    BACKSLASH,
    HASHTAG,
    AMPERSAND,
    SCOPE,
    STATEMENT,
    ARRAY,
    FUNCTION,
    CLASS,
    OBJECT,
};

class Token{
    public:
    std::string value;
    enum TokenType type;
    int weight;
    Token(std::string value = ";",enum TokenType type = END, unsigned int weight = 0){
        this -> value = value;
        this -> type = type;
        this -> weight = weight;
    }
};

Token nullvalue = Token("null", NUL);

std::string displayTokenType(TokenType token) {
    switch (token) {
        case END: return "END";
        case OPERATOR: return "OPERATOR";
        case ASSIGN: return "ASSIGN";
        case INT: return "INT";
        case FLOAT: return "FLOAT";
        case CHAR: return "CHAR";
        case IDENTIFIER: return "IDENTIFIER";
        case KEYWORD: return "KEYWORD";
        case BRACKET_OPEN: return "BRACKET_OPEN";
        case BRACKET_CLOSE: return "BRACKET_CLOSE";
        case QUESTIONMARK: return "QUESTIONMARK";
        case COMMA: return "COMMA";
        case COLON: return "COLON";
        case DOT: return "DOT";
        case BACKSLASH: return "BACKSLASH";
        case HASHTAG: return "HASHTAG";
        case AMPERSAND: return "AMPERSAND";
        case SCOPE: return "SCOPE";
        case STATEMENT: return "STATEMENT";
        case ARRAY: return "ARRAY";
        case FUNCTION: return "FUNCTION";
        case CLASS: return "CLASS";
        case OBJECT: return "OBJECT";
        case NUL: return "NULL";
        default: return "UNKNOWN";
    }
}

std::array<int,6> values = {0, 1, 2, 3, 4, 5};

std::map<std::string, Token> locked = {
    {"~END", Token(";", END)},

    {"~ASSIGN", Token("=", ASSIGN, -values[3])},
    {"~ADDASSIGN", Token("+", OPERATOR, -values[1])},
    {"~SUBASSIGN", Token("-", OPERATOR, -values[1])},
    {"~MULASSIGN", Token("*", OPERATOR, -values[2])},
    {"~DIVASSIGN", Token("/", OPERATOR, -values[2])},
    {"~MODASSIGN", Token("%", OPERATOR, -values[2])},

    {"~PLUS", Token("+", OPERATOR, values[1])},
    {"~MINUS", Token("-", OPERATOR, values[1])},
    {"~ASTERISK", Token("*", OPERATOR, values[2])},
    {"~SLASH", Token("/", OPERATOR, values[2])},
    {"~MODULO", Token("%", OPERATOR, values[2])},

    {"~NOT", Token("!", OPERATOR)},
    {"~AND", Token("&&", OPERATOR)},
    {"~OR", Token("||", OPERATOR)},
    {"~EQUAL", Token("==", OPERATOR)},
    {"~NOTEQUAL", Token("!=", OPERATOR)},
    {"~LESSTHAN", Token("<", OPERATOR)},
    {"~LESSEQUAL", Token("<=", OPERATOR)},
    {"~GREATERTHAN", Token(">", OPERATOR)},
    {"~GREATEREQUAL", Token(">=", OPERATOR)},

    {"~BRACKETOPEN", Token("(", BRACKET_OPEN)},
    {"~BRACKETCLOSE", Token(")", BRACKET_CLOSE)},
    {"~SQUAREBRACKETOPEN", Token("[", BRACKET_OPEN)},
    {"~SQUAREBRACKETCLOSE", Token("]", BRACKET_CLOSE)},
    {"~CURLYBRACKETOPEN", Token("{", BRACKET_OPEN)},
    {"~CURLYBRACKETCLOSE", Token("}", BRACKET_CLOSE)},

    {"~QUESTIONMARK", Token("?", QUESTIONMARK)},
    {"~COMMA", Token(",", COMMA)},
    {"~COLON", Token(":", COLON)},
    {"~DOT", Token(".", DOT)},
    {"~BACKSLASH", Token("\\", BACKSLASH)},
    {"~HASHTAG", Token("#", HASHTAG)},
    {"~AMPERSAND", Token("&", AMPERSAND)},
};

std::map<std::string, std::string> lockSymbol = {
    {";", "~END"},
    {"\n", "~ENDLINE"},
    {"=", "~ASSIGN"},
    {"+", "~PLUS"},
    {"-", "~MINUS"},
    {"*", "~ASTERISK"},
    {"/", "~SLASH"},
    {"%", "~MODULO"},
    {"++", "~INCREMENT"},
    {"--", "~DECREMENT"},
    {"+=", "~ADDASSIGN"},
    {"-=", "~SUBASSIGN"},
    {"*=", "~MULASSIGN"},
    {"/=", "~DIVASSIGN"},
    {"%=", "~MODASSIGN"},
    {"!", "~NOT"},
    {"&&", "~AND"},
    {"||", "~OR"},
    {"==", "~EQUAL"},
    {"!=", "~NOTEQUAL"},
    {"<", "~LESSTHAN"},
    {"<=", "~LESSEQUAL"},
    {">", "~GREATERTHAN"},
    {">=", "~GREATEREQUAL"},
    {"(", "~BRACKETOPEN"},
    {")", "~BRACKETCLOSE"},
    {"[", "~SQUAREBRACKETOPEN"},
    {"]", "~SQUAREBRACKETCLOSE"},
    {"{", "~CURLYBRACKETOPEN"},
    {"}", "~CURLYBRACKETCLOSE"},
    {"\'", "~APOSTROPHE"},
    {"\"", "~QUOTATION"},
    {"?", "~QUESTIONMARK"},
    {",", "~COMMA"},
    {":", "~COLON"},
    {".", "~DOT"},
    {"\\", "~BACKSLASH"},
    {"//", "~DOUBLESLASH"},
    {"#", "~HASHTAG"},
    {" ", "~SPACE"},
    {"\t", "~TAB"},
    {"&", "~AMPERSAND"}
    
};

std::vector<std::string> operators = {
    // "{",
    // "}",
    // "(",
    // ")",
    // "[",
    // "]",
    ";",
    " ",
    "==",
    "!=",
    "<=",
    ">=",
    "&&",
    "||",
    "++",
    "--",
    "+=",
    "-=",
    "*=",
    "/=",
    "%=",
    "//",
    "\n",
    "\t",
    "=",
    "+",
    "*",
    "/",
    "!",
    "-",
    "<",
    ">",
    "%",
    
    "'",
    "\"",
    "?",
    ",",
    ":",
    ".",
    "\\",
    "#",
    "&"
    };

std::set<std::string> keywords = {
    "import",
    "as",
    "return",
    "if",
    "else",
    "for",
    "while",
    "break",
    "continue",
    // "public",
    // "private",
    // "protected",
    };