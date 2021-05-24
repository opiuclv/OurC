# include <cstdio>
# include <cstdlib>
# include <string>
# include <vector>
# include <iostream>
# include <cstring>

using namespace std ;

void GetToken() ;
void Command() ;
void IDlessArithExpOrBexp() ;
bool BooleanOprator() ;
void NOT_ID_StartArithExpOrBexp() ;
void NOT_ID_StartArithExp() ;
void NOT_ID_StartTerm() ;
void NOT_ID_StartFactor() ;
void ArithExp() ;
void Term() ;
void Factor() ;

typedef enum {
  LEFT_PAREN = 1,
  RIGHT_PAREN = 2,
  INT = 3, // 帶有正負號
  IDENT = 4,
  DOT = 5,
  FLOAT = 6,
  PLUS = 7, // '+'
  MINUS = 8, // '-'
  MULTI = 9, // '*'
  DIV = 10, // '/'
  QUIT = 11,
  BELONG = 12, // :=
  SEMICOLON = 13, // 分號

  // BooleanOperator ::= '=' | '<>' | '>' | '<' | '>=' | '<='

  EQUAL = 14,
  NOT_EQUAL = 15, // 老大說就是不等於啦
  BIGGER = 16,
  SMALLER = 17,
  BIGGGER_EQ = 18,
  SMALLER_EQ = 19,

  // ERROR
  ERROR = 20,
  UNRECOGNIZED = 21

} Token_enum
;

struct Token {
  Token_enum token_type ;// 儲存gettoken的資料型別
  char testNum[10] ; // 儲存老大用來Debug方便所設計的testNum
  int lineNum ; // 以分號為單位來分開行
  char data[5000] ;// 儲存gettoken的內容
  bool have_defined ; // IDENT需要判斷有無被定義
  float variable_content ; // 存取要被定義的IDENT的值
} ;

vector<Token> gToken ;
vector<float> gValue ;
float gTemp_value ;
Token gToken_info ;
int gNum = 0 ;
bool gHave_error = false ; // 有錯誤所以不要印出計算結果
bool gHave_bool = false ; // 此行為布林運算不用印出計算結果
bool gFloat_operation = false ; // 這行的計算中有小數出現


void Command() { // Recursive Descent Parser的第一步 決定要走哪條路

  if ( gToken[gNum].token_type == IDENT ) {            // 第一種情況   以IDENT開頭的句子

    if ( gToken[gNum+1].token_type == BELONG ) {

      int temp_gNum = gNum ; // 用來暫存要被定義的IDENT在哪
      gToken[gNum].have_defined = true ; // 如果文法沒有錯這個IDENT就會被定義
      gNum = gNum + 2 ; // 就是GetToken的意思啦
      ArithExp() ;

      int find_id = 0 ;
      while ( find_id <= gNum ) { // 找找看有沒有這個變數
        // 因應有可能重複定義同個變數不同值，所以把目前的這個變數都更新資料
        if ( strcmp( gToken[find_id].data, gToken[temp_gNum].data ) == 0 ) {
          gToken[find_id].variable_content = gValue[0] ; // 存取IDENT的變數值
        } // if

        find_id ++ ;
      } // while

      if ( !gHave_error && !gHave_bool ) {
        if ( !gFloat_operation ) printf( "> %.0f\n", gToken[temp_gNum].variable_content ) ;
        else printf( "> %.3f\n", gToken[temp_gNum].variable_content ) ;
      } // if

    } // if
    else if ( gToken[gNum+1].token_type == ERROR ) { // ex. a:5; 錯在冒號

      printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum+1].data ) ;
      gHave_error = true ;

      int temp_Line = gToken[gNum].lineNum ;
      // 印出錯誤後把這一整行到分號都不要
      gNum ++ ;
      while ( gToken[gNum].token_type != SEMICOLON && temp_Line == gToken[gNum].lineNum ) {
        gNum ++ ;
      } // while

      return ; // 結束重跑

    } // else if
    else if ( gToken[gNum].token_type == UNRECOGNIZED ) {  // ex. abc$ := 2 + 5 ; 錯在第一個'a'

      printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum].data ) ;
      gHave_error = true ;

      int temp_Line = gToken[gNum].lineNum ;
      // 印出錯誤後把這一整行到分號都不要
      gNum ++ ;
      while ( gToken[gNum].token_type != SEMICOLON && temp_Line == gToken[gNum].lineNum ) {
        gNum ++ ;
      } // while

    } // else if
    else {
      IDlessArithExpOrBexp() ;
      if ( !gHave_error && !gHave_bool ) {
        if ( !gFloat_operation ) printf( "> %.0f\n", gValue[0] )  ; // 沒有error就印出結果
        else printf( "> %.3f\n", gValue[0] ) ;
      } // if
    } // else

    return ;
  } // if
  else if ( gToken[gNum].token_type == QUIT ) {       // 第二種情況   QUIT要結束程式
    return ;
  } // else if
  else { // 第三種情況   不是 IDENT開頭的句子
    NOT_ID_StartArithExpOrBexp() ;
    if ( !gHave_error && !gHave_bool ) {
      if ( !gFloat_operation ) printf( "> %.0f\n", gValue[0] ) ;
      else printf( "> %.3f\n", gValue[0] ) ; // 沒有error就印出結果
    } // if
  } // else

} // Command()

