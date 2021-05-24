# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <vector>
# include <iostream>
# include <string.h>

using namespace std ;


typedef enum {
  INT = 1,
  FLOAT = 2,
  INT_TYPE = 3,
  FLOAT_TYPE = 4,
  CHAR_TYPE = 5,
  BOOL_TYPE = 6,
  STRING = 7,
  STRING_TYPE = 8,
  VOID_TYPE = 9,
  IF = 10,
  ELSE = 11,
  WHILE = 12,
  DO = 13,
  RETURN = 14,
  S_LP = 15, // (
  S_RP = 16, // )
  M_LP = 17, // [
  M_RP = 18, // ]
  L_LP = 19, // {
  L_RP = 20, // }
  PLUS = 21, // '+'
  SUB = 22, // '-'
  MULTI = 23, // '*'
  DIV = 24, // '/'
  IDENT = 25,
  CONSTANT = 26, // e.g., 35, 35.67, 'a', "Hi, there", true, false      //       .35, 35., 0023
  REMAINDER = 27, // %
  HAT = 28,  // ^
  EQUAL = 29, // ==
  NOT_EQUAL = 30, // !=
  BIGGER = 31, // >
  SMALLER = 32, // <
  BIGGGER_EQ = 33, // >=
  SMALLER_EQ = 34, // <=
  ONE_AND = 35, // &
  STRAIGHT = 36, // |
  E_MARK = 37, // !
  AND = 38,    // && 
  OR  = 39,    // || 
  PE  = 40,    // += 
  ME  = 41,    // -= 
  TE  = 42,    // *= 
  DE  = 43,    // /= 
  RE  = 44,    // %= 
  PP  = 45,    // ++ 
  MM  = 46,    // -- 
  RS  = 47,    // >> 
  LS  = 48,    // << 
  SEMICOLON = 49, // 分號
  COMMA = 50, // ,
  QUESTION = 51, // ?
  COLON = 52, // :
  SIGN = 53,

  // ERROR
  UNRECOGNIZED = 54,
  UNEXPECTED = 55, 

  DONE = 56,
  LISTALLVARIABLES = 57,
  LISTALLFUCTIONS = 58,
  LISTVARIABLE = 59,
  LISTFUNCTION = 60

} Token_enum
;

struct Token {
  Token_enum token_type ;// 儲存gettoken的資料型別
  char testNum[10] ; // 儲存老大用來Debug方便所設計的testNum
  int lineNum ; // 以分號為單位來分開行
  int error_lineNum ; // 如果有錯就記錄該lineNum 因為proj2每次輸入都從1開始 每次遇到分號 都會歸0
  char data[500] ;// 儲存gettoken的內容
  bool have_defined ; // IDENT需要判斷有無被定義
  bool is_funtion_defined ; // 是不是funtion定義
  bool is_int ;
  float variable_content ; // 存取要被定義的IDENT的值
} ;

struct Function_Token {
  int start_num ; // 紀錄該function從哪裡開始
  int end_num ; // 紀錄該function從哪裡結束
  char function_name[500] ;// 儲存function名稱
} ;


// Token
void GetToken() ;

// Parser
void User_input() ;
bool Definition() ;
bool Type_specifier() ;
bool Function_definition_or_declarators() ;
bool Rest_of_declarators() ;
bool Function_definition_without_ID() ;
bool Formal_parameter_list() ;
bool Compound_statement() ;
bool Declaration() ;
bool Statement() ;
bool Expression() ;
bool Basic_expression() ;
bool Rest_of_Identifier_started_basic_exp() ;
bool Rest_of_PPMM_Identifier_started_basic_exp() ;
bool Sign() ;
bool Actual_parameter_list() ;
bool Assignment_operator() ;
bool Romce_and_romloe() ;
bool Rest_of_maybe_logical_OR_exp() ;
bool Maybe_logical_AND_exp() ;
bool Rest_of_maybe_logical_AND_exp() ;
bool Maybe_bit_OR_exp() ;
bool Rest_of_maybe_bit_OR_exp() ;
bool Maybe_bit_ex_OR_exp() ;
bool Rest_of_maybe_bit_ex_OR_exp() ;
bool Maybe_bit_AND_exp() ;
bool Rest_of_maybe_bit_AND_exp() ;
bool Maybe_equality_exp() ;
bool Rest_of_maybe_equality_exp() ;
bool Maybe_relational_exp() ;
bool Rest_of_maybe_relational_exp() ;
bool Maybe_shift_exp() ;
bool Rest_of_maybe_shift_exp() ;
bool Maybe_additive_exp() ;
bool Rest_of_maybe_additive_exp() ;
bool Maybe_mult_exp() ;
bool Rest_of_maybe_mult_exp() ;
bool Unary_exp() ;
bool Signed_unary_exp() ;
bool Unsigned_unary_exp() ;



// ERROR
void Unexpected_error() ;
bool Undefined_error() ;
void Unrecognized_error() ;



// Pretty Print
void ListAllVariables() ;          // just the names of the (global) variables,  
                                  // sorted (from smallest to greatest)
void ListAllFunctions() ;          // just the names of the (user-defined)  // functions, sorted
void ListVariable( char parameter[500] ) ; // the definition of a particular variable
void ListFunction( char parameter[500] ) ; // the definition of a particular function
void Done() ;                      // exit the interpreter

// 變數宣告
vector<Token> gToken ;
vector<float> * gValue = new vector<float>() ;
vector<Function_Token> gFunction_Token ;
float gTemp_value = 0.0 ;
Token gToken_info ;
Function_Token gFunction_Token_info ;
int gNum = 0 ;
bool gHave_error = false ; // 有錯誤所以不要印出計算結果
bool gIs_Definition = false ; // 用於判斷是不是走definition這條路，ident需不需要先被定義
bool gIs_function_Definition = false ; // 用於更深層的判斷，不只是definition是function的定義

typedef char CharArray[500];
CharArray gDefined_function_Name[500] ;


// 額外的function
float Rounding( float value ) ;
bool Definiton_and_New_Definition( int temp_num ) ;
void ListAllVariables_Sorted_and_print() ;
void ListAllFunctions_Sorted_and_print() ;
void Sort( int n ) ;
void Funtion_pretty_print( int i ) ;

// =========================================================================================================

void Funtion_pretty_print( int i ) { 

  int start_num = gFunction_Token[i].start_num ;
  int end_num = gFunction_Token[i].end_num ;

  int num_of_L_RP = 0 ;

  while ( start_num <= end_num ) {

    if ( strcmp( gToken[start_num].data, ";" ) == 0 || strcmp( gToken[start_num].data, "{" ) == 0 ) {

      printf( "%s\n", gToken[start_num].data ) ;

      if ( strcmp( gToken[start_num].data, "{" ) == 0 ) num_of_L_RP ++ ;
      if ( strcmp( gToken[start_num+1].data, "}" ) == 0 ) num_of_L_RP -- ;

      int i = 0 ;
      while ( i < num_of_L_RP ) {
        printf( "  " ) ;
        i ++ ;
      } // while

    } // if
    else if ( strcmp( gToken[start_num].data, "}" ) == 0 ) {

      printf( "%s\n", gToken[start_num].data ) ;

      if ( start_num < end_num - 1  ) {
        i = 0 ;
        while ( i < num_of_L_RP ) {
          printf( "  " ) ;
          i ++ ;
        } // while
      } // if

    } // else if
    else {

      if ( strcmp( gToken[start_num].data, "}" ) == 0 ) {
        int i = 0 ;
        while ( i < num_of_L_RP ) {
          printf( "  " ) ;
          i ++ ;
        } // while
      } // if
      printf( "%s ", gToken[start_num].data ) ;
    } // else 

    start_num ++ ;
  } // while

} // Funtion_pretty_print()

void Sort( int n ) {

  char temp[500];

  for ( int i = 0 ; i < n - 1 ; ++i ) {
    for ( int j = i + 1 ; j < n ; ++j )
    {
      if ( strcmp( gDefined_function_Name[i], gDefined_function_Name[j] ) > 0 ) 
      {
        strcpy( temp, gDefined_function_Name[i] );
        strcpy( gDefined_function_Name[i], gDefined_function_Name[j] ) ;
        strcpy( gDefined_function_Name[j], temp );
      } // if
    } // for
  } // for
} // Sort()

void ListAllVariables_Sorted_and_print() { // 因應ListAllVariables需要排序處理

  int find_id = 0 ;
  bool have_find = false ;
  int n = 0 ;
  while ( find_id < gNum ) { // 找找看有沒有這個變數
    // 在proj2 中重複定義同個變數 只有可能是變換了型別
    if ( gToken[find_id].is_funtion_defined == false && gToken[find_id].have_defined == true ) {
      printf( "-------------------------------------------I'm n!!! '%d' '%s'\n", n, gToken[find_id].data ) ;
      strcpy( gDefined_function_Name[n], gToken[find_id].data ) ;
      n ++ ;
    } // if

    find_id ++ ;
  } // while

  Sort( n ) ;
  printf( "> " ) ;

  int i = 0 ;
  while ( i < n ) {
    if ( i < n && strcmp( gDefined_function_Name[i-1], gDefined_function_Name[i] ) != 0 ) {
      printf( "%s()\n", gDefined_function_Name[i] ) ;
    } // if

    i ++ ;
  } // while

  printf( "Statement executed ...\n" ) ;

  int num = 0 ;
  while ( num <= n ) {
    strcpy( gDefined_function_Name[num], "0" );
    num ++ ;
  } // while 

} // ListAllVariables_Sorted_and_print()

void ListAllFunctions_Sorted_and_print() { // 因應ListAllFunctions需要排序處理

  int find_id = 0 ;
  bool have_find = false ;
  int n = 0 ;
  while ( find_id < gNum ) { // 找找看有沒有這個變數
    // 在proj2 中重複定義同個變數 只有可能是變換了型別
    if ( gToken[find_id].is_funtion_defined == true ) {
      printf( "-------------------------------------------I'm n!!! '%d' '%s'\n", n, gToken[find_id].data ) ;
      strcpy( gDefined_function_Name[n], gToken[find_id].data ) ;
      n ++ ;
    } // if

    find_id ++ ;
  } // while

  Sort( n ) ;
  printf( "> " ) ;

  int i = 0 ;
  while ( i < n ) {
    if ( i < n && strcmp( gDefined_function_Name[i-1], gDefined_function_Name[i] ) != 0 ) {
      printf( "%s()\n", gDefined_function_Name[i] ) ;
    } // if

    i ++ ;
  } // while

  printf( "Statement executed ...\n" ) ;

  int num = 0 ;
  while ( num <= n ) {
    strcpy( gDefined_function_Name[num], "0" );
    num ++ ;
  } // while 

} // ListAllFunctions_Sorted_and_print()

