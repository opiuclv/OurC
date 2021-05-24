# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <vector>
# include <iostream>
# include <string.h>

using namespace std ;

bool gGet_error = false ;
bool GetToken( bool get_error ) ;
bool Command() ;
bool IDlessArithExpOrBexp() ;
bool BooleanOprator() ;
bool NOT_ID_StartArithExpOrBexp() ;
bool NOT_ID_StartArithExp() ;
bool NOT_ID_StartTerm() ;
bool NOT_ID_StartFactor() ;
bool ArithExp() ;
bool Term() ;
bool Factor() ;
float Rounding( float value ) ;

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
  UNRECOGNIZED = 20,
  UNEXPECTED = 21, // 在GetToken就出現了需要使用unex判斷的地方 例如：3*-(5+2) ; 錯在'('

  SIGN = 22

} Token_enum
;

struct Token {
  Token_enum token_type ;// 儲存gettoken的資料型別
  char testNum[10] ; // 儲存老大用來Debug方便所設計的testNum
  int lineNum ; // 以分號為單位來分開行
  char data[500] ;// 儲存gettoken的內容
  bool have_defined ; // IDENT需要判斷有無被定義
  bool is_int ;
  float variable_content ; // 存取要被定義的IDENT的值
} ;

vector<Token> gToken ;
vector<float> * gValue = new vector<float>() ;
float gTemp_value = 0.0 ;
Token gToken_info ;
int gNum = 0 ;
bool gHave_error = false ; // 有錯誤所以不要印出計算結果
bool gHave_bool = false ; // 此行為布林運算不用印出計算結果
bool gFloat_operation = false ; // 這行的計算中有小數出現
bool gBool_Ans = false ; // 布林運算的結果
bool gHas_belong = false ; // 這行有出現assign的符號 所以後面在出現 bool 是錯的
int gLeft_p_num = 0 ; // 用來計算出現過幾個左括號，如果有多的右括號就是 Unexpected

char gTemp_char[10] = "" ; // 用來存取暫時讀進來還沒用的的字元 ex; a+5 的+ 用來判斷 a 是一個獨立的token
bool gLast_read_char_is_change_line = false ; 
// 這個是用來判斷該行最後一個token error時484已經讀掉換行字元了

int gLine = 0 ;

bool gForm_main_into_GetToken = false ;


// ERROR
void Unexpected_error() ;
bool Undefined_error() ;
void Unrecognized_error() ;

bool Command() { // 回傳false 代表結束程式 回傳true代表還要繼續執行


  if ( gToken[gNum].token_type == IDENT ) {  // 第一種情況   以IDENT開頭的句子

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( gToken[gNum].token_type == BELONG ) { // IDENT :=

      gHas_belong = true ; // 出現過 ':='

      int temp_gNum = gNum - 1 ; // 用來暫存要被定義的IDENT在哪

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( !ArithExp() && !gHave_error ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gHave_error ) {
          gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
          Unexpected_error() ;
        } // if
        // /////////////////////////////////////////////////////////////////////////////////////////////
        return true ;
      } // if 

      if ( gToken[gNum].token_type != SEMICOLON && !gHave_error ) { // 結束出來會是分號
        // /////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////
        return true ;
      } // if 


      if ( !gHave_error ) {

        gToken[temp_gNum].have_defined = true ; // 如果文法沒有錯這個IDENT就會被定義
        int find_id = 0 ;
        while ( find_id <= gNum ) { // 找找看有沒有這個變數
          // 因應有可能重複定義同個變數不同值，所以把目前的這個變數都更新資料
          if ( strcmp( gToken[find_id].data, gToken[temp_gNum].data ) == 0 ) {
            if ( gValue->size() > 0 ) {
              gToken[find_id].variable_content = * gValue[0].data(); // 存取IDENT的變數值
            } // if

            // 更改變數的屬性
            if ( gFloat_operation ) gToken[find_id].is_int = false ;
            if ( !gFloat_operation ) gToken[find_id].is_int = true ;
          } // if

          find_id ++ ;
        } // while

      } // if

      if ( !gHave_error && !gHave_bool ) { // 印出定義的結果
        if ( !gFloat_operation ) {
          int output = ( int ) gToken[temp_gNum].variable_content ;
          printf( "> %d\n", output ) ;
        } // if
        else { // 為了處理4捨5入的浮點數
          float console = 0 ;
          console = Rounding( gToken[temp_gNum].variable_content ) ;
          printf( "> %1.3f\n", console ) ; // 沒有error就印出結果
        } // else

      } // if

    } // if
    else {

      if ( !IDlessArithExpOrBexp() && !gHave_error ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gHave_error ) {
          gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
          Unexpected_error() ;
        } // if
        // /////////////////////////////////////////////////////////////////////////////////////////////
        return true ;
      } // if 

      if ( gToken[gNum].token_type != SEMICOLON && !gHave_error ) { // 結束出來會是分號
        // /////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////
        return true ;
      } // if 

      if ( !gHave_error && !gHave_bool ) {
        if ( !gFloat_operation ) {
          if ( gValue->size() > 0 ) {
            int output = * gValue[0].data() ;
            printf( "> %d\n", output ) ;
          } // if
        } // if
        else { // 為了處理4捨5入的浮點數
          if ( gValue->size() > 0 ) {
            float console = 0 ;
            console = Rounding( * gValue[0].data() ) ;
            printf( "> %1.3f\n", console ) ; // 沒有error就印出結果
          } // if

        } // else

      } // if
      else if ( !gHave_error && gHave_bool ) { // 有出現布林運算，就只會印出布林結果
        if ( gBool_Ans ) printf( "> true\n" ) ;
        else printf( "> false\n" ) ;

      } // else if

      return true ;

    } // else

  } // if
  else if ( gToken[gNum].token_type == SEMICOLON ) { // 一進來就直接是分號

    Unexpected_error();
    return true ;

  } // else if
  else { // 第三種情況   不是 IDENT開頭的句子

    if ( !NOT_ID_StartArithExpOrBexp() && !gHave_error ) {
      // /////////////////////////////////////////////////////////////////////////////////////////////
      gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
      Unexpected_error() ;
      // /////////////////////////////////////////////////////////////////////////////////////////////
      return true ;
    } // if 

    if ( gToken[gNum].token_type != SEMICOLON && !gHave_error ) { // 結束出來會是分號
      // /////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // /////////////////////////////////////////////////////////////////////////////////////////////
      return true ;
    } // if 

    if ( !gHave_error && !gHave_bool ) {
      if ( !gFloat_operation ) {
        if ( gValue->size() > 0 ) {
          int output = * gValue[0].data() ;
          printf( "> %d\n", output ) ;
        } // if
        
      } // if
      else { // 為了處理4捨5入的浮點數
        if ( gValue->size() > 0 ) {
          float console = 0 ;
          console = Rounding( * gValue[0].data() ) ;
          printf( "> %1.3f\n", console ) ; // 沒有error就印出結果
        } // if
      } // else

    } // if
    else if ( !gHave_error && gHave_bool ) {
      if ( gBool_Ans ) printf( "> true\n" ) ;
      else printf( "> false\n" ) ;

    } // else if

  } // else

  return true ;

} // Command()