void IDlessArithExpOrBexp() {

  //  看看這個變數有沒有被定義過
  int find_id = 0 ;
  bool found_it = false ;
  while ( find_id < gNum && !found_it ) { // 找找看有沒有這個變數

    if ( strcmp( gToken[find_id].data, gToken[gNum].data ) == 0 ) { // 找到了就把值給取出來
      gValue.push_back( gToken[find_id].variable_content ) ;
      found_it = true ;
    } // if

    find_id ++ ;

  } // while


  if ( !found_it ) {
    printf( "> Undefined identifier: '%s'\n", gToken[gNum].data ) ;
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    gNum ++ ;
    while ( gToken[gNum].token_type != SEMICOLON && temp_Line == gToken[gNum].lineNum ) {
      gNum ++ ;
    } // while

    return ;

  } // if

  // ============================================================================================

  if ( gToken[gNum+1].token_type != PLUS && gToken[gNum+1].token_type != MINUS
       && gToken[gNum+1].token_type != QUIT && !BooleanOprator() && gToken[gNum+1].token_type != SEMICOLON 
       && gToken[gNum+1].token_type != MULTI && gToken[gNum+1].token_type != DIV ) { // 不是預期中該出現的
    printf( "> Unexpected token : '%s'\n", gToken[gNum+1].data ) ;
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    gNum ++ ;
    while ( gToken[gNum].token_type != SEMICOLON && temp_Line == gToken[gNum].lineNum ) {
      gNum ++ ;
    } // while

  } // if

  while ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS
          || gToken[gNum+1].token_type == MULTI || gToken[gNum+1].token_type == DIV ) {

    if ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS ) {

      if ( gToken[gNum+1].token_type == PLUS ) {
        gNum = gNum + 2;
        Term(); // 文法是給Term沒錯

        // 做計算
        gTemp_value = gValue[gValue.size()-2] + gValue[gValue.size()-1] ; // 應該是倒數第二個加最後一個再繼續遞迴
        gValue.pop_back() ; // 算完就丟掉
        gValue.pop_back() ; // 算完就丟掉
        gValue.push_back( gTemp_value ) ; // 加入算好的值

      } // if

      if ( gToken[gNum+1].token_type == MINUS ) {
        gNum = gNum + 2;
        Term(); // 文法是給Term沒錯

        // 做計算
        gTemp_value = gValue[gValue.size()-2] - gValue[gValue.size()-1] ; // 應該是倒數第二個減最後一個再繼續遞迴
        gValue.pop_back() ; // 算完就丟掉
        gValue.pop_back() ; // 算完就丟掉
        gValue.push_back( gTemp_value ) ; // 加入算好的值
 
      } // if

    } // if
    else if ( gToken[gNum+1].token_type == MULTI || gToken[gNum+1].token_type == DIV ) {

      if ( gToken[gNum+1].token_type == MULTI ) {
        gNum = gNum + 2;
        Factor() ;
        // 做計算
        gTemp_value = gValue[gValue.size()-2] * gValue[gValue.size()-1] ;
        gValue.pop_back() ; // 算完就丟掉
        gValue.pop_back() ; // 算完就丟掉
        gValue.push_back( gTemp_value ) ; // 加入算好的值

      } // if

      if ( gToken[gNum+1].token_type == DIV ) {

        gNum = gNum + 2;
        Factor() ;
        if ( atoi( gToken[gNum].data ) == 0 ) { // 除以零的錯誤
          printf( "ERROR\n" ) ;

          // 印出錯誤後把這一整行到分號都不要
          gNum ++ ;
          while ( gToken[gNum].token_type != SEMICOLON ) {
            gNum ++ ;
          } // while

          return ; // 結束重跑

        } // if
        else { // 做計算
          if ( gValue[gValue.size()-2] < gValue[gValue.size()-1] ) gFloat_operation = true ;
          gTemp_value = gValue[gValue.size()-2] / gValue[gValue.size()-1] ;
          gValue.pop_back() ; // 算完就丟掉
          gValue.pop_back() ; // 算完就丟掉
          gValue.push_back( gTemp_value ) ; // 加入算好的值
        } // else

      } // if

    } // else if

  } // while


  float value1 = gValue[0] ; // 布林前計算的值先存起來
  gValue.clear() ; // 清空準備做下一次計算

  if ( BooleanOprator() ) { // 如果有出現布林運算

    gHave_bool = true ;
    int temp_gNum = gNum + 1 ; // 先記起來布林符號出現在哪
    gNum = gNum + 2 ;

    ArithExp() ;

    float value2 = gValue[0] ; // 布林後面的計算再存起來

    float console = value1 - value2 ; // 用來確保差距大於0.0001

    if ( gToken[temp_gNum].token_type == EQUAL && -0.0001 < console && console < 0.0001 ) {
      printf( "> true\n" ) ;
    } // if
    else if ( gToken[temp_gNum].token_type == EQUAL ) {
      if ( 0.0001 < console || console < -0.0001 ) printf( "> false\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == NOT_EQUAL ) {
      if ( 0.0001 < console || console < -0.0001 ) printf( "> true\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == NOT_EQUAL && -0.0001 < console && console < 0.0001 ) {
      printf( "> false\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGER && console > 0.0001 ) {
      printf( "> true\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGER && console <= 0.0001 ) {
      printf( "> false\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console >= 0.0001 ) {
      printf( "> true\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console < 0.0001 ) {
      printf( "> false\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER && console < -0.0001 ) {
      printf( "> true\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER && console >= -0.0001 ) {
      printf( "> false\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console <= -0.0001 ) {
      printf( "> true\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console > -0.0001 ) {
      printf( "> false\n" ) ;
    } // else if

  } // if


  return;

} // IDlessArithExpOrBexp()

bool BooleanOprator() {
  if ( gToken[gNum+1].token_type == EQUAL || gToken[gNum+1].token_type == NOT_EQUAL 
       || gToken[gNum+1].token_type == BIGGER || gToken[gNum+1].token_type == SMALLER 
       || gToken[gNum+1].token_type == BIGGGER_EQ || gToken[gNum+1].token_type == SMALLER_EQ ) return true ;
  else return false ;

} // BooleanOprator()

void NOT_ID_StartArithExpOrBexp() {

  NOT_ID_StartArithExp() ;

  float value1 = gValue[0] ; // 布林前計算的值先存起來
  gValue.clear() ; // 清空準備做下一次計算

  if ( BooleanOprator() ) { // 如果有出現布林運算

    gHave_bool = true ;
    int temp_gNum = gNum + 1 ; // 先記起來布林符號出現在哪
    gNum = gNum + 2 ;

    ArithExp() ;

    float value2 = gValue[0] ; // 布林後面的計算再存起來

    float console = value1 - value2 ; // 用來確保差距大於0.0001

    if ( gToken[temp_gNum].token_type == EQUAL && -0.0001 < console && console < 0.0001 ) {
      printf( "> true\n" ) ;
    } // if
    else if ( gToken[temp_gNum].token_type == EQUAL ) {
      if ( 0.0001 < console || console < -0.0001 ) printf( "> false\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == NOT_EQUAL ) {
      if ( 0.0001 < console || console < -0.0001 ) printf( "> true\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == NOT_EQUAL && -0.0001 < console && console < 0.0001 ) {
      printf( "> false\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGER && console > 0.0001 ) {
      printf( "> true\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGER && console <= 0.0001 ) {
      printf( "> false\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console >= 0.0001 ) {
      printf( "> true\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console < 0.0001 ) {
      printf( "> false\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER && console < -0.0001 ) {
      printf( "> true\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER && console >= -0.0001 ) {
      printf( "> false\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console <= -0.0001 ) {
      printf( "> true\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console > -0.0001 ) {
      printf( "> false\n" ) ;
    } // else if

  } // if


  return;
  
} // NOT_ID_StartArithExpOrBexp()

void NOT_ID_StartArithExp() {

  NOT_ID_StartTerm() ;

  // 這邊用+1來代表PeekToken()
  if ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS || BooleanOprator()
       || gToken[gNum+1].token_type == MULTI || gToken[gNum+1].token_type == DIV 
       || gToken[gNum+1].token_type == SEMICOLON || gToken[gNum+1].token_type == QUIT  ) {
    ; // 沒事幹 是為了else才出現的
  } // if
  else if ( gToken[gNum+1].token_type == RIGHT_PAREN ) { // ex.遇到右括號已經結束此括號內容判斷 所以返回繼續判斷
    gNum ++ ;
    return;

  } // else if
  else {
    printf( "> Unexpected token : '%s'\n", gToken[gNum+1].data ) ;
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    gNum ++ ;
    while ( gToken[gNum].token_type != SEMICOLON && temp_Line == gToken[gNum].lineNum ) {
      gNum ++ ;
    } // while

    return ; // 結束重跑

  } // else


  while ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS ) { // 重複零到多次 所以要用迴圈
    if ( gToken[gNum+1].token_type == PLUS ) {
      gNum = gNum + 2;
      Term();

      // 做計算
      gTemp_value = gValue[gValue.size()-2] + gValue[gValue.size()-1] ; // 應該是倒數第二個加最後一個再繼續遞迴
      gValue.pop_back() ; // 算完就丟掉
      gValue.pop_back() ; // 算完就丟掉
      gValue.push_back( gTemp_value ) ; // 加入算好的值

    } // if

    if ( gToken[gNum+1].token_type == MINUS ) {
      gNum = gNum + 2;
      Term();

      // 做計算
      gTemp_value = gValue[gValue.size()-2] - gValue[gValue.size()-1] ; // 應該是倒數第二個減最後一個再繼續遞迴
      gValue.pop_back() ; // 算完就丟掉
      gValue.pop_back() ; // 算完就丟掉
      gValue.push_back( gTemp_value ) ; // 加入算好的值

    } // if

  } // while

  return;

} // NOT_ID_StartArithExp()

void NOT_ID_StartTerm() {

  NOT_ID_StartFactor() ;

  // 這邊用+1來代表PeekToken()

  while ( gToken[gNum+1].token_type == MULTI || gToken[gNum+1].token_type == DIV ) { // 重複零到多次 所以要用迴圈

    if ( gToken[gNum+1].token_type == MULTI ) {
      gNum = gNum + 2;
      Factor() ;
      // 做計算
      gTemp_value = gValue[gValue.size()-2] * gValue[gValue.size()-1] ;
      gValue.pop_back() ; // 算完就丟掉
      gValue.pop_back() ; // 算完就丟掉
      gValue.push_back( gTemp_value ) ; // 加入算好的值

    } // if

    if ( gToken[gNum+1].token_type == DIV ) {

      gNum = gNum + 2;
      Factor() ;

      if ( atoi( gToken[gNum].data ) == 0 ) { // 除以零的錯誤
        printf( "ERROR\n" ) ;

        // 印出錯誤後把這一整行到分號都不要
        gNum ++ ;
        while ( gToken[gNum].token_type != SEMICOLON ) {
          gNum ++ ;
        } // while

        return ; // 結束重跑
      } // if
      else { // 做計算
        if ( gValue[gValue.size()-2] < gValue[gValue.size()-1] ) gFloat_operation = true ;
        gTemp_value = gValue[gValue.size()-2] / gValue[gValue.size()-1] ;
        gValue.pop_back() ; // 算完就丟掉
        gValue.pop_back() ; // 算完就丟掉
        gValue.push_back( gTemp_value ) ; // 加入算好的值
      } // else 

    } // if

  } // while

  return;
} // NOT_ID_StartTerm()

void NOT_ID_StartFactor() {
  // factor判斷不應該peekToken

  if ( gToken[gNum].token_type == INT || gToken[gNum].token_type == FLOAT ) {
    if ( gToken[gNum].token_type == INT ) gValue.push_back( atoi( gToken[gNum].data ) ) ;
    if ( gToken[gNum].token_type == FLOAT ) {
      gValue.push_back( atof( gToken[gNum].data ) ) ;
      gFloat_operation = true ;
    } // if

    return; // 如果是[SIGN] NUM 或是IDENT 就結束了

  } // if
  else if ( gToken[gNum].token_type == IDENT ) {

    int find_id = 0 ;
    bool found_it = false ;
    while ( find_id < gNum ) { // 找找看有沒有這個變數

      if ( strcmp( gToken[find_id].data, gToken[gNum].data ) == 0 ) { // 找到了就把值給取出來
        gValue.push_back( gToken[find_id].variable_content ) ;
        found_it = true ;
      } // if

      find_id ++ ;

    } // while

    if ( !found_it ) {
      printf( "> Undefined identifier: '%s'\n", gToken[gNum].data ) ;
      gHave_error = true ;

      int temp_Line = gToken[gNum].lineNum ;
      // 印出錯誤後把這一整行到分號都不要
      gNum ++ ;
      while ( gToken[gNum].token_type != SEMICOLON && temp_Line == gToken[gNum].lineNum ) {
        gNum ++ ;
      } // while

      return ;

    } // if

    return;

  } // else if
  else if ( gToken[gNum].token_type == LEFT_PAREN ) {
    gNum ++ ;
    ArithExp() ; // 這裡還要判斷右括號 才能知道有沒有ERROR
    // 此時回來的是右括號
  } // else if
  else if ( gToken[gNum].token_type == UNRECOGNIZED ) {  // ex. 2 + $$ - 5 ; 錯在第一個'$'
    printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum].data ) ;
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    gNum ++ ;
    while ( gToken[gNum].token_type != SEMICOLON && temp_Line == gToken[gNum].lineNum ) {
      gNum ++ ;
    } // while

  } // else if
  else if ( gToken[gNum].token_type != SEMICOLON && gToken[gNum].token_type != QUIT ) { 
    printf( "> Unexpected token : '%s'\n", gToken[gNum].data ) ; // ex . 2 + * + 5 ; 錯在'*'
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    gNum ++ ;
    while ( gToken[gNum].token_type != SEMICOLON && temp_Line == gToken[gNum].lineNum ) {
      gNum ++ ;
    } // while

  } // else if

  return;

} // NOT_ID_StartFactor()

void ArithExp()
{
  Term();
  // 這邊用+1來代表PeekToken()

  if ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS || BooleanOprator() 
       || gToken[gNum+1].token_type == MULTI || gToken[gNum+1].token_type == DIV 
       || gToken[gNum+1].token_type == SEMICOLON || gToken[gNum+1].token_type == QUIT ) {
    ; // 沒事幹 是為了else才出現的
  } // if
  else if ( gToken[gNum+1].token_type == RIGHT_PAREN ) { // ex.遇到右括號已經結束此括號內容判斷 所以返回繼續判斷

    gNum ++ ;
    return;

  } // else if
  else {
    printf( "> Unexpected token : '%s'\n", gToken[gNum+1].data ) ;
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    gNum ++ ;
    while ( gToken[gNum].token_type != SEMICOLON && temp_Line == gToken[gNum].lineNum ) {
      gNum ++ ;
    } // while

    return ; // 結束重跑

  } // else


  while ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS ) { // 重複零到多次 所以要用迴圈
    if ( gToken[gNum+1].token_type == PLUS ) {
      gNum = gNum + 2;
      Term();

      // 做計算
      gTemp_value = gValue[gValue.size()-2] + gValue[gValue.size()-1] ; // 應該是倒數第二個加最後一個再繼續遞迴
      gValue.pop_back() ; // 算完就丟掉
      gValue.pop_back() ; // 算完就丟掉
      gValue.push_back( gTemp_value ) ; // 加入算好的值

    } // if

    if ( gToken[gNum+1].token_type == MINUS ) {
      gNum = gNum + 2;
      Term();

      // 做計算
      gTemp_value = gValue[gValue.size()-2] - gValue[gValue.size()-1] ; // 應該是倒數第二個減最後一個再繼續遞迴
      gValue.pop_back() ; // 算完就丟掉
      gValue.pop_back() ; // 算完就丟掉
      gValue.push_back( gTemp_value ) ; // 加入算好的值

    } // if

  } // while

  if ( gToken[gNum+1].token_type == RIGHT_PAREN ) { // 括號內有括號 會變成在計算中遇到右括號 所以無法在上面return完判斷右括號

    gNum ++ ;
    return;

  } // if

  return;
} // ArithExp()

void Term()
{
  Factor() ;

  // 這邊用+1來代表PeekToken()

  while ( gToken[gNum+1].token_type == MULTI || gToken[gNum+1].token_type == DIV ) { // 重複零到多次 所以要用迴圈

    if ( gToken[gNum+1].token_type == MULTI ) {
      gNum = gNum + 2;
      Factor() ;
      // 做計算
      gTemp_value = gValue[gValue.size()-2] * gValue[gValue.size()-1] ;
      gValue.pop_back() ; // 算完就丟掉
      gValue.pop_back() ; // 算完就丟掉
      gValue.push_back( gTemp_value ) ; // 加入算好的值

    } // if
    
    if ( gToken[gNum+1].token_type == DIV ) {
      gNum = gNum + 2;
      Factor() ;
      
      if ( atoi( gToken[gNum].data ) == 0 ) { // 除以零的錯誤
        printf( "ERROR\n" ) ;

        // 印出錯誤後把這一整行到分號都不要
        gNum ++ ;
        while ( gToken[gNum].token_type != SEMICOLON ) {
          gNum ++ ;
        } // while

        return ; // 結束重跑

      } // if
      else { // 做計算
        if ( gValue[gValue.size()-2] < gValue[gValue.size()-1] ) gFloat_operation = true ;
        gTemp_value = gValue[gValue.size()-2] / gValue[gValue.size()-1] ;
        gValue.pop_back() ; // 算完就丟掉
        gValue.pop_back() ; // 算完就丟掉
        gValue.push_back( gTemp_value ) ; // 加入算好的值

      } // else
    } // if
  } // while

  return;
  
} // Term()

void Factor()
{
  // factor判斷不應該peekToken

  if ( gToken[gNum].token_type == INT || gToken[gNum].token_type == FLOAT ) {
    if ( gToken[gNum].token_type == INT ) gValue.push_back( atoi( gToken[gNum].data ) ) ;
    if ( gToken[gNum].token_type == FLOAT ) {
      gValue.push_back( atof( gToken[gNum].data ) ) ;
      gFloat_operation = true ;
    } // if

    return; // 如果是[SIGN] NUM 或是IDENT 就結束了

  } // if
  else if ( gToken[gNum].token_type == IDENT ) {

    int find_id = 0 ;
    bool found_it = false ;
    while ( find_id < gNum && !found_it ) { // 找找看有沒有這個變數

      if ( strcmp( gToken[find_id].data, gToken[gNum].data ) == 0 ) { // 找到了就把值給取出來
        gValue.push_back( gToken[find_id].variable_content ) ;
        found_it = true ;
      } // if

      find_id ++ ;

    } // while


    if ( !found_it ) {
      printf( "> Undefined identifier: '%s'\n", gToken[gNum].data ) ;
      gHave_error = true ;

      int temp_Line = gToken[gNum].lineNum ;
      // 印出錯誤後把這一整行到分號都不要
      gNum ++ ;
      while ( gToken[gNum].token_type != SEMICOLON && temp_Line == gToken[gNum].lineNum ) {
        gNum ++ ;
      } // while

      return ;

    } // if

    return;

  } // else if
  else if ( gToken[gNum].token_type == LEFT_PAREN ) {
    gNum ++ ;
    ArithExp() ; // 這裡還要判斷右括號 才能知道有沒有ERROR
    // 回來的是右括號
  } // else if
  else if ( gToken[gNum].token_type == UNRECOGNIZED ) {  // ex. 2 + $$ - 5 ; 錯在第一個'$'
    printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum].data ) ;
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    gNum ++ ;
    while ( gToken[gNum].token_type != SEMICOLON && temp_Line == gToken[gNum].lineNum ) {
      gNum ++ ;
    } // while

  } // else if
  else if ( gToken[gNum].token_type != SEMICOLON && gToken[gNum].token_type != QUIT ) { 
    printf( "> Unexpected token : '%s'\n", gToken[gNum].data ) ; // ex . 2 + * + 5 ; 錯在'*'
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    gNum ++ ;
    while ( gToken[gNum].token_type != SEMICOLON && temp_Line == gToken[gNum].lineNum ) {
      gNum ++ ;
    } // while

  } // else if

  return;
} // Factor()



// ********************************處理Token************************************************


// 以quit為讀取一次的終止點
// 以分號為讀取一行的分隔點
void GetToken() { // GetToken 先全部照單全收，要印的時候用C語言把歸類成 float的token，用%3f的函數去印

  // 宣吿
  char text[5000] = "" ; // 用來暫存token
  char ch[] = "0" ; // 用來讀檔
  char temp_ch[] = "0" ; // 輔助讀檔
  char temp ;
  char for_unre[] = "0" ; // 給unrecognized用的
  int line = 0 ;
  bool for_break = false ; // 給 PAL用的 break()
  bool is_sign = false ;
  bool not_quit = false ; // 如果quit是一個變數
  bool is_float = false ; // 是否為浮點數

  gToken_info.have_defined = false ; // 這裡只是給個初始值 真正判斷會在parser那邊
  gToken_info.variable_content = 0 ;

  // ********************************************************************
  scanf( "%c", &ch[0] ); // 先讀第一個測試編號
  while ( ch[0] != EOF && ch[0] != '\n' && 57 > ch[0] && ch[0] > 48 ) {
    strcat( text, ch ) ;
    scanf( "%c", &ch[0] ); // 先讀第一個測試編號
  } // while

  strcpy( gToken_info.testNum, text ) ;
  strcpy( text, "" ) ; // 清空text
  // ********************************************************************

  while ( temp != EOF ) { // 讀到結束

    while ( temp != EOF && gToken_info.token_type != QUIT ) { // 讀到換行 \n 還不知道老大input怎麼給 先不動
      // ex. 3+2 = 5
      // ex. 3+-2 = 1 因為後面那個減是負號的意思

      // ********************************************************************
      if ( ch[0] == '+' || ch[0] == '*' || ch[0] == '-' ) { // 處理加乘

        if ( temp_ch[0] == '\n' || temp_ch[0] == '=' || temp_ch[0] == ';' ) is_sign = true ; // ex. a:=-9;
        else {
          strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] ); // 如果減號前面有其他運算元 代表是負號

          if ( ch[0] == '-' ) {
            is_sign = true ;
          } // if
          
          if ( ch[0] == '+' ) {
            is_sign = true ;
          } // if
          
        } // else


        if ( temp_ch[0] == '+' ) { // 儲存運算元
          strcat( text, temp_ch ) ;
          strcpy( gToken_info.data, text ) ; // 存取token資訊
          gToken_info.lineNum = line ; // 看他屬於哪一行
          gToken_info.token_type = PLUS ;
          gToken.push_back( gToken_info ) ;
          strcpy( text, "" ) ; // 清空text
        } // if
        
        if ( temp_ch[0] == '-' ) { // 儲存運算元
          strcat( text, temp_ch ) ;
          strcpy( gToken_info.data, text ) ; // 存取token資訊
          gToken_info.lineNum = line ; // 看他屬於哪一行
          gToken_info.token_type = MINUS ;
          gToken.push_back( gToken_info ) ;
          strcpy( text, "" ) ; // 清空text
        } // if
        
        if ( temp_ch[0] == '*' ) { // 儲存運算元
          strcat( text, temp_ch ) ;
          strcpy( gToken_info.data, text ) ; // 存取token資訊
          gToken_info.lineNum = line ; // 看他屬於哪一行
          gToken_info.token_type = MULTI ;
          gToken.push_back( gToken_info ) ;
          strcpy( text, "" ) ; // 清空text
        } // if

        if ( is_sign ) { // 是sign才需要再讀一次看是不是接數字
          strcpy( temp_ch, ch ); // 儲存上一個 ch
          scanf( "%c", &ch[0] ); // 如果減號前面有其他運算元 代表是負號
        } // if

        if ( is_sign && temp_ch[0] == '-' && 58 > ch[0] && ch[0] > 47 ) { // ex. a:=-9+-18;
          strcat( text, "-" ) ;
        } // if

        if ( is_sign && temp_ch[0] == '+' && 58 > ch[0] && ch[0] > 47 ) { // ex. a:=-9+-18;
          strcat( text, "+" ) ;
        } // if


        for_break = true ;
        
      } // if

      // ********************************************************************

      if ( ch[0] == '/' ) { // 遇到除號 或是 註解
        strcat( text, ch ) ;
        strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] );

        if ( temp_ch[0] == '/' && ch[0] == '/' ) { // 是註解

          scanf( "%c", &ch[0] );
          while ( ch[0] != '\n' && ch[0] != EOF ) { // 把註解讀掉
            strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            scanf( "%c", &ch[0] );
          } // while
        } // if
        else {
          strcpy( gToken_info.data, text ) ; // 存取token資訊
          gToken_info.lineNum = line ; // 看他屬於哪一行
          gToken_info.token_type = DIV ;
          gToken.push_back( gToken_info ) ;
        } // else

        strcpy( text, "" ) ; // 清空text
      } // if


      // ********************************************************************

      if ( ch[0] == ':' ) { // 遇到冒號的處理
        strcat( text, ch ) ;
        strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] );
        if ( ch[0] == '=' ) {
          strcat( text, ch ) ;
          strcpy( gToken_info.data, ":=" ) ; // ex. a := 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = BELONG ;
          gToken.push_back( gToken_info ) ;
          strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] );
        } // if
        else if ( ch[0] == ':' ) { // a::=+-*/ 錯在第一個冒號
          strcpy( gToken_info.data, text ) ; // ex. a: ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = ERROR ;
          gToken.push_back( gToken_info ) ;
        } // else if
        else {
          strcpy( gToken_info.data, text ) ; // ex. a:5; 錯在冒號
          gToken_info.lineNum = line ;
          gToken_info.token_type = ERROR ;
          gToken.push_back( gToken_info ) ;
        } // else

        strcpy( text, "" ) ;
      } // if

      // ********************************************************************

      if ( ch[0] == '<' || ch[0] == '>' || ch[0] == '=' ) { // 遇到比較的運算元

        strcat( text, ch );
        strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] );
        if ( temp_ch[0] == '=' ) {
          strcpy( gToken_info.data, text ) ; // ex. a = 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = EQUAL;
          gToken.push_back( gToken_info );
        } // if
        else if ( temp_ch[0] == '<' && ch[0] == '=' ) {
          strcat( text, ch );
          strcpy( gToken_info.data, text ) ; // ex. a <= 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = SMALLER_EQ;
          gToken.push_back( gToken_info );
          strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] );
        } // else if
        else if ( temp_ch[0] == '>' && ch[0] == '=' ) {
          strcat( text, ch );
          strcpy( gToken_info.data, text ) ; // ex. a >= 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = BIGGGER_EQ;
          gToken.push_back( gToken_info );
          strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] );
        } // else if
        else if ( temp_ch[0] == '<' && ch[0] != '=' ) {
          strcat( text, ch );
          strcpy( gToken_info.data, text ) ; // ex. a < 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = SMALLER;
          gToken.push_back( gToken_info );
          strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] );
        } // else if
        else if ( temp_ch[0] == '>' && ch[0] != '=' ) {
          strcat( text, ch );
          strcpy( gToken_info.data, text ) ; // ex. a > 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = BIGGER;
          gToken.push_back( gToken_info );
          strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] );
        } // else if
        else if ( temp_ch[0] == '<' && ch[0] == '>' ) { // <>這個就是不等於啦 老大說的
          strcat( text, ch );
          strcpy( gToken_info.data, text ) ; // ex. a <> 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = NOT_EQUAL;
          gToken.push_back( gToken_info );
          strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] );
        } // else if

        for_break = true ;
        strcpy( text, "" ) ;

      } // if

      // ********************************************************************

      if ( ch[0] == '(' ) {
        strcpy( gToken_info.data, "(" ) ; // 存取token資訊
        gToken_info.lineNum = line ;
        gToken_info.token_type = LEFT_PAREN ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ;

        strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] );
        while ( ch[0] == '(' ) { // ex. (((a-2)+1)*2)-3) 遇到很多左括號的情況
          strcpy( gToken_info.data, "(" ) ; // 存取token資訊
          gToken_info.lineNum = line ;
          gToken_info.token_type = LEFT_PAREN ;
          gToken.push_back( gToken_info ) ;
          strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] );
        } // while
        
        for_break = true ;
      } // if

      if ( ch[0] == ')' ) {
        strcpy( gToken_info.data, ")" ) ; // 存取token資訊
        gToken_info.lineNum = line ;
        gToken_info.token_type = RIGHT_PAREN ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text
        scanf( "%c", &ch[0] );
        for_break = true ;
      } // if

      // ********************************************************************

      if ( ch[0] == ';' ) { // 分號的處理
        strcpy( gToken_info.data, ";" ) ; // 存取token資訊
        gToken_info.lineNum = line ;
        gToken_info.token_type = SEMICOLON ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text
        for_break = true ;
        line ++ ; // 下一次讀取已經不是這行了 所以++

        strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] );
        // 讀下一個東西 因為還沒有quit

      } // if

      // ********************************************************************

      if ( 58 > ch[0] && ch[0] > 47 && !for_break ) { // 數字開頭的處理
        strcat( text, ch ) ;
        strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] );

        // 如果後面還是數字就繼續合併
        while ( ch[0] != '\n' && ch[0] != EOF && ch[0] != ' ' && ch[0] > 47 && ch[0] < 58  ) {
          strcat( text, ch ) ;
          strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] );
        } // while

        if ( ch[0] == '.' ) { // 浮點數的處理
          strcat( text, ch ) ;
          strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] );
          is_float = true ;
          while ( ch[0] != '\n' && ch[0] != EOF && ch[0] != ' ' && ch[0] > 47 && ch[0] < 58  ) {
            strcat( text, ch ) ;
            strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            scanf( "%c", &ch[0] );
          } // while
        } // if

        strcpy( gToken_info.data, text ) ; // 存取token資訊
        gToken_info.lineNum = line ;
        if ( !is_float ) gToken_info.token_type = INT ;
        else gToken_info.token_type = FLOAT ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text
        for_break = true ;
      } // if

      // ********************************************************************

      if ( !for_break && ch[0] == 'q' ) { // quit 的處理

        if ( temp_ch[0] == '\n' ) not_quit = true ; // 是否是真的結束還是只是一個token
        strcat( text, ch ) ;
        strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] ) ;

        while ( ch[0] != EOF && ch[0] != ' ' && ch[0] != '\n' && ch[0] != ';' ) {
          strcat( text, ch ) ;
          strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] ) ;
        } // while

        if ( strcmp( text, "quit" ) == 0 && !not_quit ) { // 確認是不是讀到quit
          if ( ch[0] == '\n' || ch[0] == ' ' ) { // quit後面沒東西
            strcpy( gToken_info.data, text ) ;
            gToken_info.lineNum = line ;
            gToken_info.token_type = QUIT ;
            gToken.push_back( gToken_info ) ;
          } // if
        } // if
        else { // q開頭的IDENT 包含 不是結束的quit
          strcpy( gToken_info.data, text ) ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = IDENT ;
          gToken.push_back( gToken_info ) ;
        } // else if

        strcpy( text, "" ) ; // 清空text

      } // if

      // ********************************************************************

      if ( !for_break && ch[0] != ' ' && 29 < ch[0] && ch[0] < 40 ) { // 不是任何東西 ex. $$

        strcat( text, ch ) ;
        strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] ) ;

        strcpy( gToken_info.data, text ) ;
        gToken_info.lineNum = line ;
        gToken_info.token_type = UNRECOGNIZED ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text

        while ( ch[0] != EOF && ch[0] != '\n' && ch[0] != ';' ) {
          strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] ) ;
        } // while

        line ++ ;

      } // if

      // ********************************************************************

      // 這邊是在處理 字母 或 特殊符號開頭的 IDENT
      if ( !for_break && ch[0] != ' ' && ch[0] != EOF && ch[0] != '\n' && ch[0] != ':' 
           && ch[0] != ' ' && ch[0] != ';' && ch[0] != '=' && ch[0] != '(' && ch[0] != ')' 
           && ch[0] != '+' && ch[0] != '-' && ch[0] != '*' && ch[0] != '/' && ch[0] != '\t' ) { 

        strcat( text, ch ) ;
        strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        strcpy( for_unre, temp_ch ) ;


        scanf( "%c", &ch[0] ) ;
        strcpy( temp_ch, ch ) ; // 儲存上一個 ch


        while ( ch[0] != EOF && ch[0] != '\n' && ch[0] != ':' && ch[0] != ' ' && ch[0] != ';' 
                && ch[0] != '=' && 47 < ch[0] && ch[0] < 123 && ch[0] != ')' && ch[0] != ')' 
                && ch[0] != '+' && ch[0] != '-' && ch[0] != '*' && ch[0] != '/' && ch[0] != '\t'  ) {
          strcat( text, ch ) ;
          strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] ) ;
        } // while

        if ( ch[0] == ' ' || ch[0] == '+' || ch[0] == '-' || ch[0] == '*' || ch[0] == '/' 
             || ch[0] == '(' || ch[0] == ':' || ch[0] != '\t' || ch[0] != '\t' ) { // 是個正常的ident才要
          strcpy( gToken_info.data, text );
          gToken_info.lineNum = line;
          gToken_info.token_type = IDENT;
          gToken.push_back( gToken_info );
          strcpy( text, "" ); // 清空text
        } // if
        else { // 代表有接到奇怪的符號 不是ident該出現der
          strcpy( gToken_info.data, for_unre ); // 錯在第一個字
          gToken_info.lineNum = line;
          gToken_info.token_type = UNRECOGNIZED;
          gToken.push_back( gToken_info );
          strcpy( text, "" ); // 清空text

          while ( ch[0] != EOF && ch[0] != '\n' && ch[0] != ';' ) {
            strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            scanf( "%c", &ch[0] ) ;
          } // while

          line ++ ;

        } // else

      } // if


      // ********************************************************************

      if ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) { // 把空白跟換行讀掉

        temp = scanf( "%c", &ch[0] );
        while ( ch[0] != EOF && ch[0] == ' ' && ch[0] == '\n' ) {
          temp = scanf( "%c", &ch[0] );
        } // while
        
      } // if

      for_break = false ; // 跑完一次就可以解除for_break狀態
      not_quit = false ;
      is_float = false ;
      is_sign = false ;
      
    } // while

    /*
    int k = 0 ;
    while ( gToken.size() != 0 && k < gToken.size() ) {
        cout << " " << gToken[k].data << " " << gToken[k].token_type
             << " " << gToken[k].lineNum << "\n" ;
        k ++ ;
    } // while
    */

    gNum = 0 ;
    return ;

  } // while
  
  if ( ch[0] == EOF ) {
    printf( "> ERROR (no more input) : END-OF-FILE encountered\n" ) ;
    return ;
  } // if
  
} // GetToken()

int main() {
  printf( "Program starts...\n" ) ;
  GetToken();
  // 好像有除以零就會莫名其妙在這個地方卡住

  while ( gNum < gToken.size() - 2 && gToken[gNum].token_type != QUIT ) { 
    // 迴圈一次run一行(到分號)   -2是因為減一個size()減一個quit
    // printf( "有進喔！＾＾ 從'%s'進去的\n", gToken[gNum].data ) ;

    Command() ; // 進入parser運算

    gHave_error = false ; // 初始化
    gHave_bool = false ; // 初始化
    gFloat_operation = false ;
    gValue.clear() ; // 初始化

    // 退出來會在分號
    if ( gToken[gNum+1].token_type == SEMICOLON ) gNum = gNum + 2 ; // 要跳過分號
    else gNum ++ ;
  } // while

  printf( "> Program exits..." ) ;

} // main()