bool Definiton_and_New_Definition( int temp_num ) {

  gToken[temp_num].have_defined = true ; // 如果文法沒有錯這個IDENT就會被定義
  if ( gIs_function_Definition ) gToken[temp_num].is_funtion_defined = true ;
  gIs_function_Definition = false ;
  
  int find_id = 0 ;
  bool have_find = false ;
  while ( find_id < temp_num ) { // 找找看有沒有這個變數
    // 在proj2 中重複定義同個變數 只有可能是變換了型別
    if ( strcmp( gToken[find_id].data, gToken[temp_num].data ) == 0 
         && gToken[find_id].have_defined == true ) {
      have_find = true ;
    } // if

    find_id ++ ;
  } // while

  if ( !have_find ) return true ;
  else return false ;
  
} // Definiton_and_New_Definition()

void User_input() { // 用戶輸入

  // Definition 以外的路 (Statement) 都是一碰到ident就要檢查有沒有defined過

  printf( " --------------------^^1.4 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;

  if ( gToken[gNum].token_type != LISTALLFUCTIONS && gToken[gNum].token_type != LISTALLVARIABLES 
       && gToken[gNum].token_type != LISTFUNCTION && gToken[gNum].token_type != LISTVARIABLE 
       && gToken[gNum].token_type != DONE ) {

    if ( Type_specifier() || gToken[gNum].token_type == VOID_TYPE ) { // 還不確定怎麼判斷

      printf( " --------------------^^1.6 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      int temp_num ;
      if ( gToken.size() - gNum > 1 ) temp_num = gNum + 1 ;
      gHave_error = false ; // 初始化
      gIs_Definition = true ;
      gIs_function_Definition = false ;
      if ( Definition() ) {
        printf( " --------------------^^1.5 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
        if ( !gHave_error && gToken[gNum+1].lineNum == 1 ) { 
          
          if ( Definiton_and_New_Definition( temp_num ) ) {
            printf( "> Definition of %s entered ...\n", gToken[temp_num].data ) ; // 處理定義的問題

            // =============================================================================================
            // 如果該funtion沒有問題就儲存起來
            if ( gToken[temp_num].is_funtion_defined == true ) {
              gFunction_Token_info.start_num = temp_num - 1 ; // 看他屬於哪一行
              gFunction_Token_info.end_num = gNum;
              strcpy( gFunction_Token_info.function_name, gToken[temp_num].data ) ;
              gFunction_Token.push_back( gFunction_Token_info );
            } // if
            // =============================================================================================

          } // if
          else printf( "> New definition of %s entered ...\n", gToken[temp_num].data ) ;
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          printf( " --------------------^^42 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // /////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // /////////////////////////////////////////////////////////////////////////////////////////////
          return ;
        } // else if
        else if ( !gHave_error && gToken[gNum].token_type == UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unrecognized_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          gHave_error = false ; // 初始化
        } // else if
        else return ;

      } // if
      else if ( !gHave_error && gToken[gNum].token_type == UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unrecognized_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        gHave_error = false ; // 初始化
      } // else if
    } // if
    else {
      printf( " Into statement1 \n" ) ;
      gHave_error = false ; // 初始化
      gIs_Definition = false ;
      if ( Statement() ) {
        printf( "^^31" ) ;
        if ( !gHave_error && gToken[gNum+1].lineNum == 1 ) { 
          printf( "> Statement executed ...\n" ) ;
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // /////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // /////////////////////////////////////////////////////////////////////////////////////////////
          return ;
        } // else if
        else if ( !gHave_error && gToken[gNum].token_type == UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unrecognized_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          gHave_error = false ; // 初始化
        } // else if
        else return ;
      } // if
      else if ( !gHave_error && gToken[gNum].token_type == UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unrecognized_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        gHave_error = false ; // 初始化
      } // else if
      
    } // else

  } // if


  while ( gToken[gNum].token_type != DONE && gToken[gNum].token_type != LISTALLVARIABLES 
          && gToken[gNum].token_type != LISTALLFUCTIONS 
          && gToken[gNum].token_type != LISTVARIABLE && gToken[gNum].token_type != LISTFUNCTION ) {
    if ( Type_specifier() || gToken[gNum].token_type == VOID_TYPE ) { // 還不確定怎麼判斷

      printf( " --------------------^^3 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      int temp_num ;
      if ( gToken.size() - gNum > 1 ) temp_num = gNum + 1 ;
      gHave_error = false ; // 初始化
      gIs_Definition = true ;
      gIs_function_Definition = false ;
      if ( Definition() ) {
        printf( " --------------------^^4 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
        if ( !gHave_error ) {
          if ( Definiton_and_New_Definition( temp_num ) ) {
            printf( "> Definition of %s entered ...\n", gToken[temp_num].data ) ; // 處理定義的問題
            // =============================================================================================
            // 如果該funtion沒有問題就儲存起來
            if ( gToken[temp_num].is_funtion_defined == true ) {
              gFunction_Token_info.start_num = temp_num - 1 ; // 看他屬於哪一行
              gFunction_Token_info.end_num = gNum;
              strcpy( gFunction_Token_info.function_name, gToken[temp_num].data ) ;
              gFunction_Token.push_back( gFunction_Token_info );
            } // if
            // =============================================================================================
          } // if
          else printf( "> New definition of %s entered ...\n", gToken[temp_num].data ) ;
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // /////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // /////////////////////////////////////////////////////////////////////////////////////////////
          return ;
        } // else if
        else if ( !gHave_error && gToken[gNum].token_type == UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unrecognized_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          gHave_error = false ; // 初始化
        } // else if
        else return ;
      
      } // if
      else if ( !gHave_error && gToken[gNum].token_type == UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unrecognized_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        gHave_error = false ; // 初始化
      } // else if
    } // if
    else {
      printf( " Into statement2 \n" ) ;
      gHave_error = false ; // 初始化
      gIs_Definition = false ;
      if ( Statement() ) {
        printf( " --------------------^^5 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
        if ( !gHave_error && gToken[gNum+1].lineNum == 1 ) { 
          printf( "> Statement executed ...\n" ) ;
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // /////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // /////////////////////////////////////////////////////////////////////////////////////////////
          return ;
        } // else if
        else if ( !gHave_error && gToken[gNum].token_type == UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unrecognized_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          gHave_error = false ; // 初始化
        } // else if
        else return ;
      } // if
      else if ( !gHave_error && gToken[gNum].token_type == UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unrecognized_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        gHave_error = false ; // 初始化
      } // else if
    } // else
  } // while


  if ( gToken[gNum].token_type == DONE ) {
    Done() ;
    return ;
  } // if

  if ( gToken[gNum].token_type == LISTALLVARIABLES ) {
    ListAllVariables() ;
    return ;
  } // if

  if ( gToken[gNum].token_type == LISTALLFUCTIONS ) {
    ListAllFunctions() ;
    return ;
  } // if

  if ( gToken[gNum].token_type == LISTVARIABLE ) {
    ListVariable( gToken[gNum+1].data ) ;
    return ;
  } // if

  if ( gToken[gNum].token_type == LISTFUNCTION ) {
    ListFunction( gToken[gNum+1].data ) ;
    return ;
  } // if

} // User_input()

// =========================================================================================================

bool Definition() { // 定義
  printf( " --------------------^^3.1 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( gToken[gNum].token_type == VOID_TYPE ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( gToken[gNum].token_type == IDENT ) { // definition 裡的ident不用檢查有沒有被定義
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      
      printf( " --------------------^^3.6 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      if ( Function_definition_without_ID() ) return true ;
      else return false;
    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ; 
    } // else if
    else return false ;
  } // if
  else if ( Type_specifier() ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    printf( " --------------------^^3.2 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
    if ( gToken[gNum].token_type == IDENT ) { // definition 裡的ident不用檢查有沒有被定義
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      printf( " --------------------^^3.3 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      if ( Function_definition_or_declarators() ) return true ;
      else return false;
    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ; 
    } // else if
    else return false ;
  } // else if
  else return false ;


} // Definition()

// =========================================================================================================

bool Type_specifier() { // 類型說明符
  if ( gToken[gNum].token_type == INT_TYPE || gToken[gNum].token_type == CHAR_TYPE
       || gToken[gNum].token_type == FLOAT_TYPE || gToken[gNum].token_type == STRING_TYPE
       || gToken[gNum].token_type == BOOL_TYPE ) return true ;
  else return false ;
} // Type_specifier()

// =========================================================================================================

bool Function_definition_or_declarators() { // 函數定義或聲明符
  if ( gToken[gNum].token_type == S_LP ) {
    if ( Function_definition_without_ID() ) return true ;
    else return false ;
  } // if
  else if ( gToken[gNum].token_type == M_LP || gToken[gNum].token_type == COMMA 
            || gToken[gNum].token_type == SEMICOLON ) {
    if ( Rest_of_declarators() ) return true ;
    else return false ;
  } // else if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    return false ; 
  } // else if

  return false ;
} // Function_definition_or_declarators()

// =========================================================================================================

bool Rest_of_declarators() { // 變數後面有中括號 或是一次宣告很多變數 
  printf( " --------------------^^3.4 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( gToken[gNum].token_type == M_LP ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( gToken[gNum].token_type == CONSTANT ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      if ( gToken[gNum].token_type == M_RP ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
      } // if
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        return false ; 
      } // else if
      else return false ;
    } // if 
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      return false ; 
    } // else if
    else return false ;
  } // if

  while ( gToken[gNum].token_type == COMMA ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( gToken[gNum].token_type == IDENT ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
      // ///////////////////////////////////////////////////////////////////////////////////////////////////

      if ( gIs_Definition && gToken.size() - gNum > 1 ) gNum ++ ;
      if ( gToken[gNum].token_type == M_LP ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        if ( gToken[gNum].token_type == CONSTANT ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          if ( gToken[gNum].token_type == M_RP ) {
            if ( gToken.size() - gNum > 1 ) gNum ++ ;
          } // if
          else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
            // /////////////////////////////////////////////////////////////////////////////////////////////
            Unexpected_error() ;
            // /////////////////////////////////////////////////////////////////////////////////////////////
            return false ; 
          } // else if
          else return false ;
        } // if 
        else return false;
      } // if
    } // if

  } // while

  printf( " --------------------^^3.5 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( gToken[gNum].token_type == SEMICOLON ) {
    return true ;
  } // if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    return false ; 
  } // else if

  return false ;

} // Rest_of_declarators()

// =========================================================================================================

bool Function_definition_without_ID() {
  printf( " --------------------^^3.7 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;

  if ( gToken[gNum].token_type == S_LP ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( gToken[gNum].token_type == VOID_TYPE || Formal_parameter_list() ) {
      printf( " --------------------^^3.8 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      if ( gToken[gNum].token_type == VOID_TYPE ) gNum ++ ;
      if ( gToken[gNum].token_type == S_RP ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        if ( Compound_statement() ) return true ;
        else return false ;
      } // if 
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ; 
      } // else if

      return false ;
    } // if 
    else if ( gToken[gNum].token_type == S_RP ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      if ( Compound_statement() ) return true ;
      else return false ;
    } // else if 
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ; 
    } // else if

    return false ;
  } // if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    return false ; 
  } // else if
  else return false ;

  return false ;
    
} // Function_definition_without_ID()

// =========================================================================================================

bool Formal_parameter_list() { // 正式參數列表

  if ( Type_specifier() ) {

    if ( gToken.size() - gNum > 1 ) gNum ++ ;

    if ( gToken[gNum].token_type == AND ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      if ( gToken[gNum].token_type == IDENT ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
        // /////////////////////////////////////////////////////////////////////////////////////////////////

        if ( gIs_Definition && gToken.size() - gNum > 1 ) gNum ++ ;
        if ( gToken[gNum].token_type == M_LP ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          if ( gToken[gNum].token_type == CONSTANT ) {
            if ( gToken.size() - gNum > 1 ) gNum ++ ;
            if ( gToken[gNum].token_type == M_RP ) {
              if ( gToken.size() - gNum > 1 ) gNum ++ ;
              return true;
            } // if
            else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
              // ///////////////////////////////////////////////////////////////////////////////////////////
              Unexpected_error() ;
              // ///////////////////////////////////////////////////////////////////////////////////////////
              return false ; 
            } // else if
            else return false ;
          } // if
          else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
            // /////////////////////////////////////////////////////////////////////////////////////////////
            Unexpected_error() ;
            // /////////////////////////////////////////////////////////////////////////////////////////////
            return false ; 
          } // else if
          else return false ;
        } // if
        else {
          // 特殊情況 回去 function_definition_without_ID 時才會加加 所以這裡要先減回去
          if ( gIs_Definition ) gNum -- ;
          return true ;
        } // else
      } // if
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ; 
      } // else if
      else return false ;
    } // if
    else if ( gToken[gNum].token_type == IDENT ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
      // ///////////////////////////////////////////////////////////////////////////////////////////////////

      if ( gIs_Definition && gToken.size() - gNum > 1 ) gNum ++ ;
      if ( gToken[gNum].token_type == M_LP ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        if ( gToken[gNum].token_type == CONSTANT ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          if ( gToken[gNum].token_type == M_RP ) {
            if ( gToken.size() - gNum > 1 ) gNum ++ ;
            return true;
          } // if
          else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
            // /////////////////////////////////////////////////////////////////////////////////////////////
            Unexpected_error() ;
            // /////////////////////////////////////////////////////////////////////////////////////////////
            return false ; 
          } // else if
          else return false ;
        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          return false ; 
        } // else if  
        else return false ;
      } // if
      else {
        // 特殊情況 回去 function_definition_without_ID 時才會加加 所以這裡要先減回去
        if ( gIs_Definition ) gNum -- ;
        return true ;
      } // else
    } // else if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ; 
    } // else if
    else return false ;
  } // if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    return false ; 
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == COMMA ) {

    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Type_specifier() ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      if ( gToken[gNum].token_type == AND ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        if ( gToken[gNum].token_type == IDENT ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
          // ///////////////////////////////////////////////////////////////////////////////////////////////

          if ( gIs_Definition && gToken.size() - gNum > 1 ) gNum ++ ;
          if ( gToken[gNum].token_type == M_LP ) {
            if ( gToken.size() - gNum > 1 ) gNum ++ ;
            if ( gToken[gNum].token_type == CONSTANT ) {
              if ( gToken.size() - gNum > 1 ) gNum ++ ;
              if ( gToken[gNum].token_type == M_RP ) {
                if ( gToken.size() - gNum > 1 ) gNum ++ ;
              } // if
              else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
                // /////////////////////////////////////////////////////////////////////////////////////////
                Unexpected_error() ;
                // /////////////////////////////////////////////////////////////////////////////////////////
                return false ; 
              } // else if
              else return false ;
            } // if
            else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
              // ///////////////////////////////////////////////////////////////////////////////////////////
              Unexpected_error() ;
              // ///////////////////////////////////////////////////////////////////////////////////////////
              return false ; 
            } // else if
            else return false ;
          } // if
          else {
            // 特殊情況 回去 function_definition_without_ID 時才會加加 所以這裡要先減回去
            if ( gIs_Definition ) gNum -- ;
            return true ;
          } // else
        } // if
        else return false ;
      } // if
      else if ( gToken[gNum].token_type == IDENT ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
        // /////////////////////////////////////////////////////////////////////////////////////////////////

        if ( gIs_Definition && gToken.size() - gNum > 1 ) gNum ++ ;
        if ( gToken[gNum].token_type == M_LP ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          if ( gToken[gNum].token_type == CONSTANT ) {
            if ( gToken.size() - gNum > 1 ) gNum ++ ;
            if ( gToken[gNum].token_type == M_RP ) {
              if ( gToken.size() - gNum > 1 ) gNum ++ ;
            } // if
            else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
              // ///////////////////////////////////////////////////////////////////////////////////////////
              Unexpected_error() ;
              // ///////////////////////////////////////////////////////////////////////////////////////////
              return false ; 
            } // else if
            else return false ;
          } // if
          else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
            // /////////////////////////////////////////////////////////////////////////////////////////////
            Unexpected_error() ;
            // /////////////////////////////////////////////////////////////////////////////////////////////
            return false ; 
          } // else if
          else return false ;
        } // if
        else {
          // 特殊情況 回去 function_definition_without_ID 時才會加加 所以這裡要先減回去
          if ( gIs_Definition ) gNum -- ;
          return true ;
        } // else

      } // else if
      else return false ;

    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ; 
    } // else if
    else return false ;

  } // while

  return true ; // 沒有return false 就是return true ;

} // Formal_parameter_list()