bool IDlessArithExpOrBexp() {

  // ============================================================================================

  // 第一層防禦 unexpected ex. Quit quit ; 錯在第二個quit

  if ( gToken[gNum].token_type == PLUS || gToken[gNum].token_type == MINUS || BooleanOprator()
       || gToken[gNum].token_type == MULTI || gToken[gNum].token_type == DIV
       || gToken[gNum].token_type == SEMICOLON ) {
    gNum -- ; // 沒事幹 是為了else才出現的
  } // if
  else if ( !gHave_error ) {
    // ex . a quit ; 錯在'quit'
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    return false;

  } // else if

  // ============================================================================================

  // 第二層防禦 undefined
  //  看看這個變數有沒有被定義過
  // ///////////////////////////////////////////////////////////////////////////////////////////////////////
  if ( Undefined_error() ) {
    gNum ++ ;
    return false ;
  } // if
  else gNum ++ ;
  // ///////////////////////////////////////////////////////////////////////////////////////////////////////

  // ============================================================================================

  while ( gToken[gNum].token_type == PLUS || gToken[gNum].token_type == MINUS
          || gToken[gNum].token_type == MULTI || gToken[gNum].token_type == DIV ) {

    if ( gToken[gNum].token_type == PLUS || gToken[gNum].token_type == MINUS ) {

      if ( gToken[gNum].token_type == PLUS ) {

        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        if ( !Term() ) {
          // /////////////////////////////////////////////////////////////////////////////////////////////
          if ( !gHave_error ) {
            gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
            Unexpected_error() ;
          } // if
          // /////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // if 

        // 做計算
        if ( gValue->size() >= 2 ) {
          gTemp_value = gValue->at( gValue->size() - 2 ) + gValue->at( gValue->size() - 1 );
          // 應該是倒數第二個加最後一個再繼續遞迴
          gValue->pop_back(); // 算完就丟掉
          gValue->pop_back(); // 算完就丟掉
          gValue->push_back( gTemp_value ); // 加入算好的值
        } // if

      } // if
      else if ( gToken[gNum].token_type == MINUS ) {

        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;
         
        if ( !Term() ) {
          // /////////////////////////////////////////////////////////////////////////////////////////////
          if ( !gHave_error ) {
            gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
            Unexpected_error() ;
          } // if
          // /////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // if 

        // 做計算
        if ( gValue->size() >= 2 ) {
          gTemp_value = gValue->at( gValue->size() - 2 ) - gValue->at( gValue->size() - 1 );
          // 應該是倒數第二個加最後一個再繼續遞迴
          gValue->pop_back(); // 算完就丟掉
          gValue->pop_back(); // 算完就丟掉
          gValue->push_back( gTemp_value ); // 加入算好的值
        } // if

      } // else if

    } // if
    else if ( gToken[gNum].token_type == MULTI || gToken[gNum].token_type == DIV ) {

      if ( gToken[gNum].token_type == MULTI ) {

        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        if ( !Factor() ) {
          // /////////////////////////////////////////////////////////////////////////////////////////////
          if ( !gHave_error ) {
            gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
            Unexpected_error() ;
          } // if
          // /////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // if 

        // 做計算
        if ( gValue->size() >= 2 ) {
          gTemp_value = gValue->at( gValue->size() - 2 ) * gValue->at( gValue->size() - 1 );
          // 應該是倒數第二個加最後一個再繼續遞迴
          gValue->pop_back(); // 算完就丟掉
          gValue->pop_back(); // 算完就丟掉
          gValue->push_back( gTemp_value ); // 加入算好的值
        } // if

      } // if
      else if ( gToken[gNum].token_type == DIV ) {

        if ( !GetToken( gGet_error ) ) return false ; 
        else gNum ++ ;

        if ( !Factor() ) {
          // /////////////////////////////////////////////////////////////////////////////////////////////
          if ( !gHave_error ) {
            gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
            Unexpected_error() ;
          } // if
          // /////////////////////////////////////////////////////////////////////////////////////////////
          return false ;
        } // if 

        if ( gValue->at( gValue->size() - 1 ) == 0 ) { // 除以零的錯誤
          printf( "Error\n" );

          gHave_error = true;

          int temp_Line = gToken[gNum].lineNum;
          // 印出錯誤後把這一整行到分號都不要
          if ( gToken.size() - gNum > 1 ) gNum ++;
          while ( temp_Line == gToken[gNum].lineNum ) {
            if ( gToken.size() - gNum > 1 ) gNum ++;
            else return false ;
          } // while

          gValue->clear() ;

          return false ; // 結束重跑

        } // if
        else { // 做計算

          if ( gValue->size() >= 2 ) {
            gTemp_value = gValue->at( gValue->size() - 2 ) / gValue->at( gValue->size() - 1 ) ;
            // 應該是倒數第二個加最後一個再繼續遞迴
            gValue->pop_back(); // 算完就丟掉
            gValue->pop_back(); // 算完就丟掉
            gValue->push_back( gTemp_value ); // 加入算好的值
          } // if

        } // else

      } // else if

    } // else if

  } // while


  float value1 = 0.0 ;
  if ( gValue->size() > 0 ) value1 = * gValue[0].data() ; // 布林前計算的值先存起來
  else return false ;

  if ( BooleanOprator() ) { // 如果有出現布林運算

    gHave_bool = true ;
    int temp_gNum = gNum ; // 先記起來布林符號出現在哪

    gValue->clear() ; // 清空準備做下一次計算

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;
    
    if ( !ArithExp() ) {
      // /////////////////////////////////////////////////////////////////////////////////////////////
      if ( !gHave_error ) {
        gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
        Unexpected_error() ;
      } // if
      // /////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // if 

    float value2 = 0.0 ;
    if ( gValue->size() > 0 ) value2 = * gValue[0].data() ; // 布林後面的計算再存起來
    else return false ;

    float console = value1 - value2 ; // 用來確保差距大於0.0001

    if ( gToken[temp_gNum].token_type == EQUAL && -0.0001 <= console && console <= 0.0001
         && !gHave_error ) {
      gBool_Ans = true ;
    } // if
    else if ( gToken[temp_gNum].token_type == EQUAL && !gHave_error ) {
      if ( 0.0001 < console || console < -0.0001 ) gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == NOT_EQUAL && !gHave_error ) {

      if ( 0.0001 < console || console < -0.0001 ) {
        gBool_Ans = true ;
      } // if
      else if ( -0.0001 <= console && console <= 0.0001 ) {
        gBool_Ans = false ;
      } // else if

    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGER && console > 0.0001 && !gHave_error ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGER && console <= 0.0001 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console >= -0.0001 && !gHave_error  ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console < -0.0001 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER && console < -0.0001 && !gHave_error  ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER && console >= -0.0001 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console <= 0.0001 && !gHave_error  ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console > 0.0001 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if

  } // if


  return true ;


} // IDlessArithExpOrBexp()

bool BooleanOprator() {


  if ( gToken[gNum].token_type == EQUAL || gToken[gNum].token_type == NOT_EQUAL 
       || gToken[gNum].token_type == BIGGER || gToken[gNum].token_type == SMALLER 
       || gToken[gNum].token_type == BIGGGER_EQ || gToken[gNum].token_type == SMALLER_EQ ) return true ;
  else return false ;

} // BooleanOprator()

bool NOT_ID_StartArithExpOrBexp() {


  // 這裡會直接進來加減只有可能是因為上一行有錯誤
  if ( gToken[gNum].token_type == PLUS || gToken[gNum].token_type == MINUS ) {

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( gToken[gNum].token_type == INT ) {
      gNum -- ; // 剛剛先+1偷看現在減回來繼續做
      gToken[gNum].token_type = SIGN ;
    } // if
    else if ( gToken[gNum].token_type == FLOAT ) {
      gNum -- ; // 剛剛先+1偷看現在減回來繼續做
      gToken[gNum].token_type = SIGN ;
    } // else if
    else if ( !gHave_error ) {
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // /////////////////////////////////////////////////////////////////////////////////////////////////
      return false;
    } // else if

  } // if

  if ( !NOT_ID_StartArithExp() ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////
    if ( !gHave_error ) {
      gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
      Unexpected_error() ;
    } // if
    // /////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // if 

  float value1 = 0.0 ;
  if ( gValue->size() > 0 ) value1 = * gValue[0].data() ; // 布林前計算的值先存起來
  else return false ;

  if ( BooleanOprator() ) { // 如果有出現布林運算
    gHave_bool = true ;
    int temp_gNum = gNum ; // 先記起來布林符號出現在哪
    gValue->clear() ; // 清空準備做下一次計算

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;
    if ( !ArithExp() ) {
      // /////////////////////////////////////////////////////////////////////////////////////////////
      if ( !gHave_error ) {
        gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
        Unexpected_error() ;
      } // if
      // /////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // if 

    float value2 = 0.0 ;
    if ( gValue->size() > 0 ) value2 = * gValue[0].data() ; // 布林後面的計算再存起來
    else return false ;

    float console = value1 - value2 ; // 用來確保差距大於0.0001

    if ( gToken[temp_gNum].token_type == EQUAL && -0.0001 <= console && console <= 0.0001
         && !gHave_error ) {
      gBool_Ans = true ;
    } // if
    else if ( gToken[temp_gNum].token_type == EQUAL && !gHave_error ) {
      if ( 0.0001 < console || console < -0.0001 ) gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == NOT_EQUAL && !gHave_error ) {

      if ( 0.0001 < console || console < -0.0001 ) {
        gBool_Ans = true ;
      } // if
      else if ( -0.0001 <= console && console <= 0.0001 ) {
        gBool_Ans = false ;
      } // else if

    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGER && console > 0.0001 && !gHave_error ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGER && console <= 0.0001 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console >= -0.0001 && !gHave_error  ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console < -0.0001 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER && console < -0.0001 && !gHave_error  ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER && console >= -0.0001 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console <= 0.0001 && !gHave_error  ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console > 0.0001 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if

  } // if

  return true ;

} // NOT_ID_StartArithExpOrBexp()

bool NOT_ID_StartArithExp() {


  if ( !NOT_ID_StartTerm() ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////
    if ( !gHave_error ) {
      gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
      Unexpected_error() ;
    } // if
    // /////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // if 


  while ( gToken[gNum].token_type == PLUS || gToken[gNum].token_type == MINUS ) { 
    // 重複零到多次 所以要用迴圈
    if ( gToken[gNum].token_type == PLUS ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;
      if ( !Term() ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gHave_error ) {
          gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
          Unexpected_error() ;
        } // if
        // /////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // if 

      // 做計算
      if ( gValue->size() >= 2 ) {
        gTemp_value = gValue->at( gValue->size() - 2 ) + gValue->at( gValue->size() - 1 );
        // 應該是倒數第二個加最後一個再繼續遞迴
        gValue->pop_back(); // 算完就丟掉
        gValue->pop_back(); // 算完就丟掉
        gValue->push_back( gTemp_value ) ; // 加入算好的值
      } // if

    } // if
    else if ( gToken[gNum].token_type == MINUS ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( !Term() ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gHave_error ) {
          gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
          Unexpected_error() ;
        } // if
        // /////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // if 

      // 做計算
      if ( gValue->size() >= 2 ) {
        gTemp_value = gValue->at( gValue->size() - 2 ) - gValue->at( gValue->size() - 1 );
        // 應該是倒數第二個加最後一個再繼續遞迴
        gValue->pop_back(); // 算完就丟掉
        gValue->pop_back(); // 算完就丟掉
        gValue->push_back( gTemp_value ); // 加入算好的值
      } // if

    } // else if

  } // while

  return true ;

} // NOT_ID_StartArithExp()

bool NOT_ID_StartTerm() {


  if ( !NOT_ID_StartFactor() ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////
    if ( !gHave_error ) {
      gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
      Unexpected_error() ;
    } // if
    // /////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // if 

  while ( gToken[gNum].token_type == MULTI || gToken[gNum].token_type == DIV ) { 
    // 重複零到多次 所以要用迴圈

    if ( gToken[gNum].token_type == MULTI ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( !Factor() ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gHave_error ) {
          gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
          Unexpected_error() ;
        } // if
        // /////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // if 

      // 做計算
      if ( gValue->size() >= 2 ) {
        gTemp_value = gValue->at( gValue->size() - 2 ) * gValue->at( gValue->size() - 1 );
        // 應該是倒數第二個加最後一個再繼續遞迴
        gValue->pop_back(); // 算完就丟掉
        gValue->pop_back(); // 算完就丟掉
        gValue->push_back( gTemp_value ); // 加入算好的值
      } // if

    } // if
    else if ( gToken[gNum].token_type == DIV ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( !Factor() ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gHave_error ) {
          gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
          Unexpected_error() ;
        } // if
        // /////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // if 

      if ( gValue->at( gValue->size() - 1 ) == 0 ) { // 除以零的錯誤
        printf( "Error\n" );

        gHave_error = true;

        int temp_Line = gToken[gNum].lineNum;
        // 印出錯誤後把這一整行到分號都不要
        if ( gToken.size() - gNum > 1 ) gNum ++;
        while ( temp_Line == gToken[gNum].lineNum ) {
          if ( gToken.size() - gNum > 1 ) gNum ++;
          else return true ;
        } // while

        gValue->clear() ;

      } // if
      else {

        if ( gValue->size() >= 2 ) {

          gTemp_value = gValue->at( gValue->size() - 2 ) / gValue->at( gValue->size() - 1 ) ;
          // 應該是倒數第二個加最後一個再繼續遞迴
          gValue->pop_back(); // 算完就丟掉
          gValue->pop_back(); // 算完就丟掉
          gValue->push_back( gTemp_value ); // 加入算好的值
        } // if

      } // else
    
    } // else if

  } // while

  return true ;

} // NOT_ID_StartTerm()

bool NOT_ID_StartFactor() {


  // 他跟Factor()不同在於這裡不用判斷ident

  if ( gHave_error ) return false ;

  // factor判斷不應該peekToken

  if ( gToken[gNum].token_type == INT || gToken[gNum].token_type == FLOAT
       || gToken[gNum].token_type == SIGN ) {

    if ( gToken[gNum].token_type == SIGN ) {
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( gToken[gNum].token_type == INT ) {
        if ( strcmp( gToken[gNum-1].data, "-" ) == 0 ) { // 把負號加上去，再把加上負號的值取出來
          char temp[] = "-";
          strcat( temp, gToken[gNum].data );
          strcpy( gToken[gNum].data, temp );
        } // if

      } // if
      else if ( gToken[gNum].token_type == FLOAT ) {
        if ( strcmp( gToken[gNum-1].data, "-" ) == 0 ) { // 把負號加上去，再把加上負號的值取出來
          char temp[] = "-";
          strcat( temp, gToken[gNum].data );
          strcpy( gToken[gNum].data, temp );
        } // if
      } // else if
      else if ( !gHave_error ) { // Sign後面不是接數字們
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false;
      } // else if

    } // if

    if ( gToken[gNum].token_type == INT ) gValue->push_back( atoi( gToken[gNum].data ) ) ;
    if ( gToken[gNum].token_type == FLOAT ) {
      gValue->push_back( atof( gToken[gNum].data ) );
      gFloat_operation = true;
    } // if

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    return true; // 如果是[SIGN] NUM 或是IDENT 就結束了

  } // if
  else if ( gToken[gNum].token_type == LEFT_PAREN ) {
    gLeft_p_num ++ ;

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( !ArithExp() ) {
      // /////////////////////////////////////////////////////////////////////////////////////////////
      if ( !gHave_error ) {
        gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
        Unexpected_error() ;
      } // if
      // /////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // if  

    // 回來的是右括號
    if ( !gHave_error && gToken[gNum].token_type != RIGHT_PAREN ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false;

    } // if
    else if ( !gHave_error ) {
      gLeft_p_num -- ;
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;
    } // else if

  } // else if
  else if ( !gHave_error ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    return false;
  } // else if
  else {
    return false;
  } // else 

  return true;

} // NOT_ID_StartFactor()

bool ArithExp() {

  if ( !Term() ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////
    if ( !gHave_error ) {
      gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
      Unexpected_error() ;
    } // if
    // /////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // if 

  while ( gToken[gNum].token_type == PLUS 
          || gToken[gNum].token_type == MINUS ) { // 重複零到多次 所以要用迴圈

    if ( gToken[gNum].token_type == PLUS ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;
      if ( !Term() ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gHave_error ) {
          gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
          Unexpected_error() ;
        } // if
        // /////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // if 


      // 做計算
      if ( gValue->size() >= 2 ) {
        gTemp_value = gValue->at( gValue->size() - 2 ) + gValue->at( gValue->size() - 1 );
        // 應該是倒數第二個加最後一個再繼續遞迴
        gValue->pop_back(); // 算完就丟掉
        gValue->pop_back(); // 算完就丟掉
        gValue->push_back( gTemp_value ); // 加入算好的值
      } // if

    } // if
    else if ( gToken[gNum].token_type == MINUS ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( !Term() ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gHave_error ) {
          gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
          Unexpected_error() ;
        } // if
        // /////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // if 

      // 做計算
      if ( gValue->size() >= 2 ) {
        gTemp_value = gValue->at( gValue->size() - 2 ) - gValue->at( gValue->size() - 1 );
        // 應該是倒數第二個加最後一個再繼續遞迴
        gValue->pop_back(); // 算完就丟掉
        gValue->pop_back(); // 算完就丟掉
        gValue->push_back( gTemp_value ); // 加入算好的值
      } // if

    } // else if

  } // while

  return true ;

} // ArithExp()

bool Term() {

  if ( !Factor() ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////
    if ( !gHave_error ) {
      gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
      Unexpected_error() ;
    } // if
    // /////////////////////////////////////////////////////////////////////////////////////////////
    return false ;
  } // if 

  while ( gToken[gNum].token_type == MULTI || gToken[gNum].token_type == DIV ) { 
    // 重複零到多次 所以要用迴圈

    if ( gToken[gNum].token_type == MULTI ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;
      if ( !Factor() ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gHave_error ) {
          gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
          Unexpected_error() ;
        } // if
        // /////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // if 

      // 做計算
      if ( gValue->size() >= 2 ) {
        gTemp_value = gValue->at( gValue->size() - 2 ) * gValue->at( gValue->size() - 1 );
        // 應該是倒數第二個加最後一個再繼續遞迴
        gValue->pop_back(); // 算完就丟掉
        gValue->pop_back(); // 算完就丟掉
        gValue->push_back( gTemp_value ); // 加入算好的值
      } // if

    } // if
    else if ( gToken[gNum].token_type == DIV ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;
      if ( !Factor() ) {
        // /////////////////////////////////////////////////////////////////////////////////////////////
        if ( !gHave_error ) {
          gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
          Unexpected_error() ;
        } // if
        // /////////////////////////////////////////////////////////////////////////////////////////////
        return false ;
      } // if 

      if ( gValue->at( gValue->size() - 1 ) == 0 ) { // 除以零的錯誤
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

        if ( gValue->size() >= 2 ) {

          gTemp_value = gValue->at( gValue->size() - 2 ) / gValue->at( gValue->size() - 1 ) ;
          // 應該是倒數第二個加最後一個再繼續遞迴
          gValue->pop_back(); // 算完就丟掉
          gValue->pop_back(); // 算完就丟掉
          gValue->push_back( gTemp_value ); // 加入算好的值
        } // if

      } // else

    } // if

  } // while

  return true ;
  
} // Term()

bool Factor() {

  // factor判斷不應該peekToken

  if ( gHave_error ) return false ;

  if ( gToken[gNum].token_type == INT || gToken[gNum].token_type == FLOAT
       || gToken[gNum].token_type == SIGN ) {

    if ( gToken[gNum].token_type == SIGN ) {

      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;

      if ( gToken[gNum].token_type == INT ) {
        if ( strcmp( gToken[gNum-1].data, "-" ) == 0 ) { // 把負號加上去，再把加上負號的值取出來
          char temp[100] = "-";
          strcat( temp, gToken[gNum].data );
          strcpy( gToken[gNum].data, temp );
        } // if
      } // if
      else if ( gToken[gNum].token_type == FLOAT ) {
        if ( strcmp( gToken[gNum-1].data, "-" ) == 0 ) { // 把負號加上去，再把加上負號的值取出來
          char temp[100] = "-";
          strcat( temp, gToken[gNum].data );
          strcpy( gToken[gNum].data, temp );
        } // if
      } // else if
      else if ( !gHave_error ) { // Sign後面不是接數字們
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        Unexpected_error() ;
        // /////////////////////////////////////////////////////////////////////////////////////////////////
        return false;
      } // else if

    } // if

    if ( gToken[gNum].token_type == INT ) gValue->push_back( atoi( gToken[gNum].data ) ) ;
    if ( gToken[gNum].token_type == FLOAT ) {
      gValue->push_back( atof( gToken[gNum].data ) );
      gFloat_operation = true;
    } // if
 
    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    return true ; // 如果是[SIGN] NUM 或是IDENT 就結束了
  } // if
  else if ( gToken[gNum].token_type == IDENT ) {

    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    if ( Undefined_error() ) return false ;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    return true ;

  } // else if
  else if ( gToken[gNum].token_type == LEFT_PAREN ) {
    gLeft_p_num ++ ;

    if ( !GetToken( gGet_error ) ) return false ; 
    else gNum ++ ;

    if ( !ArithExp() ) {
      // /////////////////////////////////////////////////////////////////////////////////////////////
      if ( !gHave_error ) {
        gNum ++ ; // 應該只有遇到真正的quit才會進到這 因為getToken失敗但是卻沒有have error
        Unexpected_error() ;
      } // if
      // /////////////////////////////////////////////////////////////////////////////////////////////
      return false ;
    } // if  

    // 回來的是右括號
    if ( !gHave_error && gToken[gNum].token_type != RIGHT_PAREN ) {
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      Unexpected_error() ;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////
      return false;

    } // if
    else if ( !gHave_error ) {
      gLeft_p_num -- ;
      if ( !GetToken( gGet_error ) ) return false ; 
      else gNum ++ ;
    } // else if

  } // else if
  else if ( !gHave_error ) {
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    Unexpected_error() ;
    // /////////////////////////////////////////////////////////////////////////////////////////////////////
    return false;

  } // else if
  else return false ;

  return true ;

} // Factor()

// =========================================================================================================

void Unexpected_error() {

  printf( "> Unexpected token : '%s'\n", gToken[gNum].data ) ;
  gHave_error = true ;

  gGet_error = true ;

  GetToken( gGet_error ) ;

  gValue->clear() ;
  gGet_error = false  ;
  return ;
} // Unexpected_error()

bool Undefined_error() {

  int find_id = 0;
  bool found_it = false;
  while ( find_id < gNum && !found_it ) { // 找找看有沒有這個變數

    if ( strcmp( gToken[find_id].data, gToken[gNum].data ) == 0
         && gToken[find_id].have_defined == true ) {
      // 找到了就把值給取出來
      gValue->push_back( gToken[find_id].variable_content );
      found_it = true;
      if ( !gToken[find_id].is_int ) gFloat_operation = true;
    } // if

    find_id++;

  } // while

  if ( !gHave_error && !found_it ) {
    printf( "> Undefined identifier : '%s'\n", gToken[gNum].data ) ;
    gHave_error = true;

    gGet_error = true ;

    GetToken( gGet_error ) ;

    gValue->clear() ;
    gGet_error = false ;
    return true ;

  } // if

  return false ;

} // Undefined_error()

void Unrecognized_error() {

  printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum].data ) ;
  gHave_error = true ;

  gGet_error = true ;

  GetToken( gGet_error ) ;

  gValue->clear() ;
  gGet_error = false ;
  return ;

} // Unrecognized_error()

// 這個Function只是為了把老大一開始輸入的test num讀掉
void Read_test_num() {

   // 宣吿
  char text[100] = "" ; // 用來暫存token
  char ch[100] = "" ; // 用來讀檔
  char temp_ch[100] = "" ; // 輔助讀檔
  char temp = ' ' ;

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

} // Read_test_num() 



// ********************************處理Token************************************************


// 一次只回傳一個Token 如果有合法的Token就回傳True，如果EOF或是讀到quit就會回傳False
bool GetToken( bool get_error ) {

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


  // ********************************************************************

  // ex. 3+2 = 5
  // ex. 3+-2 = 1 因為後面那個減是負號的意思

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


    temp = scanf( "%c", &ch[0] ) ;

    while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) {
      if ( temp == EOF ) return false ;
      temp = scanf( "%c", &ch[0] ) ;
    } // while

  } // if

  if ( temp == EOF ) {
    // return false ;
  } // if

  // ********************************************************************
  // ********************************************************************
  // ********************************************************************

  if ( ch[0] == '+' || ch[0] == '*' || ch[0] == '-' ) { // 處理加乘

    // ex. a:=-9; or ( -5 + 6 ) or 3 * -1 or 1 - -3 or 1 < -2 or 100 + ( - - 5 + 2 )
    // 有一種狀況還未解決,就是
    // ; quit  // 這行有錯 下一行應該是負號不是減號才對
    // -36 - 23 ;

    if ( gToken.size() == 0 || gToken[gToken.size() - 1].token_type == BELONG
         || gToken[gToken.size() - 1].token_type == EQUAL
         || gToken[gToken.size() - 1].token_type == NOT_EQUAL
         || gToken[gToken.size() - 1].token_type == MULTI
         || gToken[gToken.size() - 1].token_type == MINUS
         || gToken[gToken.size() - 1].token_type == PLUS
         || gToken[gToken.size() - 1].token_type == DIV
         || gToken[gToken.size() - 1].token_type == BIGGER
         || gToken[gToken.size() - 1].token_type == BIGGGER_EQ
         || gToken[gToken.size() - 1].token_type == SMALLER
         || gToken[gToken.size() - 1].token_type == SMALLER_EQ
         || gToken[gToken.size() - 1].token_type == LEFT_PAREN
         || gToken[gToken.size() - 1].token_type == SEMICOLON
         || gToken[gToken.size() - 1].token_type == UNRECOGNIZED
         || gToken[gToken.size() - 1].token_type == UNEXPECTED
         || gToken[gToken.size() - 1].token_type == QUIT ) {

      if ( ch[0] == '+' || ch[0] == '-' ) { 
        strcpy( temp_ch, ch );

        strcat( text, ch );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = SIGN;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text


      } // if
      else if ( ch[0] == '*' ) {
        strcat( text, ch );
        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = MULTI;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text

      } // else if

    } // if
    else {
      if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch

      if ( ch[0] == '*' ) { // 儲存運算元
        strcat( text, ch ) ;
        strcpy( gToken_info.data, text ) ; // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = MULTI ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text
      } // if

      if ( ch[0] == '+' ) { // 儲存運算元
        strcat( text, ch ) ;
        strcpy( gToken_info.data, text ) ; // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = PLUS ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text
      } // if

      if ( ch[0] == '-' ) { // 儲存運算元
        strcat( text, ch ) ;
        strcpy( gToken_info.data, text ) ; // 存取token資訊
        gToken_info.lineNum = gLine ; // 看他屬於哪一行
        gToken_info.token_type = MINUS ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text
      } // if

    } // else
    
    if ( ch[0] == '\n' ) gLine ++ ;

    return true ;

  } // if


  // ********************************************************************

  if ( ch[0] == '/' ) { // 遇到除號 或是 註解

    temp = scanf( "%c", &ch[0] ) ;

    if ( ch[0] == '/' ) { // 是註解

      temp = scanf( "%c", &ch[0] ) ;
      while ( ch[0] != '\n' && temp != EOF ) { // 把註解讀掉
        temp = scanf( "%c", &ch[0] ) ;
      } // while

      if ( GetToken( gGet_error ) ) {
        return true ;
      } // if
      else return false ;

    } // if
    else {
      if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
      strcat( text, "/" ) ;
      strcpy( gToken_info.data, text ) ; // 存取token資訊
      gToken_info.lineNum = gLine ; // 看他屬於哪一行
      gToken_info.token_type = DIV ;
      gToken.push_back( gToken_info ) ;
      strcpy( text, "" ) ; // 清空text

      // 把還沒用到的char存起來之後再判斷
      if ( temp != EOF && ch[0] != ' ' && ch[0] != '\n' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;

      if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
      if ( ch[0] == '\n' ) gLine ++ ;
      return true ;

    } // else

  } // if



  // ********************************************************************

  if ( ch[0] == ':' ) { // 遇到冒號的處理

    strcat( text, ch ) ;
    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    temp = scanf( "%c", &ch[0] ) ;

    if ( ch[0] == '=' ) {
      strcat( text, ch ) ;
      strcpy( gToken_info.data, text ) ; // ex. a := 1 ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = BELONG ;
      gToken.push_back( gToken_info ) ;
      strcpy( text, "" ) ; // 清空text

      if ( ch[0] == '\n' ) gLine ++ ;
      return true ;

    } // if
    else {
      strcpy( gToken_info.data, text ) ; // ex. a:5; 錯在冒號
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = UNRECOGNIZED ;
      gToken.push_back( gToken_info ) ;
      strcpy( text, "" ) ; // 清空text

      if ( ch[0] == '\n' ) gLine ++ ;
      gNum = gToken.size() - 1 ;
      Unrecognized_error() ;
      return false;

    } // else

  } // if

  // ********************************************************************

  if ( ch[0] == '<' || ch[0] == '>' || ch[0] == '=' ) { // 遇到比較的運算元

    strcat( text, ch );
    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    temp = scanf( "%c", &ch[0] ) ;

    if ( temp_ch[0] == '=' ) {
      strcpy( gToken_info.data, text ) ; // ex. a = 1 ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = EQUAL;
      gToken.push_back( gToken_info );

    } // if
    else if ( temp_ch[0] == '<' && ch[0] == '>' ) { // <>這個就是不等於啦 老大說的
      strcat( text, ch );
      strcpy( gToken_info.data, text ) ; // ex. a <> 1 ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = NOT_EQUAL;
      gToken.push_back( gToken_info );

    } // else if
    else if ( temp_ch[0] == '<' && ch[0] == '=' ) {
      strcat( text, ch );
      strcpy( gToken_info.data, text ) ; // ex. a <= 1 ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = SMALLER_EQ;
      gToken.push_back( gToken_info );

    } // else if
    else if ( temp_ch[0] == '>' && ch[0] == '=' ) {
      strcat( text, ch );
      strcpy( gToken_info.data, text ) ; // ex. a >= 1 ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = BIGGGER_EQ;
      gToken.push_back( gToken_info );

    } // else if
    else if ( temp_ch[0] == '<' && ch[0] != '=' ) {
      strcpy( gToken_info.data, text ) ; // ex. a < 1 ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = SMALLER;
      gToken.push_back( gToken_info );
      if ( ch[0] != ' ' && ch[0] != '-' && ch[0] != '+' ) strcpy( temp_ch, ch ) ; // 為了判斷sign的話不能存
    } // else if
    else if ( temp_ch[0] == '>' && ch[0] != '=' ) {
      strcpy( gToken_info.data, text ) ; // ex. a > 1 ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = BIGGER;
      gToken.push_back( gToken_info );
      if ( ch[0] != ' ' && ch[0] != '-' && ch[0] != '+' ) strcpy( temp_ch, ch ) ; // 為了判斷sign的話不能存
    } // else if

    strcpy( text, "" ) ;

    if ( ch[0] == '=' ) { // 等於就不要了 不是等於的還要
      if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
      temp = scanf( "%c", &ch[0] ) ;
    } // if

    // 把還沒用到的char存起來之後再判斷
    if ( temp != EOF && ch[0] != ' ' && ch[0] != '\n' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
    if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
    if ( ch[0] == '\n' ) gLine ++ ;

    return true ;

  } // if

  // ********************************************************************

  if ( ch[0] == '(' ) {
    strcpy( gToken_info.data, "(" ) ; // 存取token資訊
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = LEFT_PAREN ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ;

    return true ;

  } // if

  if ( ch[0] == ')' ) {
    strcpy( gToken_info.data, ")" ) ; // 存取token資訊
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = RIGHT_PAREN ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ; // 清空text

    return true ;

  } // if

  // ********************************************************************

  if ( ch[0] == ';' ) { // 分號的處理
    strcpy( gToken_info.data, ";" ) ; // 存取token資訊
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = SEMICOLON ;
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
    if ( !is_float ) gToken_info.token_type = INT ;
    else gToken_info.token_type = FLOAT ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ; // 清空text

    // 把還沒用到的char存起來之後再判斷
    if ( temp != EOF && ch[0] != ' ' && ch[0] != '\n' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
    if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
    if ( ch[0] == '\n' ) gLine ++ ;
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
      gToken_info.token_type = FLOAT;
      gToken.push_back( gToken_info );
      strcpy( text, "" ); // 清空text

      // 把還沒用到的char存起來之後再判斷
      if ( temp != EOF && ch[0] != ' ' && ch[0] != '\n' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
      if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
      if ( ch[0] == '\n' ) gLine ++ ;
      return true ;
    } // if
    else {
      strcpy( gToken_info.data, text ); // 存取token資訊
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = DOT;
      gToken.push_back( gToken_info );
      strcpy( text, "" ); // 清空text

      return false;
    } // else

  } // if

  // ********************************************************************


  if ( ch[0] == 'q' ) { // quit 的處理

    strcat( text, ch ) ;
    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    temp = scanf( "%c", &ch[0] ) ;

    while ( temp != EOF && 47 < ch[0] && ch[0] < 123 && ch[0] != 58 && ch[0] != 59
            && ch[0] != 60 && ch[0] != 61 && ch[0] != 62 && ch[0] != 63 && ch[0] != 64
            && ch[0] != 91 && ch[0] != 92 && ch[0] != 93 && ch[0] != 94 && ch[0] != 96 ) {
      strcat( text, ch ) ;
      if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
      temp = scanf( "%c", &ch[0] ) ;
    } // while

    if ( strcmp( text, "quit" ) == 0 && gForm_main_into_GetToken == true ) { 
      // 確認是不是讀到quit

      while ( temp != EOF && ch[0] != '\n' && ch[0] != ':' && ch[0] != ' ' && ch[0] != ';'
              && ch[0] != '=' && 47 < ch[0] && ch[0] < 123 && ch[0] != 96 && ch[0] != '@'
              && ch[0] != 91 && ch[0] != 92 && ch[0] != 93 && ch[0] != 94 && ch[0] != '\t'
              && ch[0] != '>' && ch[0] != '<' && ch[0] != '?' ) {
        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;
      } // while

      strcpy( gToken_info.data, text ) ;
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = QUIT ;
      gToken.push_back( gToken_info ) ;
      strcpy( text, "" ) ; // 清空text


      // 把還沒用到的char存起來之後再判斷
      if ( ch[0] != ' ' && ch[0] != '\n' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;

      if ( ch[0] == '\n' ) gLine ++ ;
      return false ;

    } // if
    else { // q開頭的IDENT 包含 不是結束的quit

      strcpy( gToken_info.data, text );
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = IDENT;
      gToken.push_back( gToken_info );
      strcpy( text, "" ); // 清空text

      // 把還沒用到的char存起來之後再判斷
      if ( temp != EOF && ch[0] != ' ' && ch[0] != '\n' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;

      if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;

      if ( ch[0] == '\n' ) gLine ++ ;
      return true ;

    } // else


  } // if

  // ********************************************************************

  if ( 29 < ch[0] && ch[0] < 40 ) { // 不是任何東西 ex. $$

    strcat( text, ch ) ;

    strcpy( gToken_info.data, text ) ;
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = UNRECOGNIZED ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ; // 清空text

    gNum = gToken.size() - 1 ;
    Unrecognized_error() ;
    return false;

  } // if

  if ( 90 < ch[0] && ch[0] < 97 && ch[0] < 95 ) {
        // 不是任何東西 ex. [2

    strcat( text, ch ) ;

    strcpy( gToken_info.data, text ) ;
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = UNRECOGNIZED ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ; // 清空text

    gNum = gToken.size() - 1 ;
    Unrecognized_error() ;
    return false;

  } // if

  if ( 122 < ch[0] && ch[0] < 128 ) {
        // 不是任何東西 ex. {A

    strcat( text, ch ) ;

    strcpy( gToken_info.data, text ) ;
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = UNRECOGNIZED ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ; // 清空text

    if ( ch[0] == '\n' ) gLine ++ ;
    gNum = gToken.size() - 1 ;
    Unrecognized_error() ;
    return false;

  } // if

  if ( 62 < ch[0] && ch[0] < 65 ) {
    // 不是任何東西 ex. {A

    strcat( text, ch ) ;

    strcpy( gToken_info.data, text ) ;
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = UNRECOGNIZED ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ; // 清空text

    if ( ch[0] == '\n' ) gLine ++ ;
    gNum = gToken.size() - 1 ;
    Unrecognized_error() ;
    return false;

  } // if


  if ( ch[0] == 44 ) {
    // 不是任何東西 ex. {A

    strcat( text, ch ) ;

    strcpy( gToken_info.data, text ) ;
    gToken_info.lineNum = gLine ;
    gToken_info.token_type = UNRECOGNIZED ;
    gToken.push_back( gToken_info ) ;
    strcpy( text, "" ) ; // 清空text

    gNum = gToken.size() - 1 ;
    Unrecognized_error() ;
    return false;

  } // if

  // ********************************************************************

  // 這邊是在處理 '只能' 字母 或底線 開頭的IDENT      改成老大規定的開頭才能進
  if ( temp != EOF && ch[0] != 91 && ch[0] != 92 && ch[0] != 93
       && ch[0] != 94 && ch[0] != 96 && 64 < ch[0] && ch[0] < 123 ) {

    strcat( text, ch ) ;
    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    strcpy( for_unre, temp_ch ) ;

    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    temp = scanf( "%c", &ch[0] ) ;


    while ( temp != EOF && 47 < ch[0] && ch[0] < 123 && ch[0] != 58 && ch[0] != 59
            && ch[0] != 60 && ch[0] != 61 && ch[0] != 62 && ch[0] != 63 && ch[0] != 64
            && ch[0] != 91 && ch[0] != 92 && ch[0] != 93 && ch[0] != 94 && ch[0] != 96 ) {
      strcat( text, ch ) ;
      if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
      temp = scanf( "%c", &ch[0] ) ;
    } // while

    if ( ch[0] == ' ' || ch[0] == '+' || ch[0] == '-' || ch[0] == '*' || ch[0] == '/'
         || ch[0] == '(' || ch[0] == ':' || ch[0] != '\n' || ch[0] != '\t' || ch[0] != ';'
         || ch[0] == '>' || ch[0] == '<' || ch[0] == '=' || ch[0] == ')' || temp == EOF ) {
      // 是個正常的ident才要


      strcpy( gToken_info.data, text );
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = IDENT;
      gToken.push_back( gToken_info );
      strcpy( text, "" ); // 清空text

      // 把還沒用到的char存起來之後再判斷
      if ( temp != EOF && ch[0] != ' ' && ch[0] != '\n' && ch[0] != '\t' ) strcpy( gTemp_char, ch ) ;
      if ( ch[0] == '\n' ) gLast_read_char_is_change_line = true ;
      if ( ch[0] == '\n' ) gLine ++ ;
      
      return true ;

    } // if
    else { // 代表有接到奇怪的符號 不是ident該出現der
      strcpy( gToken_info.data, for_unre ); // 錯在第一個字
      gToken_info.lineNum = gLine ;
      gToken_info.token_type = UNRECOGNIZED;
      gToken.push_back( gToken_info );
      strcpy( text, "" ); // 清空text

      if ( ch[0] == '\n' ) gLine ++ ;
      gNum = gToken.size() - 1 ;
      Unrecognized_error() ;
      return false;

    } // else

  } // if

  // ********************************************************************

  if ( temp == EOF ) {
    return false ;
  } // if

  not_quit = false ;
  is_float = false ;

  return false ;

} // GetToken()

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

int main() {

  Read_test_num() ;

  printf( "Program starts...\n" ) ;

  gForm_main_into_GetToken = true ;

  while ( GetToken( gGet_error ) || gHave_error ) {

    gForm_main_into_GetToken = false ;

    if ( gToken[gToken.size()-1].token_type == QUIT ) {
      printf( "> Program exits...\n" ) ;
      return 0 ;
    } // if

    Command() ;

    gHave_error = false ; // 初始化
    gHave_bool = false ; // 初始化
    gFloat_operation = false ;
    gHas_belong = false ;
    gLeft_p_num = 0 ;
    gGet_error = false ;
    gValue->clear() ; // 初始化
    gNum ++ ;

    gForm_main_into_GetToken = true ;

  } // while

  printf( "> Program exits...\n" ) ;

  return 0 ;
  

} // main()


