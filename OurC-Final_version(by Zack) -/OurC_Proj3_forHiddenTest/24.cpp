# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <vector>
# include <iostream>
# include <string.h>
# include <math.h>

using namespace std ;


typedef enum {
  INT_TYPE = 3,
  FLOAT_TYPE = 4,
  CHAR_TYPE = 5,
  BOOL_TYPE = 6,
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
  REMAINDER = 27,
  HAT = 28,  // ^
  ONE_EQUAL = 1,
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
  LISTFUNCTION = 60,

  // ===============For Proj3==================
  // for 計算存值時 需要知道變數的型別
  INT = 61,
  FLOAT = 62,
  CHAR = 63,
  STRING = 64,
  BOOL = 65,
  NOTHING = 66,
  CIN = 67,
  COUT = 68,
  TRUE = 69,
  FALSE = 70,
  VOID = 71,
  NEGATIVE = 72,
  POSITIVE = 73
  // IDENT詳細會是甚麼型別取決於他前面是啥定義

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
  bool vari_in_func_temp_defi ;
  Token_enum detail_type ; // for 計算存值時 需要知道變數的詳細型別
  // detail_type僅需分辨constant, ident
} ;

struct Function_Token {
  int start_num ; // 紀錄該function從哪裡開始
  int end_num ; // 紀錄該function從哪裡結束
  char function_name[500] ;// 儲存function名稱
} ;

struct ALL_variable_name_and_value { // 用於儲存所有的變數名稱與內容
  char name[500] ; // variable_name
  Token_enum detail_type ;
  float constant_value ; // 如果變數是int or float就看這個
  bool bool_value ; // 如果變數是bool就看這個
  char string_value[500] ; // 如果變數是string就看這個
} ;

struct Cout_Token {
  bool is_ident ; // 是不是ident 不是就是以下幾種
  bool is_string_or_char ;
  bool is_int ;
  bool is_float ;
  bool is_bool ;
  float constant_data ; 
  bool bool_value ;
  char ident_name[500] ; // 要印出來的ident名稱
  char string_or_char_data[500] ;
} ;

struct PPMM_after_ID { // 紀錄那些ident計算完後面需要做PP or MM
  bool is_PP ; // 否則就是MM
  char name[500] ;// 儲存該變數名稱
} ;


bool gGet_error = false ;
// Token
bool GetToken( bool get_error ) ;

// Parser
bool User_input() ;
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
vector<float> gValue ;
vector<bool> gBool_Ans ; // 存取布林運算 的結果
char gString_value[500] ; // 存取字串運算 的結果
char gTemp_String_value[500] ;
vector<Function_Token> gFunction_Token ;
vector<Cout_Token> gCout_Token ;
vector<ALL_variable_name_and_value> gALL_vari_Token ;
vector<PPMM_after_ID> gPPMM_after_ID ;

float gTemp_value = 0.0 ;
Token gToken_info ;
Function_Token gFunction_Token_info ;
Cout_Token gCout_Token_info ;
ALL_variable_name_and_value gALL_vari_Token_info ;
PPMM_after_ID gPPMM_after_ID_info ;

int gNum = 0 ;
bool gHave_error = false ; // 有錯誤所以不要印出計算結果
bool gIs_Definition = false ; // 用於判斷是不是走definition這條路，ident需不需要先被定義
bool gIs_function_Definition = false ; // 用於更深層的判斷，不只是definition是function的定義

typedef char CharArray[500];
CharArray gDefined_function_Name[500] ;

char gTemp_char[10] = "" ; // 用來存取暫時讀進來還沒用的的字元 ex; a+5 的+ 用來判斷 a 是一個獨立的token
int gLine = 1 ;
vector<int> * gTemp_variable_loctation = new vector<int>() ; // 用來存取還沒跑完但是準備要被定義的變數位置
bool gAlready_Get = false ; // 用在需要peekToken時沒有用到卻已經Get的情況不需要再Get一次了的判斷
bool gLast_read_char_is_change_line = false ; 
// 這個是用來判斷該行最後一個token error時484已經讀掉換行字元了

bool gIs_cout_operation = false ; // 遇到cout代表要輸出結果
bool gIs_float_operation = false ; // 代表要印出float的結果還是int的結果
bool gAfter_LS = false ; // LS '<<' 之後如果接了'('代表下一個出現的ident或constant要印  
bool gIdent_operation = false ; // LS '<<' 之後如果直接接了ident代表接下來是一個算式 算完的結果才要印 
bool gIn_expresstion = false ; // 用於cout << ( expression ) ; 的內容出現 '>>' 也不會unex
bool gIs_shifter_constant = false ; // 如果出現 a1 << 2 那後面這個2代表shift的程度 不該被丟入gValue中計算
bool gIs_Bool_operation = false ; // 此為布林運算
bool gIs_string_operation = false ; // 此為字串運算 
vector<int> gArray_size ; // 這個變數array的size是多少 全部存入ALL variable
bool gHave_assignment = false ; 
// 特殊功能 檢查是不是已經assignment了卻還沒有算完 (a=1)+2 ->結果要是3而不是1
bool gHave_negative = false ; // 特殊功能 for 1--(36) = 37 而不是 -35
bool gHave_E_mark = false ; // 特殊功能 for b || !(b1 && b2) 


// 額外的function
float Rounding( float value ) ;
bool Definiton_and_New_Definition( int temp_num ) ;
void ListAllVariables_Sorted_and_print() ;
void ListAllFunctions_Sorted_and_print() ;
void Sort( int n ) ;
void Funtion_pretty_print( int i ) ;
void Clear_defi_variable_infuntion() ;
bool Variable_infuntion_have_defined() ;
void Print_every_variable() ;
void Determine_variable_detail_type() ;
void Assignment_calculator( int ident_location, int assignment_location ) ;
void Temp_data_prepare_to_cout( int  location, bool ident, bool string_or_char, 
                                bool is_int, bool is_float, bool is_bool, float constant, 
                                bool bool_value, char string_or_char_data[500] ) ;
void Store_ALL_variable_name_and_value( char ident_name[500], int location, bool is_already_defined ) ;
int Find_variable_location_in_ALL_variables( char ident[500] ) ;
bool Boolean_operator( int num ) ;


void Funtion_pretty_print( int i ) { 

  int start_num = gFunction_Token[i].start_num ;
  int end_num = gFunction_Token[i].end_num ;

  int num_of_L_RP = 0 ;

  while ( start_num <= end_num ) {

    if ( strcmp( gToken[start_num].data, ";" ) == 0 || strcmp( gToken[start_num].data, "{" ) == 0 ) {

      printf( "%s\n", gToken[start_num].data ) ; // 印出該token

      if ( strcmp( gToken[start_num].data, "{" ) == 0 ) num_of_L_RP ++ ;
      if ( strcmp( gToken[start_num+1].data, "}" ) == 0 ) num_of_L_RP -- ;

      int i = 0 ;
      while ( i < num_of_L_RP ) {
        printf( "  " ) ;
        i ++ ;
      } // while

    } // if
    else if ( strcmp( gToken[start_num].data, "}" ) == 0 ) {

      printf( "%s\n", gToken[start_num].data ) ; // 印出該token

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

      if ( start_num <= end_num - 1  && gToken[start_num].token_type != IF 
           && gToken[start_num].token_type != WHILE && gToken[start_num+1].token_type == S_LP ) {
        printf( "%s", gToken[start_num].data ) ; // 印出該token
      } // if
      else if ( start_num <= end_num - 1  && gToken[start_num].token_type != IF 
                && gToken[start_num].token_type != WHILE && gToken[start_num+1].token_type == M_LP ) {
        printf( "%s", gToken[start_num].data ) ; // 印出該token
      } // else if
      else if ( start_num <= end_num - 1 && gToken[start_num+1].token_type == PP ) { // 'j'++
        printf( "%s", gToken[start_num].data ) ; // 印出該token
      } // else if
      else if ( start_num <= end_num - 1 && gToken[start_num+1].token_type == MM ) { // 'j'--
        printf( "%s", gToken[start_num].data ) ; // 印出該token
      } // else if
      else if ( start_num <= end_num - 1 && gToken[start_num+1].token_type == COMMA ) { // int x[30],
        printf( "%s", gToken[start_num].data ) ; // 印出該token
      } // else if
      else printf( "%s ", gToken[start_num].data ) ; // 印出該token
      
    } // else 

    start_num ++ ;
  } // while

  printf( "Statement executed ...\n" ) ;

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

  return ;
} // Sort()