// =========================================================================================================

bool Compound_statement() { // 複合陳述
  printf( " --------------------^^43 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;

  if ( gToken[gNum].token_type == L_LP ) {

    // 是正在跑定義，又同時進到大括號，代表他應是funtion定義
    if ( gIs_Definition ) gIs_function_Definition = true ; 
    gIs_Definition = true ;

    if ( gToken.size() - gNum > 1 ) gNum ++ ;

    while ( gToken.size() - gNum > 1 ) {
      printf( " --------------------^^44 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;

      if ( gToken[gNum].token_type == L_RP ) { // 直接L_RP回去 回到user input才跳下一個
        return true ;
      } // if 
      else if ( Type_specifier() ) { 
        if ( Declaration() ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
        } // if
        else return false ;
      } // else if
      else if ( Statement() ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
      } // if
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ; 
      } // else if
      else return false ;

    } // while
  } // if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    return false ; 
  } // else if

  return false ;

} // Compound_statement()

// =========================================================================================================

bool Declaration() {
  if ( Type_specifier() ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( gToken[gNum].token_type == IDENT ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      
      if ( gIs_Definition && gToken.size() - gNum > 1 ) gNum ++ ;
      if ( Rest_of_declarators() ) return true;
      else return false ;
    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ; 
    } // else if
    else return false ;
  } // if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    return false ; 
  } // else if
  else return false ;
} // Declaration()

// =========================================================================================================

bool Statement() {
  printf( " --------------------^^6 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( gToken[gNum].token_type == SEMICOLON ) return true ;
  else if ( gToken[gNum].token_type == RETURN ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Expression() ) { // 只會跑一次
      ; // 沒事幹
    } // if

    if ( gToken[gNum].token_type == SEMICOLON ) return true ;
    else return false ;
  } // else if
  else if ( gToken[gNum].token_type == L_LP ) {
    if ( Compound_statement() ) return true ;
    else return false ;
  } // else if
  else if ( gToken[gNum].token_type == IF ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( gToken[gNum].token_type == S_LP ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      printf( " --------------------^^49 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      if ( Expression() ) ; // 對的話 沒事幹 繼續執行
      else return false ;
      printf( " --------------------^^50 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      if ( gToken[gNum].token_type == S_RP ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        if ( Statement() ) {
          ;
        } // if 

        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        printf( " --------------------^^51 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
        if ( gToken[gNum].token_type == ELSE ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          if ( Statement() ) return true ;
          else return false ;
        } // if 
        else gNum -- ;
      } // if
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;
    } // if
    else return false ;

  } // else if
  else if ( gToken[gNum].token_type == WHILE ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( gToken[gNum].token_type == S_LP ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      if ( Expression() ) ; // 對的話 沒事幹 繼續執行
      else return false ;
      if ( gToken[gNum].token_type == S_RP ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        if ( Statement() ) return true ;
        else return false ;
      } // if
    } // if
    else return false ;
  } // else if
  else if ( gToken[gNum].token_type == DO ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Statement() ) return true ;
    else return false ;

    if ( gToken[gNum].token_type == WHILE ) {
      if ( gToken[gNum].token_type == S_LP ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        if ( Expression() ) ; // 對的話 沒事幹 繼續執行
        else return false ;
        if ( gToken[gNum].token_type == S_RP ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          if ( gToken[gNum].token_type == SEMICOLON ) return true ; // 一定要接 分號
          else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
            // /////////////////////////////////////////////////////////////////////////////////////////////
            Unexpected_error() ;
            // /////////////////////////////////////////////////////////////////////////////////////////////
            return false ;
          } // else if
          else return false;

        } // if
        else return false ;

      } // if
      else return false ;

    } // if
    else return false ;

  } // else if
  else if ( Expression() ) { // expression here should not be empty
    if ( gToken[gNum].token_type == SEMICOLON ) return true ;
    else return false ;
  } // else if
  else return false ;

  return true ;

} // Statement()

// =========================================================================================================

bool Expression() {
  printf( " --------------------^^7 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( Basic_expression() ) {
    while ( gToken[gNum].token_type == COMMA ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      printf( " --------------------^^11 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      if ( Basic_expression() ) printf( " --------------------^^32 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      else {
        printf( " --------------------^^41 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
        return false ;
      } // else
    } // while

    return true ;
  } // if
  else return false ;

} // Expression()

// =========================================================================================================

bool Basic_expression() {
  printf( " --------------------^^8 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  
  if ( gToken[gNum].token_type == IDENT ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
    // /////////////////////////////////////////////////////////////////////////////////////////////////////

    if ( gIs_Definition && gToken.size() - gNum > 1 ) gNum ++ ;
    printf( " --------------------^^9 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
    if ( Rest_of_Identifier_started_basic_exp() ) {
      printf( " --------------------^^12 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      return true ;
    } // if 
    else {
      printf( " --------------------^^13 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      return false ;
    } // else 
  } // if
  else if ( gToken[gNum].token_type == PP || gToken[gNum].token_type == MM ) {

    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( gToken[gNum].token_type == IDENT ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
      // ///////////////////////////////////////////////////////////////////////////////////////////////////

      if ( gIs_Definition && gToken.size() - gNum > 1 ) gNum ++ ;
      if ( Rest_of_PPMM_Identifier_started_basic_exp() ) return true ;
      else return false ;
    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
    
  } // else if
  else if ( Sign() ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    while ( Sign() ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
    } // while

    if ( Signed_unary_exp() ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      if ( Romce_and_romloe() ) return true ;
      else return false ;
    } // if
    else return false ;
  } // else if
  else {
    if ( gToken[gNum].token_type == CONSTANT ) {
      // 一直遞迴下去吧~~~~如果這裡已經是分號了，一樣繼續遞迴下去
      // 會在Rest_of_maybe_mult_exp() 在一樣是分號回來
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      printf( " --------------------^^15 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      if ( Romce_and_romloe() ) return true ;
      else return false ;
    } // if
    else if ( gToken[gNum].token_type == S_LP ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      if ( Expression() ) {
        if ( gToken[gNum].token_type == S_RP ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // else if
        else return false ;

        if ( Romce_and_romloe() ) return true ;
        else return false ;
      } // if
      else return false ;
    } // else if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
  
    } // else if
    else return false ;
  } // else

} // Basic_expression()

// =========================================================================================================

bool Rest_of_Identifier_started_basic_exp() {
  printf( " --------------------^^30 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( gToken[gNum].token_type == M_LP || Assignment_operator() ) {
    if ( gToken[gNum].token_type == M_LP ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      if ( Expression() ) {
        printf( " --------------------^^51 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
        if ( gToken[gNum].token_type == M_RP ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          ;
        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // /////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // /////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // else if
        else return false ;
      } // if
      else return false ;
    } // if
    printf( " --------------------^^52 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
    if ( Assignment_operator() ) {
      printf( " --------------------^^14 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      if ( Basic_expression() ) return true ;
      else return false ;
    } // if
    else if ( gToken[gNum].token_type == PP || gToken[gNum].token_type == MM ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;

      if ( Romce_and_romloe() ) return true ;
      else return false ;
    } // else if
    else if ( Romce_and_romloe() ) {
      return true ;
    } // else if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
  } // if
  else if ( gToken[gNum].token_type == S_LP ) {
    
    if ( gToken.size() - gNum > 1 ) gNum ++ ;

    if ( gToken[gNum].token_type == S_RP ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      if ( Romce_and_romloe() ) return true ;
      else return false ;
    } // if
    else if ( Actual_parameter_list() ) {
      printf( " --------------------^^48 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
      if ( gToken[gNum].token_type == S_RP ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        if ( Romce_and_romloe() ) return true ;
        else return false ;
      } // if
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;
    } // else if 
    else return false;

  } // else if 
  else {
    if ( gToken[gNum].token_type == PP || gToken[gNum].token_type == MM ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
    } // if

    if ( Romce_and_romloe() ) return true ;
    else return false ;
  } // else 

  return true ;

} // Rest_of_Identifier_started_basic_exp()

// =========================================================================================================

bool Rest_of_PPMM_Identifier_started_basic_exp() {
  if ( gToken[gNum].token_type == M_LP ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Expression() ) ;
    else return false ;
    if ( gToken[gNum].token_type == M_RP ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
  } // if

  if ( Romce_and_romloe() ) return true ;
  else return false ;
} // Rest_of_PPMM_Identifier_started_basic_exp()

// =========================================================================================================

bool Sign() {
  if ( gToken[gNum].token_type == SIGN ) return true ; // '+' '=' '!'
  else return false ;
} // Sign()

// =========================================================================================================

bool Actual_parameter_list() {

  if ( Basic_expression() ) return true ;
  else return false ;
  
  while ( gToken[gNum].token_type == COMMA ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Basic_expression() ) ; 
    else return false ; // 錯誤

  } // while

  return true ;

} // Actual_parameter_list()

// =========================================================================================================

bool Assignment_operator() {
  if ( gToken[gNum].token_type == EQUAL || gToken[gNum].token_type == TE 
       || gToken[gNum].token_type == DE || gToken[gNum].token_type == RE 
       || gToken[gNum].token_type == PE || gToken[gNum].token_type == ME ) return true ;
  else return false ; 
} // Assignment_operator()

// =========================================================================================================

bool Romce_and_romloe() {

  if ( Rest_of_maybe_logical_OR_exp() ) {
    ; // 沒事幹
  } // if 
  else return false ;

  if ( gToken[gNum].token_type == QUESTION ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Basic_expression() ) return true ;
    else return false ;
    if ( gToken[gNum].token_type == COLON ) {
      if ( Basic_expression() ) return true ;
      else return false ;
    } // if
    else return false ;
  } // if

  return true ;

} // Romce_and_romloe()

// =========================================================================================================

bool Rest_of_maybe_logical_OR_exp() {

  if ( Rest_of_maybe_logical_AND_exp() ) {
    ; // 沒事幹
  } // if 
  else return false ;

  while ( gToken[gNum].token_type == OR ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_logical_AND_exp() ) return true ;
    else return false ;
  } // while

  return true ;

} // Rest_of_maybe_logical_OR_exp()

// =========================================================================================================

bool Maybe_logical_AND_exp() {

  if ( Maybe_bit_OR_exp() ) {
    ; // 沒事幹
  } // if 
  else return false ;

  while ( gToken[gNum].token_type == AND ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_bit_OR_exp() ) return true ;
    else return false ;
  } // while

  return true ;

} // Maybe_logical_AND_exp()

// =========================================================================================================

bool Rest_of_maybe_logical_AND_exp() {
  printf( " --------------------^^16 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( Rest_of_maybe_bit_OR_exp() ) {
    ; // 沒事幹
  } // if 
  else return false ;

  while ( gToken[gNum].token_type == AND ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_bit_OR_exp() ) ; 
    else return false ; // 錯誤

  } // while

  return true ;
} // Rest_of_maybe_logical_AND_exp()

// =========================================================================================================

bool Maybe_bit_OR_exp() {

  if ( Maybe_bit_ex_OR_exp() ) {
    ; // 沒事幹
  } // if 
  else return false ;

  while ( gToken[gNum].token_type == STRAIGHT ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_bit_ex_OR_exp() ) ; 
    else return false ; // 錯誤

  } // while

  return true ;
} // Maybe_bit_OR_exp()

// =========================================================================================================

bool Rest_of_maybe_bit_OR_exp() {

  printf( " --------------------^^17 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( Rest_of_maybe_bit_ex_OR_exp() ) {
    ; // 沒事幹
  } // if 
  else return false ;

  while ( gToken[gNum].token_type == STRAIGHT ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_bit_ex_OR_exp() ) ; 
    else return false ; // 錯誤

  } // while

  return true ;
} // Rest_of_maybe_bit_OR_exp()

// =========================================================================================================

bool Maybe_bit_ex_OR_exp() {

  if ( Maybe_bit_AND_exp() ) {
    ; // 沒事幹
  } // if 

  while ( gToken[gNum].token_type == HAT ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_bit_AND_exp() ) ; 
    else return false ; // 錯誤

  } // while

  return true ;
} // Maybe_bit_ex_OR_exp()

// =========================================================================================================

bool Rest_of_maybe_bit_ex_OR_exp() {
  printf( " --------------------^^18 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( Rest_of_maybe_bit_AND_exp() ) {
    ; // 沒事幹
  } // if 

  while ( gToken[gNum].token_type == HAT ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_bit_AND_exp() ) ; 
    else return false ; // 錯誤

  } // while

  return true ;
} // Rest_of_maybe_bit_ex_OR_exp()

// =========================================================================================================

bool Maybe_bit_AND_exp() {
 
  if ( Maybe_equality_exp() ) {
    ; // 沒事幹
  } // if 

  while ( gToken[gNum].token_type == ONE_AND ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_equality_exp() ) ; 
    else return false ; // 錯誤

  } // while

  return true ;
} // Maybe_bit_AND_exp()

// =========================================================================================================

bool Rest_of_maybe_bit_AND_exp() {
  printf( " --------------------^^19 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( Rest_of_maybe_equality_exp() ) {
    ; // 沒事幹
  } // if 

  while ( gToken[gNum].token_type == ONE_AND ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_equality_exp() ) ; 
    else return false ; // 錯誤

  } // while
  
  return true ;
} // Rest_of_maybe_bit_AND_exp()

// =========================================================================================================

bool Maybe_equality_exp() {

  if ( Maybe_relational_exp() ) {
    ; // 沒事幹
  } // if 

  while ( gToken[gNum].token_type == EQUAL || gToken[gNum].token_type == NOT_EQUAL ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_relational_exp() ) ; 
    else return false ; // 錯誤

  } // while
  
  return true ;
} // Maybe_equality_exp()

// =========================================================================================================

bool Rest_of_maybe_equality_exp() {
  printf( " --------------------^^20 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( Rest_of_maybe_relational_exp() ) {
    ; // 沒事幹
  } // if 

  while ( gToken[gNum].token_type == EQUAL || gToken[gNum].token_type == NOT_EQUAL ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_relational_exp() ) ; 
    else return false ; // 錯誤

  } // while
  
  return true ;
} // Rest_of_maybe_equality_exp()

// =========================================================================================================

bool Maybe_relational_exp() {

  if ( Maybe_shift_exp() ) {
    ; // 沒事幹
  } // if 

  while ( gToken[gNum].token_type == SMALLER_EQ || gToken[gNum].token_type == BIGGGER_EQ
          || gToken[gNum].token_type == SMALLER || gToken[gNum].token_type == BIGGER ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_shift_exp() ) ; 
    else return false ; // 錯誤

  } // while
  
  return true ;
} // Maybe_relational_exp()

// =========================================================================================================

bool Rest_of_maybe_relational_exp() {
  printf( " --------------------^^21 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( Rest_of_maybe_shift_exp() ) {
    ; // 沒事幹
  } // if 

  while ( gToken[gNum].token_type == SMALLER_EQ || gToken[gNum].token_type == BIGGGER_EQ
          || gToken[gNum].token_type == SMALLER || gToken[gNum].token_type == BIGGER ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_shift_exp() ) ; 
    else return false ; // 錯誤

  } // while
  
  return true ;

} // Rest_of_maybe_relational_exp()