void ListAllVariables_Sorted_and_print() { // 因應ListAllVariables需要排序處理

  int find_id = 0 ;
  bool have_find = false ;
  int n = 0 ;
  while ( find_id < gNum ) { // 找找看有沒有這個變數
    // 在proj2 中重複定義同個變數 只有可能是變換了型別
    if ( gToken[find_id].is_funtion_defined == false && gToken[find_id].have_defined == true ) {
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
      printf( "%s\n", gDefined_function_Name[i] ) ;
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
    if ( gToken[find_id].is_funtion_defined == true && gToken[find_id].have_defined == true ) {
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

bool Definiton_and_New_Definition( int i ) {

  gToken[gTemp_variable_loctation->at( i )].have_defined = true ; // 如果文法沒有錯這個IDENT就會被定義
  // 定義funtion名稱
  if ( gIs_function_Definition ) gToken[gTemp_variable_loctation->at( i )].is_funtion_defined = true ;
  gIs_function_Definition = false ;
  
  int find_id = 0 ;
  bool have_find = false ;
  while ( find_id < gTemp_variable_loctation->at( i ) ) { // 找找看有沒有這個變數
    // 在proj2 中重複定義同個變數 只有可能是變換了型別
    if ( strcmp( gToken[find_id].data, gToken[gTemp_variable_loctation->at( i )].data ) == 0 
         && gToken[find_id].have_defined == true ) {
      have_find = true ; // 有找到代表此變數為新定義
    } // if

    find_id ++ ;
  } // while

  if ( !have_find ) return true ;
  else return false ;
  
} // Definiton_and_New_Definition()

void Clear_defi_variable_infuntion() { // funtion定義跑完了就初始化這些變數

  int num = 0 ;
  while ( num < gToken.size() ) {
    if ( gToken[num].vari_in_func_temp_defi == true ) {
      gToken[num].vari_in_func_temp_defi = false ;
      gToken[num].have_defined = false ;
      gToken[num].is_funtion_defined = false ;
    } // if

    num ++ ;
  } // while

  return ;

} // Clear_defi_variable_infuntion()

bool Variable_infuntion_have_defined() { // 找找看funtion內這個變數有沒有被定義過
  
  // 兩個方向要找 1.funtion內被定義過 2.他已經被定義過了是個全域變數
  int find_id = 0;
  bool found_it = false;
  while ( find_id < gNum && !found_it ) { // 找找看有沒有這個變數

    if ( strcmp( gToken[find_id].data, gToken[gNum].data ) == 0
         && gToken[find_id].vari_in_func_temp_defi == true ) {
      found_it = true;
    } // if

    if ( strcmp( gToken[find_id].data, gToken[gNum].data ) == 0
         && gToken[find_id].is_funtion_defined == true ) {
      found_it = true;
    } // if

    if ( strcmp( gToken[find_id].data, gToken[gNum].data ) == 0
         && gToken[find_id].have_defined == true ) {
      found_it = true;
    } // if

    // 找到了就把值給取出來
    if ( found_it ) gValue.push_back( gToken[find_id].variable_content );

    find_id ++;

  } // while

  if ( !gHave_error && !found_it ) {
    if ( gToken[gNum].lineNum != 0 ) {
      printf( "> Line %d : undefined identifier : '%s'\n", gToken[gNum].lineNum, gToken[gNum].data ) ;
    } // if
    else printf( "> Line %d : undefined identifier : '%s'\n", 1, gToken[gNum].data ) ;

    gHave_error = true;

    gGet_error = true ;

    GetToken( gGet_error ) ;

    gIs_Definition = false ;
    gIs_cout_operation = false ;
    gAfter_LS = false ;
    gIs_float_operation = false ;
    gIs_function_Definition = false ;
    gGet_error = false ;
    gValue.clear(); // 初始化
    gBool_Ans.clear(); // 初始化
    strcpy( gString_value, "" ) ;
    gTemp_variable_loctation->clear(); // 初始化
    gLine = 1 ;
    bool gAlready_Get = false ;
    Clear_defi_variable_infuntion();
    
    if ( !GetToken( gGet_error ) ) return true ; // 這裡回傳true才是錯 
    else gNum ++ ;

    return true ;

  } // if

  return false ;
  
} // Variable_infuntion_have_defined()

// For P3 v==================================================================================================

void Determine_variable_detail_type() { // 當ident定義時判斷他是屬於哪種型別

  int num = gNum - 1 ;

  while ( gToken[num].token_type != INT_TYPE && gToken[num].token_type != FLOAT_TYPE &&
          gToken[num].token_type != CHAR_TYPE && gToken[num].token_type != STRING_TYPE &&
          gToken[num].token_type != BOOL_TYPE && gToken[num].token_type != VOID_TYPE ) {
    num -- ;
    if ( num < -1 ) {
      printf( "This variable without input type definition\n" ) ;
      return ;
    } // if
  } // while

  if ( gToken[num].token_type == INT_TYPE ) {
    gToken[gNum].detail_type = INT ;
  } // if
  else if ( gToken[num].token_type == FLOAT_TYPE ) {
    gToken[gNum].detail_type = FLOAT ;
  } // else if
  else if ( gToken[num].token_type == CHAR_TYPE ) {
    gToken[gNum].detail_type = CHAR ;
  } // else if
  else if ( gToken[num].token_type == STRING_TYPE ) {
    gToken[gNum].detail_type = STRING ;
  } // else if
  else if ( gToken[num].token_type == BOOL_TYPE ) {
    gToken[gNum].detail_type = BOOL ;
  } // else if
  else if ( gToken[num].token_type == VOID_TYPE ) {
    gToken[gNum].detail_type = VOID ;
  } // else if

  return ;

} // Determine_variable_detail_type()

void Assignment_calculator( int ident_location, int assignment_location ) { // assignment符號的計算


  // ===================================================================================================
  if ( gPPMM_after_ID.size() > 0 ) {

    int start = 0 ;
    int find = -1 ;

    while ( start < gPPMM_after_ID.size() ) {
      find = Find_variable_location_in_ALL_variables( gPPMM_after_ID[start].name ) ;
      if ( find != -1 && gPPMM_after_ID[start].is_PP == true ) {
        gALL_vari_Token[find].constant_value = gALL_vari_Token[find].constant_value + 1 ;
      } // if
      else if ( find != -1 && gPPMM_after_ID[start].is_PP == false ) {
        gALL_vari_Token[find].constant_value = gALL_vari_Token[find].constant_value - 1 ;
      } // else if

      start ++ ;

    } // while

    gPPMM_after_ID.clear() ;
  } // if
  // ===================================================================================================

  // 先找出該變數的存取位置
  int find_definition = Find_variable_location_in_ALL_variables( gToken[ident_location].data ) ;

  if ( find_definition != -1 ) {

    // 首先判斷該變數的型別 如果是int的話
    if ( gALL_vari_Token[find_definition].detail_type == INT ) {
      // 根據該變數的儲存位置改變其值內容
      if ( gToken[assignment_location].token_type == ONE_EQUAL ) { // '='
        if ( gValue.size() > 0 ) {
          int a = gValue[gValue.size()-1] ;
          gValue.pop_back() ;
          gValue.pop_back() ;
          gValue.push_back( a );
          gALL_vari_Token[find_definition].constant_value = gValue[gValue.size()-1] ;
        } // if
      } // if
      else if ( gToken[assignment_location].token_type == PE ) { // +=
        gALL_vari_Token[find_definition].constant_value = 
        gALL_vari_Token[find_definition].constant_value + gValue[gValue.size()-1] ;

        if ( gValue.size() > 0 ) gValue.pop_back() ;
        if ( gValue.size() > 0 ) gValue.pop_back() ;
        gValue.push_back( gALL_vari_Token[find_definition].constant_value ) ;
      } // else if 
      else if ( gToken[assignment_location].token_type == ME ) { // -=
        gALL_vari_Token[find_definition].constant_value = 
        gALL_vari_Token[find_definition].constant_value - gValue[gValue.size()-1] ;

        if ( gValue.size() > 0 ) gValue.pop_back() ;
        if ( gValue.size() > 0 ) gValue.pop_back() ;
        gValue.push_back( gALL_vari_Token[find_definition].constant_value ) ;
      } // else if 
      else if ( gToken[assignment_location].token_type == TE ) { // *=
        gALL_vari_Token[find_definition].constant_value = 
        gALL_vari_Token[find_definition].constant_value * gValue[gValue.size()-1] ;

        if ( gValue.size() > 0 ) gValue.pop_back() ;
        if ( gValue.size() > 0 ) gValue.pop_back() ;
        gValue.push_back( gALL_vari_Token[find_definition].constant_value ) ;
      } // else if 
      else if ( gToken[assignment_location].token_type == DE ) { // /=
        gALL_vari_Token[find_definition].constant_value = 
        gALL_vari_Token[find_definition].constant_value / gValue[gValue.size()-1] ;

        if ( gValue.size() > 0 ) gValue.pop_back() ;
        if ( gValue.size() > 0 ) gValue.pop_back() ;
        gValue.push_back( gALL_vari_Token[find_definition].constant_value ) ;
      } // else if 
      else if ( gToken[assignment_location].token_type == RE ) { // %=
        int value1 = gALL_vari_Token[find_definition].constant_value ; 
        int value2 = gValue[gValue.size()-1] ;
        gALL_vari_Token[find_definition].constant_value = value1 % value2 ;

        if ( gValue.size() > 0 ) gValue.pop_back() ;
        if ( gValue.size() > 0 ) gValue.pop_back() ;
        gValue.push_back( gALL_vari_Token[find_definition].constant_value ) ;
      } // else if 

      // gValue[0] = gValue[gValue.size()-1] ;

    } // if
    else if ( gALL_vari_Token[find_definition].detail_type == FLOAT ) {
      // 根據該變數的儲存位置改變其值內容
      if ( gToken[assignment_location].token_type == ONE_EQUAL ) { // '='
        gTemp_value = gValue[gValue.size()-1] ;
        gValue.pop_back() ;
        gValue.pop_back() ;
        gValue.push_back( gTemp_value );
        gALL_vari_Token[find_definition].constant_value = gValue[0] ;
      } // if
      else if ( gToken[assignment_location].token_type == PE ) { // +=
        gALL_vari_Token[find_definition].constant_value = 
        gALL_vari_Token[find_definition].constant_value + gValue[0] ;
      } // else if 
      else if ( gToken[assignment_location].token_type == ME ) { // -=
        gALL_vari_Token[find_definition].constant_value = 
        gALL_vari_Token[find_definition].constant_value - gValue[0] ;
      } // else if 
      else if ( gToken[assignment_location].token_type == TE ) { // *=
        gALL_vari_Token[find_definition].constant_value = 
        gALL_vari_Token[find_definition].constant_value * gValue[0] ;
      } // else if 
      else if ( gToken[assignment_location].token_type == DE ) { // /=
        gALL_vari_Token[find_definition].constant_value = 
        gALL_vari_Token[find_definition].constant_value / gValue[0] ;
      } // else if 
      else if ( gToken[assignment_location].token_type == RE ) { // %=
        int value1 = gALL_vari_Token[find_definition].constant_value ; 
        int value2 = gValue[0] ;
        gALL_vari_Token[find_definition].constant_value = value1 % value2 ;
      } // else if 

      gValue[0] = gValue[gValue.size()-1] ;

    } // else if
    else if ( gALL_vari_Token[find_definition].detail_type == BOOL ) {

      if ( gIs_Bool_operation ) {
        gIs_Bool_operation = false ;
        gALL_vari_Token[find_definition].bool_value = gBool_Ans[gBool_Ans.size() - 1] ;
        gBool_Ans.clear() ;
      } // if
      else {
        if ( gToken[assignment_location+1].detail_type == TRUE ) { // '='
          gALL_vari_Token[find_definition].bool_value = true ;
        } // if
        else if ( gToken[assignment_location+1].detail_type == FALSE ) { // '='
          gALL_vari_Token[find_definition].bool_value = false ;
        } // if
      } // else

    } // else if
    else if ( gALL_vari_Token[find_definition].detail_type == STRING ) {

      if ( gToken[assignment_location].token_type == ONE_EQUAL ) { // '='
        strcpy( gALL_vari_Token[find_definition].string_value, gString_value ) ;
      } // if
      else if ( gToken[assignment_location].token_type == PE ) { // +=

        char temp[500] = "" ;
        strcat( temp, gALL_vari_Token[find_definition].string_value ) ;
        strcat( temp, gString_value ) ;
        strcpy( gString_value, temp ) ;
        strcpy( gALL_vari_Token[find_definition].string_value, temp ) ;
      } // else if 

    } // else if
    else if ( gALL_vari_Token[find_definition].detail_type == CHAR ) {

      if ( gToken[assignment_location].token_type == ONE_EQUAL ) { // '='
        strcpy( gALL_vari_Token[find_definition].string_value, gString_value ) ;
      } // if

    } // else if

  } // if

  
  // 這裡不能做初始化 因為有可能還要繼續賦值給其他變數
  // gValue.clear() ;
  gBool_Ans.clear(); // 初始化
  // strcpy( gString_value, "" ) ;

  return ;

} // Assignment_calculator()

void Temp_data_prepare_to_cout( int  location, bool ident, bool string_or_char, 
                                bool is_int, bool is_float, bool is_bool, float constant, 
                                bool bool_value, char string_or_char_data[500] ) { 
  // 儲存 '<<' 與 '<<'中間要印的內容
  // 中間會出現幾種情況
  // 情況1 : ident 需判斷其型別 再 印出相關結果
  // 情況2 : 如果是數字就會用 一個變數去存
  // 情況3 : 如果中間是一串Expression 就存最後要印的變數
  if ( ident ) {
    gCout_Token_info.is_ident = true ;
    gCout_Token_info.is_int = false ;
    gCout_Token_info.is_float = false ;
    gCout_Token_info.is_string_or_char = false ;
    gCout_Token_info.is_bool = false ;
    gCout_Token_info.bool_value = false ;
    strcpy( gCout_Token_info.ident_name, gToken[location].data ) ;
    strcpy( gCout_Token_info.string_or_char_data, "" ) ;
    gCout_Token_info.constant_data = 0 ;
    gCout_Token.push_back( gCout_Token_info );
  } // if
  else if ( is_int ) {
    gCout_Token_info.is_ident = false ;
    gCout_Token_info.is_int = true ;
    gCout_Token_info.is_float = false ;
    gCout_Token_info.is_string_or_char = false ;
    gCout_Token_info.is_bool = false ;
    gCout_Token_info.bool_value = false ;
    strcpy( gCout_Token_info.ident_name, "" ) ;
    strcpy( gCout_Token_info.string_or_char_data, "" ) ;
    gCout_Token_info.constant_data = constant ;
    gCout_Token.push_back( gCout_Token_info );
  } // else if
  else if ( is_float ) {
    gCout_Token_info.is_ident = false ;
    gCout_Token_info.is_int = false ;
    gCout_Token_info.is_float = true ;
    gCout_Token_info.is_string_or_char = false ;
    gCout_Token_info.is_bool = false ;
    gCout_Token_info.bool_value = false ;
    strcpy( gCout_Token_info.ident_name, "" ) ;
    strcpy( gCout_Token_info.string_or_char_data, "" ) ;
    gCout_Token_info.constant_data = constant ;
    gCout_Token.push_back( gCout_Token_info );
  } // else if
  else if ( string_or_char ) {
    gCout_Token_info.is_ident = false ;
    gCout_Token_info.is_int = false ;
    gCout_Token_info.is_float = false ;
    gCout_Token_info.is_string_or_char = true ;
    gCout_Token_info.is_bool = false ;
    gCout_Token_info.bool_value = false ;
    strcpy( gCout_Token_info.ident_name, "" ) ;
    strcpy( gCout_Token_info.string_or_char_data, string_or_char_data ) ;
    gCout_Token_info.constant_data = 0 ;
    gCout_Token.push_back( gCout_Token_info );
  } // else if
  else if ( is_bool ) {
    gCout_Token_info.is_ident = false ;
    gCout_Token_info.is_int = false ;
    gCout_Token_info.is_float = false ;
    gCout_Token_info.is_string_or_char = false ;
    gCout_Token_info.is_bool = true ;
    gCout_Token_info.bool_value = bool_value ;
    strcpy( gCout_Token_info.ident_name, "" ) ;
    strcpy( gCout_Token_info.string_or_char_data, string_or_char_data ) ;
    gCout_Token_info.constant_data = 0 ;
    gCout_Token.push_back( gCout_Token_info );
  } // else if

  return ;

} // Temp_data_prepare_to_cout()

void Print_cout_data() { // 印出cout結果
  // 布林必須印出 true or false 
  // 字串必須解除 "" 符號 並印出其內容
  // 數字忠實的印出來
  // int 與 float型別的ident 直接印出其內容

  if ( gCout_Token.size() > 0 )  printf( "> " ) ;
  int i = 0 ;
  while ( i < gCout_Token.size() ) { 

    if ( gCout_Token[i].is_ident == true ) { // ident又分成以下幾種
      int find_it = Find_variable_location_in_ALL_variables( gCout_Token[i].ident_name ) ;

      if ( find_it != -1 ) {

        if ( gALL_vari_Token[find_it].detail_type == INT ) {
          int output = gALL_vari_Token[find_it].constant_value ;
          printf( "%d", output ) ;
        } // if
        else if ( gALL_vari_Token[find_it].detail_type == FLOAT ) {
          printf( "%f", gALL_vari_Token[find_it].constant_value ) ;
        } // else if
        else if ( gALL_vari_Token[find_it].detail_type == STRING ) {
          printf( "%s", gALL_vari_Token[find_it].string_value ) ;
        } // else if
        else if ( gALL_vari_Token[find_it].detail_type == BOOL ) {
          if ( gALL_vari_Token[find_it].bool_value == true ) {
            printf( "true" ) ;
          } // if
          else if ( gALL_vari_Token[find_it].bool_value == false ) {
            printf( "false" ) ;
          } // else if
        } // else if

      } // if

    } // if
    else if ( gCout_Token[i].is_int == true ) {
      int output = gCout_Token[i].constant_data ;
      printf( "%d", output ) ;

    } // else if
    else if ( gCout_Token[i].is_float == true ) {
      printf( "%f", gCout_Token[i].constant_data ) ;
    } // else if
    else if ( gCout_Token[i].is_string_or_char == true ) {
      if ( strcmp( gCout_Token[i].string_or_char_data, "\n" ) == 0 ) {
        printf( "\n" ) ;
      } // if
      else {
        printf( "%s", gCout_Token[i].string_or_char_data ) ;
      } // else 
    } // else if
    else if ( gCout_Token[i].is_bool == true ) {
      if ( gCout_Token[i].bool_value == true ) {
        printf( "true" ) ;
      } // if
      else {
        printf( "false" ) ;
      } // else 
    } // else if

    i ++ ;

  } // while

  printf( "Statement executed ...\n" ) ;


  gCout_Token.clear() ; // 初始化

  return ;

} // Print_cout_data()

void Store_ALL_variable_name_and_value( char ident_name[500], int location, bool is_already_defined ) { 
  // 存取變數資料進去vactor

  if ( !is_already_defined ) { // 沒有定義過就直接設定完 push back進去
    strcpy( gALL_vari_Token_info.name, ident_name ) ;
    gALL_vari_Token_info.detail_type = gToken[location].detail_type ;
    gALL_vari_Token_info.bool_value = false ;
    gALL_vari_Token_info.constant_value = 0 ;
    strcpy( gALL_vari_Token_info.string_value, "" ) ;
    gALL_vari_Token.push_back( gALL_vari_Token_info ) ;
  } // if
  else { // 重新定義的變數 更改他的detail type即可
    int find = Find_variable_location_in_ALL_variables( gToken[location].data ) ;
    if ( find != -1 ) gALL_vari_Token[find].detail_type = gToken[location].detail_type ;
  } // else

} // Store_ALL_variable_name_and_value()

// 比對輸入的ident data找到該ident的變數在ALL_variables中儲存的位置並回傳
int Find_variable_location_in_ALL_variables( char ident[500] ) { 

  int find_it = 0 ;
  bool fount_it = false ;

  while ( find_it < gALL_vari_Token.size() && !fount_it ) {

    if ( strcmp( gALL_vari_Token[find_it].name, ident ) == 0 ) {
      fount_it = true ;
    } // if

    find_it ++ ;
  } // while

  if ( fount_it ) find_it -- ; // 最後迴圈會多加一次所以要減回來
  else find_it = -1 ;

  return find_it ;

} // Find_variable_location_in_ALL_variables()

bool Boolean_operator( int num ) { // 看看是不是布林運算

  if ( gToken[num].token_type == EQUAL || gToken[num].token_type == NOT_EQUAL
       || gToken[num].token_type == BIGGER || gToken[num].token_type == BIGGGER_EQ
       || gToken[num].token_type == SMALLER || gToken[num].token_type == SMALLER_EQ ) return true ;
  else return false ; 

} // Boolean_operator()

// For P3 ^==================================================================================================

void Print_every_variable() { // 顯示目前所有的變數狀態

  int num = 0 ;
  bool have_defined = false ;
  bool is_funtion_defined = false ;
  bool vari_in_func_temp_defi = false ;

  while ( num < gToken.size() ) {

    if ( gToken[num].have_defined == true ) {
      have_defined = true ;
    } // if

    if ( gToken[num].is_funtion_defined == true ) {
      is_funtion_defined = true ;
    } // if

    if ( gToken[num].vari_in_func_temp_defi == true ) {
      vari_in_func_temp_defi = true ;
    } // if

    if ( have_defined && is_funtion_defined && vari_in_func_temp_defi ) {
      printf( "I'm '%s' ,have_defined = O, is_funtion_defined = O, vari_in_func_temp_defi = O\n", 
              gToken[num].data ) ;
    } // if
    else if ( have_defined && !is_funtion_defined && !vari_in_func_temp_defi ) {
      printf( "I'm '%s' ,have_defined = O, is_funtion_defined = X, vari_in_func_temp_defi = X\n",
              gToken[num].data ) ;
    } // else if
    else if ( have_defined && is_funtion_defined && !vari_in_func_temp_defi ) {
      printf( "I'm '%s' ,have_defined = O, is_funtion_defined = O, vari_in_func_temp_defi = X\n",
              gToken[num].data ) ;
    } // else if
    else if ( have_defined && !is_funtion_defined && vari_in_func_temp_defi ) {
      printf( "I'm '%s' ,have_defined = O, is_funtion_defined = X, vari_in_func_temp_defi = O\n",
              gToken[num].data ) ;
    } // else if
    else if ( !have_defined && is_funtion_defined && !vari_in_func_temp_defi ) {
      printf( "I'm '%s' ,have_defined = X, is_funtion_defined = O, vari_in_func_temp_defi = X\n",
              gToken[num].data ) ;
    } // else if
    else if ( !have_defined && is_funtion_defined && vari_in_func_temp_defi ) {
      printf( "I'm '%s' ,have_defined = X, is_funtion_defined = O, vari_in_func_temp_defi = O\n",
              gToken[num].data ) ;
    } // else if
    else if ( have_defined && is_funtion_defined && !vari_in_func_temp_defi ) {
      printf( "I'm '%s' ,have_defined = O, is_funtion_defined = O, vari_in_func_temp_defi = X\n",
              gToken[num].data ) ;
    } // else if
    else if ( !have_defined && !is_funtion_defined && vari_in_func_temp_defi ) {
      printf( "I'm '%s' ,have_defined = X, is_funtion_defined = X, vari_in_func_temp_defi = O\n",
              gToken[num].data ) ;
    } // else if

    num ++ ;
    have_defined = false ;
    is_funtion_defined = false ;
    vari_in_func_temp_defi = false ;
  } // while

  return ;

} // Print_every_variable()

// =========================================================================================================

bool User_input() { // 用戶輸入
  // 重置function內的變數定義
  // Definition 以外的路 (Statement) 都是一碰到ident就要檢查有沒有defined過

  if ( gToken[gNum].token_type != LISTALLFUCTIONS && gToken[gNum].token_type != LISTALLVARIABLES 
       && gToken[gNum].token_type != LISTFUNCTION && gToken[gNum].token_type != LISTVARIABLE 
       && gToken[gNum].token_type != DONE ) {

    if ( Type_specifier() || gToken[gNum].token_type == VOID_TYPE ) { // 還不確定怎麼判斷

      gTemp_variable_loctation->clear() ;
      gTemp_variable_loctation->push_back( gNum + 1 ) ;

      gHave_error = false ; // 初始化
      gIs_Definition = true ;
      gIs_cout_operation = false ;
      gAfter_LS = false ;
      gIs_float_operation = false ;
      gIs_function_Definition = false ;
      gGet_error = false ;
      gValue.clear(); // 初始化
      gBool_Ans.clear(); // 初始化
      strcpy( gString_value, "" ) ;
      Clear_defi_variable_infuntion() ;

      // Print_every_variable() ;

      if ( Definition() ) {

        if ( !gHave_error ) { 

          int  i = 0 ; // 0就是最新丟進去的變數

          // 會用迴圈是因為有可能一次定義好幾個變數 ex.int x, y ;
          // 不會重複印是因為已經印過的會在進去Definition()前被clear()
          while ( i < gTemp_variable_loctation->size() ) { 
          
            if ( Definiton_and_New_Definition( i ) ) {

              if ( i == 0 ) printf( "> " ) ;
              // 處理定義的問題
              if ( gToken[gTemp_variable_loctation->at( i )].is_funtion_defined == true ) {
                printf( "Definition of %s() entered ...\n", 
                        gToken[gTemp_variable_loctation->at( i )].data ) ;
              } // if
              else {
                printf( "Definition of %s entered ...\n", 
                           gToken[gTemp_variable_loctation->at( i )].data ) ;

                // 判斷這個變數是不是 Array
                if ( gToken[gTemp_variable_loctation->at( i )+1].token_type != M_LP ) {
                  // 把定義好的 variable 內容存起來方便計算時取值
                  Store_ALL_variable_name_and_value( gToken[gTemp_variable_loctation->at( i )].data, 
                                                     gTemp_variable_loctation->at( i ), false ) ; 
                } // if
                else {
                  if ( gArray_size.size() > 0 ) {
                    int size = gArray_size[0] ;
                    gArray_size.pop_back() ;

                    int start = 0 ;

                    while ( start < size ) {
                      char str[30];
                      str[0] = start + 48 ;
                      char temp[500] ;
                      strcpy( temp, gToken[gTemp_variable_loctation->at( i )].data ) ;
                      strcat( temp, "[" ) ;
                      strcat( temp, str ) ;
                      strcat( temp, "]" ) ;
                      Store_ALL_variable_name_and_value( temp, 
                                                         gTemp_variable_loctation->at( i ), false ) ; 
                      start ++ ;
                    } // while

                  } // if

                } // else 

              } // else


              // ===========================================================================================
              // 如果該funtion沒有問題就儲存起來
              // 如果他是一個funtion定義
              if ( gToken[gTemp_variable_loctation->at( i )].is_funtion_defined == true ) { 
                gFunction_Token_info.start_num = gTemp_variable_loctation->at( i ) - 1 ; // 看他屬於哪一行
                gFunction_Token_info.end_num = gNum;
                strcpy( gFunction_Token_info.function_name, 
                        gToken[gTemp_variable_loctation->at( i )].data ) ;
                gFunction_Token.push_back( gFunction_Token_info );
              } // if
              // ===========================================================================================

            } // if
            else {
              if ( i == 0 ) printf( "> " ) ;
              if ( gToken[gTemp_variable_loctation->at( i )].is_funtion_defined == true ) {
                printf( "New definition of %s() entered ...\n",
                        gToken[gTemp_variable_loctation->at( i )].data ) ;
              } // if
              else printf( "New definition of %s entered ...\n",
                           gToken[gTemp_variable_loctation->at( i )].data ) ;

              // ===========================================================================================
              // 如果該funtion沒有問題就儲存起來
              // 如果他是一個funtion定義
              if ( gToken[gTemp_variable_loctation->at( i )].is_funtion_defined == true ) { 
                gFunction_Token_info.start_num = gTemp_variable_loctation->at( i ) - 1 ; // 看他屬於哪一行
                gFunction_Token_info.end_num = gNum;
                strcpy( gFunction_Token_info.function_name, 
                        gToken[gTemp_variable_loctation->at( i )].data ) ;
                gFunction_Token.push_back( gFunction_Token_info );
              } // if
              // ===========================================================================================
            } // else


            i ++ ;

          } // while


          gLine = 0 ; // 每次輸出結果就初始化為1
          if ( !gAlready_Get && !GetToken( gGet_error ) ) return false ;  // 只有這幾個特別處理因為他在statement()後
          if ( !gAlready_Get ) {
            gNum ++ ;
          } // if 
          else {
            gLine = 1 ;
            gToken[gNum].lineNum = 1 ; 
            // 因為右大括號後面不是接應該出現的ELSE 所以前面已經結束了這是新的一行
            gAlready_Get = false ;
          } // else


        } // if
        else return true ;

      } // if

    } // if
    else if ( gToken[gNum].token_type != DONE ) {

      if ( gToken[gNum].token_type == LISTALLVARIABLES ) {
        ListAllVariables() ;
      } // if
      else if ( gToken[gNum].token_type == LISTALLFUCTIONS ) {
        ListAllFunctions() ;
      } // else if
      else if ( gToken[gNum].token_type == LISTVARIABLE ) {
        if ( !GetToken( gGet_error ) ) return false ; // 先讀掉左括號
        else gNum ++ ;
        if ( !GetToken( gGet_error ) ) return false ; // 這個才會是參數名稱
        else gNum ++ ;
        ListVariable( gToken[gNum].data ) ;
        if ( !GetToken( gGet_error ) ) return false ; // 讀掉右括號
        else gNum ++ ;
        if ( !GetToken( gGet_error ) ) return false ; // 讀掉分號
        else gNum ++ ;
        gLine = 0 ;
        if ( !GetToken( gGet_error ) ) return false ; // 讀下一個input
        else gNum ++ ;
      } // else if
      else if ( gToken[gNum].token_type == LISTFUNCTION ) {
        if ( !GetToken( gGet_error ) ) return false ; // 先讀掉左括號
        else gNum ++ ;
        if ( !GetToken( gGet_error ) ) return false ; // 這個才會是參數名稱
        else gNum ++ ;
        ListFunction( gToken[gNum].data ) ;
        if ( !GetToken( gGet_error ) ) return false ; // 讀掉右括號
        else gNum ++ ;
        if ( !GetToken( gGet_error ) ) return false ; // 讀掉分號
        else gNum ++ ;
        gLine = 0 ;
        if ( !GetToken( gGet_error ) ) return false ; // 讀下一個input
        else gNum ++ ;
      } // else if

      else {
        gHave_error = false ; // 初始化
        gIs_Definition = false ;
        gIs_cout_operation = false ;
        gAfter_LS = false ;
        gIs_float_operation = false ;
        gIs_function_Definition = false ;
        gGet_error = false ;
        gTemp_variable_loctation->clear() ;
        gValue.clear(); // 初始化
        gBool_Ans.clear(); // 初始化
        strcpy( gString_value, "" ) ;
        Clear_defi_variable_infuntion() ;

        // Print_every_variable() ;

        if ( Statement() ) {
          if ( !gHave_error && !gIs_cout_operation ) { 
            
            printf( "> Statement executed ...\n" ) ;
            gLine = 0 ; // 每次輸出結果就初始化為1

            if ( !gAlready_Get && !GetToken( gGet_error ) ) return false ;  // 只有這幾個特別處理因為他在statement()後
            if ( !gAlready_Get ) {
              gNum ++ ;
            } // if 
            else {
              gLine = 1 ;
              gToken[gNum].lineNum = 1 ; 
              // 因為右大括號後面不是接應該出現的ELSE 所以前面已經結束了這是新的一行
              gAlready_Get = false ;
            } // else

          } // if
          else if ( !gHave_error && gIs_cout_operation ) { 
            
            Print_cout_data() ;
            gLine = 0 ; // 每次輸出結果就初始化為1

            if ( !gAlready_Get && !GetToken( gGet_error ) ) return false ;  // 只有這幾個特別處理因為他在statement()後
            if ( !gAlready_Get ) {
              gNum ++ ;
            } // if 
            else {
              gLine = 1 ;
              gToken[gNum].lineNum = 1 ; 
              // 因為右大括號後面不是接應該出現的ELSE 所以前面已經結束了這是新的一行
              gAlready_Get = false ;
            } // else

          } // else if
          else return true ;
        } // if

      } // else
      
    } // else if

  } // if


  // ===================================================================================================
  if ( gPPMM_after_ID.size() > 0 ) {

    int start = 0 ;
    int find = -1 ;

    while ( start < gPPMM_after_ID.size() ) {
      find = Find_variable_location_in_ALL_variables( gPPMM_after_ID[start].name ) ;
      if ( find != -1 && gPPMM_after_ID[start].is_PP == true ) {
        gALL_vari_Token[find].constant_value = gALL_vari_Token[find].constant_value + 1 ;
      } // if
      else if ( find != -1 && gPPMM_after_ID[start].is_PP == false ) {
        gALL_vari_Token[find].constant_value = gALL_vari_Token[find].constant_value - 1 ;
      } // else if

      start ++ ;

    } // while

    gPPMM_after_ID.clear() ;
  } // if
  // ===================================================================================================


  while ( gToken[gNum].token_type != DONE ) {

    if ( gToken[gNum].token_type == LISTALLVARIABLES ) {
      ListAllVariables() ;
    } // if
    else if ( gToken[gNum].token_type == LISTALLFUCTIONS ) {
      ListAllFunctions() ;
    } // else if
    else if ( gToken[gNum].token_type == LISTVARIABLE ) {
      if ( !GetToken( gGet_error ) ) return false ; // 先讀掉左括號
      else gNum ++ ;
      if ( !GetToken( gGet_error ) ) return false ; // 這個才會是參數名稱
      else gNum ++ ;
      ListVariable( gToken[gNum].data ) ;
      if ( !GetToken( gGet_error ) ) return false ; // 讀掉右括號
      else gNum ++ ;
      if ( !GetToken( gGet_error ) ) return false ; // 讀掉分號
      else gNum ++ ;
      if ( !GetToken( gGet_error ) ) return false ; // 讀下一個input
      else gNum ++ ;
    } // else if
    else if ( gToken[gNum].token_type == LISTFUNCTION ) {
      if ( !GetToken( gGet_error ) ) return false ; // 先讀掉左括號
      else gNum ++ ;
      if ( !GetToken( gGet_error ) ) return false ; // 這個才會是參數名稱
      else gNum ++ ;
      ListFunction( gToken[gNum].data ) ;
      if ( !GetToken( gGet_error ) ) return false ; // 讀掉右括號
      else gNum ++ ;
      if ( !GetToken( gGet_error ) ) return false ; // 讀掉分號
      else gNum ++ ;
      if ( !GetToken( gGet_error ) ) return false ; // 讀下一個input
      else gNum ++ ;
    } // else if
    else if ( Type_specifier() || gToken[gNum].token_type == VOID_TYPE ) { // 還不確定怎麼判斷

      gTemp_variable_loctation->clear() ;
      gTemp_variable_loctation->push_back( gNum + 1 ) ;

      gHave_error = false ; // 初始化
      gIs_Definition = true ;
      gIs_cout_operation = false ;
      gAfter_LS = false ;
      gIs_float_operation = false ;
      gIs_function_Definition = false ;
      gGet_error = false ;
      gValue.clear(); // 初始化
      gBool_Ans.clear(); // 初始化
      strcpy( gString_value, "" ) ;
      Clear_defi_variable_infuntion() ;

      // Print_every_variable() ;

      if ( Definition() ) {

        if ( !gHave_error ) { 

          int  i = 0 ;

          while ( i < gTemp_variable_loctation->size() ) {
          
            if ( Definiton_and_New_Definition( i ) ) {

              if ( i == 0 ) printf( "> " ) ;
              // 處理定義的問題
              if ( gToken[gTemp_variable_loctation->at( i )].is_funtion_defined == true ) {
                printf( "Definition of %s() entered ...\n", 
                        gToken[gTemp_variable_loctation->at( i )].data ) ; 
              } // if
              else {
                printf( "Definition of %s entered ...\n", 
                        gToken[gTemp_variable_loctation->at( i )].data ) ; 

                // 判斷這個變數是不是 Array
                if ( gToken[gTemp_variable_loctation->at( i )+1].token_type != M_LP ) {
                  // 把定義好的 variable 內容存起來方便計算時取值
                  Store_ALL_variable_name_and_value( gToken[gTemp_variable_loctation->at( i )].data, 
                                                     gTemp_variable_loctation->at( i ), false ) ; 
                } // if
                else {
                  if ( gArray_size.size() > 0 ) {
                    int size = gArray_size[0] ;
                    gArray_size.pop_back() ;

                    int start = 0 ;

                    while ( start < size ) {
                      char str[30];
                      str[0] = start + 48 ;
                      char temp[500] ;
                      strcpy( temp, gToken[gTemp_variable_loctation->at( i )].data ) ;
                      strcat( temp, "[" ) ;
                      strcat( temp, str ) ;
                      strcat( temp, "]" ) ;
                      Store_ALL_variable_name_and_value( temp, 
                                                         gTemp_variable_loctation->at( i ), false ) ; 
                      start ++ ;
                    } // while

                  } // if

                } // else 

              } // else


              // ===========================================================================================
              // 如果該funtion沒有問題就儲存起來
              // 如果他是一個funtion定義
              if ( gToken[gTemp_variable_loctation->at( i )].is_funtion_defined == true ) { 
                gFunction_Token_info.start_num = gTemp_variable_loctation->at( i ) - 1 ; // 看他屬於哪一行
                gFunction_Token_info.end_num = gNum;
                strcpy( gFunction_Token_info.function_name, 
                        gToken[gTemp_variable_loctation->at( i )].data ) ;
                gFunction_Token.push_back( gFunction_Token_info );
              } // if
              // ===========================================================================================

            } // if
            else {
              if ( i == 0 ) printf( "> " ) ;
              if ( gToken[gTemp_variable_loctation->at( i )].is_funtion_defined == true ) {
                printf( "New definition of %s() entered ...\n",
                        gToken[gTemp_variable_loctation->at( i )].data ) ;
              } // if
              else printf( "New definition of %s entered ...\n",
                           gToken[gTemp_variable_loctation->at( i )].data ) ;

              // ===========================================================================================
              // 如果該funtion沒有問題就儲存起來
              // 如果他是一個funtion定義
              if ( gToken[gTemp_variable_loctation->at( i )].is_funtion_defined == true ) { 
                gFunction_Token_info.start_num = gTemp_variable_loctation->at( i ) - 1 ; // 看他屬於哪一行
                gFunction_Token_info.end_num = gNum;
                strcpy( gFunction_Token_info.function_name, 
                        gToken[gTemp_variable_loctation->at( i )].data ) ;
                gFunction_Token.push_back( gFunction_Token_info );
              } // if
              // ===========================================================================================
            } // else


            i ++ ;

          } // while


          gLine = 0 ; // 每次輸出結果就初始化為1
          if ( !gAlready_Get && !GetToken( gGet_error ) ) return false ;  // 只有這幾個特別處理因為他在statement()後
          if ( !gAlready_Get ) {
            gNum ++ ;
          } // if 
          else {
            gLine = 1 ;
            gToken[gNum].lineNum = 1 ; 
            // 因為右大括號後面不是接應該出現的ELSE 所以前面已經結束了這是新的一行
            gAlready_Get = false ;
          } // else


        } // if
        else return true ;
      
      } // if
    } // else if
    else {

      gHave_error = false ; // 初始化
      gIs_Definition = false ;
      gIs_cout_operation = false ;
      gAfter_LS = false ;
      gIs_float_operation = false ;
      gGet_error = false ;
      gIs_function_Definition = false ;
      gTemp_variable_loctation->clear() ;
      gValue.clear(); // 初始化
      gBool_Ans.clear(); // 初始化
      strcpy( gString_value, "" ) ;
      Clear_defi_variable_infuntion() ;

      // Print_every_variable() ;

      if ( Statement() ) {

        if ( !gHave_error && !gIs_cout_operation ) { 
          
          printf( "> Statement executed ...\n" ) ;

          gLine = 0 ; // 每次輸出結果就初始化為1

          if ( !gAlready_Get && !GetToken( gGet_error ) ) return false ;  // 只有這幾個特別處理因為他在statement()後
          if ( !gAlready_Get ) {
            gNum ++ ;
          } // if 
          else {
            gLine = 1 ;
            gToken[gNum].lineNum = 1 ; 
            // 因為右大括號後面不是接應該出現的ELSE 所以前面已經結束了這是新的一行
            gAlready_Get = false ;
          } // else

        } // if
        else if ( !gHave_error && gIs_cout_operation ) { 
            
          Print_cout_data() ;
          gLine = 0 ; // 每次輸出結果就初始化為1

          if ( !gAlready_Get && !GetToken( gGet_error ) ) return false ;  // 只有這幾個特別處理因為他在statement()後
          if ( !gAlready_Get ) {
            gNum ++ ;
          } // if 
          else {
            gLine = 1 ;
            gToken[gNum].lineNum = 1 ; 
            // 因為右大括號後面不是接應該出現的ELSE 所以前面已經結束了這是新的一行
            gAlready_Get = false ;
          } // else

        } // else if
        else return true ;
      } // if

    } // else


    // ===================================================================================================
    if ( gPPMM_after_ID.size() > 0 ) {

      int start = 0 ;
      int find = -1 ;

      while ( start < gPPMM_after_ID.size() ) {
        find = Find_variable_location_in_ALL_variables( gPPMM_after_ID[start].name ) ;
        if ( find != -1 && gPPMM_after_ID[start].is_PP == true ) {
          gALL_vari_Token[find].constant_value = gALL_vari_Token[find].constant_value + 1 ;
        } // if
        else if ( find != -1 && gPPMM_after_ID[start].is_PP == false ) {
          gALL_vari_Token[find].constant_value = gALL_vari_Token[find].constant_value - 1 ;
        } // else if

        start ++ ;

      } // while

      gPPMM_after_ID.clear() ;
    } // if
    // ===================================================================================================


  } // while


  gTemp_variable_loctation->clear() ;

  gHave_error = false ; // 初始化
  gIs_Definition = false ;
  gIs_cout_operation = false ;
  gAfter_LS = false ;
  gIs_float_operation = false ;
  gIs_function_Definition = false ;
  gGet_error = false ;
  gValue.clear(); // 初始化
  gBool_Ans.clear(); // 初始化
  strcpy( gString_value, "" ) ;
  Clear_defi_variable_infuntion() ;


  if ( gToken[gNum].token_type == DONE ) {
    Done() ;
    return false ; // 只有這個是return false因為要結束執行了
  } // if

  return true ;

} // User_input()

// =========================================================================================================

bool Definition() { // 定義

  if ( gToken[gNum].token_type == VOID_TYPE ) {
    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( gToken[gNum].token_type == IDENT ) { // definition 裡的ident不用檢查有沒有被定義

      Determine_variable_detail_type() ; // 在ident定義時判斷更詳細的變數型別

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      
      if ( Function_definition_without_ID() ) return true ;
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
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
  } // if
  else if ( Type_specifier() ) {

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( gToken[gNum].token_type == IDENT ) { // definition 裡的ident不用檢查有沒有被定義

      Determine_variable_detail_type() ; // 在ident定義時判斷更詳細的變數型別

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;


      if ( Function_definition_or_declarators() ) return true ;
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
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
  } // else if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;


} // Definition()

// =========================================================================================================

bool Type_specifier() { // 類型說明符
  if ( gToken[gNum].token_type == INT_TYPE || gToken[gNum].token_type == CHAR_TYPE
       || gToken[gNum].token_type == FLOAT_TYPE || gToken[gNum].token_type == STRING_TYPE
       || gToken[gNum].token_type == BOOL_TYPE ) {
    gIs_Definition = true ;
    return true ;
  } // if
  else return false ;
} // Type_specifier()

// =========================================================================================================

bool Function_definition_or_declarators() { // 

  if ( gToken[gNum].token_type == S_LP ) {
    if ( Function_definition_without_ID() ) return true ;
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
  } // if
  else if ( gToken[gNum].token_type == M_LP || gToken[gNum].token_type == COMMA 
            || gToken[gNum].token_type == SEMICOLON ) {
    if ( Rest_of_declarators() ) return true ;
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////
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

  if ( !gHave_error ) return true ;
  else return false ;
} // Function_definition_or_declarators()

// =========================================================================================================

bool Rest_of_declarators() { // 變數後面有中括號 或是一次宣告很多變數 

  if ( gToken[gNum].token_type == M_LP ) {

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( gToken[gNum].token_type == CONSTANT ) {

      gArray_size.push_back( atoi( gToken[gNum].data ) ) ;

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( gToken[gNum].token_type == M_RP ) {
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

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

  while ( !gHave_error && gToken[gNum].token_type == COMMA ) {

    if ( gHave_error ) return false ;
    
    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( gToken[gNum].token_type == IDENT ) {

      if ( !gIs_function_Definition ) gTemp_variable_loctation->push_back( gNum ) ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
      else if ( gIs_function_Definition ) { // 在funtion中出現 剛剛又經歷過Type_specifier代表他要被定義
        gToken[gNum].vari_in_func_temp_defi = true ;
      } // else if
      // 在funtion內出現的ident不是出現在type_specifier()後就要檢查有沒有被定義
      // ///////////////////////////////////////////////////////////////////////////////////////////////////


      if ( gIs_Definition ) {
        Determine_variable_detail_type() ; // 在ident定義時判斷更詳細的變數型別
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;
      } // if

      if ( gToken[gNum].token_type == M_LP ) {
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        if ( gToken[gNum].token_type == CONSTANT ) {
          
          gArray_size.push_back( atoi( gToken[gNum].data ) ) ;

          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;

          if ( gToken[gNum].token_type == M_RP ) {
            if ( !GetToken( gGet_error ) ) return false ; 
            else gNum ++ ;

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

  if ( !gHave_error && gToken[gNum].token_type == SEMICOLON ) {
    return true ;
  } // if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    return false ; 
  } // else if

  if ( !gHave_error ) return true ;
  else return false ;

} // Rest_of_declarators()

// =========================================================================================================

bool Function_definition_without_ID() {


  if ( gToken[gNum].token_type == S_LP ) {

    // 是正在跑定義，又同時進到左小括號，代表他一定應是funtion定義
    if ( gIs_Definition ) gIs_function_Definition = true ; 

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( gToken[gNum].token_type == S_RP ) {
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Compound_statement() ) return true ;
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;
    } // if 
    else if ( gToken[gNum].token_type == VOID_TYPE || Formal_parameter_list() ) {

      if ( gToken[gNum].token_type == VOID_TYPE ) { 
        // 不是void就不用get是因為在Formal_parameter_list就已經預先Get好了
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;
      } // if
      
      if ( gToken[gNum].token_type == S_RP ) {
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        if ( Compound_statement() ) return true ;
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
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

      return false ;
    } // else if 
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

    return false ;
  } // if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    return false ; 
  } // else if
  else return false ;

  if ( !gHave_error ) return true ;
  else return false ;
    
} // Function_definition_without_ID()

// =========================================================================================================

bool Formal_parameter_list() { // 正式參數列表

  if ( Type_specifier() ) {

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;


    if ( gToken[gNum].token_type == ONE_AND ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( gToken[gNum].token_type == IDENT ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
        else if ( gIs_function_Definition ) { // 在funtion中出現 剛剛又經歷過Type_specifier代表他要被定義
          gToken[gNum].vari_in_func_temp_defi = true ;
        } // else if
        // /////////////////////////////////////////////////////////////////////////////////////////////////

        if ( gIs_Definition ) {
          Determine_variable_detail_type() ; // 在ident定義時判斷更詳細的變數型別
          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;
        } // if


        if ( gToken[gNum].token_type == M_LP ) {
          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;

          if ( gToken[gNum].token_type == CONSTANT ) {
            // =============================================================================================

            // 情況1 : 是一個statement的計算 把數值存入 gValue中方便計算
            // 情況2 : Cout中出現數字 但這個數字是用來計算的不用print ( 用是不是 << 直接接數字來判斷 )
            // 情況2 : 是一個準備Cout的數字 存入準備print的vector
            if ( gToken[gNum].detail_type == INT || gToken[gNum].detail_type == FLOAT ) {

              if ( !gIs_Definition && !gIs_function_Definition && !gIs_cout_operation ) {
                if ( gToken[gNum].detail_type == INT ) {
                  gValue.push_back( atoi( gToken[gNum].data ) ) ;
                } // if
                else if ( gToken[gNum].detail_type == FLOAT ) {
                  gValue.push_back( atof( gToken[gNum].data ) ) ;
                  gIs_float_operation = true ;
                } // else if
              } // if
              else if ( !gIs_Definition && !gIs_function_Definition && 
                        gIs_cout_operation && !gAfter_LS ) {
                if ( gToken[gNum].detail_type == INT ) {
                  gValue.push_back( atoi( gToken[gNum].data ) ) ;
                } // if
                else if ( gToken[gNum].detail_type == FLOAT ) {
                  gValue.push_back( atof( gToken[gNum].data ) ) ;
                  gIs_float_operation = true ;
                } // else if
              } // else if
              else if ( !gIs_Definition && !gIs_function_Definition && 
                        gIs_cout_operation && gAfter_LS ) {
                gAfter_LS = false ;

                if ( gToken[gNum].detail_type == INT ) {
                  gValue.push_back( atoi( gToken[gNum].data ) ) ;
                  gIdent_operation = true ;
                } // if
                else if ( gToken[gNum].detail_type == FLOAT ) {
                  gValue.push_back( atof( gToken[gNum].data ) ) ;
                  gIs_float_operation = true ;
                  gIdent_operation = true ;
                } // else if

              } // else if

            } // if
            else if ( gToken[gNum].detail_type == STRING || gToken[gNum].detail_type == CHAR ) {

              strcat( gString_value, gToken[gNum].data ) ;

            } // else if

            // =============================================================================================

            if ( !GetToken( gGet_error ) ) return false ; 
            else gNum ++ ;

            if ( gToken[gNum].token_type == M_RP ) {
              if ( !GetToken( gGet_error ) ) return false ; 
              else gNum ++ ;

              // return true; 這裡不用return因為還要判斷逗號
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
      else if ( gIs_function_Definition ) { // 在funtion中出現 剛剛又經歷過Type_specifier代表他要被定義
        gToken[gNum].vari_in_func_temp_defi = true ;
      } // else if
      // ///////////////////////////////////////////////////////////////////////////////////////////////////

      if ( gIs_Definition ) {
        Determine_variable_detail_type() ; // 在ident定義時判斷更詳細的變數型別
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;
      } // if

      if ( gToken[gNum].token_type == M_LP ) {
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        if ( gToken[gNum].token_type == CONSTANT ) {

          // ===============================================================================================

          // 情況1 : 是一個statement的計算 把數值存入 gValue中方便計算
          // 情況2 : Cout中出現數字 但這個數字是用來計算的不用print ( 用是不是 << 直接接數字來判斷 )
          // 情況2 : 是一個準備Cout的數字 存入準備print的vector
          if ( gToken[gNum].detail_type == INT || gToken[gNum].detail_type == FLOAT ) {

            if ( !gIs_Definition && !gIs_function_Definition && !gIs_cout_operation ) {
              if ( gToken[gNum].detail_type == INT ) {
                gValue.push_back( atoi( gToken[gNum].data ) ) ;
              } // if
              else if ( gToken[gNum].detail_type == FLOAT ) {
                gValue.push_back( atof( gToken[gNum].data ) ) ;
                gIs_float_operation = true ;
              } // else if
            } // if
            else if ( !gIs_Definition && !gIs_function_Definition && 
                      gIs_cout_operation && !gAfter_LS ) {
              if ( gToken[gNum].detail_type == INT ) {
                gValue.push_back( atoi( gToken[gNum].data ) ) ;
              } // if
              else if ( gToken[gNum].detail_type == FLOAT ) {
                gValue.push_back( atof( gToken[gNum].data ) ) ;
                gIs_float_operation = true ;
              } // else if  
            } // else if
            else if ( !gIs_Definition && !gIs_function_Definition && 
                      gIs_cout_operation && gAfter_LS ) {
              gAfter_LS = false ;

              if ( gToken[gNum].detail_type == INT ) {
                gValue.push_back( atoi( gToken[gNum].data ) ) ;
                gIdent_operation = true ;
              } // if
              else if ( gToken[gNum].detail_type == FLOAT ) {
                gValue.push_back( atof( gToken[gNum].data ) ) ;
                gIs_float_operation = true ;
                gIdent_operation = true ;
              } // else if

            } // else if

          } // if
          else if ( gToken[gNum].detail_type == STRING || gToken[gNum].detail_type == CHAR ) {

            strcat( gString_value, gToken[gNum].data ) ;

          } // else if

          // ===============================================================================================

          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;

          if ( gToken[gNum].token_type == M_RP ) {
            if ( !GetToken( gGet_error ) ) return false ; 
            else gNum ++ ;

            // return true; 這裡不用return因為還要判斷逗號
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

    if ( gHave_error ) return false ;

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Type_specifier() ) {
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( gToken[gNum].token_type == ONE_AND ) {
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        if ( gToken[gNum].token_type == IDENT ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
          else if ( gIs_function_Definition ) { // 在funtion中出現 剛剛又經歷過Type_specifier代表他要被定義
            gToken[gNum].vari_in_func_temp_defi = true ;
          } // else if
          // ///////////////////////////////////////////////////////////////////////////////////////////////

          if ( gIs_Definition ) {
            Determine_variable_detail_type() ; // 在ident定義時判斷更詳細的變數型別
            if ( !GetToken( gGet_error ) ) return false ; 
            else gNum ++ ;
          } // if

          if ( gToken[gNum].token_type == M_LP ) {
            if ( !GetToken( gGet_error ) ) return false ; 
            else gNum ++ ;

            if ( gToken[gNum].token_type == CONSTANT ) {
              // ===========================================================================================

              // 情況1 : 是一個statement的計算 把數值存入 gValue中方便計算
              // 情況2 : Cout中出現數字 但這個數字是用來計算的不用print ( 用是不是 << 直接接數字來判斷 )
              // 情況2 : 是一個準備Cout的數字 存入準備print的vector
              if ( gToken[gNum].detail_type == INT || gToken[gNum].detail_type == FLOAT ) {

                if ( !gIs_Definition && !gIs_function_Definition && !gIs_cout_operation ) {
                  if ( gToken[gNum].detail_type == INT ) {
                    gValue.push_back( atoi( gToken[gNum].data ) ) ;
                  } // if
                  else if ( gToken[gNum].detail_type == FLOAT ) {
                    gValue.push_back( atof( gToken[gNum].data ) ) ;
                    gIs_float_operation = true ;
                  } // else if
                } // if
                else if ( !gIs_Definition && !gIs_function_Definition && 
                          gIs_cout_operation && !gAfter_LS ) {
                  if ( gToken[gNum].detail_type == INT ) {
                    gValue.push_back( atoi( gToken[gNum].data ) ) ;
                  } // if
                  else if ( gToken[gNum].detail_type == FLOAT ) {
                    gValue.push_back( atof( gToken[gNum].data ) ) ;
                    gIs_float_operation = true ;
                  } // else if
                } // else if
                else if ( !gIs_Definition && !gIs_function_Definition && 
                          gIs_cout_operation && gAfter_LS ) {
                  gAfter_LS = false ;

                  if ( gToken[gNum].detail_type == INT ) {
                    gValue.push_back( atoi( gToken[gNum].data ) ) ;
                    gIdent_operation = true ;
                  } // if
                  else if ( gToken[gNum].detail_type == FLOAT ) {
                    gValue.push_back( atof( gToken[gNum].data ) ) ;
                    gIs_float_operation = true ;
                    gIdent_operation = true ;
                  } // else if

                } // else if

              } // if
              else if ( gToken[gNum].detail_type == STRING || gToken[gNum].detail_type == CHAR ) {

                strcat( gString_value, gToken[gNum].data ) ;

              } // else if

              // ===========================================================================================

              if ( !GetToken( gGet_error ) ) return false ; 
              else gNum ++ ;

              if ( gToken[gNum].token_type == M_RP ) {
                if ( !GetToken( gGet_error ) ) return false ; 
                else gNum ++ ;
                // return true; 這裡不用return因為還要判斷逗號
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
        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // else if
        else return false ;

      } // if
      else if ( gToken[gNum].token_type == IDENT ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
        else if ( gIs_function_Definition ) { // 在funtion中出現 剛剛又經歷過Type_specifier代表他要被定義
          gToken[gNum].vari_in_func_temp_defi = true ;
        } // else if
        // /////////////////////////////////////////////////////////////////////////////////////////////////

        if ( gIs_Definition ) {
          Determine_variable_detail_type() ; // 在ident定義時判斷更詳細的變數型別
          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;
        } // if

        if ( gToken[gNum].token_type == M_LP ) {
          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;

          if ( gToken[gNum].token_type == CONSTANT ) {

            // =============================================================================================

            // 情況1 : 是一個statement的計算 把數值存入 gValue中方便計算
            // 情況2 : Cout中出現數字 但這個數字是用來計算的不用print ( 用是不是 << 直接接數字來判斷 )
            // 情況2 : 是一個準備Cout的數字 存入準備print的vector
            if ( gToken[gNum].detail_type == INT || gToken[gNum].detail_type == FLOAT ) {

              if ( !gIs_Definition && !gIs_function_Definition && !gIs_cout_operation ) {
                if ( gToken[gNum].detail_type == INT ) {
                  gValue.push_back( atoi( gToken[gNum].data ) ) ;
                } // if
                else if ( gToken[gNum].detail_type == FLOAT ) {
                  gValue.push_back( atof( gToken[gNum].data ) ) ;
                  gIs_float_operation = true ;
                } // else if
              } // if
              else if ( !gIs_Definition && !gIs_function_Definition && 
                        gIs_cout_operation && !gAfter_LS ) {
                if ( gToken[gNum].detail_type == INT ) {
                  gValue.push_back( atoi( gToken[gNum].data ) ) ;
                } // if
                else if ( gToken[gNum].detail_type == FLOAT ) {
                  gValue.push_back( atof( gToken[gNum].data ) ) ;
                  gIs_float_operation = true ;
                } // else if
              } // else if
              else if ( !gIs_Definition && !gIs_function_Definition && 
                        gIs_cout_operation && gAfter_LS ) {
                gAfter_LS = false ;

                if ( gToken[gNum].detail_type == INT ) {
                  gValue.push_back( atoi( gToken[gNum].data ) ) ;
                  gIdent_operation = true ;
                } // if
                else if ( gToken[gNum].detail_type == FLOAT ) {
                  gValue.push_back( atof( gToken[gNum].data ) ) ;
                  gIs_float_operation = true ;
                  gIdent_operation = true ;
                } // else if

              } // else if

            } // if
            else if ( gToken[gNum].detail_type == STRING || gToken[gNum].detail_type == CHAR ) {

              strcat( gString_value, gToken[gNum].data ) ;

            } // else if

            // =============================================================================================

            if ( !GetToken( gGet_error ) ) return false ; 
            else gNum ++ ;

            if ( gToken[gNum].token_type == M_RP ) {
              if ( !GetToken( gGet_error ) ) return false ; 
              else gNum ++ ;
              // return true; 這裡不用return因為還要判斷逗號
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

      } // else if
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
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

  if ( !gHave_error ) return true ;
  else return false ;

} // Formal_parameter_list()

// =========================================================================================================

bool Compound_statement() { // 複合陳述
 
  if ( gToken[gNum].token_type == L_LP ) {

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    while ( gToken[gNum].token_type != L_RP ) { // 直接L_RP回去 回到user input才跳下一個

      if ( gHave_error ) return false ;

      if ( Type_specifier() ) {
         
        if ( Declaration() ) {
          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;
        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////
          return false ; 
        } // else if
        else return false ;
      } // if
      else if ( Statement() ) {
        if ( !gAlready_Get && !GetToken( gGet_error ) ) return false ;  // 只有這幾個特別處理因為他在statement()後
        if ( !gAlready_Get ) {
          gNum ++ ;
        } // if 
        else gAlready_Get = false ;
      } // else if
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // ///////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // ///////////////////////////////////////////////////////////////////////////////////////////
        return false ; 
      } // else if
      else return false ;

    } // while

    if ( !gHave_error ) return true ;
    else return false ;

  } // if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ; 
  } // else if
  else return false ;

  if ( !gHave_error ) return true ;
  else return false ;

} // Compound_statement()

// =========================================================================================================

bool Declaration() {

  if ( Type_specifier() ) {

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( gToken[gNum].token_type == IDENT ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
      else if ( gIs_function_Definition ) { // 在funtion中出現 剛剛又經歷過Type_specifier代表他要被定義
        gToken[gNum].vari_in_func_temp_defi = true ;
      } // else if
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      
      if ( gIs_Definition ) {
        Determine_variable_detail_type() ; // 在ident定義時判斷更詳細的變數型別
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;
      } // if

      if ( Rest_of_declarators() ) return true;
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // ///////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // ///////////////////////////////////////////////////////////////////////////////////////////
        return false ; 
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
  } // if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    return false ; 
  } // else if
  else return false ;


  return true ;

} // Declaration()

// =========================================================================================================

bool Statement() {

  if ( gToken[gNum].token_type == SEMICOLON ) return true ;
  else if ( gToken[gNum].token_type == RETURN ) {

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Expression() ) { // 只會跑一次
      ; // 沒事幹
    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

    if ( gToken[gNum].token_type == SEMICOLON ) return true ;
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // else if
  else if ( gToken[gNum].token_type == L_LP ) {
    if ( Compound_statement() ) return true ;
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
  } // else if
  else if ( gToken[gNum].token_type == IF ) {

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( gToken[gNum].token_type == S_LP ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Expression() ) ; // 對的話 沒事幹 繼續執行
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;

      if ( gToken[gNum].token_type == S_RP ) {

        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        if ( Statement() ) {
          ;
        } // if 
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // else if
        else return false ;

        if ( !gAlready_Get && !GetToken( gGet_error ) ) return false ;  // 只有這幾個特別處理因為他在statement()後
        if ( !gAlready_Get ) {
          gNum ++ ;
        } // if 
        else gAlready_Get = false ;
 
        if ( gToken[gNum].token_type == ELSE ) {
          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;

          if ( Statement() ) return true ;
          else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
            // /////////////////////////////////////////////////////////////////////////////////////////////
            Unexpected_error() ;
            // /////////////////////////////////////////////////////////////////////////////////////////////
            return false ;
          } // else if
          else return false ;
        } // if 
        else {
          gAlready_Get = true ;
        } // else 

        return true ;
      } // if
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
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

  } // else if
  else if ( gToken[gNum].token_type == WHILE ) {

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( gToken[gNum].token_type == S_LP ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Expression() ) ; // 對的話 沒事幹 繼續執行
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;

      if ( gToken[gNum].token_type == S_RP ) {
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        if ( Statement() ) return true ;
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
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // else if
  else if ( gToken[gNum].token_type == DO ) {
    // exit( 0 ) ;
    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Statement() ) ;
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

    // 回來的會是右大括號 必須讀下一個token
    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( gToken[gNum].token_type == WHILE ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( gToken[gNum].token_type == S_LP ) {

        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        if ( Expression() ) ; // 對的話 沒事幹 繼續執行
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // else if
        else return false ;

        if ( gToken[gNum].token_type == S_RP ) {

          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;

          if ( gToken[gNum].token_type == SEMICOLON ) return true ; // 一定要接 分號
          else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
            // /////////////////////////////////////////////////////////////////////////////////////////////
            Unexpected_error() ;
            // /////////////////////////////////////////////////////////////////////////////////////////////
            return false ;
          } // else if
          else return false;

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
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // else if
  else if ( Expression() ) { // expression here should not be empty
    if ( gToken[gNum].token_type == SEMICOLON ) return true ;
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
  } // else if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  if ( !gHave_error ) return true ;
  else return false ;

} // Statement()

// =========================================================================================================

bool Expression() {


  if ( Basic_expression() ) {

    while ( !gHave_error && gToken[gNum].token_type == COMMA ) {
      if ( gHave_error ) return false ;

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Basic_expression() ) ;
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // ///////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // ///////////////////////////////////////////////////////////////////////////////////////////
        return false ; 
      } // else if
      else return false ;

    } // while

    if ( !gHave_error ) return true ;
    else return false ;

  } // if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////
    return false ; 
  } // else if
  else return false ;

} // Expression()

// =========================================================================================================

// cin '>>' ,  cout '<<' 應該只會進這裡 需要判斷他們有沒有接錯 operator
bool Basic_expression() {
  
  if ( gToken[gNum].token_type == IDENT ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
    else if ( gIs_Definition && gIs_function_Definition ) Variable_infuntion_have_defined() ; 
    // 在funtion內出現的ident不是出現在type_specifier()後就要檢查有沒有被定義
    // /////////////////////////////////////////////////////////////////////////////////////////////////////

    if ( gIs_Definition ) {
      Determine_variable_detail_type() ; // 在ident定義時判斷更詳細的變數型別
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;
    } // if
    else { // 只有在 << ( 後面的ident才有可能是assignment operator 其他都只是計算式 
      // 但是這個變數不能是 && || 與 布林運算 因為這些都是要印運算的結果而不是變數本身的值
      if ( gAfter_LS && gToken[gNum-2].token_type == S_LP && gToken[gNum].token_type != AND && 
           gToken[gNum].token_type != OR && !Boolean_operator( gNum ) &&
           gToken[gNum].token_type != M_LP ) { 
        gAfter_LS = false ;
        char string_or_char[500] = "" ;
        Temp_data_prepare_to_cout( gNum-1, true, false, false, false, false, 0, false, string_or_char ) ; 
      } // if

      if ( gToken[gNum].token_type != M_LP ) gAfter_LS = false ;

    } // else

    if ( Rest_of_Identifier_started_basic_exp() ) return true ;
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
  } // if
  else if ( gToken[gNum].token_type == PP || gToken[gNum].token_type == MM ) {

    // 這個 [ PP | MM ] 只有可能出現在下一個ident的'前'面 (立即運算)

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( gToken[gNum].token_type == IDENT ) {

      // ===================================================================================================

      int find = Find_variable_location_in_ALL_variables( gToken[gNum].data ) ;
      if ( find != -1 ) {
        if ( gALL_vari_Token[find].detail_type == INT || gALL_vari_Token[find].detail_type == FLOAT ) {

          int find = Find_variable_location_in_ALL_variables( gToken[gNum].data ) ;

          if ( gToken[gNum-1].token_type == PP ) {
            gALL_vari_Token[find].constant_value = gALL_vari_Token[find].constant_value + 1 ;
          } // if
          else {
            gALL_vari_Token[find].constant_value = gALL_vari_Token[find].constant_value - 1 ;
          } // else 

        } // if
      } // if

      // ===================================================================================================


      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
      else if ( gIs_function_Definition ) { // 在funtion中出現 剛剛又經歷過Type_specifier代表他要被定義
        gToken[gNum].vari_in_func_temp_defi = true ;
      } // else if
      // 在funtion內出現的ident不是出現在type_specifier()後就要檢查有沒有被定義
      // ///////////////////////////////////////////////////////////////////////////////////////////////////


      if ( gIs_Definition ) {
        Determine_variable_detail_type() ; // 在ident定義時判斷更詳細的變數型別
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;
      } // if

      if ( Rest_of_PPMM_Identifier_started_basic_exp() ) return true ;
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // ///////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // ///////////////////////////////////////////////////////////////////////////////////////////
        return false ; 
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
    
  } // else if
  else if ( Sign() ) {

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    while ( Sign() ) {
      if ( gHave_error ) return false ;

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

    } // while

    if ( Signed_unary_exp() ) {

      if ( Romce_and_romloe() ) return true ;
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
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

  } // else if
  else {
    if ( gToken[gNum].token_type == CONSTANT ) {
      // 一直遞迴下去吧~~~~如果這裡已經是分號了，一樣繼續遞迴下去
      // 會在Rest_of_maybe_mult_exp() 在一樣是分號回來

      // ===================================================================================================

      // 情況1 : 是一個statement的計算 把數值存入 gValue中方便計算
      // 情況2 : Cout中出現數字 但這個數字是用來計算的不用print ( 用是不是 << 直接接數字來判斷 )
      // 情況2 : 是一個準備Cout的數字 存入準備print的vector

      if ( gToken[gNum-1].token_type != M_LP ) { // 只有這個constant有加這一層for array不要多存一次value
        if ( gToken[gNum].detail_type == INT || gToken[gNum].detail_type == FLOAT ) {

          if ( !gIs_Definition && !gIs_function_Definition && !gIs_cout_operation ) {
            if ( gToken[gNum].detail_type == INT ) {
              gValue.push_back( atoi( gToken[gNum].data ) ) ;
            } // if
            else if ( gToken[gNum].detail_type == FLOAT ) {
              float a = atof( gToken[gNum].data ) ;
              gValue.push_back( atof( gToken[gNum].data ) ) ;
              gIs_float_operation = true ;
            } // else if
          } // if
          else if ( !gIs_Definition && !gIs_function_Definition && 
                    gIs_cout_operation && !gAfter_LS ) {
            if ( gToken[gNum].detail_type == INT ) {
              gValue.push_back( atoi( gToken[gNum].data ) ) ;
            } // if
            else if ( gToken[gNum].detail_type == FLOAT ) {
              gValue.push_back( atof( gToken[gNum].data ) ) ;
              gIs_float_operation = true ;
            } // else if
          } // else if
          else if ( !gIs_Definition && !gIs_function_Definition && 
                    gIs_cout_operation && gAfter_LS ) {
            gAfter_LS = false ;

            if ( gToken[gNum].detail_type == INT ) {
              gValue.push_back( atoi( gToken[gNum].data ) ) ;
              gIdent_operation = true ;
            } // if
            else if ( gToken[gNum].detail_type == FLOAT ) {
              gValue.push_back( atof( gToken[gNum].data ) ) ;
              gIs_float_operation = true ;
              gIdent_operation = true ;
            } // else if

          } // else if

        } // if
        else if ( gToken[gNum].detail_type == STRING || gToken[gNum].detail_type == CHAR ) {

          strcat( gString_value, gToken[gNum].data ) ;

        } // else if

      } // if

      // ===================================================================================================

      // ===================================================================================================
      // cin '>>' ,  cout '<<' 應該只會進這裡 需要判斷他們有沒有接錯 operator
      if ( gToken[gNum].detail_type == CIN ) {
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;
 
        if ( gToken[gNum].token_type != RS && !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // if

      } // if
      else if ( gToken[gNum].detail_type == COUT ) {

        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        gIs_cout_operation = true ; // 這次是cout運算 需要印出結果
 
        if ( gToken[gNum].token_type != LS && !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // if

      } // else if
      else {
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;
      } // else

      // ===================================================================================================

      if ( Romce_and_romloe() ) {
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
    else if ( gToken[gNum].token_type == S_LP ) {
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Expression() ) {
        if ( gToken[gNum].token_type == S_RP ) {
          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;

        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // else if
        else return false ;

        if ( Romce_and_romloe() ) return true ;
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
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
  // [ '[' expression ']' ] ( assignment_operator basic_expression | [ PP | MM ] romce_and_romloe ) 
  // | '(' [ actual_parameter_list ] ')' romce_and_romloe

  if ( gToken[gNum].token_type == M_LP || Assignment_operator() 
       || gToken[gNum].token_type == PP || gToken[gNum].token_type == MM ) {

    int temp_Num = gNum - 1 ;
    
    if ( gToken[gNum].token_type == M_LP ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Expression() ) {

        if ( gToken[gNum].token_type == M_RP ) {

          // ===============================================================================================
          // 這裡要做array 中括號的處理讓ident可以正確抓到是哪一個值ex. a[2] ;
          // 目前預設的是使用者一定是輸入 ident[constant] 而不是別的算式
          // 打算的作法是直接把ident改變

          strcat( gToken[temp_Num].data, "[" ) ;
          strcat( gToken[temp_Num].data, gToken[gNum-1].data ) ;
          strcat( gToken[temp_Num].data, "]" ) ;

          // 做好了新的ident之後就代替Undefined沒有取值的部分改成在這邊取

          int find = 0 ;
          find = Find_variable_location_in_ALL_variables( gToken[temp_Num].data ) ;

          if ( find != -1 ) {

            if ( gALL_vari_Token[find].detail_type == INT || gALL_vari_Token[find].detail_type == FLOAT ) {
              if ( gALL_vari_Token[find].detail_type == FLOAT ) gIs_float_operation = true ;

              // 前面有接負號的話就去把他的值找出來乘負號，再丟進去計算 ( 注意 並沒有實際改動該變數的值)
              if ( gToken[temp_Num-1].token_type == SIGN && gToken[temp_Num-1].detail_type == NEGATIVE ) { 
                int i = Find_variable_location_in_ALL_variables( gToken[temp_Num].data ) ;
                float num = ( -1 ) * gALL_vari_Token[i].constant_value ;
                gValue.push_back( num ) ;
              } // if
              else gValue.push_back( gALL_vari_Token[find].constant_value ) ;

            } // if
            else if ( gALL_vari_Token[find].detail_type == STRING || 
                      gALL_vari_Token[find].detail_type == CHAR ) {
              strcat( gString_value, gALL_vari_Token[find].string_value ) ;
            } // else if
            // 找到了就把值給取出來
            
          } // if

          // ===============================================================================================

          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;

          // 延續 << ( 接 ident 未完成的存取cout temp data繼續完成 for array的情況
          if ( gAfter_LS && gToken[gNum].token_type != AND && 
               gToken[gNum].token_type != OR && !Boolean_operator( gNum ) ) { 
            gAfter_LS = false ;
            char string_or_char[500] = "" ;
            Temp_data_prepare_to_cout( temp_Num, true, false, false, false, 
                                       false, 0, false, string_or_char ) ; 
          } // if

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
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;
    } // if

    if ( Assignment_operator() ) {

      // 這個if的功能是把下一個明明是接等於卻把值丟進去gValue中干擾計算的值丟掉
      if ( gToken[gNum].token_type == ONE_EQUAL && gToken[gNum-1].token_type == IDENT ) {
        
        if ( gToken[gNum-1].detail_type == INT || gToken[gNum-1].detail_type == FLOAT ) {
          if ( gValue.size() > 0 ) gValue.pop_back() ;
        } // if

      } // if

      // ===================================================================================================
      // 有經過 Assignment_operator() 只有可能是做賦值給ident的動作
      int fined_ident = gNum ;
      int assignment_location = gNum ;

      // 這裡要改 因為不是全部情況前面都不要
      strcpy( gString_value, "" ) ; // 經過assignment operator 就要把這個清空因為代表前面存的不要

      while ( gToken[fined_ident].token_type != IDENT ) {
        fined_ident = fined_ident - 1 ;
      } // while
      // ===================================================================================================

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Basic_expression() ) {
        // =================================================================================================
        // 做完計算 就可以賦值給ident了
        Assignment_calculator( fined_ident, assignment_location ) ;
        gHave_assignment = true ;
        // =================================================================================================
        return true ;
      } // if
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;

    } // if
    else if ( gToken[gNum].token_type == PP || gToken[gNum].token_type == MM ) {

      // 這個 [ PP | MM ] 只有可能來自於basic expression的ident後面
      
      // ===================================================================================================
      if ( gToken[gNum].token_type == PP ) gPPMM_after_ID_info.is_PP = true ;
      else gPPMM_after_ID_info.is_PP = false ;
      
      if ( gToken[gNum-1].token_type == M_RP ) {
        int num = gNum - 4 ;
        strcpy( gPPMM_after_ID_info.name, gToken[num].data ) ;
      } // if
      else strcpy( gPPMM_after_ID_info.name, gToken[gNum-1].data ) ;

      gPPMM_after_ID.push_back( gPPMM_after_ID_info ) ;
      // ===================================================================================================

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Romce_and_romloe() ) return true ;
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;
    } // else if
    else {
      if ( Romce_and_romloe() ) return true ;
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;
    } // else

  } // if
  else if ( gToken[gNum].token_type == S_LP ) {
    
    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;


    if ( gToken[gNum].token_type == S_RP ) {
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Romce_and_romloe() ) return true ;
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;
    } // if
    else if ( Actual_parameter_list() ) {

      if ( gToken[gNum].token_type == S_RP ) {
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        if ( Romce_and_romloe() ) return true ;
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
    } // else if 
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // else if 
  else { // 這裡可以當作是其他會跑進去的情況
    if ( Romce_and_romloe() ) return true ;
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
  } // else
  

  if ( !gHave_error ) return true ;
  else return false ;

} // Rest_of_Identifier_started_basic_exp()

// =========================================================================================================

bool Rest_of_PPMM_Identifier_started_basic_exp() {

  if ( gToken[gNum].token_type == M_LP ) {

    int temp_Num = gNum - 1 ;

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Expression() ) ;
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

    if ( gToken[gNum].token_type == M_RP ) {

      // ===============================================================================================
      // 這裡要做array 中括號的處理讓ident可以正確抓到是哪一個值ex. a[2] ;
      // 目前預設的是使用者一定是輸入 ident[constant] 而不是別的算式
      // 打算的作法是直接把ident改變

      int start = 0 ;
      if ( gValue.size() > 0 ) start =  gValue[gValue.size()-1] ;

      char str[30];
      str[0] = start + 48 ;
      strcat( gToken[temp_Num].data, "[" ) ;
      strcat( gToken[temp_Num].data, gToken[gNum-1].data ) ;
      strcat( gToken[temp_Num].data, "]" ) ;

      // 做好了新的ident之後就代替Undefined沒有取值的部分改成在這邊取

      int find = 0 ;
      find = Find_variable_location_in_ALL_variables( gToken[temp_Num].data ) ;

      if ( find != -1 ) {

        if ( gALL_vari_Token[find].detail_type == INT || gALL_vari_Token[find].detail_type == FLOAT ) {
          if ( gALL_vari_Token[find].detail_type == FLOAT ) gIs_float_operation = true ;

          // 前面有接負號的話就去把他的值找出來乘負號，再丟進去計算 ( 注意 並沒有實際改動該變數的值)
          if ( gToken[temp_Num-1].token_type == SIGN && gToken[temp_Num-1].detail_type == NEGATIVE ) { 
            int i = Find_variable_location_in_ALL_variables( gToken[temp_Num].data ) ;
            float num = ( -1 ) * gALL_vari_Token[i].constant_value ;
            gValue.push_back( num ) ;
          } // if
          else gValue.push_back( gALL_vari_Token[find].constant_value ) ;

        } // if
        else if ( gALL_vari_Token[find].detail_type == STRING || 
                  gALL_vari_Token[find].detail_type == CHAR ) {
          strcat( gString_value, gALL_vari_Token[find].string_value ) ;
        } // else if
        // 找到了就把值給取出來
        
      } // if

      // ===============================================================================================

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Romce_and_romloe() ) return true ;
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // ///////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
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
  } // if
  else if ( Romce_and_romloe() ) return true ;
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;
} // Rest_of_PPMM_Identifier_started_basic_exp()

// =========================================================================================================

bool Sign() { // 如果直接進sign的是plus 或是 sub 那很有可能是因為上一行有錯 變成sign的腳色

  if ( gToken[gNum].token_type == SIGN || gToken[gNum].token_type == SUB
       || gToken[gNum].token_type == PLUS ) return true ; // '+' '=' '!'
  else return false ;
} // Sign() 

// =========================================================================================================

bool Actual_parameter_list() {

  if ( Basic_expression() ) ;
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;
  
  while ( gToken[gNum].token_type == COMMA ) {
    if ( gHave_error ) return false ;

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Basic_expression() ) ; 
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while

  if ( !gHave_error ) return true ;
  else return false ;

} // Actual_parameter_list()

// =========================================================================================================

bool Assignment_operator() {

  if ( gToken[gNum].token_type == ONE_EQUAL || gToken[gNum].token_type == TE 
       || gToken[gNum].token_type == DE || gToken[gNum].token_type == RE 
       || gToken[gNum].token_type == PE || gToken[gNum].token_type == ME ) return true ;
  else return false ; 
} // Assignment_operator()

// =========================================================================================================

bool Romce_and_romloe() {

  if ( Rest_of_maybe_logical_OR_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  if ( gToken[gNum].token_type == QUESTION ) {
    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Basic_expression() ) ;
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

    if ( gToken[gNum].token_type == COLON ) {
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;
      if ( Basic_expression() ) return true ;
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
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
  } // if

  if ( !gHave_error ) return true ;
  else return false ;


} // Romce_and_romloe()

// =========================================================================================================

bool Rest_of_maybe_logical_OR_exp() {

  if ( Rest_of_maybe_logical_AND_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == OR ) {
    if ( gHave_error ) return false ;

    // =====================================================================================================

    int temp_gNum = gNum ; // 先把布林符號的位置存起來

    gIs_Bool_operation = true ;

    bool value1 = false ;
    int find1 = 0 ;
    find1 = Find_variable_location_in_ALL_variables( gToken[gNum-1].data ) ;

    if ( gToken[gNum-2].token_type != S_LP && !Boolean_operator( gNum-2 ) && gBool_Ans.size() > 0 ) {
      value1 = gBool_Ans[ gBool_Ans.size() - 1 ] ; // 布林前計算的值先存起來
    } // if
    else if ( find1 != -1 && gALL_vari_Token[find1].detail_type == BOOL ) {
      value1 = gALL_vari_Token[find1].bool_value ; // 布林前計算的值先存起來
    } // else if
    else if ( gToken[gNum-1].detail_type == TRUE || gToken[gNum-1].detail_type == FALSE ) {

      if ( gToken[gNum-1].detail_type == TRUE ) { // 0是false,非0是true
        value1 = true ;
      } // if
      else value1 = false ;

    } // else if
    else if ( find1 != -1 ) {
      if ( gALL_vari_Token[find1].detail_type == INT || gALL_vari_Token[find1].detail_type == FLOAT ) {

        if ( gValue[gValue.size()-1] == 0 ) { // 0是false,非0是true
          value1 = false ;
        } // if
        else value1 = true ;

      } // if
    } // else if 

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Maybe_logical_AND_exp() ) {

      bool value2 = false ;

      // 這裡有分成後面直接接布林變數來判斷 
      // 或是有可能是計算一大串然後得到的結果再判斷
      // 或是有可能直接接一個數字
      // 或是 a && b && c 都是布林

      int find2 = 0 ;
      if ( gToken[temp_gNum+1].detail_type == E_MARK ) {
        find2 = Find_variable_location_in_ALL_variables( gToken[temp_gNum+2].data ) ;
      } // if
      else if ( gToken[temp_gNum+1].token_type == IDENT ) {
        find2 = Find_variable_location_in_ALL_variables( gToken[temp_gNum+1].data ) ;
      } // else if

      if ( gBool_Ans.size() > 0 ) { // 代表後面的算式 是一連串的的布林運算

        int a = gNum ;
        while ( a > 0 && gToken[a].token_type != LS && gToken[a].detail_type != E_MARK ) {

          if ( gToken[a].detail_type == E_MARK ) {

            if ( gBool_Ans[gBool_Ans.size()-1] == true ) {
              gBool_Ans[gBool_Ans.size()-1] = false ;
            } // if
            else if ( gBool_Ans[gBool_Ans.size()-1] == false ) {
              gBool_Ans[gBool_Ans.size()-1] = true ;
            } // else if

            a ++ ;

          } // if

          a -- ;
        } // while

        value2 = gBool_Ans[gBool_Ans.size()-1] ;
        gBool_Ans.pop_back() ;
      } // if
      else { // 代表後面接單獨的ident或數字
      
        if ( find2 != -1 && gALL_vari_Token[find2].detail_type == BOOL ) { // 這個ident是布林就把值撈出來
          value2 = gALL_vari_Token[find2].bool_value ; 

          // Signed_Unary_exp 有因為驚嘆號改過值 現在把他改回來 這邊都預設!後面整串只會接一個變數才這麼處理
          int a = gNum ;

          while ( a > 0 && gToken[a].token_type != LS ) {

            if ( gToken[a].detail_type == E_MARK ) {
              int find = Find_variable_location_in_ALL_variables( gToken[a+1].data ) ;
              if ( find != -1 && gALL_vari_Token[find].detail_type == BOOL ) {
                if ( gALL_vari_Token[find].bool_value == true ) {
                  gALL_vari_Token[find].bool_value = false ;
                } // if
                else if ( gALL_vari_Token[find].bool_value == false ) {
                  gALL_vari_Token[find].bool_value = true ;
                } // else if
              } // if 
            } // if

            a -- ;
          } // while

        } // if
        else if ( gToken[gNum-1].detail_type == TRUE || gToken[gNum-1].detail_type == FALSE ) {

          if ( gToken[gNum-1].detail_type == TRUE ) { // 0是false,非0是true
            value2 = true ;
          } // if
          else value2 = false ;

        } // else if
        else if ( gValue.size() > 0 ) { // 他是其他計算

          if ( gValue[gValue.size()-1] == 0 ) { // 0是false,非0是true
            value2 = false ;
          } // if
          else value2 = true ;

        } // else if

      } // else

      if ( value1 || value2 ) {
        gBool_Ans.push_back( true ) ;
      } // if
      else {
        gBool_Ans.push_back( false ) ;
      } // else 

      // ===================================================================================================

    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while

  if ( !gHave_error ) return true ;
  else return false ;

} // Rest_of_maybe_logical_OR_exp()

// =========================================================================================================

bool Maybe_logical_AND_exp() {

  if ( Maybe_bit_OR_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == AND ) {

    if ( gHave_error ) return false ;

    // =====================================================================================================

    int temp_gNum = gNum ; // 先把布林符號的位置存起來

    gIs_Bool_operation = true ;

    bool value1 = false ;
    int find1 = 0 ;
    find1 = Find_variable_location_in_ALL_variables( gToken[gNum-1].data ) ;

    if ( gToken[gNum-2].token_type != S_LP && !Boolean_operator( gNum-2 ) && gBool_Ans.size() > 0 ) {
      value1 = gBool_Ans[ gBool_Ans.size() - 1 ] ; // 布林前計算的值先存起來
    } // if
    else if ( find1 != -1 && gALL_vari_Token[find1].detail_type == BOOL ) {
      value1 = gALL_vari_Token[find1].bool_value ; // 布林前計算的值先存起來
    } // else if
    else if ( gToken[gNum-1].detail_type == TRUE || gToken[gNum-1].detail_type == FALSE ) {

      if ( gToken[gNum-1].detail_type == TRUE ) { // 0是false,非0是true
        value1 = true ;
      } // if
      else value1 = false ;

    } // else if
    else if ( find1 != -1 ) {
      if ( gALL_vari_Token[find1].detail_type == INT || gALL_vari_Token[find1].detail_type == FLOAT ) {

        if ( gValue[gValue.size()-1] == 0 ) { // 0是false,非0是true
          value1 = false ;
        } // if
        else value1 = true ;

      } // if
    } // else if 

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Maybe_bit_OR_exp() ) {

      bool value2 = false ;

      // 這裡有分成後面直接接布林變數來判斷 
      // 或是有可能是計算一大串然後得到的結果再判斷
      // 或是有可能直接接一個數字
      // 或是 a && b && c 都是布林
      int find2 = 0 ;
      if ( gToken[temp_gNum+1].detail_type == E_MARK ) {
        find2 = Find_variable_location_in_ALL_variables( gToken[temp_gNum+2].data ) ;
      } // if
      else if ( gToken[temp_gNum+1].token_type == IDENT ) {
        find2 = Find_variable_location_in_ALL_variables( gToken[temp_gNum+1].data ) ;
      } // else if 

      if ( gBool_Ans.size() > 0 ) { // 代表後面的算式 是一連串的的布林運算

        int a = gNum ;
        while ( a > 0 && gToken[a].token_type != LS && gToken[a].detail_type != E_MARK ) {

          if ( gToken[a].detail_type == E_MARK ) {

            if ( gBool_Ans[gBool_Ans.size()-1] == true ) {
              gBool_Ans[gBool_Ans.size()-1] = false ;
            } // if
            else if ( gBool_Ans[gBool_Ans.size()-1] == false ) {
              gBool_Ans[gBool_Ans.size()-1] = true ;
            } // else if

            a ++ ;

          } // if

          a -- ;
        } // while

        value2 = gBool_Ans[gBool_Ans.size()-1] ;
        gBool_Ans.pop_back() ;
      } // if
      else if ( gToken[gNum-1].detail_type == TRUE || gToken[gNum-1].detail_type == FALSE ) {

        if ( gToken[gNum-1].detail_type == TRUE ) { // 0是false,非0是true
          value2 = true ;
        } // if
        else value2 = false ;

      } // else if
      else { // 代表後面接單獨的ident或數字
        if ( find2 != -1 && gALL_vari_Token[find2].detail_type == BOOL ) { // 這個ident是布林就把值撈出來
          value2 = gALL_vari_Token[find2].bool_value ; 

          // Signed_Unary_exp 有因為驚嘆號改過值 現在把他改回來 這邊都預設!後面整串只會接一個變數才這麼處理
          int a = gNum ;

          while ( a > 0 && gToken[a].token_type != LS ) {

            if ( gToken[a].detail_type == E_MARK ) {
              int find = Find_variable_location_in_ALL_variables( gToken[a+1].data ) ;
              if ( find != -1 && gALL_vari_Token[find].detail_type == BOOL ) {
                if ( gALL_vari_Token[find].bool_value == true ) {
                  gALL_vari_Token[find].bool_value = false ;
                } // if
                else if ( gALL_vari_Token[find].bool_value == false ) {
                  gALL_vari_Token[find].bool_value = true ;
                } // else if
              } // if 
            } // if

            a -- ;
          } // while

        } // if
        else if ( gValue.size() > 0 ) { // 他是其他計算

          if ( gValue[gValue.size()-1] == 0 ) { // 0是false,非0是true
            value2 = false ;
          } // if
          else value2 = true ;

        } // else if

      } // else

      if ( value1 && value2 ) {
        gBool_Ans.push_back( true ) ;
      } // if
      else {
        gBool_Ans.push_back( false ) ;
      } // else 

      // ===================================================================================================

    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
  } // while

  if ( !gHave_error ) return true ;
  else return false ;

} // Maybe_logical_AND_exp()

// =========================================================================================================

bool Rest_of_maybe_logical_AND_exp() {

  if ( Rest_of_maybe_bit_OR_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == AND ) {

    if ( gHave_error ) return false ;

    // =====================================================================================================

    int temp_gNum = gNum ; // 先把布林符號的位置存起來

    gIs_Bool_operation = true ;

    bool value1 = false ;
    int find1 = 0 ;
    find1 = Find_variable_location_in_ALL_variables( gToken[gNum-1].data ) ;

    if ( gToken[gNum-2].token_type != S_LP && !Boolean_operator( gNum-2 ) && gBool_Ans.size() > 0 ) {
      value1 = gBool_Ans[ gBool_Ans.size() - 1 ] ; // 布林前計算的值先存起來
    } // if
    else if ( find1 != -1 && gALL_vari_Token[find1].detail_type == BOOL ) {
      value1 = gALL_vari_Token[find1].bool_value ; // 布林前計算的值先存起來
    } // else if
    else if ( gToken[gNum-1].detail_type == TRUE || gToken[gNum-1].detail_type == FALSE ) {

      if ( gToken[gNum-1].detail_type == TRUE ) { // 0是false,非0是true
        value1 = true ;
      } // if
      else value1 = false ;

    } // else if
    else if ( find1 != -1 ) {
      if ( gALL_vari_Token[find1].detail_type == INT || gALL_vari_Token[find1].detail_type == FLOAT ) {

        if ( gValue[gValue.size()-1] == 0 ) { // 0是false,非0是true
          value1 = false ;
        } // if
        else value1 = true ;

      } // if
    } // else if 


    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Maybe_bit_OR_exp() ) {

      bool value2 = false ;

      // 這裡有分成後面直接接布林變數來判斷 
      // 或是有可能是計算一大串然後得到的結果再判斷
      // 或是有可能直接接一個數字
      // 或是 a && b && c 都是布林
      int find2 = -1 ;
      if ( gToken[temp_gNum+1].detail_type == E_MARK ) {
        find2 = Find_variable_location_in_ALL_variables( gToken[temp_gNum+2].data ) ;
      } // if
      else if ( gToken[temp_gNum+1].token_type == IDENT ) {
        find2 = Find_variable_location_in_ALL_variables( gToken[temp_gNum+1].data ) ;
      } // else if

      if ( gBool_Ans.size() > 0 ) { // 代表後面的算式 是一連串的的布林運算

        int a = gNum ;
        while ( a > 0 && gToken[a].token_type != LS && gToken[a].detail_type != E_MARK ) {

          if ( gToken[a].detail_type == E_MARK ) {

            if ( gBool_Ans[gBool_Ans.size()-1] == true ) {
              gBool_Ans[gBool_Ans.size()-1] = false ;
            } // if
            else if ( gBool_Ans[gBool_Ans.size()-1] == false ) {
              gBool_Ans[gBool_Ans.size()-1] = true ;
            } // else if

            a ++ ;

          } // if

          a -- ;
        } // while

        value2 = gBool_Ans[gBool_Ans.size()-1] ;
        gBool_Ans.pop_back() ;
      } // if
      else { // 代表後面接單獨的ident或數字
        if ( find2 != -1 && gALL_vari_Token[find2].detail_type == BOOL ) { // 這個ident是布林就把值撈出來

          value2 = gALL_vari_Token[find2].bool_value ; 

          // Signed_Unary_exp 有因為驚嘆號改過值 現在把他改回來 這邊都預設!後面整串只會接一個變數才這麼處理
          int a = gNum ;

          while ( a > 0 && gToken[a].token_type != LS ) {

            if ( gToken[a].detail_type == E_MARK ) {
              int find = Find_variable_location_in_ALL_variables( gToken[a+1].data ) ;
              if ( find != -1 && gALL_vari_Token[find].detail_type == BOOL ) {
                if ( gALL_vari_Token[find].bool_value == true ) {
                  gALL_vari_Token[find].bool_value = false ;
                } // if
                else if ( gALL_vari_Token[find].bool_value == false ) {
                  gALL_vari_Token[find].bool_value = true ;
                } // else if
              } // if 
            } // if

            a -- ;
          } // while

        } // if
        else if ( gToken[gNum-1].detail_type == TRUE || gToken[gNum-1].detail_type == FALSE ) {

          if ( gToken[gNum-1].detail_type == TRUE ) { // 0是false,非0是true
            value2 = true ;
          } // if
          else value2 = false ;

        } // else if
        else if ( gValue.size() > 0 ) { // 他是其他計算

          if ( gValue[gValue.size()-1] == 0 ) { // 0是false,非0是true
            value2 = false ;
          } // if
          else value2 = true ;

        } // else if

      } // else

      if ( value1 && value2 ) {
        gBool_Ans.push_back( true ) ;
      } // if
      else {
        gBool_Ans.push_back( false ) ;
      } // else 

      // ===================================================================================================

    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while

  if ( !gHave_error ) return true ;
  else return false ;
} // Rest_of_maybe_logical_AND_exp()

// =========================================================================================================

bool Maybe_bit_OR_exp() {

  if ( Maybe_bit_ex_OR_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == STRAIGHT ) {
    // exit( 0 ) ; 不是這
    if ( gHave_error ) return false ;

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Maybe_bit_ex_OR_exp() ) ; 
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while

  if ( !gHave_error ) return true ;
  else return false ;
} // Maybe_bit_OR_exp()

// =========================================================================================================

bool Rest_of_maybe_bit_OR_exp() {

  if ( Rest_of_maybe_bit_ex_OR_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == STRAIGHT ) {
    // exit( 0 ) ; 不是這
    if ( gHave_error ) return false ;

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Maybe_bit_ex_OR_exp() ) ; 
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while

  if ( !gHave_error ) return true ;
  else return false ;
} // Rest_of_maybe_bit_OR_exp()

// =========================================================================================================

bool Maybe_bit_ex_OR_exp() {

  if ( Maybe_bit_AND_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == HAT ) {
    // exit( 0 ) ; 不是這
    if ( gHave_error ) return false ;

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Maybe_bit_AND_exp() ) ; 
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while

  if ( !gHave_error ) return true ;
  else return false ;
} // Maybe_bit_ex_OR_exp()

// =========================================================================================================

bool Rest_of_maybe_bit_ex_OR_exp() {

  if ( Rest_of_maybe_bit_AND_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == HAT ) {
    // exit( 0 ) ; 不是這
    if ( gHave_error ) return false ;

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Maybe_bit_AND_exp() ) ; 
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while

  if ( !gHave_error ) return true ;
  else return false ;
} // Rest_of_maybe_bit_ex_OR_exp()

// =========================================================================================================

bool Maybe_bit_AND_exp() {
 
  if ( Maybe_equality_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == ONE_AND ) {
    // exit( 0 ) ; 不是這
    if ( gHave_error ) return false ;

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Maybe_equality_exp() ) ; 
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while

  if ( !gHave_error ) return true ;
  else return false ;
} // Maybe_bit_AND_exp()

// =========================================================================================================

bool Rest_of_maybe_bit_AND_exp() {

  if ( Rest_of_maybe_equality_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == ONE_AND ) {
    // exit( 0 ) ; 不是這
    if ( gHave_error ) return false ;

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( Maybe_equality_exp() ) ; 
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while
  
  if ( !gHave_error ) return true ;
  else return false ;
} // Rest_of_maybe_bit_AND_exp()

// =========================================================================================================

bool Maybe_equality_exp() {

  if ( Maybe_relational_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == EQUAL || gToken[gNum].token_type == NOT_EQUAL ) {
    if ( gHave_error ) return false ;

    int temp_gNum = gNum ; // 先把布林符號的位置存起來

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    // =====================================================================================================
    gIs_Bool_operation = true ;

    float value1 = 0.0 ;
    if ( gValue.size() > 0 ) value1 = gValue[gValue.size()-1] ; // 布林前計算的值先存起來
    else {
      printf( "you input error with not int or float but equal and not equal\n " ) ;
      return false ;
    } // else

    if ( Maybe_relational_exp() ) {

      float value2 = 0.0 ;
      if ( gValue.size() > 0 ) value2 = gValue[gValue.size()-1] ; // 布林後面的計算再存起來
      else return false ;

      float console = value1 - value2 ; // 用來確保差距大於0.0001

      if ( gToken[temp_gNum].token_type == EQUAL && -0.0001 <= console && console <= 0.0001
           && !gHave_error ) {
        gBool_Ans.push_back( true ) ;
      } // if
      else if ( gToken[temp_gNum].token_type == EQUAL && !gHave_error ) {
        if ( 0.0001 < console || console < -0.0001 ) gBool_Ans.push_back( false ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == NOT_EQUAL && !gHave_error ) {

        if ( 0.0001 < console || console < -0.0001 ) {
          gBool_Ans.push_back( true ) ;
        } // if
        else if ( -0.0001 <= console && console <= 0.0001 ) {
          gBool_Ans.push_back( false ) ;
        } // else if

      } // else if

      // ===================================================================================================

    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while
  
  if ( !gHave_error ) return true ;
  else return false ;
} // Maybe_equality_exp()

// =========================================================================================================

bool Rest_of_maybe_equality_exp() {

  if ( Rest_of_maybe_relational_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == EQUAL || gToken[gNum].token_type == NOT_EQUAL ) {
    if ( gHave_error ) return false ;

    int temp_gNum = gNum ; // 先把布林符號的位置存起來

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    // =====================================================================================================
    gIs_Bool_operation = true ;

    float value1 = 0.0 ;
    if ( gValue.size() > 0 ) value1 = gValue[gValue.size()-1] ; // 布林前計算的值先存起來
    else {
      printf( "you input error with not int or float but equal and not equal\n " ) ;
      return false ;
    } // else

    if ( Maybe_relational_exp() ) {

      float value2 = 0.0 ;
      if ( gValue.size() > 0 ) value2 = gValue[gValue.size()-1] ; // 布林後面的計算再存起來
      else return false ;

      float console = value1 - value2 ; // 用來確保差距大於0.0001

      if ( gToken[temp_gNum].token_type == EQUAL && -0.0001 <= console && console <= 0.0001
           && !gHave_error ) {
        gBool_Ans.push_back( true ) ;
      } // if
      else if ( gToken[temp_gNum].token_type == EQUAL && !gHave_error ) {
        if ( 0.0001 < console || console < -0.0001 ) gBool_Ans.push_back( false ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == NOT_EQUAL && !gHave_error ) {

        if ( 0.0001 < console || console < -0.0001 ) {
          gBool_Ans.push_back( true ) ;
        } // if
        else if ( -0.0001 <= console && console <= 0.0001 ) {
          gBool_Ans.push_back( false ) ;
        } // else if

      } // else if

      // ===================================================================================================

    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while
  
  if ( !gHave_error ) return true ;
  else return false ;
} // Rest_of_maybe_equality_exp()

// =========================================================================================================

bool Maybe_relational_exp() {

  if ( Maybe_shift_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == SMALLER_EQ || gToken[gNum].token_type == BIGGGER_EQ
          || gToken[gNum].token_type == SMALLER || gToken[gNum].token_type == BIGGER ) {
    if ( gHave_error ) return false ;

    int temp_gNum = gNum ; // 先把布林符號的位置存起來

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    // =====================================================================================================
    gIs_Bool_operation = true ;

    float value1 = 0.0 ;
    if ( gValue.size() > 0 ) value1 = gValue[gValue.size()-1] ; // 布林前計算的值先存起來
    else return false ;

    if ( Maybe_shift_exp() ) {

      float value2 = 0.0 ;
      if ( gValue.size() > 0 ) value2 = gValue[gValue.size()-1] ; // 布林後面的計算再存起來
      else return false ;

      float console = value1 - value2 ; // 用來確保差距大於0.0001

      if ( gToken[temp_gNum].token_type == BIGGER && console > 0.0001 && !gHave_error ) {
        gBool_Ans.push_back( true ) ;
      } // if
      else if ( gToken[temp_gNum].token_type == BIGGER && console <= 0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( false ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console >= -0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( true ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console < -0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( false ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == SMALLER && console < -0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( true ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == SMALLER && console >= -0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( false ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console <= 0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( true ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console > 0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( false ) ;
      } // else if

      // ===================================================================================================


    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while
  
  if ( !gHave_error ) return true ;
  else return false ;
} // Maybe_relational_exp()

// =========================================================================================================

bool Rest_of_maybe_relational_exp() {

  if ( Rest_of_maybe_shift_exp() ) {
    ; // 沒事幹
  } // if
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ; 

  while ( gToken[gNum].token_type == SMALLER_EQ || gToken[gNum].token_type == BIGGGER_EQ
          || gToken[gNum].token_type == SMALLER || gToken[gNum].token_type == BIGGER ) {

    if ( gHave_error ) return false ;

    int temp_gNum = gNum ; // 先把布林符號的位置存起來

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    // =====================================================================================================
    gIs_Bool_operation = true ;

    float value1 = 0.0 ;
    if ( gValue.size() > 0 ) value1 = gValue[gValue.size()-1] ; // 布林前計算的值先存起來
    else return false ;

    if ( Maybe_shift_exp() ) {

      float value2 = 0.0 ;
      if ( gValue.size() > 0 ) value2 = gValue[gValue.size()-1] ; // 布林後面的計算再存起來
      else return false ;

      float console = value1 - value2 ; // 用來確保差距大於0.0001

      if ( gToken[temp_gNum].token_type == BIGGER && console > 0.0001 && !gHave_error ) {
        gBool_Ans.push_back( true ) ;
      } // if
      else if ( gToken[temp_gNum].token_type == BIGGER && console <= 0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( false ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console >= -0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( true ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console < -0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( false ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == SMALLER && console < -0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( true ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == SMALLER && console >= -0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( false ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console <= 0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( true ) ;
      } // else if
      else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console > 0.0001 && !gHave_error  ) {
        gBool_Ans.push_back( false ) ;
      } // else if

      // ===================================================================================================


    } // if 
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while
  
  if ( !gHave_error ) return true ;
  else return false ;

} // Rest_of_maybe_relational_exp()

// =========================================================================================================

bool Maybe_shift_exp() {

  if ( Maybe_additive_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == LS || gToken[gNum].token_type == RS ) {
    if ( gHave_error ) return false ;

    if ( gIs_cout_operation && gToken[gNum].token_type == RS && !gIn_expresstion && !gHave_error ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // if

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    gAfter_LS = true ;

    if ( gIn_expresstion ) {

      if ( gToken[gNum-1].token_type == LS ) {

        int output = gValue[gValue.size()-1] ;

        gValue[gValue.size()-1] = output << atoi( gToken[gNum].data ) ;

        gIs_shifter_constant = true ; // 目前的token 數字是移動多少格不要加入gValue故先紀錄起來

      } // if
      else if ( gToken[gNum-1].token_type == RS ) {

        int output = gValue[gValue.size()-1] ;

        gValue[gValue.size()-1] = output >> atoi( gToken[gNum].data ) ;

        // if ( 0 >  gValue[gValue.size()-1] > -1024 ) 
        // gValue[gValue.size()-1] = gValue[gValue.size()-1] - 1 ;

        gIs_shifter_constant = true ; // 目前的token 數字是移動多少格不要加入gValue故先紀錄起來

      } // else if

      gAfter_LS = false ;

    } // if

    if ( Maybe_additive_exp() ) {
      
      if ( gIdent_operation && !gIs_Bool_operation && !gIs_string_operation ) {
        gIdent_operation = false ;
        if ( gIs_float_operation ) {
          char string_or_char[500] = "" ;
          Temp_data_prepare_to_cout( 0, false, false, false, true, false, 
                                     gValue[0], false, string_or_char ) ;
        } // if
        else {
          int find = -1 ; // ex. cout << bool1 ;
          find = Find_variable_location_in_ALL_variables( gToken[gNum-1].data ) ;

          if ( find != -1 && gALL_vari_Token[find].detail_type == BOOL ) {
            char string_or_char[500] = "" ;
            Temp_data_prepare_to_cout( gNum-1, true, false, false, false, false, 
                                       0, false, string_or_char ) ;
          } // if
          else if ( find != -1 && gALL_vari_Token[find].detail_type == STRING ) {
            char string_or_char[500] = "" ;
            Temp_data_prepare_to_cout( gNum-1, true, false, false, false, false, 
                                       0, false, string_or_char ) ;
          } // else if
          else {
            char string_or_char[500] = "" ;
            Temp_data_prepare_to_cout( 0, false, false, true, false, false, 
                                       gValue[0], false, string_or_char ) ;
          } // else

        } // else

        gValue.clear() ;

      } // if

      gIdent_operation = false ;
      
      if ( gIs_Bool_operation && !gIdent_operation && !gIs_string_operation ) {
        gIs_Bool_operation = false ;
        char string_or_char[500] = "" ;
        Temp_data_prepare_to_cout( 0, false, false, false, false, true, 
                                   0, gBool_Ans[0], string_or_char ) ;
      } // if

      gIs_Bool_operation = false ;

      if ( !gIs_Bool_operation && !gIdent_operation && gIs_string_operation ) {
        gIs_string_operation = false ;
        char string_or_char[500] = "" ;
        strcpy( string_or_char, gString_value ) ;
        Temp_data_prepare_to_cout( 0, false, true, false, false, false, 
                                   0, false, string_or_char ) ;
      } // if

      gIs_string_operation = false ;
      strcpy( gString_value, "" ) ; // 每次 '<<' 後都要初始化

      gHave_assignment = false ;

    } // if 
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while
  
  if ( !gHave_error ) return true ;
  else return false ;
} // Maybe_shift_exp()

// =========================================================================================================

bool Rest_of_maybe_shift_exp() {

  if ( Rest_of_maybe_additive_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == LS || gToken[gNum].token_type == RS ) {

    if ( gHave_error ) return false ;

    if ( gIs_cout_operation && gToken[gNum].token_type == RS && !gIn_expresstion && !gHave_error ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // if

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    gAfter_LS = true ;

    if ( gIn_expresstion ) { // 如果在cout (expression)中出現LS or RS代表他是單純的shifter符號

      if ( gToken[gNum-1].token_type == LS ) {

        int output = gValue[gValue.size()-1] ;

        gValue[gValue.size()-1] = output << atoi( gToken[gNum].data ) ;

        gIs_shifter_constant = true ; // 目前的token 數字是移動多少格不要加入gValue故先紀錄起來

      } // if
      else if ( gToken[gNum-1].token_type == RS ) {

        int output = gValue[gValue.size()-1] ;

        gValue[gValue.size()-1] = output >> atoi( gToken[gNum].data ) ;

        gIs_shifter_constant = true ; // 目前的token 數字是移動多少格不要加入gValue故先紀錄起來

      } // else if

      gAfter_LS = false ;

    } // if

    if ( Maybe_additive_exp() ) {

      if ( gIdent_operation && !gIs_Bool_operation && !gIs_string_operation ) {
        gIdent_operation = false ;
        if ( gIs_float_operation ) {
          char string_or_char[500] = "" ;
          Temp_data_prepare_to_cout( 0, false, false, false, true, false, 
                                     gValue[ gValue.size() - 1 ], false, string_or_char ) ;
        } // if
        else {
          int find = -1 ; // ex. cout << bool1 ;
          find = Find_variable_location_in_ALL_variables( gToken[gNum-1].data ) ;

          if ( find != -1 && gALL_vari_Token[find].detail_type == BOOL ) {
            char string_or_char[500] = "" ;
            Temp_data_prepare_to_cout( gNum-1, true, false, false, false, false, 
                                       0, false, string_or_char ) ;
          } // if
          else if ( find != -1 && gALL_vari_Token[find].detail_type == STRING ) {
            char string_or_char[500] = "" ;
            Temp_data_prepare_to_cout( gNum-1, true, false, false, false, false, 
                                       0, false, string_or_char ) ;
          } // else if
          else {
            char string_or_char[500] = "" ;
            Temp_data_prepare_to_cout( 0, false, false, true, false, false, 
                                       gValue[ gValue.size() - 1 ], false, string_or_char ) ;
          } // else

        } // else

        gValue.clear() ;

      } // if

      gIdent_operation = false ;
      
      if ( gIs_Bool_operation && !gIdent_operation && !gIs_string_operation ) {
        gIs_Bool_operation = false ;
        char string_or_char[500] = "" ;
        Temp_data_prepare_to_cout( 0, false, false, false, false, true, 
                                   0, gBool_Ans[0], string_or_char ) ;
      } // if

      gIs_Bool_operation = false ;

      if ( !gIs_Bool_operation && !gIdent_operation && gIs_string_operation ) {
        gIs_string_operation = false ;
        char string_or_char[500] = "" ;
        strcpy( string_or_char, gString_value ) ;
        Temp_data_prepare_to_cout( 0, false, true, false, false, false, 
                                   0, false, string_or_char ) ;
      } // if

      gIs_string_operation = false ;
      strcpy( gString_value, "" ) ; // 每次 '<<' 後都要初始化

      gHave_assignment = false ;


    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

  } // while
  
  if ( !gHave_error ) return true ;
  else return false ;
} // Rest_of_maybe_shift_exp()

// =========================================================================================================

// + - 運算 有可能為一般數字計算 string計算僅有可能為加法運算在Undefined那邊做
bool Maybe_additive_exp() {

  if ( Maybe_mult_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == PLUS || gToken[gNum].token_type == SUB ) {

    if ( gToken[gNum].token_type == PLUS ) {

      if ( gHave_error ) return false ;

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Maybe_mult_exp() ) { // 應該是在這邊做計算
        if ( gValue.size() >= 2 ) {
          if ( !gIs_float_operation ) {
            int value1 = gValue[gValue.size() - 2] ;
            int value2 = gValue[gValue.size() - 1] ;

            gTemp_value = value1 + value2;

          } // if
          else gTemp_value = gValue[gValue.size() - 2] + gValue[gValue.size() - 1];
          // 應該是倒數第二個加最後一個再繼續遞迴
          gValue.pop_back(); // 算完就丟掉
          gValue.pop_back(); // 算完就丟掉
          gValue.push_back( gTemp_value ); // 加入算好的值
        } // if
      } // if 
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;

    } // if
    else if ( gToken[gNum].token_type == SUB ) {

      if ( gHave_error ) return false ;

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Maybe_mult_exp() ) { // 應該是在這邊做計算
        if ( gValue.size() >= 2 ) {
          if ( !gIs_float_operation ) {
            int value1 = gValue[gValue.size() - 2] ;
            int value2 = gValue[gValue.size() - 1] ;

            gTemp_value = value1 - value2;

          } // if
          else gTemp_value = gValue[gValue.size() - 2] - gValue[gValue.size() - 1];
          // 應該是倒數第二個加最後一個再繼續遞迴
          gValue.pop_back(); // 算完就丟掉
          gValue.pop_back(); // 算完就丟掉
          gValue.push_back( gTemp_value ); // 加入算好的值
        } // if
      } // if 
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;

    } // else if

  } // while
  
  if ( !gHave_error ) return true ;
  else return false ;
} // Maybe_additive_exp()

// =========================================================================================================

// + - 運算 有可能為一般數字計算 string計算僅有可能為加法運算在Undefined那邊做
bool Rest_of_maybe_additive_exp() {

  if ( Rest_of_maybe_mult_exp() ) {
    ; // 沒事幹
  } // if 
  else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

  while ( gToken[gNum].token_type == PLUS || gToken[gNum].token_type == SUB ) {

    if ( gToken[gNum].token_type == PLUS ) {

      if ( gHave_error ) return false ;

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Maybe_mult_exp() ) { // 應該是在這邊做計算

        if ( gValue.size() >= 2 ) {
          if ( !gIs_float_operation ) {
            int value1 = gValue[gValue.size() - 2] ;
            int value2 = gValue[gValue.size() - 1] ;

            gTemp_value = value1 + value2;

          } // if
          else gTemp_value = gValue[gValue.size() - 2] + gValue[gValue.size() - 1];
          // 應該是倒數第二個加最後一個再繼續遞迴
          gValue.pop_back(); // 算完就丟掉
          gValue.pop_back(); // 算完就丟掉
          gValue.push_back( gTemp_value ); // 加入算好的值
        } // if

      } // if 
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;

    } // if
    else if ( gToken[gNum].token_type == SUB ) {

      if ( gHave_error ) return false ;

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Maybe_mult_exp() ) { // 應該是在這邊做計算

        if ( gValue.size() >= 2 ) {
          if ( !gIs_float_operation ) {
            int value1 = gValue[gValue.size() - 2] ;
            int value2 = gValue[gValue.size() - 1] ;

            gTemp_value = value1 - value2;

          } // if
          else gTemp_value = gValue[gValue.size() - 2] - gValue[gValue.size() - 1];

          // 應該是倒數第二個加最後一個再繼續遞迴
          gValue.pop_back(); // 算完就丟掉
          gValue.pop_back(); // 算完就丟掉
          gValue.push_back( gTemp_value ); // 加入算好的值
        } // if
      } // if 
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;

    } // else if

  } // while
  
  if ( !gHave_error ) return true ;
  else return false ;
} // Rest_of_maybe_additive_exp()

// =========================================================================================================

bool Maybe_mult_exp() {

  if ( Unary_exp() ) {
    if ( Rest_of_maybe_mult_exp() ) return true ;
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
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

  if ( !gHave_error ) return true ;
  else return false ;

} // Maybe_mult_exp()

// =========================================================================================================

// * / % 運算 只有可能為一般數字計算 不可能為string計算
bool Rest_of_maybe_mult_exp() { // 分號會到這個funtion然後直接return回去
  
  while ( gToken[gNum].token_type == MULTI || gToken[gNum].token_type == DIV 
          || gToken[gNum].token_type == REMAINDER ) {

    if ( gToken[gNum].token_type == MULTI ) {

      if ( gHave_error ) return false ;

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Unary_exp() ) { // 應該是在這邊做計算
  
        if ( gValue.size() >= 2 ) {

          if ( !gIs_float_operation ) {
            int value1 = gValue[gValue.size() - 2] ;
            int value2 = gValue[gValue.size() - 1] ;

            gTemp_value = value1 * value2;

          } // if
          else gTemp_value = gValue[gValue.size() - 2] * gValue[gValue.size() - 1];

          // 應該是倒數第二個加最後一個再繼續遞迴
          gValue.pop_back(); // 算完就丟掉
          gValue.pop_back(); // 算完就丟掉
          gValue.push_back( gTemp_value ); // 加入算好的值
        } // if

      } // if 
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;

    } // if
    else if ( gToken[gNum].token_type == DIV ) {

      if ( gHave_error ) return false ;

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Unary_exp() ) { // 應該是在這邊做計算

        if ( gValue[gValue.size() - 1] == 0 ) { // 除以零的錯誤
          printf( "Error\n" );

          gHave_error = true;

          int temp_Line = gToken[gNum].lineNum;
          // 印出錯誤後把這一整行到分號都不要
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          while ( temp_Line == gToken[gNum].lineNum ) {
            if ( gToken.size() - gNum > 1 ) gNum ++ ;
            else return false ;
          } // while


        } // if
        else { // 做計算

          if ( gValue.size() >= 2 ) {

            if ( !gIs_float_operation ) {
              int value1 = gValue[gValue.size() - 2] ;
              int value2 = gValue[gValue.size() - 1] ;

              gTemp_value = value1 / value2;

            } // if
            else gTemp_value = gValue[gValue.size() - 2] / gValue[gValue.size() - 1];
            // 應該是倒數第二個加最後一個再繼續遞迴

            gValue.pop_back(); // 算完就丟掉
            gValue.pop_back(); // 算完就丟掉
            gValue.push_back( gTemp_value ); // 加入算好的值
          } // if

        } // else

      } // if 
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;

    } // else if
    else if ( gToken[gNum].token_type == REMAINDER ) {

      if ( gHave_error ) return false ;

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Unary_exp() ) { // 應該是在這邊做計算
        if ( gValue.size() >= 2 ) {
          int value1 = gValue[gValue.size() - 2 ] ; 
          int value2 = gValue[gValue.size() - 1] ;
          gTemp_value = value1 % value2 ;
          // 應該是倒數第二個加最後一個再繼續遞迴
          gValue.pop_back(); // 算完就丟掉
          gValue.pop_back(); // 算完就丟掉
          gValue.push_back( gTemp_value ); // 加入算好的值
        } // if
      } // if 
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;

    } // else if

  } // while

  if ( !gHave_error ) return true ;
  else return false ; // could be empty ! 
  
} // Rest_of_maybe_mult_exp()

// =========================================================================================================

bool Unary_exp() {
  
  if ( Sign() ) {
    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    while ( Sign() ) {
      
      if ( gHave_error ) return false ;

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

    } // while

    if ( Signed_unary_exp() ) return true ;
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
  } // if 
  else if ( gToken[gNum].token_type == IDENT || gToken[gNum].token_type == CONSTANT 
            || gToken[gNum].token_type == S_LP ) {
    
    // 這裡的Constant不用push進 gValue因為這是我自己加的條件

    // 這裡不用判斷 Undefined 進去下一個函式再判斷
    if ( Unsigned_unary_exp() ) return true ;
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;
  } // else if 
  else if ( gToken[gNum].token_type == PP || gToken[gNum].token_type == MM ) {

    // 這個 [ PP | MM ] 只有可能出現在下一個ident的'前'面 (立即運算)

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( gToken[gNum].token_type == IDENT ) {

      // ===================================================================================================

      int find = -1 ;
      find = Find_variable_location_in_ALL_variables( gToken[gNum].data ) ;

      if ( find != -1 ) {
        if ( gALL_vari_Token[find].detail_type == INT || gALL_vari_Token[find].detail_type == FLOAT ) {

          if ( gToken[gNum-1].token_type == PP ) {
            gALL_vari_Token[find].constant_value = gALL_vari_Token[find].constant_value + 1 ;
          } // if
          else {
            gALL_vari_Token[find].constant_value = gALL_vari_Token[find].constant_value - 1 ;
          } // else 

        } // if
      } // if

      // ===================================================================================================

      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
      else if ( gIs_function_Definition ) { // 在funtion中出現 剛剛又經歷過Type_specifier代表他要被定義
        gToken[gNum].vari_in_func_temp_defi = true ;
      } // else if
      // 在funtion內出現的ident不是出現在type_specifier()後就要檢查有沒有被定義
      // ///////////////////////////////////////////////////////////////////////////////////////////////////


      if ( gIs_Definition ) {
        Determine_variable_detail_type() ; // 在ident定義時判斷更詳細的變數型別
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;
      } // if

      if ( gToken[gNum].token_type == M_LP ) {

        int temp_Num = gNum - 1 ;

        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        if ( Expression() ) {

          if ( gToken[gNum].token_type == M_RP ) {

            // =============================================================================================
            // 這裡要做array 中括號的處理讓ident可以正確抓到是哪一個值ex. a[2] ;
            // 目前預設的是使用者一定是輸入 ident[constant] 而不是別的算式
            // 打算的作法是直接把ident改變

            int start = 0 ;
            if ( gValue.size() > 0 ) start =  gValue[gValue.size()-1] ;

            char str[30];
            str[0] = start + 48 ;
            strcat( gToken[temp_Num].data, "[" ) ;
            strcat( gToken[temp_Num].data, gToken[gNum-1].data ) ;
            strcat( gToken[temp_Num].data, "]" ) ;

            // 做好了新的ident之後就代替Undefined沒有取值的部分改成在這邊取

            int find = -1 ;
            find = Find_variable_location_in_ALL_variables( gToken[temp_Num].data ) ;

            if ( find != -1 ) {

              if ( gALL_vari_Token[find].detail_type == INT || 
                   gALL_vari_Token[find].detail_type == FLOAT ) {

                if ( gALL_vari_Token[find].detail_type == FLOAT ) gIs_float_operation = true ;

                // 前面有接負號的話就去把他的值找出來乘負號，再丟進去計算 ( 注意 並沒有實際改動該變數的值)
                if ( gToken[temp_Num-1].token_type == SIGN && 
                     gToken[temp_Num-1].detail_type == NEGATIVE ) { 

                  int i = Find_variable_location_in_ALL_variables( gToken[temp_Num].data ) ;
                  float num = ( -1 ) * gALL_vari_Token[i].constant_value ;
                  gValue.push_back( num ) ;
                } // if
                else gValue.push_back( gALL_vari_Token[find].constant_value ) ;

              } // if
              else if ( gALL_vari_Token[find].detail_type == STRING || 
                        gALL_vari_Token[find].detail_type == CHAR ) {
                strcat( gString_value, gALL_vari_Token[find].string_value ) ;
              } // else if
              // 找到了就把值給取出來
              
            } // if

            // =============================================================================================


            if ( !GetToken( gGet_error ) ) return false ; 
            else gNum ++ ;

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
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // else if
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
    else if ( gIs_Definition && gIs_function_Definition ) Variable_infuntion_have_defined() ; 
    // 在funtion內出現的ident不是出現在type_specifier()後就要檢查有沒有被定義
    // /////////////////////////////////////////////////////////////////////////////////////////////////////

    if ( gToken[gNum-2].detail_type == E_MARK ) {
      int find = -1 ;
      find = Find_variable_location_in_ALL_variables( gToken[gNum-1].data ) ;
      if ( find != -1 ) {
        if ( gALL_vari_Token[find].detail_type == BOOL ) {
          if ( gALL_vari_Token[find].bool_value == true )  gALL_vari_Token[find].bool_value = false ;
          else if ( gALL_vari_Token[find].bool_value == false )  gALL_vari_Token[find].bool_value = true ;
        } // if 
      } // if

    } // if

    if ( gIs_Definition ) {
      Determine_variable_detail_type() ; // 在ident定義時判斷更詳細的變數型別
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;
    } // if
    else {
      if ( gAfter_LS ) {

        int find = -1 ;
        find = Find_variable_location_in_ALL_variables( gToken[gNum-1].data ) ;
        if ( find != -1 ) {
          if ( gALL_vari_Token[find].detail_type == INT || gALL_vari_Token[find].detail_type == FLOAT ||
               gALL_vari_Token[find].detail_type == BOOL ) {
            gIdent_operation = true ;
          } // if
          else if ( gALL_vari_Token[find].detail_type == STRING || 
                    gALL_vari_Token[find].detail_type == CHAR ) {
            gIs_string_operation = true ;
          } // else if

          gAfter_LS = false ;

        } // if

      } // if
      // cout 後面的ident只會出現在這!!!! 儲存 '<<' 之後的ident 代表他要印

    } // else

    if ( gToken[gNum].token_type == S_LP ) {
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( gToken[gNum].token_type == S_RP ) {
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        return true ;
      } // if
      else if ( Actual_parameter_list() ) {
        
        if ( gToken[gNum].token_type == S_RP ) {
          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;

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

      int temp_Num = gNum - 1 ;

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( Expression() ) {
        ; // 沒事幹
      } // if
      else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // else if
      else return false ;

      if ( gToken[gNum].token_type == M_RP ) {

        // ===============================================================================================
        // 這裡要做array 中括號的處理讓ident可以正確抓到是哪一個值ex. a[2] ;
        // 目前預設的是使用者一定是輸入 ident[constant] 而不是別的算式
        // 打算的作法是直接把ident改變

        int start = 0 ;
        if ( gValue.size() > 0 ) start =  gValue[gValue.size()-1] ;

        char str[30];
        str[0] = start + 48 ;
        strcat( gToken[temp_Num].data, "[" ) ;
        strcat( gToken[temp_Num].data, gToken[gNum-1].data ) ;
        strcat( gToken[temp_Num].data, "]" ) ;

        // 做好了新的ident之後就代替Undefined沒有取值的部分改成在這邊取

        int find = -1 ;
        find = Find_variable_location_in_ALL_variables( gToken[temp_Num].data ) ;

        if ( find != -1 ) {

          if ( gALL_vari_Token[find].detail_type == INT || 
               gALL_vari_Token[find].detail_type == FLOAT ) {
            if ( gALL_vari_Token[find].detail_type == FLOAT ) gIs_float_operation = true ;

            // 前面有接負號的話就去把他的值找出來乘負號，再丟進去計算 ( 注意 並沒有實際改動該變數的值)
            if ( gToken[temp_Num-1].token_type == SIGN && 
                 gToken[temp_Num-1].detail_type == NEGATIVE ) { 
              int i = Find_variable_location_in_ALL_variables( gToken[temp_Num].data ) ;
              float num = ( -1 ) * gALL_vari_Token[i].constant_value ;
              gValue.push_back( num ) ;
            } // if
            else gValue.push_back( gALL_vari_Token[find].constant_value ) ;

          } // if
          else if ( gALL_vari_Token[find].detail_type == STRING || 
                    gALL_vari_Token[find].detail_type == CHAR ) {
            strcat( gString_value, gALL_vari_Token[find].string_value ) ;
          } // else if
          // 找到了就把值給取出來

          // 前面沒有成功找到選擇是哪個operation的話在這邊重新判斷
          if ( gAfter_LS ) {

            if ( gALL_vari_Token[find].detail_type == INT || gALL_vari_Token[find].detail_type == FLOAT ||
                 gALL_vari_Token[find].detail_type == BOOL ) {
              gIdent_operation = true ;
            } // if
            else if ( gALL_vari_Token[find].detail_type == STRING || 
                      gALL_vari_Token[find].detail_type == CHAR ) {
              gIs_string_operation = true ;
            } // else if

            gAfter_LS = false ;

          } // if
          
        } // if

        // ===============================================================================================

        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

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

    // =====================================================================================================

    // 情況1 : 是一個statement的計算 把數值存入 gValue中方便計算
    // 情況2 : Cout中出現數字 但這個數字是用來計算的不用print ( 用是不是 << 直接接數字來判斷 )
    // 情況2 : 是一個準備Cout的數字 存入準備print的vector
      
    if ( gToken[gNum].detail_type == INT || gToken[gNum].detail_type == FLOAT ) {

      if ( gToken[gNum-1].token_type == SIGN && gToken[gNum-1].detail_type == NEGATIVE ) { 
        // 前面有接負號的話就去把他的值找出來乘負號
        char temp[500] = "-";
        strcat( temp, gToken[gNum].data );
        strcpy( gToken[gNum].data, temp );
      } // if

      if ( !gIs_Definition && !gIs_function_Definition && !gIs_cout_operation ) {
        if ( gToken[gNum].detail_type == INT && !gIs_shifter_constant ) {
          gValue.push_back( atoi( gToken[gNum].data ) ) ;
        } // if
        else if ( gToken[gNum].detail_type == FLOAT ) {
          gValue.push_back( atof( gToken[gNum].data ) ) ;
          gIs_float_operation = true ;
        } // else if
      } // if
      else if ( !gIs_Definition && !gIs_function_Definition && 
                gIs_cout_operation && !gAfter_LS && !gIs_shifter_constant ) {
        if ( gToken[gNum].detail_type == INT ) {
          gValue.push_back( atoi( gToken[gNum].data ) ) ;
        } // if
        else if ( gToken[gNum].detail_type == FLOAT ) {
          gValue.push_back( atof( gToken[gNum].data ) ) ;
          gIs_float_operation = true ;
        } // else if
      } // else if
      else if ( !gIs_Definition && !gIs_function_Definition && 
                gIs_cout_operation && gAfter_LS && !gIs_shifter_constant ) {
        gAfter_LS = false ;

        if ( gToken[gNum].detail_type == INT ) {
          gValue.push_back( atoi( gToken[gNum].data ) ) ;
          gIdent_operation = true ;
        } // if
        else if ( gToken[gNum].detail_type == FLOAT ) {
          gValue.push_back( atof( gToken[gNum].data ) ) ;
          gIs_float_operation = true ;
          gIdent_operation = true ;
        } // else if

      } // else if


      gIs_shifter_constant = false ;

    } // if
    else if ( gToken[gNum].detail_type == STRING || gToken[gNum].detail_type == CHAR ) {

      // only for << "\n" ; 這個特別情況 為空代表 \n為單獨存在或是存在於第一個
      if ( strcmp( gString_value, "" ) == 0 )  { 
        gIs_string_operation = true ;
      } // if

      strcat( gString_value, gToken[gNum].data ) ;

    } // else if

    // =====================================================================================================

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    return true ;
  } // else if
  else if ( gToken[gNum].token_type == S_LP ) {

    if ( gToken[gNum-1].detail_type == NEGATIVE ) {
      gHave_negative = true ;
    } // if

    if ( gToken[gNum-1].detail_type == E_MARK ) {
      gHave_E_mark = true ;
    } // if

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    gIn_expresstion = true ;

    if ( Expression() ) {
      gIn_expresstion = false ; // 沒事幹
    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

    if ( gToken[gNum].token_type == S_RP ) {
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      // ===================================================================================================

      // 這裡是為了已經assignment後卻繼續在計算的情況設立
      // 把gCout清空
      // 並把assign的那個變數的value取出來繼續算
      // 重新設定是哪種operation
      if ( gCout_Token.size() > 0 && gHave_assignment == true && gToken[gNum].token_type != LS ) {

        gHave_assignment = false ;

        int find = -1 ;
        find = Find_variable_location_in_ALL_variables( gCout_Token[0].ident_name ) ;

        gCout_Token.clear() ;
        
        if ( find != -1 ) {
          
          // 該assignment的變數是哪種型別 接下來就是哪種運算繼續做
          if ( gALL_vari_Token[find].detail_type == INT || gALL_vari_Token[find].detail_type == FLOAT ||
               gALL_vari_Token[find].detail_type == BOOL ) {
            gIdent_operation = true ;
          } // if
          else if ( gALL_vari_Token[find].detail_type == STRING || 
                    gALL_vari_Token[find].detail_type == CHAR ) {
            gIs_string_operation = true ;
          } // else if

        } // if

      } // if

      // ===================================================================================================

      if ( gHave_negative == true ) {
        gValue[ gValue.size() - 1 ] = ( -1 ) * gValue[ gValue.size() - 1 ] ;
        gHave_negative = false ;
      } // if

      if ( gHave_E_mark == true ) {

        if ( gBool_Ans.size() > 0 ) {
          if ( gBool_Ans[gBool_Ans.size()-1] == true ) gBool_Ans[gBool_Ans.size()-1] = false ;
          else if ( gBool_Ans[gBool_Ans.size()-1] == false ) gBool_Ans[gBool_Ans.size()-1] = true ;
        } // if

        gHave_E_mark = false ;
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
    // ///////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

} // Signed_unary_exp()

// =========================================================================================================

bool Unsigned_unary_exp() {

  if ( gToken[gNum].token_type == IDENT ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( !gIs_Definition && Undefined_error() ) return false ; // else 繼續執行
    else if ( gIs_Definition && gIs_function_Definition ) Variable_infuntion_have_defined() ; 
    // 在funtion內出現的ident不是出現在type_specifier()後就要檢查有沒有被定義 
    // /////////////////////////////////////////////////////////////////////////////////////////////////////

    if ( gIs_Definition ) {
      Determine_variable_detail_type() ; // 在ident定義時判斷更詳細的變數型別
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;
    } // if
    else {

      if ( gAfter_LS ) {

        int find = -1 ;
        find = Find_variable_location_in_ALL_variables( gToken[gNum-1].data ) ;
        if ( find != -1 ) {
          if ( gALL_vari_Token[find].detail_type == INT || gALL_vari_Token[find].detail_type == FLOAT ||
               gALL_vari_Token[find].detail_type == BOOL ) {
            gIdent_operation = true ;
          } // if
          else if ( gALL_vari_Token[find].detail_type == STRING || 
                    gALL_vari_Token[find].detail_type == CHAR ) {
            gIs_string_operation = true ;
          } // else if

          gAfter_LS = false ;

        } // if
        // cout 後面的ident只會出現在這!!!! 儲存 '<<' 之後的ident 代表他要印
      } // if

    } // else

    if ( gToken[gNum].token_type == S_LP ) {
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( gToken[gNum].token_type == S_RP ) { // 直接接右括號
        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        return true ;
      } // if
      else if ( Actual_parameter_list() ) { // 或是先接 APL 再接右括號
        if ( gToken[gNum].token_type == S_RP ) {
          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;

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
    else if ( gToken[gNum].token_type == M_LP || gToken[gNum].token_type == PP 
              || gToken[gNum].token_type == MM ) {

      if ( gToken[gNum].token_type == M_LP ) {

        int temp_Num = gNum - 1 ;

        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        if ( Expression() ) {
          ; // 沒事幹
        } // if
        else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          Unexpected_error() ;
          // ///////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // else if
        else return false ;

        if ( gToken[gNum].token_type == M_RP ) {

          // ===============================================================================================
          // 這裡要做array 中括號的處理讓ident可以正確抓到是哪一個值ex. a[2] ;
          // 目前預設的是使用者一定是輸入 ident[constant] 而不是別的算式
          // 打算的作法是直接把ident改變

          int start = 0 ;
          if ( gValue.size() > 0 ) start =  gValue[gValue.size()-1] ;

          char str[30];
          str[0] = start + 48 ;
          strcat( gToken[temp_Num].data, "[" ) ;
          strcat( gToken[temp_Num].data, gToken[gNum-1].data ) ;
          strcat( gToken[temp_Num].data, "]" ) ;

          // 做好了新的ident之後就代替Undefined沒有取值的部分改成在這邊取

          int find = -1 ;
          find = Find_variable_location_in_ALL_variables( gToken[temp_Num].data ) ;

          if ( find != -1 ) {

            if ( gALL_vari_Token[find].detail_type == INT || 
                 gALL_vari_Token[find].detail_type == FLOAT ) {
              if ( gALL_vari_Token[find].detail_type == FLOAT ) gIs_float_operation = true ;

              // 前面有接負號的話就去把他的值找出來乘負號，再丟進去計算 ( 注意 並沒有實際改動該變數的值)
              if ( gToken[temp_Num-1].token_type == SIGN && 
                   gToken[temp_Num-1].detail_type == NEGATIVE ) { 
                int i = Find_variable_location_in_ALL_variables( gToken[temp_Num].data ) ;
                float num = ( -1 ) * gALL_vari_Token[i].constant_value ;
                gValue.push_back( num ) ;
              } // if
              else gValue.push_back( gALL_vari_Token[find].constant_value ) ;

            } // if
            else if ( gALL_vari_Token[find].detail_type == STRING || 
                      gALL_vari_Token[find].detail_type == CHAR ) {
              strcat( gString_value, gALL_vari_Token[find].string_value ) ;
            } // else if
            // 找到了就把值給取出來

            // 前面沒有成功找到選擇是哪個operation的話在這邊重新判斷
            if ( gAfter_LS ) {

              if ( gALL_vari_Token[find].detail_type == INT || gALL_vari_Token[find].detail_type == FLOAT ||
                   gALL_vari_Token[find].detail_type == BOOL ) {
                gIdent_operation = true ;
              } // if
              else if ( gALL_vari_Token[find].detail_type == STRING || 
                        gALL_vari_Token[find].detail_type == CHAR ) {
                gIs_string_operation = true ;
              } // else if

              gAfter_LS = false ;

            } // if
            
          } // if

          // ===============================================================================================

          if ( !GetToken( gGet_error ) ) return false ; 
          else gNum ++ ;

          // return true ; // 還要繼續判斷
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

        // 這個 [ PP | MM ] 只有可能來自於basic expression的ident後面

        // =================================================================================================
        if ( gToken[gNum].token_type == PP ) gPPMM_after_ID_info.is_PP = true ;
        else gPPMM_after_ID_info.is_PP = false ;
        
        if ( gToken[gNum-1].token_type == M_RP ) {
          int num = gNum - 4 ;
          strcpy( gPPMM_after_ID_info.name, gToken[num].data ) ;
        } // if
        else strcpy( gPPMM_after_ID_info.name, gToken[gNum-1].data ) ;

        gPPMM_after_ID.push_back( gPPMM_after_ID_info ) ;
        // =================================================================================================

        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

      } // if

      return true ;
    } // else if

    return true ;
  } // if
  else if ( gToken[gNum].token_type == CONSTANT ) {
    // =====================================================================================================

    // 情況1 : 是一個statement的計算 把數值存入 gValue中方便計算
    // 情況2 : Cout中出現數字 但這個數字是用來計算的不用print ( 用是不是 << 直接接數字來判斷 )
    // 情況2 : 是一個準備Cout的數字 存入準備print的vector
      
    if ( gToken[gNum].detail_type == INT || gToken[gNum].detail_type == FLOAT ) {

      if ( !gIs_Definition && !gIs_function_Definition && !gIs_cout_operation && !gIs_shifter_constant ) {
        if ( gToken[gNum].detail_type == INT ) {
          gValue.push_back( atoi( gToken[gNum].data ) ) ;
        } // if
        else if ( gToken[gNum].detail_type == FLOAT ) {
          gValue.push_back( atof( gToken[gNum].data ) ) ;
          gIs_float_operation = true ;
        } // else if
      } // if
      else if ( !gIs_Definition && !gIs_function_Definition && 
                gIs_cout_operation && !gAfter_LS && !gIs_shifter_constant ) {
        if ( gToken[gNum].detail_type == INT ) {
          gValue.push_back( atoi( gToken[gNum].data ) ) ;
        } // if
        else if ( gToken[gNum].detail_type == FLOAT ) {
          gValue.push_back( atof( gToken[gNum].data ) ) ;
          gIs_float_operation = true ;
        } // else if
      } // else if
      else if ( !gIs_Definition && !gIs_function_Definition && 
                gIs_cout_operation && gAfter_LS && !gIs_shifter_constant ) {
        gAfter_LS = false ;

        if ( gToken[gNum].detail_type == INT ) {
          gValue.push_back( atoi( gToken[gNum].data ) ) ;
          gIdent_operation = true ;
        } // if
        else if ( gToken[gNum].detail_type == FLOAT ) {
          gValue.push_back( atof( gToken[gNum].data ) ) ;
          gIs_float_operation = true ;
          gIdent_operation = true ;
        } // else if

      } // else if

      gIs_shifter_constant = false ;

    } // if
    else if ( gToken[gNum].detail_type == STRING || gToken[gNum].detail_type == CHAR ) {

      // only for << "\n" ; 這個特別情況 為空代表 \n為單獨存在或是存在於第一個
      if ( strcmp( gString_value, "" ) == 0 )  { 
        gIs_string_operation = true ;
      } // else if

      if ( strcmp( gToken[gNum].data, "\\n" ) == 0 && strcmp( gString_value, "" ) != 0 )  { 
        strcat( gString_value, "\n" ) ;
      } // else if
      else strcat( gString_value, gToken[gNum].data ) ;
      
    } // else if

    // =====================================================================================================

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    return true ;
  } // else if
  else if ( gToken[gNum].token_type == S_LP ) {

    // 如果又遇到左括號 代表要定義新的string才相加
    // 這時先把前面加好的清空再繼續運算才不會錯
    // 但是在清空前要先記錄下來之後再加回來
    if ( strcmp( gString_value, "" ) != 0 ) {
      strcpy( gTemp_String_value, gString_value ) ;
      strcpy( gString_value, "" ) ;
    } // if

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    gIn_expresstion = true ;

    if ( Expression() ) {
      gIn_expresstion = false ; // 沒事幹
    } // if
    else if ( !gHave_error && gToken[gNum].token_type != UNRECOGNIZED ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // else if
    else return false ;

    if ( gToken[gNum].token_type == S_RP ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      // ===================================================================================================

      // 這裡是為了已經assignment後卻繼續在計算的情況設立
      // 把gCout清空
      // 並把assign的那個變數的value取出來繼續算
      // 重新設定是哪種operation
      if ( gCout_Token.size() > 0 && gHave_assignment == true && gToken[gNum].token_type != LS ) {

        gHave_assignment = false ;

        int find = -1 ;
        find = Find_variable_location_in_ALL_variables( gCout_Token[0].ident_name ) ;

        gCout_Token.clear() ;
        
        if ( find != -1 ) {
          
          // 該assignment的變數是哪種型別 接下來就是哪種運算繼續做
          if ( gALL_vari_Token[find].detail_type == INT || gALL_vari_Token[find].detail_type == FLOAT ||
               gALL_vari_Token[find].detail_type == BOOL ) {
            gIdent_operation = true ;
          } // if
          else if ( gALL_vari_Token[find].detail_type == STRING || 
                    gALL_vari_Token[find].detail_type == CHAR ) {
            gIs_string_operation = true ;
          } // else if

        } // if

      } // if

      // ===================================================================================================

      if ( strcmp( gTemp_String_value, "" ) != 0 ) {

        strcat( gTemp_String_value, gString_value ) ;
        strcpy( gString_value, gTemp_String_value ) ;
        strcpy( gTemp_String_value, "" ) ;
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
    // ///////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // else if
  else return false ;

} // Unsigned_unary_exp()

// =========================================================================================================


void Unexpected_error() {

  if ( gToken[gNum].lineNum != 0 ) {
    printf( "> Line %d : unexpected token : '%s'\n", gToken[gNum].lineNum, gToken[gNum].data );
  } // if
  else printf( "> Line %d : unexpected token : '%s'\n", 1, gToken[gNum].data );

  gHave_error = true ;

  gGet_error = true ;

  GetToken( gGet_error ) ;

  gIs_Definition = false ;
  gIs_cout_operation = false ;
  gAfter_LS = false ;
  gIs_float_operation = false ;
  gIs_function_Definition = false ;
  gGet_error = false ;
  gValue.clear(); // 初始化
  gBool_Ans.clear(); // 初始化
  strcpy( gString_value, "" ) ;
  gTemp_variable_loctation->clear(); // 初始化
  gLine = 1 ;
  bool gAlready_Get = false ;
  Clear_defi_variable_infuntion() ;


  if ( !GetToken( gGet_error ) ) return ; 
  else gNum ++ ;

  return ;

} // Unexpected_error()

// =========================================================================================================

// 負責判斷 該 ident有無定義 再判斷該ident為何種型別 再選擇丟入gValue or gString_value
bool Undefined_error() {

  int find_id = 0;
  bool found_it = false;
  while ( find_id < gNum && !found_it ) { // 找找看有沒有這個變數

    if ( strcmp( gToken[find_id].data, gToken[gNum].data ) == 0
         && gToken[find_id].have_defined == true ) {
      
      int find = -1 ;
      find = Find_variable_location_in_ALL_variables( gToken[gNum].data ) ;

      if ( find != -1 ) {

        if ( gALL_vari_Token[find].detail_type == INT || gALL_vari_Token[find].detail_type == FLOAT ) {
          if ( gALL_vari_Token[find].detail_type == FLOAT ) gIs_float_operation = true ;

          // 前面有接負號的話就去把他的值找出來乘負號，再丟進去計算 ( 注意 並沒有實際改動該變數的值)
          if ( gToken[gNum-1].token_type == SIGN && gToken[gNum-1].detail_type == NEGATIVE ) { 
            int i = Find_variable_location_in_ALL_variables( gToken[gNum].data ) ;
            float num = ( -1 ) * gALL_vari_Token[i].constant_value ;
            gValue.push_back( num ) ;
          } // if
          else gValue.push_back( gALL_vari_Token[find].constant_value ) ;

        } // if
        else if ( gALL_vari_Token[find].detail_type == STRING || 
                  gALL_vari_Token[find].detail_type == CHAR ) {
          strcat( gString_value, gALL_vari_Token[find].string_value ) ;
        } // else if
        // 找到了就把值給取出來

      } // if

      found_it = true;
    } // if

    find_id++;

  } // while

  if ( !gHave_error && !found_it ) {

    if ( gToken[gNum].lineNum != 0 ) {
      printf( "> Line %d : undefined identifier : '%s'\n", gToken[gNum].lineNum, gToken[gNum].data ) ;
    } // if
    else printf( "> Line %d : undefined identifier : '%s'\n", 1, gToken[gNum].data ) ;

    gHave_error = true;

    gGet_error = true ;

    GetToken( gGet_error ) ;

    gIs_Definition = false ;
    gIs_cout_operation = false ;
    gAfter_LS = false ;
    gIs_float_operation = false ;
    gIs_function_Definition = false ;
    gGet_error = false ;
    gValue.clear(); // 初始化
    gBool_Ans.clear(); // 初始化
    strcpy( gString_value, "" ) ;
    gTemp_variable_loctation->clear(); // 初始化
    gLine = 1 ;
    bool gAlready_Get = false ;
    Clear_defi_variable_infuntion() ;
    
    if ( !GetToken( gGet_error ) ) return true ; // 這裡回傳true才是錯 
    else gNum ++ ;

    return true ;

  } // if
  else {
    if ( !GetToken( gGet_error ) ) return true ; // 這裡回傳true才是錯 
    else gNum ++ ;

    return false ;
  } // else 

  return false ;

} // Undefined_error()

// =========================================================================================================

void Unrecognized_error() {
  // exit( 0 ) ;
  if ( gToken[gNum].lineNum != 0 ) {
    printf( "> Line %d : unrecognized token with first char : '%s'\n", 
            gToken[gNum].lineNum, gToken[gNum].data ) ;
  } // if
  else printf( "> Line %d : unrecognized token with first char : '%s'\n",
               1, gToken[gNum].data );                                          

  gHave_error = true ;

  gGet_error = true ;

  GetToken( gGet_error ) ;

  gIs_Definition = false ;
  gIs_function_Definition = false ;
  gIs_cout_operation = false ;
  gAfter_LS = false ;
  gIs_float_operation = false ;
  gGet_error = false ;
  gValue.clear(); // 初始化
  gBool_Ans.clear(); // 初始化
  strcpy( gString_value, "" ) ;
  gTemp_variable_loctation->clear(); // 初始化
  gLine = 1 ;
  bool gAlready_Get = false ;
  Clear_defi_variable_infuntion() ;

  if ( !GetToken( gGet_error ) ) return ;
  else gNum ++ ;

  return ;

} // Unrecognized_error()

// =========================================================================================================

void ListAllVariables() { // 把所有的一般變數排序後印出來
  // exit( 0 ) ;
  ListAllVariables_Sorted_and_print() ;

  if ( !GetToken( gGet_error ) ) return ; 
  else gNum ++ ;
  if ( gToken[gNum].token_type == SEMICOLON ) {
    gLine = 0 ;
    if ( !GetToken( gGet_error ) ) return ; 
    else gNum ++ ;
    // 做事
  } // if 

} // ListAllVariables()

// =========================================================================================================


void ListAllFunctions() { // 把所有的funtion名稱排序後印出來

  ListAllFunctions_Sorted_and_print() ;

  if ( !GetToken( gGet_error ) ) return ; 
  else gNum ++ ;
  if ( gToken[gNum].token_type == SEMICOLON ) {
    gLine = 0 ;
    if ( !GetToken( gGet_error ) ) return ; 
    else gNum ++ ;
    // 做事
  } // if 

} // ListAllFunctions()

// =========================================================================================================

void ListVariable( char parameter[500] ) { // 把傳進來該參數名稱 的變數 名別與名稱完整印出來
  // exit( 0 ) ;
  int find_variable = gNum - 1 ;

  while ( find_variable >= 0 ) { // 減回去找找看有沒有定義過這個變數，因為新定義的變數會在後面

    if ( strcmp( gToken[find_variable].data, parameter ) == 0 
         && gToken[find_variable].have_defined == true ) { // 找到變數了
      
      int find_type = find_variable - 1 ;

      while ( gToken[find_type].token_type == COMMA ) { // 先去找該變數的型別，如果遇到逗號就再往前兩個去找
        find_type = find_type - 2 ; // 因為要跳過逗號和逗號的前一個變數
      } // while

      printf( "> %s %s", gToken[find_type].data, gToken[find_variable].data ) ; // 印出型別和名稱

      int after_variable_name = find_variable + 1 ;

      // 變數後面接左中括號 ex. char a[10] ;
      while ( gToken[after_variable_name].token_type != SEMICOLON 
              && gToken[after_variable_name].token_type != COMMA ) {
        if ( gToken[after_variable_name].token_type == M_RP  ) {
          printf( "%s", gToken[after_variable_name].data ) ;
        } // if
        else printf( "%s ", gToken[after_variable_name].data ) ;
        after_variable_name ++ ;
      } // while

      // 還有接逗號 去宣告其他變數 就直接讀到分號 ex. char a[10], b[20] ;
      while ( gToken[after_variable_name].token_type != SEMICOLON ) {
        after_variable_name ++ ;
      } // while

      printf( " %s\n", gToken[after_variable_name].data ) ; // 印出分號
      printf( "Statement executed ...\n" ) ;
      gLine = 1 ;
      return ;
    } // if

    gLine = 1 ;

    find_variable -- ;
  } // while

  printf( "> can't find %s\n", parameter ) ;
  printf( "Statement executed ...\n" ) ;

  return ;

} // ListVariable()

// =========================================================================================================

void ListFunction( char parameter[500] ) { // 把傳進來該參數名稱 的funtion名稱與內容依照規格印出來

  printf( "> " ) ;

  int find_function = gFunction_Token.size() - 1 ;
  while ( find_function >= 0 ) { // 先找到該funtion存的位置再依照規則印出來 用後面往前找才會找到新的

    if ( strcmp( gFunction_Token[find_function].function_name, parameter ) == 0 ) { 
      Funtion_pretty_print( find_function ) ;

      gLine = 1 ;
      return ;
    } // if

    find_function -- ;
  } // while

  gLine = 1 ;
  printf( "can't find %s\n", parameter ) ;
  printf( "Statement executed ...\n" ) ;

  return ;

} // ListFunction()

// =========================================================================================================

void Done() { // 結束執行
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


// 這個Function只是為了把老大一開始輸入的test num讀掉
void Read_test_num() {

   // 宣吿
  char text[100] = "" ; // 用來暫存token
  char ch[100] = "" ; // 用來讀檔
  char temp_ch[100] = "" ; // 輔助讀檔
  char temp = ' ' ;

  // ********************************************************************
  temp = scanf( "%c", &ch[0] ) ; // 先讀第一個測試編號
  while ( temp != EOF && ch[0] != '\n' && 58 > ch[0] && ch[0] > 47 ) {
    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    strcat( text, ch ) ;
    temp = scanf( "%c", &ch[0] ) ; // 先讀第一個測試編號
  } // while

  if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch

  if ( temp == EOF ) {
    printf( "Our-C running ...\n" ) ;
    printf( "> Our-C exited ..." ) ;
    exit( 0 ) ;
  } // if

  strcpy( gToken_info.testNum, text ) ;
  strcpy( text, "" ) ; // 清空text

} // Read_test_num() 


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


bool GetToken( bool get_error ) { // GetToken 先全部照單全收，要印的時候用C語言把歸類成 float的token，用%3f的函數去印

  // 宣吿
  char text[100] = "" ; // 用來暫存token
  char ch[100] = "" ; // 用來讀檔
  char temp_ch[100] = "" ; // 輔助讀檔
  char temp = ' ' ;
  char for_unre[100] = "" ; // 給unrecognized用的
  bool not_quit = false ; // 如果quit是一個變數
  bool is_float = false ; // 是否為浮點數

  gToken_info.have_defined = false ; // 這裡只是給個初始值 真正判斷會在parser那邊
  gToken_info.is_int = true ;
  gToken_info.variable_content = 0 ;
  gToken_info.error_lineNum = 0 ;
  gToken_info.is_funtion_defined = false ;
  gToken_info.vari_in_func_temp_defi = false ;
  

  // ********************************************************************
  // ********************************************************************
  // ********************************************************************
  // ********************************************************************

  if ( gGet_error == true ) { // 有錯就直接讀完

    if ( !gLast_read_char_is_change_line ) {
      if ( temp != EOF && ch[0] != '\n' && gTemp_char[0] != '\n' ) temp = scanf( "%c", &ch[0] ) ;
      while ( temp != EOF && ch[0] != '\n' && gTemp_char[0] != '\n' ) {
        temp = scanf( "%c", &ch[0] ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
      } // while
    } // if
    
    if ( ch[0] == '\n' ) gLine ++ ;

    strcpy( gTemp_char, "" ) ; // 清空
    gGet_error = false ;
    return true ;
  } // if

  gLast_read_char_is_change_line = false ;

  if ( strcmp( gTemp_char, "" ) == 0 ) {
    temp = scanf( "%c", &ch[0] ) ;
  } // if
  else {
    if ( gTemp_char[0] != '\n' ) { // 是換行字元直接清空 讀新的
      strcpy( ch, gTemp_char ) ; // 把還沒用到的char丟回去判斷
      strcpy( gTemp_char, "" ) ; // 清空
    } // if
    else {
      strcpy( gTemp_char, "" ) ; // 清空
      temp = scanf( "%c", &ch[0] ) ;
    } // else

  } // else 


  if ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) { // 把空白跟換行讀掉

    if ( ch[0] == '\n' ) gLine ++ ;
    temp = scanf( "%c", &ch[0] ) ;
    if ( ch[0] == '\n' ) gLine ++ ;
    while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
      if ( temp == EOF ) return false ;
      temp = scanf( "%c", &ch[0] ) ;
      if ( ch[0] == '\n' ) gLine ++ ;
    } // while

  } // if

  if ( temp == EOF ) {
    // return false ;
  } // if

  // ********************************************************************
  // ********************************************************************
  // ********************************************************************
  // ********************************************************************

  if ( ch[0] == '+' || ch[0] == '*' || ch[0] == '-' ) { // 處理加減乘

    if ( gToken.size() == 0 || gToken[gToken.size() - 1].token_type == RS
         || gToken[gToken.size() - 1].token_type == LS
         || gToken[gToken.size() - 1].token_type == ONE_EQUAL
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
         || gToken[gToken.size() - 1].token_type == UNRECOGNIZED ) {

      if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ;
      temp = scanf( "%c", &ch[0] ) ;

      if ( temp_ch[0] == '+' && ch[0] == '=' ) { 

        strcat( text, "+=" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = PE;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text

      } // if
      else if ( temp_ch[0] == '-' && ch[0] == '=' ) { 

        strcat( text, "-=" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = ME;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text

      } // else if
      else if ( temp_ch[0] == '*' && ch[0] == '=' ) { 

        strcat( text, "*=" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = TE;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text

      } // else if
      else if ( temp_ch[0] == '+' && ch[0] == '+' ) { 

        strcat( text, "++" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = PP;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text

      } // else if
      else if ( temp_ch[0] == '-' && ch[0] == '-' ) { 

        strcat( text, "--" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = MM;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text

      } // else if
      else if ( temp_ch[0] == '+' && ch[0] != '=' ) { 

        strcat( text, "+" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = SIGN;
        gToken_info.detail_type = POSITIVE ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
        if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
        if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;

      } // else if
      else if ( temp_ch[0] == '-' && ch[0] != '=' ) { 

        strcat( text, "-" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = SIGN;
        gToken_info.detail_type = NEGATIVE ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
        if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
        if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;

      } // else if
      else { // 前面都不是就只有乘法進得來了

        strcat( text, "*" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = MULTI;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
        if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
        if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;

      } // else

    } // if
    else {

      if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ;
      temp = scanf( "%c", &ch[0] ) ;

      if ( temp_ch[0] == '+' && ch[0] == '=' ) { 

        strcat( text, "+=" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = PE;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text

      } // if
      else if ( temp_ch[0] == '-' && ch[0] == '=' ) { 

        strcat( text, "-=" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = ME;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text

      } // else if
      else if ( temp_ch[0] == '*' && ch[0] == '=' ) { 

        strcat( text, "*=" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = TE;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text

      } // else if
      else if ( temp_ch[0] == '+' && ch[0] == '+' ) { 

        strcat( text, "++" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = PP;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text

      } // else if
      else if ( temp_ch[0] == '-' && ch[0] == '-' ) { 

        strcat( text, "--" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = MM;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text

      } // else if
      else if ( temp_ch[0] == '+' && ch[0] != '=' ) { 

        strcat( text, "+" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = PLUS;
        gToken_info.detail_type = POSITIVE ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
        if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
        if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;

      } // else if
      else if ( temp_ch[0] == '-' && ch[0] != '=' ) { 

        strcat( text, "-" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = SUB;
        gToken_info.detail_type = NEGATIVE ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
        if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
        if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;

      } // else if
      else { // 前面都不是就只有乘法進得來了

        strcat( text, "*" );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = MULTI;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
        if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
        if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;

      } // else

    } // else

  
    return true ;

  } // if

  // ********************************************************************

  if ( ch[0] == '/' ) { // 遇到除號 或是 註解 或是DE

    bool need_line_plus = false ;
    if ( temp_ch[0] != ';' && temp_ch[0] != '}' ) need_line_plus = true ;

    temp = scanf( "%c", &ch[0] ) ;

    if ( ch[0] == '/' ) { // 是註解

      if ( need_line_plus == true ) gLine ++ ; 

      temp = scanf( "%c", &ch[0] ) ;
      while ( ch[0] != '\n' && temp != EOF ) { // 把註解讀掉
        temp = scanf( "%c", &ch[0] ) ;
      } // while

      if ( GetToken( gGet_error ) ) {
        return true ;
      } // if

    } // if
    else {

      if ( ch[0] == '=' ) {
        strcpy( gToken_info.data, "/=" ) ; // 存取token資訊
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = DE ;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ;

      } // if
      else {
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
        strcpy( gToken_info.data, "/" ) ; // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = DIV ;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text

        if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
        if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
        strcpy( text, "" ); // 清空text
        if ( ch[0] == '\n' ) gLine ++ ;
      } // else

      return true ;

    } // else

  } // if

  // ********************************************************************

  if ( ch[0] == '<' || ch[0] == '>' || ch[0] == '=' ) { // 遇到比較的運算元

    strcat( text, ch );
    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    temp = scanf( "%c", &ch[0] ) ;

    if ( temp_ch[0] == '=' ) {
  
      if ( ch[0] != '=' ) {
        strcpy( gToken_info.data, text ) ; // ex. a = 1 ;
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = ONE_EQUAL ;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        // 把還沒用到的char存起來之後再判斷
        if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
        if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
      } // if
      else { // "=="
        strcat( text, ch );
        strcpy( gToken_info.data, text ) ; 
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = EQUAL;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
      } // else

    } // if
    else if ( temp_ch[0] == '<' && ch[0] == '=' ) {
      strcat( text, ch );
      strcpy( gToken_info.data, text ) ; // ex. a <= 1 ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = SMALLER_EQ;
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info );
    } // else if
    else if ( temp_ch[0] == '>' && ch[0] == '=' ) {
      strcat( text, ch );
      strcpy( gToken_info.data, text ) ; // ex. a >= 1 ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = BIGGGER_EQ;
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info );
    } // else if
    else if ( temp_ch[0] == '<' && ch[0] == '<' ) {
      strcat( text, ch );
      strcpy( gToken_info.data, text ) ; // ex. a <= 1 ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = LS;
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info );
    } // else if
    else if ( temp_ch[0] == '>' && ch[0] == '>' ) {
      strcat( text, ch );
      strcpy( gToken_info.data, text ) ; // ex. a >= 1 ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = RS;
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info );
    } // else if
    else if ( temp_ch[0] == '<' && ch[0] != '=' ) {
      strcpy( gToken_info.data, text ) ; // ex. a < 1 ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = SMALLER;
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info );
      if ( ch[0] != ' ' && ch[0] != '-' && ch[0] != '+' ) strcpy( temp_ch, ch ) ; // 為了判斷sign的話不能存
      // 把還沒用到的char存起來之後再判斷
      if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
      if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
    } // else if
    else if ( temp_ch[0] == '>' && ch[0] != '=' ) {
      strcpy( gToken_info.data, text ) ; // ex. a > 1 ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = BIGGER;
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info );
      if ( ch[0] != ' ' && ch[0] != '-' && ch[0] != '+' ) strcpy( temp_ch, ch ) ; // 為了判斷sign的話不能存
      // 把還沒用到的char存起來之後再判斷
      if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
      if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
    } // else if

    strcpy( text, "" ) ;
    if ( ch[0] == '\n' ) gLine ++ ;
  
    return true ;

  } // if

  // ********************************************************************

  if ( ch[0] == '\'' ) { // --------------------------------如果get到不是( 先不討論 )
    // strcat( text, ch );
    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    temp = scanf( "%c", &ch[0] ) ;
    strcat( text, ch );
    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    temp = scanf( "%c", &ch[0] ) ;
    // strcat( text, ch );

    strcpy( gToken_info.data, text ) ; // 存取token資訊
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = CONSTANT ;
    gToken_info.detail_type = CHAR ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ;

    return true ;

  } // if

  // ********************************************************************

  if ( ch[0] == '(' ) {
    strcpy( gToken_info.data, "(" ) ; // 存取token資訊
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = S_LP ;
    gToken_info.detail_type = NOTHING ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ;

    return true ;

  } // if

  if ( ch[0] == ')' ) {

    strcpy( gToken_info.data, ")" ) ; // 存取token資訊
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = S_RP ;
    gToken_info.detail_type = NOTHING ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ;
  
    return true ;

  } // if

  // ********************************************************************

  if ( ch[0] == '[' ) {
    strcpy( gToken_info.data, "[" ) ; // 存取token資訊
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = M_LP ;
    gToken_info.detail_type = NOTHING ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ;
  
    return true ;

  } // if

  if ( ch[0] == ']' ) {
    strcpy( gToken_info.data, "]" ) ; // 存取token資訊
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = M_RP ;
    gToken_info.detail_type = NOTHING ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ; // 清空text
  
    return true ;

  } // if

  // ********************************************************************

  if ( ch[0] == '{' ) {
    strcpy( gToken_info.data, "{" ) ; // 存取token資訊
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = L_LP ;
    gToken_info.detail_type = NOTHING ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ;
  
    return true ;

  } // if

  if ( ch[0] == '}' ) {
    strcpy( gToken_info.data, "}" ) ; // 存取token資訊
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = L_RP ;
    gToken_info.detail_type = NOTHING ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ; // 清空text 

    return true ;

  } // if

  // ********************************************************************

  if ( ch[0] == ';' ) { // 分號的處理
    strcpy( gToken_info.data, ";" ) ; // 存取token資訊
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = SEMICOLON ;
    gToken_info.detail_type = NOTHING ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ; // 清空text
  
    return true ;

  } // if

  // ********************************************************************

  if ( 58 > ch[0] && ch[0] > 47 ) { // 數字開頭的處理

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
    gToken_info.lineNum = gLine ;
    if ( !is_float ) {
      gToken_info.token_type = CONSTANT ; // int
      gToken_info.detail_type = INT ;
    } // if
    else {
      gToken_info.token_type = CONSTANT ; // float
      gToken_info.detail_type = FLOAT ;
    } // else

    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ; // 清空text
    if ( ch[0] == '\n' ) gLine ++ ;

    // 把還沒用到的char存起來之後再判斷
    if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
    if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
  
    return true ;

  } // if

  // ********************************************************************

  if ( ch[0] == '.' ) { // 點開頭的處理

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
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = CONSTANT; // Float
      gToken_info.detail_type = FLOAT ;
      gToken.push_back( gToken_info );
      strcpy( text, "" ); // 清空text
    } // if
    else {
      strcpy( gToken_info.data, text ); // 存取token資訊
      gToken_info.lineNum = gLine ;
      gToken_info.error_lineNum = gLine ;
      gToken_info.token_type = UNRECOGNIZED;
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info );

      if ( ch[0] == '\n' ) gLine ++ ;
      gNum ++ ;
      Unrecognized_error() ;
      return false;

    } // else

    if ( ch[0] == '\n' ) gLine ++ ;

    // 把還沒用到的char存起來之後再判斷
    if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
    if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
  
    return true ; 

  } // if

  // ********************************************************************


  if ( ch[0] == '"' ) { // 處理字串

    // 一律不要前後的引號

    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch

    temp = scanf( "%c", &ch[0] ) ;
    while ( temp != EOF && ch[0] != '"' ) {

      if ( ch[0] == 92 ) {

        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;

        if ( ch[0] == 110 ) {
          strcat( text, "\n" ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // if
        else strcat( text, temp_ch ) ;

      } // if
      else {
        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
      } // else

    } // while

    strcpy( gToken_info.data, text );
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = CONSTANT ; 
    gToken_info.detail_type = STRING ;
    gToken.push_back( gToken_info );

    strcpy( text, "" ); // 清空text
    // 不用這行 if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
    if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;

    return true ; 

  } // if 


  // ********************************************************************


  if ( ch[0] == ':' ) { // 處理冒號

    strcat( text, ch ) ;
    strcpy( gToken_info.data, text );
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = COLON ; 
    gToken_info.detail_type = NOTHING ;
    gToken.push_back( gToken_info );

    strcpy( text, "" ); // 清空text

    return true ; 

  } // if 


  // ********************************************************************


  if ( ch[0] == '^' ) { // 處理^

    strcat( text, ch ) ;
    strcpy( gToken_info.data, text );
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = HAT ; 
    gToken_info.detail_type = NOTHING ;
    gToken.push_back( gToken_info );

    strcpy( text, "" ); // 清空text

    return true ; 

  } // if 

  
  // ********************************************************************


  if ( ch[0] == '?' ) { // 處理問號

    strcat( text, ch ) ;
    strcpy( gToken_info.data, text );
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = QUESTION ; 
    gToken_info.detail_type = NOTHING ;
    gToken.push_back( gToken_info );

    strcpy( text, "" ); // 清空text
    return true ; 

  } // if 


  // ********************************************************************


  if ( ch[0] == ',' ) { // 處理逗號

    strcat( text, ch ) ;
    strcpy( gToken_info.data, text );
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = COMMA ; 
    gToken_info.detail_type = NOTHING ;
    gToken.push_back( gToken_info );

    strcpy( text, "" ); // 清空text

    return true ; 

  } // if 


  // ********************************************************************


  if ( ch[0] == '%' ) { // 處理%

    strcat( text, ch );

    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    temp = scanf( "%c", &ch[0] ) ;

    if ( ch[0] == '=' ) {
      strcpy( gToken_info.data, "%=" ) ; // 存取token資訊
      gToken_info.lineNum = gLine ; // 看他屬於哪一行
      gToken_info.token_type = RE ;
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info ) ;
      strcpy( text, "" ) ; // 清空text
    } // if
    else {
      strcpy( gToken_info.data, "%" ) ; // 存取token資訊
      gToken_info.lineNum = gLine ; // 看他屬於哪一行
      gToken_info.token_type = REMAINDER ;
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info ) ;
      strcpy( text, "" ) ; // 清空text
      // 把還沒用到的char存起來之後再判斷
      if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
      if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
    } // else
  
    strcpy( text, "" ); // 清空text
    if ( ch[0] == '\n' ) gLine ++ ;
    // 把還沒用到的char存起來之後再判斷
  
    return true ; 

  } // if 

   // ********************************************************************

  
  if ( ch[0] == '!' ) { // 驚嘆號

    strcat( text, ch );

    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    temp = scanf( "%c", &ch[0] ) ;

    if ( ch[0] == '=' ) {
      strcpy( gToken_info.data, "!=" ) ; // 存取token資訊
      gToken_info.lineNum = gLine ; // 看他屬於哪一行
      gToken_info.token_type = NOT_EQUAL ;
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info ) ;
      strcpy( text, "" ) ; // 清空text
    } // if
    else {
      strcpy( gToken_info.data, "!" ) ; // 存取token資訊
      gToken_info.lineNum = gLine ; // 看他屬於哪一行
      gToken_info.token_type = SIGN ; // 其實我有寫一個enum E_mark只是 驚嘆號只用在sign的情況
      gToken_info.detail_type = E_MARK ;
      gToken.push_back( gToken_info ) ;
      strcpy( text, "" ) ; // 清空text
      // 把還沒用到的char存起來之後再判斷
      if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
      if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
    } // else
  
    strcpy( text, "" ); // 清空text
    if ( ch[0] == '\n' ) gLine ++ ;
    // 把還沒用到的char存起來之後再判斷
  
    return true ; 

  } // if


  // ********************************************************************


  if ( ch[0] == '&' ) { // 處理AND -> &&

    strcat( text, ch ) ;

    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    temp = scanf( "%c", &ch[0] ) ;

    if ( ch[0] == '&' ) {
      strcat( text, ch ) ;
      strcpy( gToken_info.data, text );
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = AND ; 
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info );
    } // if
    else {
      strcpy( gToken_info.data, text );
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = ONE_AND ; 
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info );
      if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
      if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
    } // else 


    strcpy( text, "" ); // 清空text
    if ( ch[0] == '\n' ) gLine ++ ;
    // 把還沒用到的char存起來之後再判斷
  
    return true ; 

  } // if 


  // ********************************************************************


  if ( ch[0] == '|' ) { // 處理OR -> ||

    strcat( text, ch ) ;

    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    temp = scanf( "%c", &ch[0] ) ;

    if ( ch[0] == '|' ) {
      strcat( text, ch ) ;
      strcpy( gToken_info.data, text );
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = OR ; 
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info );
    } // if
    else {
      strcpy( gToken_info.data, text );
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = STRAIGHT ; 
      gToken_info.detail_type = NOTHING ;
      gToken.push_back( gToken_info );
      if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
      if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
    } // else 

    strcpy( text, "" ); // 清空text
    if ( ch[0] == '\n' ) gLine ++ ;
  
    return true ; 

  } // if 
  // ********************************************************************

  // 這邊是在處理 字母 或 底線開頭的 IDENT
  if ( temp != EOF && ch[0] != 91 && ch[0] != 92 && ch[0] != 93
       && ch[0] != 94 && ch[0] != 96 && 64 < ch[0] && ch[0] < 123 ) {

    strcat( text, ch ) ;
    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    strcpy( for_unre, temp_ch ) ;

    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    temp = scanf( "%c", &ch[0] ) ;

    if ( ch[0] == 110 && temp_ch[0] == 92 ) {
      strcat( text, "\n" ) ;
      if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
      temp = scanf( "%c", &ch[0] ) ;
    } // if

    while ( temp != EOF && 47 < ch[0] && ch[0] < 123 && ch[0] != 58 
            && ch[0] != 59 && ch[0] != 60 && ch[0] != 61 && ch[0] != 62 && ch[0] != 63 
            && ch[0] != 64 && ch[0] != 91 && ch[0] != 92 && ch[0] != 93
            && ch[0] != 94 && ch[0] != 96 ) {

      if ( ch[0] == 92 ) {
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
        if ( ch[0] == 110 ) {
          strcat( text, "\\n" ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
        } // if
        else strcat( text, temp_ch ) ;
      } // if
      else {
        strcat( text, ch ) ;

        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
      } // else

    } // while


    if ( ch[0] == ' ' || ch[0] == '+' || ch[0] == '-' || ch[0] == '*' || ch[0] == '/'
         || ch[0] == '(' || ch[0] == ':' || ch[0] != '\n' || ch[0] != '\t' || ch[0] == '%'
         || ch[0] == '!' || ch[0] == '|' || ch[0] == '&' || ch[0] == '^' || ch[0] == ';'
         || ch[0] == '>' || ch[0] == '<' || ch[0] == '=' || ch[0] == ')' || temp == EOF ) {
      // 是個正常的ident才要

      if ( strcmp( text, "int" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = INT_TYPE;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // if
      else if ( strcmp( text, "float" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = FLOAT_TYPE;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "char" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = CHAR_TYPE;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "bool" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = BOOL_TYPE;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "string" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = STRING_TYPE;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "void" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = VOID_TYPE;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "if" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = IF;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "else" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = ELSE;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "while" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = WHILE;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "do" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = DO;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "return" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = RETURN;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "cin" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = CONSTANT;
        gToken_info.detail_type = CIN ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "cout" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = CONSTANT;
        gToken_info.detail_type = COUT ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "true" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = CONSTANT;
        gToken_info.detail_type = TRUE ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "false" ) == 0 ) {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = CONSTANT;
        gToken_info.detail_type = FALSE; 
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if
      else if ( strcmp( text, "Done" ) == 0 ) {

        while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
          if ( temp == EOF ) return false ;
        } // while

        if ( ch[0] == '(' ) {
          strcat( text, ch ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
          while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ) ;
            if ( temp == EOF ) return false ;
          } // while

          if ( ch[0] == ')' ) {
            strcat( text, ch ) ;
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = gLine ;
            gToken_info.token_type = DONE;
            gToken_info.detail_type = NOTHING ;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ) ;
          } // if

        } // if
        else {
          strcpy( gToken_info.data, text );
          gToken_info.lineNum = gLine ;
          gToken_info.token_type = IDENT;
          gToken_info.detail_type = NOTHING ;
          gToken.push_back( gToken_info );
          strcpy( text, "" ); // 清空text
        } // else
      
      } // else if
      else if ( strcmp( text, "ListAllVariables" ) == 0 ) {

        while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
          if ( temp == EOF ) return false ;
        } // while

        if ( ch[0] == '(' ) {
          strcat( text, ch ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
          while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ) ;
            if ( temp == EOF ) return false ;
          } // while

          if ( ch[0] == ')' ) {
            strcat( text, ch ) ;
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = gLine ;
            gToken_info.token_type = LISTALLVARIABLES;
            gToken_info.detail_type = NOTHING ;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ) ;
          } // if
        } // if
        else {
          strcpy( gToken_info.data, text );
          gToken_info.lineNum = gLine ;
          gToken_info.token_type = IDENT;
          gToken_info.detail_type = NOTHING ;
          gToken.push_back( gToken_info );
          strcpy( text, "" ); // 清空text
        } // else
      
      } // else if
      else if ( strcmp( text, "ListAllFunctions" ) == 0 ) {

        while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
          if ( temp == EOF ) return false ;
        } // while

        if ( ch[0] == '(' ) {
          strcat( text, ch ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
          while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ) ;
            if ( temp == EOF ) return false ;
          } // while

          if ( ch[0] == ')' ) {
            strcat( text, ch ) ;
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = gLine ;
            gToken_info.token_type = LISTALLFUCTIONS;
            gToken_info.detail_type = NOTHING ;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ) ;
          } // if
          
        } // if
        else {
          strcpy( gToken_info.data, text );
          gToken_info.lineNum = gLine ;
          gToken_info.token_type = IDENT;
          gToken_info.detail_type = NOTHING ;
          gToken.push_back( gToken_info );
          strcpy( text, "" ); // 清空text
        } // else
      
      } // else if
      else if ( strcmp( text, "ListVariable" ) == 0 ) { // 這個function裡會有參數

        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = LISTVARIABLE;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      
      } // else if
      else if ( strcmp( text, "ListFunction" ) == 0 ) { // 這個function裡會有參數

        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = LISTFUNCTION;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      
      } // else if
      else {
        strcpy( gToken_info.data, text );
        gToken_info.lineNum = gLine ;
        gToken_info.token_type = IDENT;
        gToken_info.detail_type = NOTHING ;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
      } // else if

    } // if

    if ( ch[0] == '\n' ) gLine ++ ;
    // 把還沒用到的char存起來之後再判斷
    if ( temp != EOF && ch[0] != ' ' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
    if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
  
    return true ; 

  } // if

  // ********************************************************************

  if ( ch[0] == 35 || ch[0] == 36 || ch[0] == 64 || ch[0] == 92  
       || ch[0] == 94 || ch[0] == 96 || ch[0] == 126 || ch[0] == 127 ) {
    // 不是任何東西 ex. {A

    strcat( text, ch ) ;

    strcpy( gToken_info.data, text ) ;
    gToken_info.lineNum = gLine ;
    gToken_info.error_lineNum = gLine ;
    gToken_info.token_type = UNRECOGNIZED ;
    gToken_info.detail_type = NOTHING ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ; // 清空text

    if ( ch[0] == '\n' ) gLine ++ ;
    gNum = gToken.size() - 1 ;
    Unrecognized_error() ;
    return false;

  } // if

  // ********************************************************************


  if ( temp == EOF ) {
    return false ;
  } // if

  not_quit = false ;
  is_float = false ;

  return false ;

} // GetToken()



int main() {

  bool finish = false ;

  Read_test_num() ;

  printf( "Our-C running ...\n" ) ;
  while ( !finish && GetToken( gGet_error ) ) {
    if ( !User_input() ) finish = true ;
    gNum ++ ;
  } // while

  // Print_every_variable() ;
  
  printf( "> Our-C exited ..." ) ;

  return 0 ;

} // main()