// =========================================================================================================

bool Maybe_shift_exp() {

  if ( Maybe_additive_exp() ) {
    ; // 沒事幹
  } // if 

  while ( gToken[gNum].token_type == LS || gToken[gNum].token_type == RS ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_additive_exp() ) ; 
    else return false ; // 錯誤

  } // while
  
  return true ;
} // Maybe_shift_exp()

// =========================================================================================================

bool Rest_of_maybe_shift_exp() {
  printf( " --------------------^^22 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( Rest_of_maybe_additive_exp() ) {
    ; // 沒事幹
  } // if 

  while ( gToken[gNum].token_type == LS || gToken[gNum].token_type == RS ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_additive_exp() ) ; 
    else return false ; // 錯誤

  } // while
  
  return true ;
} // Rest_of_maybe_shift_exp()

// =========================================================================================================

bool Maybe_additive_exp() {

  if ( Maybe_mult_exp() ) {
    ; // 沒事幹
  } // if 

  while ( gToken[gNum].token_type == PLUS || gToken[gNum].token_type == SUB ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_mult_exp() ) ; 
    else return false ; // 錯誤

  } // while
  
  return true ;
} // Maybe_additive_exp()

// =========================================================================================================

bool Rest_of_maybe_additive_exp() {
  printf( " --------------------^^23 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( Rest_of_maybe_mult_exp() ) {
    ; // 沒事幹
  } // if 

  while ( gToken[gNum].token_type == PLUS || gToken[gNum].token_type == SUB ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Maybe_mult_exp() ) ; 
    else return false ; // 錯誤

  } // while
  
  return true ;
} // Rest_of_maybe_additive_exp()

// =========================================================================================================

bool Maybe_mult_exp() {
  printf( " --------------------^^39 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( Unary_exp() ) {
    if ( Rest_of_maybe_mult_exp() ) return true ;
    else return false ;
  } // if
  else return false;

} // Maybe_mult_exp()

// =========================================================================================================

bool Rest_of_maybe_mult_exp() {
  printf( " --------------------^^24 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  while ( gToken[gNum].token_type == MULTI || gToken[gNum].token_type == DIV 
          || gToken[gNum].token_type == REMAINDER ) {
    printf( " --------------------^^42 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Unary_exp() ) {
      ; // 沒事幹
    } // if
    else return false ;
  } // while

  return true ; // could be empty ! 
} // Rest_of_maybe_mult_exp()

// =========================================================================================================

bool Unary_exp() {
  printf( " --------------------^^38 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( Sign() ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    while ( Sign() ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
    } // while

    if ( Signed_unary_exp() ) return true ;
    else return false ;
  } // if 
  else if ( gToken[gNum].token_type == IDENT || gToken[gNum].token_type == CONSTANT 
            || gToken[gNum].token_type == S_LP ) {
    // 這裡不用判斷 Undefined 進去下一個函式再判斷
    if ( Unsigned_unary_exp() ) return true ;
    else return false ;
  } // else if 
  else if ( gToken[gNum].token_type == PP || gToken[gNum].token_type == MM ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( gToken[gNum].token_type == IDENT ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
      // ///////////////////////////////////////////////////////////////////////////////////////////////////

      if ( gIs_Definition && gToken.size() - gNum > 1 ) gNum ++ ;
      if ( gToken[gNum].token_type == M_LP ) {
        if ( Expression() ) {
          if ( gToken[gNum].token_type == M_RP ) {
            if ( gToken.size() - gNum > 1 ) gNum ++ ;
            return true ;
          } // if
          else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
            // ///////////////////////////////////////////////////////////////////////////////////////////
            Unexpected_error() ;
            // ///////////////////////////////////////////////////////////////////////////////////////////
            return false ;
          } // else if
          else return false ;
        } // if
        else return false ;
      } // if

      return true ;
    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
  } // else if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;
} // Unary_exp()

// =========================================================================================================

bool Signed_unary_exp() {
  if ( gToken[gNum].token_type == IDENT ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
    // /////////////////////////////////////////////////////////////////////////////////////////////////////

    if ( gIs_Definition && gToken.size() - gNum > 1 ) gNum ++ ;
    if ( gToken[gNum].token_type == S_LP ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      if ( gToken[gNum].token_type == S_RP ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        return true ;
      } // if
      else if ( Actual_parameter_list() ) {
        
        if ( gToken[gNum].token_type == S_RP ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          return true ;
        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // else if
        else return false ;
      } // else if
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;

    } // if
    else if ( gToken[gNum].token_type == M_LP ) {
      if ( Expression() ) {
        ; // 沒事幹
      } // if
      else return false;
      if ( gToken[gNum].token_type == M_RP ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        return true ;
      } // if
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;
    } // else if

    return true ;
  } // if
  else if ( gToken[gNum].token_type == CONSTANT ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    return true ;
  } // else if
  else if ( gToken[gNum].token_type == S_LP ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Expression() ) {
      ; // 沒事幹
    } // if
    else return false ;
    if ( gToken[gNum].token_type == S_RP ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      return true ;
    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
  } // else if

  return true ;
} // Signed_unary_exp()

// =========================================================================================================

bool Unsigned_unary_exp() {

  printf( " --------------------^^40 : data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
  if ( gToken[gNum].token_type == IDENT ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
    // /////////////////////////////////////////////////////////////////////////////////////////////////////

    if ( gIs_Definition && gToken.size() - gNum > 1 ) gNum ++ ;
    if ( gToken[gNum].token_type == S_LP ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      if ( gToken[gNum].token_type == S_RP ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        return true ;
      } // if
      else if ( Actual_parameter_list() ) {
        if ( gToken[gNum].token_type == S_RP ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          return true ;
        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // else if
        else return false ;
      } // else if
      else return false ;
    } // if
    else if ( gToken[gNum].token_type == M_LP || gToken[gNum].token_type == PP 
              || gToken[gNum].token_type == MM ) {
      if ( gToken[gNum].token_type == M_LP ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        if ( Expression() ) {
          ; // 沒事幹
        } // if
        else return false ;
        if ( gToken[gNum].token_type == M_RP ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          return true ;
        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // else if
        else return false ;
      } // if

      if ( gToken[gNum].token_type == PP || gToken[gNum].token_type == MM ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
      } // if

      return true ;
    } // else if

    return true ;
  } // if
  else if ( gToken[gNum].token_type == CONSTANT ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    return true ;
  } // else if
  else if ( gToken[gNum].token_type == S_LP ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    if ( Expression() ) {
      ; // 沒事幹
    } // if
    else return false ;
    if ( gToken[gNum].token_type == S_RP ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      return true ;
    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
  } // else if

  return true ;
} // Unsigned_unary_exp()


// =========================================================================================================


void Unexpected_error() {

  printf( "> Line %d : unexpected token : '%s'\n", gToken[gNum].lineNum, gToken[gNum].data );

  gHave_error = true;

  int temp_Line = gToken[gNum].lineNum;
  // 印出錯誤後把這一整行到分號都不要
  while ( temp_Line == gToken[gNum].lineNum && gToken[gNum].token_type != SEMICOLON 
          && gToken[gNum].token_type != L_RP ) {
    if ( gToken.size() - gNum > 1 ) gNum++;
    else return ;
  } // while

  if ( gToken.size() - gNum > 1 && gToken[gNum].token_type == L_RP ) gNum++;

  // 重置錯誤後的行數 Proj2獨有
  if ( gToken.size() - gNum > 1 && gToken[gNum].token_type != SEMICOLON 
       && gToken[gNum].token_type != L_RP ) {
    int temp_gNum = gNum ;
    while ( temp_gNum < gToken.size() && gToken[temp_gNum].token_type != SEMICOLON 
            && gToken[gNum].token_type != L_RP ) {
      gToken[temp_gNum].lineNum = gToken[temp_gNum].lineNum - temp_Line ;
      temp_gNum ++ ;
    } // while

    gToken[temp_gNum].lineNum = gToken[temp_gNum].lineNum - temp_Line ; // 分號那行也要改
  } // if
  else if ( gToken.size() - gNum > 1 && gToken[gNum].token_type == SEMICOLON 
            && temp_Line == gToken[gNum].lineNum ) gNum ++ ;

  printf( "nextToken->'%s'nextLine->'%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;

  gValue->clear(); // 初始化

} // Unexpected_error()

// =========================================================================================================

bool Undefined_error() {

  int find_id = 0;
  bool found_it = false;
  while ( find_id < gNum && !found_it ) { // 找找看有沒有這個變數

    if ( strcmp( gToken[find_id].data, gToken[gNum].data ) == 0
         && gToken[find_id].have_defined == true ) {
      // 找到了就把值給取出來
      gValue->push_back( gToken[find_id].variable_content );
      found_it = true;
    } // if

    find_id++;

  } // while

  if ( !gHave_error && !found_it ) {
    printf( "> Line %d : undefined identifier : '%s'\n", gToken[gNum].lineNum, gToken[gNum].data ) ;
    gHave_error = true;

    int temp_Line = gToken[gNum].lineNum;
    // 印出錯誤後把這一整行到分號都不要
    if ( gToken.size() - gNum > 1 ) gNum++;
    while ( temp_Line == gToken[gNum].lineNum && gToken[gNum].token_type != SEMICOLON ) {
      if ( gToken.size() - gNum > 1 ) gNum++;
      else return true ;
    } // while

    // 重置錯誤後的行數 Proj2獨有
    if ( gToken.size() - gNum > 1 && gToken[gNum].token_type != SEMICOLON 
        && gToken[gNum].token_type != L_RP ) {
      int temp_gNum = gNum ;
      while ( temp_gNum < gToken.size() && gToken[temp_gNum].token_type != SEMICOLON 
              && gToken[gNum].token_type != L_RP ) {
        gToken[temp_gNum].lineNum = gToken[temp_gNum].lineNum - temp_Line ;
        temp_gNum ++ ;
      } // while

      gToken[temp_gNum].lineNum = gToken[temp_gNum].lineNum - temp_Line ; // 分號那行也要改
    } // if
    else if ( gToken.size() - gNum > 1 && gToken[gNum].token_type == SEMICOLON 
              && temp_Line == gToken[gNum].lineNum ) gNum ++ ;

    printf( "nextToken->'%s'nextLine->'%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;

    gValue->clear(); // 初始化
    return true ;

  } // if
  else if ( gToken.size() - gNum > 1 ) {
    gNum++;
    return false ;
  } // else if 

  return false ;

} // Undefined_error()

// =========================================================================================================

void Unrecognized_error() {

  printf( "> Line %d : unrecognized token with first char : '%s'\n",
          gToken[gNum].lineNum, gToken[gNum].data );

  gHave_error = true;

  int temp_Line = gToken[gNum].lineNum;
  // 印出錯誤後把這一整行到分號都不要
  while ( temp_Line == gToken[gNum].lineNum && gToken[gNum].token_type != SEMICOLON ) {
    if ( gToken.size() - gNum > 1 ) gNum++;
    else return ;
  } // while

  // 重置錯誤後的行數 Proj2獨有
  if ( gToken.size() - gNum > 1 && gToken[gNum].token_type != SEMICOLON 
       && gToken[gNum].token_type != L_RP ) {
    int temp_gNum = gNum ;
    while ( temp_gNum < gToken.size() && gToken[temp_gNum].token_type != SEMICOLON 
            && gToken[gNum].token_type != L_RP ) {
      gToken[temp_gNum].lineNum = gToken[temp_gNum].lineNum - temp_Line ;
      temp_gNum ++ ;
    } // while

    gToken[temp_gNum].lineNum = gToken[temp_gNum].lineNum - temp_Line ; // 分號那行也要改
  } // if
  else if ( gToken.size() - gNum > 1 && gToken[gNum].token_type == SEMICOLON 
            && temp_Line == gToken[gNum].lineNum ) gNum ++ ;

  printf( "nextToken->'%s'nextLine->'%d'  I'm unre : 11111\n", gToken[gNum].data, gToken[gNum].lineNum ) ;

  gValue->clear(); // 初始化

} // Unrecognized_error()

// =========================================================================================================

void ListAllVariables() {

  printf( "Into ListAllVariables without parameter!! data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;

  if ( gToken.size() - gNum > 1 ) gNum++;
  if ( gToken[gNum].token_type == SEMICOLON ) {
    if ( gToken.size() - gNum > 1 ) gNum++;

    // 做事
  } // if 

} // ListAllVariables()

// =========================================================================================================


void ListAllFunctions() {

  printf( "Into ListAllFunctions without parameter!! data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;

  ListAllFunctions_Sorted_and_print() ;

  if ( gToken.size() - gNum > 1 ) gNum++;
  if ( gToken[gNum].token_type == SEMICOLON ) {
    if ( gToken.size() - gNum > 1 ) gNum++;

    // 做事
  } // if 

} // ListAllFunctions()

// =========================================================================================================

void ListVariable( char parameter[500] ) {

  printf( "Into ListVariable with parameter!! data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;

  if ( gToken.size() - gNum > 1 ) gNum = gNum+2;

  if ( gToken[gNum].token_type == SEMICOLON ) {
    if ( gToken.size() - gNum > 1 ) gNum++;

    // 做事
  } // if 

} // ListVariable()

// =========================================================================================================

void ListFunction( char parameter[500] ) {

  printf( "Into ListFunction with parameter!! data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;

  printf( "> " ) ;

  int i = 0 ;
  while ( i < gFunction_Token.size() ) { // 先找到該funtion存的位置再依照規則印出來

    if ( strcmp( gFunction_Token[i].function_name, parameter ) == 0 ) { 
      Funtion_pretty_print( i ) ;
    } // if

    i ++ ;
  } // while

  if ( gToken.size() - gNum > 1 ) gNum = gNum+2;
  
  if ( gToken[gNum].token_type == SEMICOLON ) {
    if ( gToken.size() - gNum > 1 ) gNum++;
  } // if 

} // ListFunction()

// =========================================================================================================

void Done() { // 結束執行
  if ( gToken.size() > 0 ) gNum = gToken.size() ; 
  return ;
} // Done()


// =========================================================================================================


float Rounding( float value ) { // 為了處理4捨5入的浮點數

  float console = 0 ;
  float temp = 0 ;
  int a = 0 ; // 判斷小數點後第四位有沒有大於四

  temp = value * 10000 ;
  a = ( int ) temp  % 10 ;

  if ( a > 4 ) {
    temp = temp + 5 ;
    console = temp / 10000 ;
  } // if
  else console = temp / 10000 ;

  return console ;

} // Rounding()


// =========================================================================================================
// =========================================================================================================
// =========================================================================================================
// =========================================================================================================
// =========================================================================================================
// =========================================================================================================
// =========================================================================================================
// =========================================================================================================
// =========================================================================================================
// =========================================================================================================
// =========================================================================================================


void GetToken() { // GetToken 先全部照單全收，要印的時候用C語言把歸類成 float的token，用%3f的函數去印

  // 宣吿
  char text[100] = "" ; // 用來暫存token
  char ch[100] = "" ; // 用來讀檔
  char temp_ch[100] = "" ; // 輔助讀檔
  char temp = ' ' ;
  char for_unre[100] = "" ; // 給unrecognized用的
  int line = 1 ; // Proj2 Line好像是從1開始
  bool for_break = false ; // 給 PAL用的 break()
  bool not_quit = false ; // 如果quit是一個變數
  bool is_float = false ; // 是否為浮點數

  bool no_need_this_RP = false ; // 給ListVariable和ListFunction讀掉參數後的右括號用的

  gToken_info.have_defined = false ; // 這裡只是給個初始值 真正判斷會在parser那邊
  gToken_info.is_int = true ;
  gToken_info.variable_content = 0 ;
  gToken_info.error_lineNum = 0 ;
  gToken_info.is_funtion_defined = false ;
  

  // ********************************************************************
  if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
  temp = scanf( "%c", &ch[0] ) ; // 先讀第一個測試編號
  while ( temp != EOF && ch[0] != '\n' && 58 > ch[0] && ch[0] > 47 ) {
    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    strcat( text, ch ) ;
    temp = scanf( "%c", &ch[0] ) ; // 先讀第一個測試編號
  } // while

  if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch

  strcpy( gToken_info.testNum, text ) ;
  strcpy( text, "" ) ; // 清空text
  // ********************************************************************
  while ( temp != EOF ) { // 讀到結束

    while ( temp != EOF ) { 

      if ( ch[0] == '+' || ch[0] == '*' || ch[0] == '-' ) { // 處理加乘

        // ex. a:=-9; or ( -5 + 6 ) or 3 * -1 or 1 - -3 or 1 < -2 or 100 + ( - - 5 + 2 )
        // 有一種狀況還未解決,就是
        // ; quit  // 這行有錯 下一行應該是負號不是減號才對
        // -36 - 23 ;

        if ( gToken.size() == 0 || gToken[gToken.size() - 1].token_type == RS
             || gToken[gToken.size() - 1].token_type == LS
             || gToken[gToken.size() - 1].token_type == EQUAL
             || gToken[gToken.size() - 1].token_type == NOT_EQUAL
             || gToken[gToken.size() - 1].token_type == MULTI
             || gToken[gToken.size() - 1].token_type == SUB
             || gToken[gToken.size() - 1].token_type == PLUS
             || gToken[gToken.size() - 1].token_type == DIV
             || gToken[gToken.size() - 1].token_type == BIGGER
             || gToken[gToken.size() - 1].token_type == BIGGGER_EQ
             || gToken[gToken.size() - 1].token_type == SMALLER
             || gToken[gToken.size() - 1].token_type == SMALLER_EQ
             || gToken[gToken.size() - 1].token_type == S_LP
             || gToken[gToken.size() - 1].token_type == M_LP
             || gToken[gToken.size() - 1].token_type == L_LP
             || gToken[gToken.size() - 1].token_type == SEMICOLON
             || gToken[gToken.size() - 1].token_type == UNRECOGNIZED
             || gToken[gToken.size() - 1].token_type == UNEXPECTED ) {

          if ( ch[0] == '+' || ch[0] == '-' ) {
            strcpy( temp_ch, ch );

            strcat( text, ch );
            strcpy( gToken_info.data, text ); // 存取token資訊
            gToken_info.lineNum = line; // 看他屬於哪一行
            gToken_info.token_type = SIGN;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text

            temp = scanf( "%c", &ch[0] ) ; // 如果減號前面有其他運算元 代表是負號
            if ( ch[0] == '\n' ) line ++;
            while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) { // 讀到下一個合理字元出現
              temp = scanf( "%c", &ch[0] ) ;
              if ( ch[0] == '\n' ) line ++;
            } // while
          } // if
          else if ( ch[0] == '*' ) {
            strcat( text, ch );
            strcpy( gToken_info.data, text ); // 存取token資訊
            gToken_info.lineNum = line; // 看他屬於哪一行
            gToken_info.token_type = MULTI;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text

            temp = scanf( "%c", &ch[0] ) ; // 如果減號前面有其他運算元 代表是負號
            if ( ch[0] == '\n' ) line ++;
            while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) { // 讀到下一個合理字元出現
              temp = scanf( "%c", &ch[0] ) ;
              if ( ch[0] == '\n' ) line ++;
            } // while

          } // else if

        } // if
        else {
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch

          if ( ch[0] == '*' ) { // 儲存運算元
            strcat( text, ch ) ;
            strcpy( gToken_info.data, text ) ; // 存取token資訊
            gToken_info.lineNum = line ; // 看他屬於哪一行
            gToken_info.token_type = MULTI ;
            gToken.push_back( gToken_info ) ;
            strcpy( text, "" ) ; // 清空text
          } // if

          if ( ch[0] == '+' ) { // 儲存運算元
            strcat( text, ch ) ;
            strcpy( gToken_info.data, text ) ; // 存取token資訊
            gToken_info.lineNum = line ; // 看他屬於哪一行
            gToken_info.token_type = PLUS ;
            gToken.push_back( gToken_info ) ;
            strcpy( text, "" ) ; // 清空text
          } // if

          if ( ch[0] == '-' ) { // 儲存運算元
            strcat( text, ch ) ;
            strcpy( gToken_info.data, text ) ; // 存取token資訊
            gToken_info.lineNum = line ; // 看他屬於哪一行
            gToken_info.token_type = SUB ;
            gToken.push_back( gToken_info ) ;
            strcpy( text, "" ) ; // 清空text
          } // if

          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ; // 如果減號前面有其他運算元 代表是負號
          if ( ch[0] == '\n' ) line ++ ;
          while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) { // 讀到下一個合理字元出現
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ) ;
            if ( ch[0] == '\n' ) line ++ ;
          } // while

        } // else

        for_break = true ;

        if ( ch[0] == '\n' ) line ++ ;

      } // if


      // ********************************************************************
      if ( ch[0] == '!' ) { // 遇到除號 或是 註解

        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
        strcat( text, "!" ) ;
        strcpy( gToken_info.data, text ) ; // 存取token資訊
        gToken_info.lineNum = line ; // 看他屬於哪一行
        gToken_info.token_type = SIGN ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text

        if ( ch[0] == '\n' ) line ++ ;

      } // if

      // ********************************************************************
      if ( ch[0] == '/' ) { // 遇到除號 或是 註解

        bool need_line_plus = false ;
        if ( temp_ch[0] != ';' && temp_ch[0] != '}' ) need_line_plus = true ;

        temp = scanf( "%c", &ch[0] ) ;

        if ( ch[0] == '/' ) { // 是註解

          if ( need_line_plus == true ) line ++ ; 

          temp = scanf( "%c", &ch[0] ) ;
          while ( ch[0] != '\n' && temp != EOF ) { // 把註解讀掉
            temp = scanf( "%c", &ch[0] ) ;
          } // while

        } // if
        else {
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
          strcat( text, "/" ) ;
          strcpy( gToken_info.data, text ) ; // 存取token資訊
          gToken_info.lineNum = line ; // 看他屬於哪一行
          gToken_info.token_type = DIV ;
          gToken.push_back( gToken_info ) ;
          strcpy( text, "" ) ; // 清空text
        } // else

        if ( ch[0] == '\n' ) temp = scanf( "%c", &ch[0] ) ; // 請注意 此行不需要line ++ 是對的
        for_break = true ;

      } // if

      // ********************************************************************

      if ( ch[0] == ':' ) { // 遇到冒號的處理
        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
      
        strcpy( gToken_info.data, text ) ; // ex. a:5; 錯在冒號
        gToken_info.lineNum = line ;
        gToken_info.error_lineNum = line ;
        gToken_info.token_type = UNRECOGNIZED ;
        gToken.push_back( gToken_info ) ;

        strcpy( text, "" ) ;
        while ( temp != EOF && ch[0] != '\n' ) {
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // while


        if ( ch[0] == '\n' ) line ++;
        for_break = true ;


      } // if

      // ********************************************************************

      if ( ch[0] == '<' || ch[0] == '>' || ch[0] == '=' ) { // 遇到比較的運算元

        strcat( text, ch );
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
        if ( temp_ch[0] == '=' ) {
          strcpy( gToken_info.data, text ) ; // ex. a = 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = EQUAL;
          gToken.push_back( gToken_info );
        } // if
        else if ( temp_ch[0] == '<' && ch[0] == '>' ) { // <>這個就是不等於啦 老大說的
          strcat( text, ch );
          strcpy( gToken_info.data, text ) ; // ex. a <> 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = NOT_EQUAL;
          gToken.push_back( gToken_info );
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // else if
        else if ( temp_ch[0] == '<' && ch[0] == '=' ) {
          strcat( text, ch );
          strcpy( gToken_info.data, text ) ; // ex. a <= 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = SMALLER_EQ;
          gToken.push_back( gToken_info );
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // else if
        else if ( temp_ch[0] == '>' && ch[0] == '=' ) {
          strcat( text, ch );
          strcpy( gToken_info.data, text ) ; // ex. a >= 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = BIGGGER_EQ;
          gToken.push_back( gToken_info );
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // else if
        else if ( temp_ch[0] == '<' && ch[0] == '<' ) {
          strcat( text, ch );
          strcpy( gToken_info.data, text ) ; // ex. a <= 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = LS;
          gToken.push_back( gToken_info );
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // else if
        else if ( temp_ch[0] == '>' && ch[0] == '>' ) {
          strcat( text, ch );
          strcpy( gToken_info.data, text ) ; // ex. a >= 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = RS;
          gToken.push_back( gToken_info );
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // else if
        else if ( temp_ch[0] == '<' && ch[0] != '=' ) {
          strcpy( gToken_info.data, text ) ; // ex. a < 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = SMALLER;
          gToken.push_back( gToken_info );
          if ( ch[0] != ' ' && ch[0] != '-' && ch[0] != '+' ) strcpy( temp_ch, ch ) ; // 為了判斷sign的話不能存
        } // else if
        else if ( temp_ch[0] == '>' && ch[0] != '=' ) {
          strcpy( gToken_info.data, text ) ; // ex. a > 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = BIGGER;
          gToken.push_back( gToken_info );
          if ( ch[0] != ' ' && ch[0] != '-' && ch[0] != '+' ) strcpy( temp_ch, ch ) ; // 為了判斷sign的話不能存
        } // else if

        for_break = true ;
        strcpy( text, "" ) ;
        if ( ch[0] == '\n' ) line ++ ;

      } // if

      // ********************************************************************

      if ( ch[0] == '(' ) {
        strcpy( gToken_info.data, "(" ) ; // 存取token資訊
        gToken_info.lineNum = line ;
        gToken_info.token_type = S_LP ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ;

        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
        while ( ch[0] == '(' ) { // ex. (((a-2)+1)*2)-3) 遇到很多左括號的情況
          strcpy( gToken_info.data, "(" ) ; // 存取token資訊
          gToken_info.lineNum = line ;
          gToken_info.token_type = S_LP ;
          gToken.push_back( gToken_info ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // while

        for_break = true ;
        if ( ch[0] == '\n' ) line ++ ;

      } // if

      if ( ch[0] == ')' ) {

        if ( !no_need_this_RP ) {
          strcpy( gToken_info.data, ")" ) ; // 存取token資訊
          gToken_info.lineNum = line ;
          gToken_info.token_type = S_RP ;
          gToken.push_back( gToken_info ) ;
          strcpy( text, "" ) ; // 清空text
        } // if
        else {
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
          no_need_this_RP = false ;
        } // else 

        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
        while ( ch[0] == ')' ) { // ex. (((a-2)+1)*2)-3) 遇到很多左括號的情況
          strcpy( gToken_info.data, ")" ) ; // 存取token資訊
          gToken_info.lineNum = line ;
          gToken_info.token_type = S_RP ;
          gToken.push_back( gToken_info ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // while

        for_break = true ;
        if ( ch[0] == '\n' ) line ++ ;

      } // if

      // ********************************************************************

      if ( ch[0] == '[' ) {
        strcpy( gToken_info.data, "[" ) ; // 存取token資訊
        gToken_info.lineNum = line ;
        gToken_info.token_type = M_LP ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ;

        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
        while ( ch[0] == '[' ) { // ex. (((a-2)+1)*2)-3) 遇到很多左括號的情況
          strcpy( gToken_info.data, "[" ) ; // 存取token資訊
          gToken_info.lineNum = line ;
          gToken_info.token_type = M_LP ;
          gToken.push_back( gToken_info ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // while

        for_break = true ;
        if ( ch[0] == '\n' ) line ++ ;

      } // if

      if ( ch[0] == ']' ) {
        strcpy( gToken_info.data, "]" ) ; // 存取token資訊
        gToken_info.lineNum = line ;
        gToken_info.token_type = M_RP ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text

        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
        while ( ch[0] == ']' ) { // ex. (((a-2)+1)*2)-3) 遇到很多左括號的情況
          strcpy( gToken_info.data, "]" ) ; // 存取token資訊
          gToken_info.lineNum = line ;
          gToken_info.token_type = M_RP ;
          gToken.push_back( gToken_info ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // while

        for_break = true ;
        if ( ch[0] == '\n' ) line ++ ;

      } // if

      // ********************************************************************

      if ( ch[0] == '{' ) {
        strcpy( gToken_info.data, "{" ) ; // 存取token資訊
        gToken_info.lineNum = line ;
        gToken_info.token_type = L_LP ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ;

        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
        while ( ch[0] == '{' ) { // ex. (((a-2)+1)*2)-3) 遇到很多左括號的情況
          strcpy( gToken_info.data, "{" ) ; // 存取token資訊
          gToken_info.lineNum = line ;
          gToken_info.token_type = L_LP ;
          gToken.push_back( gToken_info ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // while

        for_break = true ;
        if ( ch[0] == '\n' ) line ++ ;

      } // if

      if ( ch[0] == '}' ) {
        strcpy( gToken_info.data, "}" ) ; // 存取token資訊
        gToken_info.lineNum = line ;
        gToken_info.token_type = L_RP ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text

        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
        while ( ch[0] == '}' ) { // ex. (((a-2)+1)*2)-3) 遇到很多左括號的情況
          strcpy( gToken_info.data, "}" ) ; // 存取token資訊
          gToken_info.lineNum = line ;
          gToken_info.token_type = L_RP ;
          gToken.push_back( gToken_info ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // while

        for_break = true ;
        line = 1 ; // line重置 分號以外只有右大括號需要重置 

      } // if

      // ********************************************************************

      if ( ch[0] == ';' ) { // 分號的處理
        strcpy( gToken_info.data, ";" ) ; // 存取token資訊
        gToken_info.lineNum = line ;
        gToken_info.token_type = SEMICOLON ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text
        for_break = true ;

        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;

        // if ( ch[0] == '\n' ) temp = scanf( "%c", &ch[0] ) ;
        line = 1 ; // line重置
        for_break = true ;

      } // if

      // ********************************************************************

      if ( 58 > ch[0] && ch[0] > 47 && !for_break ) { // 數字開頭的處理

        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;

        // 如果後面還是數字就繼續合併
        while ( temp != EOF && ch[0] != '\n' && 47 < ch[0] && ch[0] < 58 ) {

          strcat( text, ch );
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;

        } // while

        if ( ch[0] == '.' ) { // 浮點數的處理
          strcat( text, ch ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
          is_float = true ;
          while ( ch[0] != '\n' && temp != EOF && ch[0] != ' ' && ch[0] > 47 && ch[0] < 58  ) {
            strcat( text, ch ) ;
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ) ;
          } // while
        } // if

        strcpy( gToken_info.data, text ) ; // 存取token資訊
        gToken_info.lineNum = line ;
        if ( !is_float ) gToken_info.token_type = CONSTANT ; // int
        else gToken_info.token_type = CONSTANT ; // float
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text
        for_break = true ;
        if ( ch[0] == '\n' ) line ++ ;

      } // if

      // ********************************************************************

      if ( ch[0] == '.' && !for_break ) { // 點開頭的處理

        strcpy( text, "" ); // 清空text
        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;

        // 如果後面還是數字就繼續合併
        if ( 47 < ch[0] && ch[0] < 58 ) {
          while ( ch[0] != '\n' && temp != EOF && ch[0] != ' ' && ch[0] > 47 && ch[0] < 58 ) {
            strcat( text, ch );
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ) ;
          } // while

          strcpy( gToken_info.data, text ); // 存取token資訊
          gToken_info.lineNum = line;
          gToken_info.token_type = CONSTANT; // Float
          gToken.push_back( gToken_info );
          strcpy( text, "" ); // 清空text
        } // if
        else {
          strcpy( gToken_info.data, text ); // 存取token資訊
          gToken_info.lineNum = line;
          gToken_info.error_lineNum = line ;
          gToken_info.token_type = UNRECOGNIZED;
          gToken.push_back( gToken_info );
          strcpy( text, "" ); // 清空text
          while ( temp != EOF && ch[0] != '\n' ) {
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ) ;
          } // while

        } // else

        if ( ch[0] == '\n' ) line ++;

        for_break = true ;

      } // if

      // ********************************************************************


      if ( !for_break && ch[0] == '"' ) { // 處理字串

        if ( gToken[gToken.size() - 1].token_type == LISTFUNCTION 
             || gToken[gToken.size() - 1].token_type == LISTVARIABLE ) { // 參數不用引號

          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch

          temp = scanf( "%c", &ch[0] ) ;
          while ( temp != EOF && ch[0] != '"' ) {
            strcat( text, ch ) ;
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ) ;
          } // while

          strcpy( gToken_info.data, text );
          gToken_info.lineNum = line;
          gToken_info.token_type = CONSTANT ; 
          gToken.push_back( gToken_info );
          strcpy( text, "" ); // 清空text
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
          if ( ch[0] == '\n' ) line ++;

        } // if
        else {
          strcat( text, ch ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch

          temp = scanf( "%c", &ch[0] ) ;
          while ( temp != EOF && ch[0] != '"' ) {
            strcat( text, ch ) ;
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ) ;
          } // while

          strcat( text, ch ) ;
          strcpy( gToken_info.data, text );
          gToken_info.lineNum = line;
          gToken_info.token_type = CONSTANT ; 
          gToken.push_back( gToken_info );
          strcpy( text, "" ); // 清空text
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
          if ( ch[0] == '\n' ) line ++;
        } // else 

      } // if 


      // ********************************************************************


      if ( !for_break && ch[0] == ':' ) { // 處理冒號

        strcat( text, ch ) ;
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = line;
        gToken_info.token_type = COLON ; 
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
        if ( ch[0] == '\n' ) line ++;

      } // if 

      // ********************************************************************

      // 這邊是在處理 字母 或 特殊符號開頭的 IDENT
      if ( !for_break && temp != EOF && ch[0] != 91 && ch[0] != 92 && ch[0] != 93
           && ch[0] != 94 && ch[0] != 95 && ch[0] != 96 && 64 < ch[0] && ch[0] < 123 ) {

        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        strcpy( for_unre, temp_ch ) ;



        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;


        while ( temp != EOF && 47 < ch[0] && ch[0] < 123 && ch[0] != 58 
                && ch[0] != 59 && ch[0] != 60 && ch[0] != 61
                && ch[0] != 91 && ch[0] != 92 && ch[0] != 93 && ch[0] != 94 && ch[0] != 96 ) {
          strcat( text, ch ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // while


        if ( ch[0] == ' ' || ch[0] == '+' || ch[0] == '-' || ch[0] == '*' || ch[0] == '/'
             || ch[0] == '(' || ch[0] == ':' || ch[0] != '\n' || ch[0] != '\t' || ch[0] == '%'
             || ch[0] == '!' || ch[0] == '|' || ch[0] == '&' || ch[0] == '^' || ch[0] == ';'
             || ch[0] == '>' || ch[0] == '<' || ch[0] == '=' || ch[0] == ')' || temp == EOF ) {
          // 是個正常的ident才要

          if ( strcmp( text, "int" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = INT_TYPE;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // if
          else if ( strcmp( text, "float" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = FLOAT_TYPE;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "char" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = CHAR_TYPE;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "bool" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = BOOL_TYPE;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "string" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = STRING_TYPE;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "void" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = VOID_TYPE;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "if" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = IF;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "else" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = ELSE;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "while" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = WHILE;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "do" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = DO;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "return" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = RETURN;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "cin" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = CONSTANT;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "cout" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = CONSTANT;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "true" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = CONSTANT;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "false" ) == 0 ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = CONSTANT; 
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if
          else if ( strcmp( text, "Done" ) == 0 ) {

            while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
              if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
              temp = scanf( "%c", &ch[0] ) ;
            } // while
  
            if ( ch[0] == '(' ) {
              strcat( text, ch ) ;
              if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
              temp = scanf( "%c", &ch[0] ) ;
              while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
                if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
                temp = scanf( "%c", &ch[0] ) ;
              } // while

              if ( ch[0] == ')' ) {
                strcat( text, ch ) ;
                strcpy( gToken_info.data, text );
                gToken_info.lineNum = line;
                gToken_info.token_type = DONE;
                gToken.push_back( gToken_info );
                strcpy( text, "" ); // 清空text
                if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
                temp = scanf( "%c", &ch[0] ) ;
              } // if

            } // if
            else {
              strcpy( gToken_info.data, text );
              gToken_info.lineNum = line;
              gToken_info.token_type = IDENT;
              gToken.push_back( gToken_info );
              strcpy( text, "" ); // 清空text
            } // else
          
          } // else if
          else if ( strcmp( text, "ListAllVariables" ) == 0 ) {
  
            while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
              if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
              temp = scanf( "%c", &ch[0] ) ;
            } // while
  
            if ( ch[0] == '(' ) {
              strcat( text, ch ) ;
              if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
              temp = scanf( "%c", &ch[0] ) ;
              while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
                if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
                temp = scanf( "%c", &ch[0] ) ;
              } // while

              if ( ch[0] == ')' ) {
                strcat( text, ch ) ;
                strcpy( gToken_info.data, text );
                gToken_info.lineNum = line;
                gToken_info.token_type = LISTALLVARIABLES;
                gToken.push_back( gToken_info );
                strcpy( text, "" ); // 清空text
                if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
                temp = scanf( "%c", &ch[0] ) ;
              } // if
            } // if
            else {
              strcpy( gToken_info.data, text );
              gToken_info.lineNum = line;
              gToken_info.token_type = IDENT;
              gToken.push_back( gToken_info );
              strcpy( text, "" ); // 清空text
            } // else
          
          } // else if
          else if ( strcmp( text, "ListAllFunctions" ) == 0 ) {
  
            while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
              if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
              temp = scanf( "%c", &ch[0] ) ;
            } // while
  
            if ( ch[0] == '(' ) {
              strcat( text, ch ) ;
              if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
              temp = scanf( "%c", &ch[0] ) ;
              while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
                if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
                temp = scanf( "%c", &ch[0] ) ;
              } // while

              if ( ch[0] == ')' ) {
                strcat( text, ch ) ;
                strcpy( gToken_info.data, text );
                gToken_info.lineNum = line;
                gToken_info.token_type = LISTALLFUCTIONS;
                gToken.push_back( gToken_info );
                strcpy( text, "" ); // 清空text
                if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
                temp = scanf( "%c", &ch[0] ) ;
              } // if
            } // if
            else {
              strcpy( gToken_info.data, text );
              gToken_info.lineNum = line;
              gToken_info.token_type = IDENT;
              gToken.push_back( gToken_info );
              strcpy( text, "" ); // 清空text
            } // else
          
          } // else if
          else if ( strcmp( text, "ListVariable" ) == 0 ) { // 這個function裡會有參數
            no_need_this_RP = true ;
  
            if ( ch[0] == '(' ) { // 把左括號讀掉 只存函式名稱 然後下一個找參數名稱             
              strcpy( gToken_info.data, text );
              gToken_info.lineNum = line;
              gToken_info.token_type = LISTVARIABLE;
              gToken.push_back( gToken_info );
              strcpy( text, "" ); // 清空text
              if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
              temp = scanf( "%c", &ch[0] ) ;
            } // if
            else {
              strcpy( gToken_info.data, text );
              gToken_info.lineNum = line;
              gToken_info.token_type = IDENT;
              gToken.push_back( gToken_info );
              strcpy( text, "" ); // 清空text
            } // else
          
          } // else if
          else if ( strcmp( text, "ListFunction" ) == 0 ) { // 這個function裡會有參數
            no_need_this_RP = true ;
  
            if ( ch[0] == '(' ) { // 把左括號讀掉 只存函式名稱 然後下一個找參數名稱             
              strcpy( gToken_info.data, text );
              gToken_info.lineNum = line;
              gToken_info.token_type = LISTFUNCTION;
              gToken.push_back( gToken_info );
              strcpy( text, "" ); // 清空text
              if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
              temp = scanf( "%c", &ch[0] ) ;
            } // if
            else {
              strcpy( gToken_info.data, text );
              gToken_info.lineNum = line;
              gToken_info.token_type = IDENT;
              gToken.push_back( gToken_info );
              strcpy( text, "" ); // 清空text
            } // else
          
          } // else if
          else {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = IDENT;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // else if

        } // if

        if ( ch[0] == '\n' ) line ++;

      } // if

      // ********************************************************************

      if ( ch[0] == 35 || ch[0] == 36 || ch[0] == 64 || ch[0] == 92  
           || ch[0] == 94 || ch[0] == 95 || ch[0] == 96 || ch[0] == 126 || ch[0] == 127 ) {
        // 不是任何東西 ex. {A

        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;

        strcpy( gToken_info.data, text ) ;
        gToken_info.lineNum = line ;
        gToken_info.error_lineNum = line ;
        gToken_info.token_type = UNRECOGNIZED ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text

        while ( temp != EOF && ch[0] != '\n' ) {
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // while


        if ( ch[0] == '\n' ) line ++;
        for_break = true ;

      } // if

      // ********************************************************************
    

      if ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) { // 把空白跟換行讀掉

        temp = scanf( "%c", &ch[0] ) ;
        if ( ch[0] == '\n' ) line ++ ;
        while ( temp != EOF && ch[0] == ' ' && ch[0] == '\n' ) {
          if ( ch[0] == '\n' ) line ++ ;
          temp = scanf( "%c", &ch[0] ) ;
        } // while

      } // if


      for_break = false ; // 跑完一次就可以解除for_break狀態
      not_quit = false ;
      is_float = false ;

    } // while

    
    int k = 0 ;
    while ( gToken.size() != 0 && k < gToken.size() ) {
      cout << " " << gToken[k].data << " " << gToken[k].token_type
           << " " << gToken[k].lineNum << "\n" ;
      k ++ ;
    } // while

    gNum = 0 ;
    return ;

  } // while

} // GetToken()



int main() {

  printf( "Our-C running ...\n" ) ;
  GetToken();

  if ( 0 < gToken.size() && gToken.size() <= 2 ) {
    printf( "Ready to go into Userinput1 data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
    User_input() ;
  } // if 
  
  while ( gNum < gToken.size() - 1 ) {
    printf( "Ready to go into Userinput2 data: '%s' line: '%d'\n", gToken[gNum].data, gToken[gNum].lineNum ) ;
    User_input() ;
  } // while
  

  printf( "> Our-C exited ..." ) ;

} // main()
