# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <vector>
# include <iostream>
# include <string.h>

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
  ERROR = 20,
  UNRECOGNIZED = 21,
  UNEXPECTED = 22 // 在GetToken就出現了需要使用unex判斷的地方 例如：3*-(5+2) ; 錯在'('

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
vector<float> * gValue = new vector<float>() ;
float gTemp_value = 0.0 ;
Token gToken_info ;
int gNum = 0 ;
bool gHave_error = false ; // 有錯誤所以不要印出計算結果
bool gHave_bool = false ; // 此行為布林運算不用印出計算結果
bool gFloat_operation = false ; // 這行的計算中有小數出現
bool gBool_Ans = false ; // 布林運算的結果


void Command() { // Recursive Descent Parser的第一步 決定要走哪條路


  if ( gToken[gNum].token_type == IDENT ) {            // 第一種情況   以IDENT開頭的句子
  
    if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加

      if ( gToken[gNum+1].token_type == BELONG ) {

        int temp_gNum = gNum ; // 用來暫存要被定義的IDENT在哪

        if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
          gNum = gNum + 2; // 就是GetToken的意思啦
        } // if
        else {
          return ;
        } // else

        ArithExp() ;

        if ( !gHave_error ) {
          gToken[temp_gNum].have_defined = true ; // 如果文法沒有錯這個IDENT就會被定義
        } // if

        int find_id = 0 ;
        while ( find_id <= gNum ) { // 找找看有沒有這個變數
          // 因應有可能重複定義同個變數不同值，所以把目前的這個變數都更新資料
          if ( strcmp( gToken[find_id].data, gToken[temp_gNum].data ) == 0 ) {
            gToken[find_id].variable_content = * gValue[0].data() ; // 存取IDENT的變數值
            if ( gFloat_operation ) gToken[find_id].token_type = FLOAT ;
          } // if

          find_id ++ ;
        } // while

        if ( !gHave_error && !gHave_bool ) {
          if ( !gFloat_operation ) printf( "> %.0f\n", gToken[temp_gNum].variable_content ) ;
          else { // 為了處理4捨5入的浮點數
            float console = 0 ;
            console = Rounding( gToken[temp_gNum].variable_content ) ;
            printf( "> %1.3f\n", console ) ; // 沒有error就印出結果
            gToken[temp_gNum].token_type = FLOAT ; // 把那個ident的型別改成float因為之後運算要改成float operation
          } // else

        } // if

      } // if
      else if ( gToken[gNum+1].token_type == ERROR ) { // ex. a:5; 錯在冒號

        printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum+1].data ) ;
        gHave_error = true ;

        int temp_Line = gToken[gNum+1].lineNum ;
        // 印出錯誤後把這一整行到分號都不要
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        while ( temp_Line == gToken[gNum].lineNum ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          else return ;
        } // while

        gValue->clear() ; // 初始化

      } // else if
      else if ( gToken[gNum+1].token_type == UNRECOGNIZED ) {  // ex. abc$ := 2 + 5 ; 錯在第一個'a'

        printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum+1].data ) ;
        gHave_error = true ;

        int temp_Line = gToken[gNum].lineNum ;
        // 印出錯誤後把這一整行到分號都不要
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        while ( temp_Line == gToken[gNum].lineNum ) {
          if ( gToken.size() - gNum > 1 ) gNum ++ ;
          else return ;
        } // while

        gValue->clear() ; // 初始化


      } // else if
      else {
        IDlessArithExpOrBexp() ;
        if ( !gHave_error && !gHave_bool ) {
          if ( !gFloat_operation ) printf( "> %.0f\n", * gValue[0].data() )  ; // 沒有error就印出結果
          else { // 為了處理4捨5入的浮點數
            float console = 0 ;
            console = Rounding( * gValue[0].data() ) ;
            printf( "> %1.3f\n", console ) ; // 沒有error就印出結果
          } // else

        } // if
        else if ( !gHave_error && gHave_bool ) {
          if ( gBool_Ans ) printf( "> true\n" ) ;
          else printf( "> false\n" ) ;

        } // else if

      } // else

    } // if
  } // if
  else if ( gToken[gNum].token_type == QUIT ) {       // 第二種情況   QUIT要結束程式

    gNum = gToken.size() ; // 直接後面都不要了

  } // else if
  else if ( gToken[gNum].token_type == SEMICOLON ) { // 一進來就直接是分號

    // 直接return就好

    gHave_error = true ; // 為了return回去不要多加一行 還是要加這行
    printf( "> Unexpected token : '%s'\n", gToken[gNum].data ) ;


    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    while ( temp_Line == gToken[gNum].lineNum ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      else return ;
    } // while

    gValue->clear() ; // 初始化

  } // else if
  else { // 第三種情況   不是 IDENT開頭的句子

    NOT_ID_StartArithExpOrBexp() ;

    if ( !gHave_error && !gHave_bool ) {
      if ( !gFloat_operation ) printf( "> %.0f\n", * gValue[0].data() ) ;
      else { // 為了處理4捨5入的浮點數
        float console = 0 ;
        console = Rounding( * gValue[0].data() ) ;
        printf( "> %1.3f\n", console ) ; // 沒有error就印出結果
      } // else

    } // if
    else if ( !gHave_error && gHave_bool ) {
      if ( gBool_Ans ) printf( "> true\n" ) ;
      else printf( "> false\n" ) ;

    } // else if

  } // else

  if ( gHave_error ) { // 針對錯誤行後的行第一個出現的負號正號做處理
    if ( gToken.size() - gNum > 3 ) {
      if ( gToken[gNum].token_type == MINUS ) {
        if ( gToken[gNum+1].token_type == INT || gToken[gNum+1].token_type == FLOAT ) {
          if ( gToken[gNum].lineNum == gToken[gNum+1].lineNum 
               || gToken[gNum].lineNum == gToken[gNum+1].lineNum-1 ) {
            // 這個步驟是確保不會連續出現兩個以上的sign
            // 詳情請測試G8數據21後半
            char temp[] = "-";
            strcat( temp, gToken[gNum + 1].data );
            strcpy( gToken[gNum + 1].data, temp );
            gNum++;
          } // if
        } // if
      } // if
      else if ( gToken[gNum].token_type == PLUS ) {
        if ( gToken[gNum+1].token_type == INT || gToken[gNum+1].token_type == FLOAT ) {
          if ( gToken[gNum].lineNum == gToken[gNum+1].lineNum 
               || gToken[gNum].lineNum == gToken[gNum+1].lineNum-1 ) {
            gNum++;
          } // if
        } // if
      } // if

    } // if
  } // if

  return ;

} // Command()

void IDlessArithExpOrBexp() {

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加
    // 第一層防禦 unexpected ex. Quit quit ; 錯在第二個quit
    if ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS || BooleanOprator()
         || gToken[gNum+1].token_type == MULTI || gToken[gNum+1].token_type == DIV
         || gToken[gNum+1].token_type == SEMICOLON || gToken[gNum+1].token_type == QUIT ) { 
      ; // 沒事幹 是為了else才出現的
    } // if
    else if ( gToken[gNum+1].token_type == RIGHT_PAREN ) { // ex.遇到右括號已經結束此括號內容判斷 所以返回繼續判斷

      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      return;

    } // else if
    else {
      printf( "> Unexpected token : '%s'\n", gToken[gNum+1].data );
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        else return ;
      } // while

      gValue->clear(); // 初始化

      return; // 結束重跑

    } // else

  } // if

  // 第二程防禦 undefined
  //  看看這個變數有沒有被定義過
  int find_id = 0 ;
  bool found_it = false ;
  while ( find_id < gNum && !found_it && strcmp( gToken[gNum].data, "quit" ) != 0  ) { // 找找看有沒有這個變數

    if ( strcmp( gToken[find_id].data, gToken[gNum].data ) == 0 && gToken[find_id].have_defined == true ) { 
      // 找到了就把值給取出來
      gValue->push_back( gToken[find_id].variable_content ) ;
      found_it = true ;
      if ( gToken[find_id].token_type == FLOAT ) gFloat_operation = true ;
    } // if

    find_id ++ ;

  } // while

  if ( !found_it ) {
    printf( "> Undefined identifier : '%s'\n", gToken[gNum].data ) ;
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    while ( temp_Line == gToken[gNum].lineNum ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      else return ;
    } // while

    gValue->clear() ; // 初始化

    return ;

  } // if

  // ============================================================================================

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加

    if ( gToken[gNum+ 1].token_type != PLUS && gToken[gNum+1].token_type != MINUS
         && gToken[gNum+1].token_type != QUIT && !BooleanOprator() && gToken[gNum+1].token_type != SEMICOLON
         && gToken[gNum+1].token_type != MULTI && gToken[gNum+1].token_type != DIV ) { // 不是預期中該出現的
      printf( "> Unexpected token : '%s'\n", gToken[gNum+1].data );
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        else return ;
      } // while

      gValue->clear(); // 初始化

      return;

    } // if

  } // if

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加

    while ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS
            || gToken[gNum+1].token_type == MULTI || gToken[gNum+1].token_type == DIV ) {

      if ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS ) {

        if ( gToken.size() - gNum > 1 ) {

          if ( gToken[gNum + 1].token_type == PLUS ) {

            if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
              gNum = gNum + 2; // 就是GetToken的意思啦
              Term();
            } // if
            else {
              return;
            } // else

            if ( gHave_error ) return;

            // 做計算
            if ( gValue->size() >= 2 ) {
              gTemp_value = gValue->at( gValue->size() - 2 ) + gValue->at( gValue->size() - 1 );
              // 應該是倒數第二個加最後一個再繼續遞迴
              gValue->pop_back(); // 算完就丟掉
              gValue->pop_back(); // 算完就丟掉
              gValue->push_back( gTemp_value ); // 加入算好的值
            } // if


          } // if
          else if ( gToken[gNum + 1].token_type == MINUS ) {

            if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
              gNum = gNum + 2; // 就是GetToken的意思啦
              Term();
            } // if
            else {
              return;
            } // else

            if ( gHave_error ) return;

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

      } // if
      else if ( gToken[gNum+1].token_type == MULTI || gToken[gNum+1].token_type == DIV ) {

        if ( gToken.size() - gNum > 1 ) {

          if ( gToken[gNum + 1].token_type == MULTI ) {

            if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
              gNum = gNum + 2; // 就是GetToken的意思啦
              Factor();
            } // if
            else {
              return;
            } // else


            if ( gHave_error ) return;

            // 做計算
            if ( gValue->size() >= 2 ) {
              gTemp_value = gValue->at( gValue->size() - 2 ) * gValue->at( gValue->size() - 1 );
              // 應該是倒數第二個加最後一個再繼續遞迴
              gValue->pop_back(); // 算完就丟掉
              gValue->pop_back(); // 算完就丟掉
              gValue->push_back( gTemp_value ); // 加入算好的值
            } // if

          } // if
          else if ( gToken[gNum + 1].token_type == DIV ) {

            if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
              gNum = gNum + 2; // 就是GetToken的意思啦
              Factor();
            } // if
            else {
              return;
            } // else


            if ( gHave_error ) return;

            if ( gValue->at( gValue->size() - 1 ) == 0 ) { // 除以零的錯誤
              printf( "> ERROR\n" );

              gHave_error = true;

              int temp_Line = gToken[gNum].lineNum;
              // 印出錯誤後把這一整行到分號都不要
              if ( gToken.size() - gNum > 1 ) gNum ++;
              while ( temp_Line == gToken[gNum].lineNum ) {
                if ( gToken.size() - gNum > 1 ) gNum ++;
                else return ;
              } // while

              gValue->clear() ;

              return; // 結束重跑

            } // if
            else { // 做計算

              if ( gValue->size() >= 2 ) {
                if ( gValue->at( gValue->size() - 2 ) < gValue->at( gValue->size() - 1 ) ) {
                  gFloat_operation = true;
                } // if

                if ( ( int ) gValue->at( gValue->size() - 1 ) != 0 ) {
                  if ( ( int ) gValue->at(gValue->size() - 2) % ( int ) gValue->at(gValue->size() - 1) != 0 ) {
                    gFloat_operation = true;
                  } // if
                } // if

                gTemp_value = gValue->at( gValue->size() - 2 ) / gValue->at( gValue->size() - 1 ) ;
                // 應該是倒數第二個加最後一個再繼續遞迴
                gValue->pop_back(); // 算完就丟掉
                gValue->pop_back(); // 算完就丟掉
                gValue->push_back( gTemp_value ); // 加入算好的值
              } // if

            } // else

          } // else if

        } // if

      } // else if

      if ( gToken.size() - gNum <= 1 ) return ;

    } // while

  } // if


  float value1 = * gValue[0].data() ; // 布林前計算的值先存起來
  gValue->clear() ; // 清空準備做下一次計算

  if ( BooleanOprator() ) { // 如果有出現布林運算
    gHave_bool = true ;
    int temp_gNum = gNum + 1 ; // 先記起來布林符號出現在哪

    if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
      gNum = gNum + 2; // 就是GetToken的意思啦
    } // if
    else {
      return ;
    } // else

    ArithExp() ;

    float value2 = * gValue[0].data() ; // 布林後面的計算再存起來

    float console = value1 - value2 ; // 用來確保差距大於0.0001

    if ( gToken[temp_gNum].token_type == EQUAL && -0.0001 < console && console < 0.0001
         && !gHave_error ) {
      gBool_Ans = true ;
    } // if
    else if ( gToken[temp_gNum].token_type == EQUAL && !gHave_error ) {
      if ( 0.0001 < console || console < -0.0001 ) printf( "> false\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == NOT_EQUAL && !gHave_error ) {
      if ( 0.0001 < console || console < -0.0001 ) printf( "> true\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == NOT_EQUAL && -0.0001 < console && console < 0.0001
              && !gHave_error ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGER && console >= 0.0001 && !gHave_error ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGER && console < 0.0001 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console >= 0 && !gHave_error  ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console < 0 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER && console < -0.0001 && !gHave_error  ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER && console >= -0.0001 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console <= 0 && !gHave_error  ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console > 0 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if

  } // if

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加

    // 已經要return回command了 照理來說應該已經要結束在分號了 不是分號反而奇怪
    if ( gToken[gNum+1].token_type == SEMICOLON || gHave_error ) {
      return;
    } // if
    else if ( gToken[gNum+1].token_type == UNRECOGNIZED ) {

      printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum+1].data );
      // ex . 2 + 3.4.5 + 6 ; 錯在.5不是分號下一行 也不是預期中該出現的
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        else return ;
      } // while

      return;

    } // else if
    else {
      printf( "> Unexpected token : '%s'\n", gToken[gNum+1].data );
      // ex . 2 + 3.4.5 + 6 ; 錯在.5不是分號下一行 也不是預期中該出現的
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        else return ;
      } // while

      return;

    } // else

  } // if

} // IDlessArithExpOrBexp()

bool BooleanOprator() {

  if ( gToken[gNum+1].token_type == EQUAL || gToken[gNum+1].token_type == NOT_EQUAL 
       || gToken[gNum+1].token_type == BIGGER || gToken[gNum+1].token_type == SMALLER 
       || gToken[gNum+1].token_type == BIGGGER_EQ || gToken[gNum+1].token_type == SMALLER_EQ ) return true ;
  else return false ;

} // BooleanOprator()

void NOT_ID_StartArithExpOrBexp() {

  NOT_ID_StartArithExp() ;

  if ( gHave_error ) return ;


  float value1 = * gValue[0].data() ; // 布林前計算的值先存起來
  gValue->clear() ; // 清空準備做下一次計算

  if ( BooleanOprator() ) { // 如果有出現布林運算
    gHave_bool = true ;
    int temp_gNum = gNum + 1 ; // 先記起來布林符號出現在哪

    if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
      gNum = gNum + 2 ; // 就是GetToken的意思啦
    } // if
    else {
      return ;
    } // else

    ArithExp() ;

    float value2 = * gValue[0].data() ; // 布林後面的計算再存起來

    float console = value1 - value2 ; // 用來確保差距大於0.0001

    if ( gToken[temp_gNum].token_type == EQUAL && -0.0001 < console && console < 0.0001
         && !gHave_error ) {
      gBool_Ans = true ;
    } // if
    else if ( gToken[temp_gNum].token_type == EQUAL && !gHave_error ) {
      if ( 0.0001 < console || console < -0.0001 ) printf( "> false\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == NOT_EQUAL && !gHave_error ) {
      if ( 0.0001 < console || console < -0.0001 ) printf( "> true\n" ) ;
    } // else if
    else if ( gToken[temp_gNum].token_type == NOT_EQUAL && -0.0001 < console && console < 0.0001
              && !gHave_error ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGER && console >= 0.0001 && !gHave_error ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGER && console < 0.0001 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console >= 0 && !gHave_error  ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == BIGGGER_EQ && console < 0 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER && console < -0.0001 && !gHave_error  ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER && console >= -0.0001 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console <= 0 && !gHave_error  ) {
      gBool_Ans = true ;
    } // else if
    else if ( gToken[temp_gNum].token_type == SMALLER_EQ && console > 0 && !gHave_error  ) {
      gBool_Ans = false ;
    } // else if

  } // if

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加
    // 已經要return回command了 照理來說應該已經要結束在分號了 不是分號反而奇怪
    if ( gToken[gNum + 1].token_type == SEMICOLON || gHave_error ) {
      return;
    } // if
    else if ( gToken[gNum + 1].token_type == UNRECOGNIZED ) {

      printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum + 1].data );
      // ex . 2 + 3.4.5 + 6 ; 錯在.5不是分號下一行 也不是預期中該出現的
      gHave_error = true;

      int temp_Line = gToken[gNum].lineNum;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum++;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum++;
        else return;
      } // while

      return;

    } // else if
    else {
      printf( "> Unexpected token : '%s'\n", gToken[gNum + 1].data );
      // ex . 2 + 3.4.5 + 6 ; 錯在.5不是分號下一行 也不是預期中該出現的
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum++;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum++;
        else return;
      } // while

      return;

    } // else

  } // if

} // NOT_ID_StartArithExpOrBexp()

void NOT_ID_StartArithExp() {

  NOT_ID_StartTerm() ;

  if ( gHave_error ) return ;

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加
    // 這邊用+1來代表PeekToken()
    if ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS || BooleanOprator()
         || gToken[gNum+1].token_type == MULTI || gToken[gNum+1].token_type == DIV
         || gToken[gNum+1].token_type == SEMICOLON || gToken[gNum+1].token_type == QUIT ) {
      ; // 沒事幹 是為了else才出現的
    } // if
    else {
      printf( "> Unexpected token : '%s'\n", gToken[gNum+1].data );
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum ;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        else return ;
      } // while

      gValue->clear(); // 初始化

      return; // 結束重跑

    } // else

  } // if

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加

    while ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS ) { // 重複零到多次 所以要用迴圈

      if ( gToken.size() - gNum > 1 ) {
        if ( gToken[gNum + 1].token_type == PLUS ) {

          if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
            gNum = gNum + 2; // 就是GetToken的意思啦
            Term();
          } // if
          else {
            return;
          } // else

          if ( gHave_error ) return;

          // 做計算
          if ( gValue->size() >= 2 ) {
            gTemp_value = gValue->at( gValue->size() - 2 ) + gValue->at( gValue->size() - 1 );
            // 應該是倒數第二個加最後一個再繼續遞迴
            gValue->pop_back(); // 算完就丟掉
            gValue->pop_back(); // 算完就丟掉
            gValue->push_back( gTemp_value ) ; // 加入算好的值
          } // if


        } // if
        else if ( gToken[gNum + 1].token_type == MINUS ) {

          if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
            gNum = gNum + 2; // 就是GetToken的意思啦
            Term();
          } // if
          else {
            return;
          } // else


          if ( gHave_error ) return;

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

      if ( gToken.size() - gNum <= 1 ) return ;

    } // while

  } // if

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加

    if ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS
         || gToken[gNum+1].token_type == RIGHT_PAREN || gToken[gNum+1].token_type == MULTI
         || gToken[gNum+1].token_type == DIV || BooleanOprator()
         || gToken[gNum+1].token_type == SEMICOLON || gToken[gNum+1].token_type == QUIT
         || gToken[gNum+1].token_type == IDENT || gHave_error ) {
      return;
    } // if
    else if ( gToken[gNum+1].token_type == UNRECOGNIZED ) {

      printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum+1].data );
      // ex . 2 + 3.4.5 + 6 ; 錯在.5不是分號下一行 也不是預期中該出現的
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++;
        else return ;
      } // while

      return;

    } // else if
    else {
      printf( "> Unexpected token : '%s'\n", gToken[gNum+1].data );
      // ex . 2 + 3.4.5 + 6 ; 錯在.5不是分號下一行 也不是預期中該出現的
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        else return ;
      } // while

      return;

    } // else

  } // if

} // NOT_ID_StartArithExp()

void NOT_ID_StartTerm() {

  NOT_ID_StartFactor() ;

  if ( gHave_error ) return ;

  // 這邊用+1來代表PeekToken()

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加

    while ( gToken[gNum+1].token_type == MULTI || gToken[gNum+1].token_type == DIV ) { // 重複零到多次 所以要用迴圈

      if ( gToken.size() - gNum > 1 ) {

        if ( gToken[gNum + 1].token_type == MULTI ) {

          if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
            gNum = gNum + 2; // 就是GetToken的意思啦
            Factor();
          } // if
          else {
            return;
          } // else


          if ( gHave_error ) return;

          // 做計算
          if ( gValue->size() >= 2 ) {
            gTemp_value = gValue->at( gValue->size() - 2 ) * gValue->at( gValue->size() - 1 );
            // 應該是倒數第二個加最後一個再繼續遞迴
            gValue->pop_back(); // 算完就丟掉
            gValue->pop_back(); // 算完就丟掉
            gValue->push_back( gTemp_value ); // 加入算好的值
          } // if

        } // if
        else if ( gToken[gNum + 1].token_type == DIV ) {

          if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
            gNum = gNum + 2; // 就是GetToken的意思啦
            Factor();
          } // if
          else {
            return;
          } // else

          if ( gHave_error ) return;

          if ( gValue->at( gValue->size() - 1 ) == 0 ) { // 除以零的錯誤
            printf( "> ERROR\n" );

            gHave_error = true;

            int temp_Line = gToken[gNum].lineNum;
            // 印出錯誤後把這一整行到分號都不要
            if ( gToken.size() - gNum > 1 ) gNum ++;
            while ( temp_Line == gToken[gNum].lineNum ) {
              if ( gToken.size() - gNum > 1 ) gNum ++;
              else return ;
            } // while

            gValue->clear() ;

          } // if
          else { // 做計算 // 錯在這裡！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！

            if ( gValue->size() >= 2 ) {
              if ( gValue->at( gValue->size() - 2 ) < gValue->at( gValue->size() - 1 ) ) {
                gFloat_operation = true;
              } // if

              if ( ( int ) gValue->at( gValue->size() - 1 ) != 0 ) {
                if ( ( int ) gValue->at(gValue->size() - 2) % ( int ) gValue->at(gValue->size() - 1) != 0 ) {
                  gFloat_operation = true;
                } // if
              } // if

              gTemp_value = gValue->at( gValue->size() - 2 ) / gValue->at( gValue->size() - 1 ) ;
              // 應該是倒數第二個加最後一個再繼續遞迴
              gValue->pop_back(); // 算完就丟掉
              gValue->pop_back(); // 算完就丟掉
              gValue->push_back( gTemp_value ); // 加入算好的值
            } // if

          } // else

        } // else if

      } // if

      if ( gToken.size() - gNum <= 1 ) return ;

    } // while

  } // if

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加

    if ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS
         || gToken[gNum+1].token_type == LEFT_PAREN || gToken[gNum+1].token_type == MULTI
         || gToken[gNum+1].token_type == DIV || BooleanOprator()
         || gToken[gNum+1].token_type == SEMICOLON || gToken[gNum+1].token_type == QUIT
         || gToken[gNum+1].token_type == IDENT || gHave_error ) {
      return;
    } // if
    else if ( gToken[gNum+1].token_type == UNRECOGNIZED ) {

      printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum+1].data );
      // ex . 2 + 3.4.5 + 6 ; 錯在.5不是分號下一行 也不是預期中該出現的
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;

      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++;
        else return ;
      } // while

      return;

    } // else if
    else {
      printf( "> Unexpected token : '%s'\n", gToken[gNum+1].data );
      // ex . 2 + 3.4.5 + 6 ; 錯在.5不是分號下一行 也不是預期中該出現的
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        else return ;
      } // while

      return;

    } // else

  } // if

} // NOT_ID_StartTerm()

void NOT_ID_StartFactor() {

  if ( gHave_error ) return ;

  // factor判斷不應該peekToken

  if ( gToken[gNum].token_type == INT || gToken[gNum].token_type == FLOAT ) {
    if ( gToken[gNum].token_type == INT ) gValue->push_back( atoi( gToken[gNum].data ) ) ;
    if ( gToken[gNum].token_type == FLOAT ) {
      gValue->push_back( atof( gToken[gNum].data ) ) ;
      gFloat_operation = true ;
    } // if

    return; // 如果是[SIGN] NUM 或是IDENT 就結束了

  } // if
  else if ( gToken[gNum].token_type == IDENT ) {

    int find_id = 0 ;
    bool found_it = false ;
    while ( find_id < gNum ) { // 找找看有沒有這個變數

      if ( strcmp( gToken[find_id].data, gToken[gNum].data ) == 0 
           && gToken[find_id].have_defined == true ) { 
      // 找到了就把值給取出來
        gValue->push_back( gToken[find_id].variable_content ) ;
        found_it = true ;
        if ( gToken[find_id].token_type == FLOAT ) gFloat_operation = true ;
      } // if

      find_id ++ ;

    } // while

    if ( !found_it ) {
      printf( "> Undefined identifier : '%s'\n", gToken[gNum].data ) ;
      gHave_error = true ;

      int temp_Line = gToken[gNum].lineNum ;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        else return ;
      } // while

      gValue->clear() ; // 初始化

      return ;

    } // if

    return;

  } // else if
  else if ( gToken[gNum].token_type == UNRECOGNIZED ) {  // ex. 2 + $$ - 5 ; 錯在第一個'$'
    printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum].data ) ;
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    while ( temp_Line == gToken[gNum].lineNum ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      else return ;
    } // while

    gValue->clear() ; // 初始化

    return ;

  } // else if
  else if ( gToken[gNum].token_type == UNEXPECTED ) {  // ex. 2 + $$ - 5 ; 錯在第一個'$'
    printf( "> Unexpected token : '%s'\n", gToken[gNum].data ) ;
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    while ( temp_Line == gToken[gNum].lineNum ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      else return ;
    } // while

    gValue->clear() ; // 初始化

    return ;

  } // else if
  else if ( gToken[gNum].token_type == LEFT_PAREN ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    ArithExp() ; // 這裡還要判斷右括號 才能知道有沒有ERROR
    // 此時回來的是右括號
  } // else if
  else {
    printf( "> Unexpected token : '%s'\n", gToken[gNum].data ) ; // ex . 2 + * + 5 ; 錯在'*'
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    while ( temp_Line == gToken[gNum].lineNum ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      else return ;
    } // while

    gValue->clear() ; // 初始化

    return ;

  } // else

  return;

} // NOT_ID_StartFactor()

void ArithExp()
{
  Term();

  if ( gHave_error ) return ;

  // 這邊用+1來代表PeekToken()

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加

    if ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS || BooleanOprator()
         || gToken[gNum+1].token_type == MULTI || gToken[gNum+1].token_type == DIV
         || gToken[gNum+1].token_type == SEMICOLON || gToken[gNum+1].token_type == QUIT ) {
      ; // 沒事幹 是為了else才出現的
    } // if
    else if ( gToken[gNum+1].token_type == RIGHT_PAREN ) { // ex.遇到右括號已經結束此括號內容判斷 所以返回繼續判斷

      if ( gToken.size() - gNum > 1 ) gNum ++;
      return;

    } // else if
    else {
      printf( "> Unexpected token : '%s'\n", gToken[gNum+1].data );
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++;
      } // while

      gValue->clear(); // 初始化

      return; // 結束重跑

    } // else

  } // if

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加

    while ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS ) { // 重複零到多次 所以要用迴圈

      if ( gToken.size() - gNum > 1 ) {
        if ( gToken[gNum + 1].token_type == PLUS ) {

          if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
            gNum = gNum + 2; // 就是GetToken的意思啦
            Term();
          } // if
          else {
            return;
          } // else

          if ( gHave_error ) return;


          // 做計算
          if ( gValue->size() >= 2 ) {
            gTemp_value = gValue->at( gValue->size() - 2 ) + gValue->at( gValue->size() - 1 );
            // 應該是倒數第二個加最後一個再繼續遞迴
            gValue->pop_back(); // 算完就丟掉
            gValue->pop_back(); // 算完就丟掉
            gValue->push_back( gTemp_value ); // 加入算好的值
          } // if


        } // if
        else if ( gToken[gNum + 1].token_type == MINUS ) {

          if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
            gNum = gNum + 2; // 就是GetToken的意思啦
            Term();
          } // if
          else {
            return;
          } // else


          if ( gHave_error ) return;

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

      if ( gToken.size() - gNum <= 1 ) return ;

    } // while

  } // if

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加

    // !!!!!!!!!!!!!!!!!!!只有ArithExp要加上這個小if
    if ( gToken[gNum+1].token_type == RIGHT_PAREN ) { // 括號內有括號 會變成在計算中遇到右括號 所以無法在上面return完判斷右括號

      if ( gToken.size() - gNum > 1 ) gNum ++ ; // !!!!!!!!!!!!!!!!!!!只有ArithExp要加上這個小if
      return;

    } // if
    else if ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS
              || gToken[gNum+1].token_type == RIGHT_PAREN || gToken[gNum+1].token_type == MULTI
              || gToken[gNum+1].token_type == DIV || BooleanOprator()
              || gToken[gNum+1].token_type == SEMICOLON || gToken[gNum+1].token_type == QUIT
              || gToken[gNum+1].token_type == IDENT || gHave_error ) {
      return;
    } // else if
    else if ( gToken[gNum+1].token_type == UNRECOGNIZED ) {

      printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum+1].data );
      // ex . 2 + 3.4.5 + 6 ; 錯在.5不是分號下一行 也不是預期中該出現的
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++;
        else return ;
      } // while

      return;

    } // else if
    else {
      printf( "> Unexpected token : '%s'\n", gToken[gNum+1].data );
      // ex . 2 + 3.4.5 + 6 ; 錯在.5不是分號下一行 也不是預期中該出現的
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;

      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++;
        else return ;
      } // while

      return;

    } // else

  } // if

} // ArithExp()

void Term()
{

  Factor() ;


  if ( gHave_error ) return ;

  // 這邊用+1來代表PeekToken()

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加

    while ( gToken[gNum+1].token_type == MULTI || gToken[gNum+1].token_type == DIV ) { // 重複零到多次 所以要用迴圈

      if ( gToken.size() - gNum > 1 ) {

        if ( gToken[gNum + 1].token_type == MULTI ) {

          if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
            gNum = gNum + 2; // 就是GetToken的意思啦
            Factor();
          } // if
          else {
            return;
          } // else


          if ( gHave_error ) return;

          // 做計算
          if ( gValue->size() >= 2 ) {
            gTemp_value = gTemp_value = gValue->at( gValue->size() - 2 ) * gValue->at( gValue->size() - 1 );
            // 應該是倒數第二個加最後一個再繼續遞迴
            gValue->pop_back(); // 算完就丟掉
            gValue->pop_back(); // 算完就丟掉
            gValue->push_back( gTemp_value ); // 加入算好的值
          } // if

        } // if
        else if ( gToken[gNum + 1].token_type == DIV ) {

          if ( gToken.size() - gNum > 2 ) { // 確保不會沒有空間還加
            gNum = gNum + 2; // 就是GetToken的意思啦
            Factor();
          } // if
          else {
            return;
          } // else

          if ( gHave_error ) return;

          if ( gValue->at( gValue->size() - 1 ) == 0 ) { // 除以零的錯誤
            printf( "> ERROR\n" );

            gHave_error = true;

            int temp_Line = gToken[gNum].lineNum;
            // 印出錯誤後把這一整行到分號都不要
            if ( gToken.size() - gNum > 1 ) gNum ++ ;
            while ( temp_Line == gToken[gNum].lineNum ) {
              if ( gToken.size() - gNum > 1 ) gNum ++ ;
              else return ;
            } // while


          } // if
          else { // 做計算

            if ( gValue->size() >= 2 ) {
              if ( gValue->at( gValue->size() - 2 ) < gValue->at( gValue->size() - 1 ) ) {
                gFloat_operation = true;
              } // if

              if ( ( int ) gValue->at( gValue->size() - 1 ) != 0 ) {
                if ( ( int ) gValue->at(gValue->size() - 2) % ( int ) gValue->at(gValue->size() - 1) != 0 ) {
                  gFloat_operation = true;
                } // if
              } // if

              gTemp_value = gValue->at( gValue->size() - 2 ) / gValue->at( gValue->size() - 1 ) ;
              // 應該是倒數第二個加最後一個再繼續遞迴
              gValue->pop_back(); // 算完就丟掉
              gValue->pop_back(); // 算完就丟掉
              gValue->push_back( gTemp_value ); // 加入算好的值
            } // if

          } // else

        } // else if

      } // if

      if ( gToken.size() - gNum <= 1 ) return ;

    } // while

  } // if

  if ( gToken.size() - gNum > 1 ) { // 確保不會沒有空間還加

    if ( gToken[gNum+1].token_type == PLUS || gToken[gNum+1].token_type == MINUS
         || gToken[gNum+1].token_type == RIGHT_PAREN || gToken[gNum+1].token_type == MULTI
         || gToken[gNum+1].token_type == DIV || BooleanOprator()
         || gToken[gNum+1].token_type == SEMICOLON || gToken[gNum+1].token_type == QUIT
         || gToken[gNum+1].token_type == IDENT || gHave_error ) {
      return;
    } // if
    else if ( gToken[gNum+1].token_type == UNRECOGNIZED ) {

      printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum+1].data );
      // ex . 2 + 3.4.5 + 6 ; 錯在.5不是分號下一行 也不是預期中該出現的
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++ ;
        else return ;
      } // while

      return;

    } // else if
    else {
      printf( "> Unexpected token : '%s'\n", gToken[gNum+1].data );
      // ex . 2 + 3.4.5 + 6 ; 錯在.5不是分號下一行 也不是預期中該出現的
      gHave_error = true;

      int temp_Line = gToken[gNum+1].lineNum;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++;
        else return ;
      } // while

      return;

    } // else

  } // if
  
} // Term()

void Factor()
{
  // factor判斷不應該peekToken


  if ( gHave_error ) return ;

  if ( gToken[gNum].token_type == INT || gToken[gNum].token_type == FLOAT ) {
    if ( gToken[gNum].token_type == INT ) gValue->push_back( atoi( gToken[gNum].data ) ) ;
    if ( gToken[gNum].token_type == FLOAT ) {
      gValue->push_back( atof( gToken[gNum].data ) ) ;
      gFloat_operation = true ;
    } // if

    return; // 如果是[SIGN] NUM 或是IDENT 就結束了

  } // if
  else if ( gToken[gNum].token_type == IDENT ) {

    int find_id = 0 ;
    bool found_it = false ;
    while ( find_id < gNum && !found_it && strcmp( gToken[gNum].data, "quit" ) != 0 ) { // 找找看有沒有這個變數

      if ( strcmp( gToken[find_id].data, gToken[gNum].data ) == 0 
           && gToken[find_id].have_defined == true ) { 
      // 找到了就把值給取出來
        gValue->push_back( gToken[find_id].variable_content ) ;
        found_it = true ;
        if ( gToken[find_id].token_type == FLOAT ) gFloat_operation = true ;
      } // if

      find_id ++ ;

    } // while

    if ( !found_it ) {
      printf( "> Undefined identifier : '%s'\n", gToken[gNum].data ) ;
      gHave_error = true ;

      int temp_Line = gToken[gNum].lineNum ;
      // 印出錯誤後把這一整行到分號都不要
      if ( gToken.size() - gNum > 1 ) gNum ++;
      while ( temp_Line == gToken[gNum].lineNum ) {
        if ( gToken.size() - gNum > 1 ) gNum ++;
        else return ;
      } // while

      gValue->clear() ; // 初始化

      return ;

    } // if

    return;

  } // else if
  else if ( gToken[gNum].token_type == UNRECOGNIZED ) {  // ex. 2 + $$ - 5 ; 錯在第一個'$'
    printf( "> Unrecognized token with first char : '%s'\n", gToken[gNum].data ) ;
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    while ( temp_Line == gToken[gNum].lineNum ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      else return ;
    } // while

    gValue->clear() ; // 初始化

    return ;

  } // else if

  else if ( gToken[gNum].token_type == UNEXPECTED ) {  // ex. 2 + $$ - 5 ; 錯在第一個'$'
    printf( "> Unexpected token : '%s'\n", gToken[gNum].data ) ;
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    while ( temp_Line == gToken[gNum].lineNum ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      else return ;
    } // while

    gValue->clear() ; // 初始化

    return ;

  } // else if
  else if ( gToken[gNum].token_type == LEFT_PAREN ) {
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    ArithExp() ; // 這裡還要判斷右括號 才能知道有沒有ERROR
    // 回來的是右括號
  } // else if
  else {
    printf( "> Unexpected token : '%s'\n", gToken[gNum].data ) ; // ex . 2 + * + 5 ; 錯在'*'
    gHave_error = true ;

    int temp_Line = gToken[gNum].lineNum ;
    // 印出錯誤後把這一整行到分號都不要
    if ( gToken.size() - gNum > 1 ) gNum ++ ;
    while ( temp_Line == gToken[gNum].lineNum ) {
      if ( gToken.size() - gNum > 1 ) gNum ++ ;
      else return ;
    } // while

    gValue->clear() ; // 初始化

    return;

  } // else

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
  bool error_sign = false ;

  gToken_info.have_defined = false ; // 這裡只是給個初始值 真正判斷會在parser那邊
  gToken_info.variable_content = 0 ;

  // ********************************************************************
  if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
  temp = scanf( "%c", &ch[0] ); // 先讀第一個測試編號
  while ( temp != EOF && ch[0] != '\n' && 58 > ch[0] && ch[0] > 47 ) {
    if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
    strcat( text, ch ) ;
    temp = scanf( "%c", &ch[0] ); // 先讀第一個測試編號
  } // while

  if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch

  strcpy( gToken_info.testNum, text ) ;
  strcpy( text, "" ) ; // 清空text
  // ********************************************************************

  while ( temp != EOF ) { // 讀到結束

    while ( temp != EOF ) { // 讀到換行 \n 還不知道老大input怎麼給 先不動
      // ex. 3+2 = 5
      // ex. 3+-2 = 1 因為後面那個減是負號的意思

      // ********************************************************************

      if ( ch[0] == '+' || ch[0] == '*' || ch[0] == '-' ) { // 處理加乘

        // ex. a:=-9; or ( -5 + 6 ) or 3 * -1 or 1 - -3 or 1 < -2 or 100 + ( - - 5 + 2 )
        // 有一種狀況還未解決,就是
        // ; quit  // 這行有錯 下一行應該是負號不是減號才對
        // -36 - 23 ;
        int temp_l = 0 ;

        if ( temp_ch[0] == '=' || temp_ch[0] == ';' || temp_ch[0] == '(' || temp_ch[0] == '+'
             || temp_ch[0] == '*' || temp_ch[0] == '/' || temp_ch[0] == '>' || temp_ch[0] == '<'
             || temp_ch[0] == '-' ) {

          if ( gToken.size() > 0 ) { // 裡面至少有一個token 才會有效
            if ( ch[0] == '+' || ch[0] == '-' ) {
              strcpy( temp_ch, ch ) ;
              temp_l = line ;
              is_sign = true;
            } // if
            else if ( ch[0] == '*' ) {
              strcat( text, ch );
              strcpy( gToken_info.data, text ); // 存取token資訊
              gToken_info.lineNum = line; // 看他屬於哪一行
              gToken_info.token_type = MULTI;
              gToken.push_back( gToken_info  );
              strcpy( text, "" ); // 清空text

              temp = scanf( "%c", &ch[0] ); // 如果減號前面有其他運算元 代表是負號
              if ( ch[0] == '\n' ) line++;
              while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) { // 讀到下一個合理字元出現
                temp = scanf( "%c", &ch[0] );
                if ( ch[0] == '\n' ) line++;
              } // while

            } // else if

          } // if
          else {
            strcat( text, ch );
            strcpy( gToken_info.data, text ) ; // 存取token資訊
            gToken_info.lineNum = line; // 看他屬於哪一行
            gToken_info.token_type = UNEXPECTED;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ); // 如果減號前面有其他運算元 代表是負號
            if ( ch[0] == '\n' ) line++;
            while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) { // 讀到下一個合理字元出現
              if ( ch[0] != ' ' || ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
              temp = scanf( "%c", &ch[0] );
              if ( ch[0] == '\n' ) line ++;
            } // while
          } // else

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
            gToken_info.token_type = MINUS ;
            gToken.push_back( gToken_info ) ;
            strcpy( text, "" ) ; // 清空text
          } // if

          if ( ch[0] != ' ' || ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ); // 如果減號前面有其他運算元 代表是負號
          if ( ch[0] == '\n' ) line ++ ;
          while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) { // 讀到下一個合理字元出現
            if ( ch[0] != ' ' || ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] );
            if ( ch[0] == '\n' ) line ++ ;
          } // while

          // 這個if 是用來處理100 + ( --5 +2 ) ; 這樣的狀況 仔細思考 --5那邊的處理
          if ( gToken[gToken.size()-1].token_type == UNEXPECTED && temp_ch[0] == '-' 
               && 58 > ch[0] && ch[0] > 47 ) {
            strcat( text, "-" ) ;
            is_sign = false ;
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          } // if

          if ( ch[0] == '*' ) {
            strcat( text, ch );
            strcpy( gToken_info.data, text ); // 存取token資訊
            gToken_info.lineNum = line; // 看他屬於哪一行
            gToken_info.token_type = UNEXPECTED;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] ); // 如果減號前面有其他運算元 代表是負號
            if ( ch[0] == '\n' ) line ++ ;
            while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) { // 讀到下一個合理字元出現
              if ( ch[0] != ' ' || ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
              temp = scanf( "%c", &ch[0] );
              if ( ch[0] == '\n' ) line++;
            } // while

          } // if

        } // else

        if ( is_sign ) { // 是sign才需要再讀一次看是不是接數字

          temp = scanf( "%c", &ch[0] ); // 如果減號前面有其他運算元 代表是負號
          if ( ch[0] == '\n' ) line ++ ;
          while ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) { // 讀到下一個合理字元出現
            temp = scanf( "%c", &ch[0] );
            if ( ch[0] == '\n' ) line ++ ;
          } // while

        } // if

        if ( is_sign && temp_ch[0] == '-' && 58 > ch[0] && ch[0] > 47 ) { // ex. a:=-9+-18;
          strcat( text, "-" ) ;
          is_sign = false ;
        } // if
        else if ( is_sign && temp_ch[0] == '+' && 58 > ch[0] && ch[0] > 47 ) { // ex. a:=-9+-18;
          strcat( text, "" ) ;
          is_sign = false ;
        } // else if
        else if ( is_sign && temp_ch[0] == '+' ) { // sign後面不是接數字  反而是接+-*/這些
          if ( ch[0] == '(' || ch[0] == '+' || ch[0] == '-' || ch[0] == '*' || ch[0] == '.'
               || ch[0] == ')' || ch[0] == '=' || ch[0] == '<' || ch[0] == '>' || ch[0] == ':' ) {

            if ( temp_l == line ) { // 不同行的錯要分開看
              strcat( text, ch );
              strcpy( gToken_info.data, text ); // 存取token資訊
              gToken_info.lineNum = line; // 看他屬於哪一行
              gToken_info.token_type = UNEXPECTED;
              gToken.push_back( gToken_info );
              strcpy( text, "" ); // 清空text
              is_sign = false;

              while ( temp != EOF || ch[0] != '\n' ) { // 把這行讀掉不要
                if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
                temp = scanf( "%c", &ch[0] );
                if ( ch[0] == '\n' ) line++;
              } // while
            } // if
            else { // 先正常給他存加 再到文法跑錯誤
              strcat( text, temp_ch ) ;
              strcpy( gToken_info.data, text ) ; // 存取token資訊
              gToken_info.lineNum = line ; // 看他屬於哪一行
              gToken_info.token_type = PLUS ;
              gToken.push_back( gToken_info ) ;
              strcpy( text, "" ) ; // 清空text
            } // else

          } // if
          else {
            error_sign = true ;
            is_sign = false;
          } // else

        } // else if
        else if ( is_sign && temp_ch[0] == '-' ) { // sign後面不是接數字  反而是接+-*/這些

          if ( ch[0] == '(' || ch[0] == '+' || ch[0] == '-' || ch[0] == '*' || ch[0] == '.'
               || ch[0] == ')' || ch[0] == '=' || ch[0] == '<' || ch[0] == '>' || ch[0] == ':' ) {

            if ( temp_l == line ) { // 不同行的錯要分開看
              strcat( text, ch );
              strcpy( gToken_info.data, text ); // 存取token資訊
              gToken_info.lineNum = line; // 看他屬於哪一行
              gToken_info.token_type = UNEXPECTED;
              gToken.push_back( gToken_info );
              strcpy( text, "" ); // 清空text
              is_sign = false;

              while ( temp != EOF || ch[0] != '\n' ) { // 把這行讀掉不要
                if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
                temp = scanf( "%c", &ch[0] );
                if ( ch[0] == '\n' ) line++;
              } // while
            } // if
            else { // 先正常給他存減 再到文法跑錯誤
              strcat( text, temp_ch ) ;
              strcpy( gToken_info.data, text ) ; // 存取token資訊
              gToken_info.lineNum = line ; // 看他屬於哪一行
              gToken_info.token_type = MINUS ;
              gToken.push_back( gToken_info ) ;
              strcpy( text, "" ) ; // 清空text
            } // else

          } // if
          else if ( ch[0] != '/' ) { 
            error_sign = true ;
            is_sign = false;
          } // else if

        } // else if

        for_break = true ;

        if ( ch[0] == '\n' ) line ++ ;

      } // if


      // ********************************************************************

      if ( ch[0] == '/' ) { // 遇到除號 或是 註解

        temp = scanf( "%c", &ch[0] );

        if ( ch[0] == '/' ) { // 是註解

          temp = scanf( "%c", &ch[0] );
          while ( ch[0] != '\n' && temp != EOF ) { // 把註解讀掉
            temp = scanf( "%c", &ch[0] );
          } // while

        } // if
        else {
          strcat( text, "/" ) ;
          strcpy( gToken_info.data, text ) ; // 存取token資訊
          gToken_info.lineNum = line ; // 看他屬於哪一行
          gToken_info.token_type = DIV ;
          gToken.push_back( gToken_info ) ;
          strcpy( text, "" ) ; // 清空text
        } // else

        if ( ch[0] == '\n' ) line ++ ;
        error_sign = false ;
      } // if



      // ********************************************************************

      if ( ch[0] == ':' ) { // 遇到冒號的處理
        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] );
        if ( ch[0] == '=' ) {
          strcat( text, ch ) ;
          strcpy( gToken_info.data, ":=" ) ; // ex. a := 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = BELONG ;
          gToken.push_back( gToken_info ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] );
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
        if ( ch[0] == '\n' ) line ++ ;

      } // if

      // ********************************************************************

      if ( ch[0] == '<' || ch[0] == '>' || ch[0] == '=' ) { // 遇到比較的運算元

        strcat( text, ch );
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] );
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
          temp = scanf( "%c", &ch[0] );
        } // else if
        else if ( temp_ch[0] == '<' && ch[0] == '=' ) {
          strcat( text, ch );
          strcpy( gToken_info.data, text ) ; // ex. a <= 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = SMALLER_EQ;
          gToken.push_back( gToken_info );
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] );
        } // else if
        else if ( temp_ch[0] == '>' && ch[0] == '=' ) {
          strcat( text, ch );
          strcpy( gToken_info.data, text ) ; // ex. a >= 1 ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = BIGGGER_EQ;
          gToken.push_back( gToken_info );
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] );
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
        gToken_info.token_type = LEFT_PAREN ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ;

        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] );
        while ( ch[0] == '(' ) { // ex. (((a-2)+1)*2)-3) 遇到很多左括號的情況
          strcpy( gToken_info.data, "(" ) ; // 存取token資訊
          gToken_info.lineNum = line ;
          gToken_info.token_type = LEFT_PAREN ;
          gToken.push_back( gToken_info ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] );
        } // while

        for_break = true ;
        if ( ch[0] == '\n' ) line ++ ;

      } // if

      if ( ch[0] == ')' ) {
        strcpy( gToken_info.data, ")" ) ; // 存取token資訊
        gToken_info.lineNum = line ;
        gToken_info.token_type = RIGHT_PAREN ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text
        temp = scanf( "%c", &ch[0] );
        for_break = true ;
        if ( ch[0] == '\n' ) line ++ ;

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
        temp = scanf( "%c", &ch[0] );
        // 讀下一個東西 因為還沒有quit

        if ( ch[0] == '\n' ) line ++ ;

      } // if

      // ********************************************************************

      if ( 58 > ch[0] && ch[0] > 47 && !for_break ) { // 數字開頭的處理

        if ( is_sign ) {
          is_sign = false ;
          strcat( text, "-" ) ; // 到了這裡is sign居然還有作用代表可能是這樣的情況需要補他的符號
        } // if

        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] );

        // 如果後面還是數字就繼續合併
        int i = 0 ;
        while ( ch[0] == '0' || ch[0] == '1' || ch[0] == '2' || ch[0] == '3' || ch[0] == '4'
                || ch[0] == '5' || ch[0] == '6' || ch[0] == '7' || ch[0] == '8' || ch[0] == '9'
                || ch[0] == '\n' ) {

          if ( ch[0] > 47 && ch[0] < 58 ) {
            strcat( text, ch );
          } // if
          
          if ( ch[0] == '\n' ) i ++ ;

          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ); // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] );

        } // while

        if ( ch[0] == '.' ) { // 浮點數的處理
          strcat( text, ch ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] );
          is_float = true ;
          while ( ch[0] != '\n' && temp != EOF && ch[0] != ' ' && ch[0] > 47 && ch[0] < 58  ) {
            strcat( text, ch ) ;
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            temp = scanf( "%c", &ch[0] );
          } // while
        } // if

        strcpy( gToken_info.data, text ) ; // 存取token資訊
        gToken_info.lineNum = line ;
        if ( !is_float ) gToken_info.token_type = INT ;
        else gToken_info.token_type = FLOAT ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text
        for_break = true ;
        if ( ch[0] == '\n' ) line ++ ;
        line = line + i ;

      } // if

      // ********************************************************************

      if ( ch[0] == '.' && !for_break ) { // 點開頭的處理

        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] ) ;

        // 如果後面還是數字就繼續合併
        while ( ch[0] != '\n' && temp != EOF && ch[0] != ' ' && ch[0] > 47 && ch[0] < 58 ) {
          strcat( text, ch ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] ) ;
        } // while

        strcpy( gToken_info.data, text ); // 存取token資訊
        gToken_info.lineNum = line;
        gToken_info.token_type = FLOAT;
        gToken.push_back( gToken_info );
        strcpy( text, "" ); // 清空text
        for_break = true;
        if ( ch[0] == '\n' ) line++;

        for_break = true ;
        error_sign = false ;

      } // if

      // ********************************************************************


      if ( !for_break && ch[0] == 'q' ) { // quit 的處理

        if ( gToken.size() > 0 ) {
          if ( gToken[gToken.size() - 1].lineNum == line 
               && gToken[gToken.size() - 1].token_type != SEMICOLON ) {
            not_quit = true;
          } // if
          
        } // if
        // 是否是真的結束還是只是一個 使用line看看quit是不是出在新的一行

        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        temp = scanf( "%c", &ch[0] ) ;

        int i = 0 ; // 這是為了 quit@#% 這個也是符合嚼宴的quit 所以取前四個來看

        while ( temp != EOF && ch[0] != ' ' && ch[0] != '\n' && ch[0] != ';' && i < 3 ) {
          strcat( text, ch ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          temp = scanf( "%c", &ch[0] ) ;
          i ++ ;
        } // while

        if ( strcmp( text, "quit" ) == 0 && !not_quit ) { // 確認是不是讀到quit
          strcpy( gToken_info.data, text ) ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = QUIT ;
          gToken.push_back( gToken_info ) ;

        } // if
        else { // q開頭的IDENT 包含 不是結束的quit
          strcpy( gToken_info.data, text ) ;
          gToken_info.lineNum = line ;
          gToken_info.token_type = IDENT ;
          gToken.push_back( gToken_info ) ;
        } // else if

        strcpy( text, "" ) ; // 清空text
        if ( ch[0] == '\n' ) line ++ ;

        for_break = true ;
        error_sign = false ;

      } // if

      // ********************************************************************

      if ( !for_break && ch[0] != ' ' && 29 < ch[0] && ch[0] < 40 ) { // 不是任何東西 ex. $$

        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] ) ;

        strcpy( gToken_info.data, text ) ;
        gToken_info.lineNum = line ;
        gToken_info.token_type = UNRECOGNIZED ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text

        while ( ch[0] != EOF && ch[0] != '\n' ) {
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] ) ;
        } // while

        is_sign = false ;
        line ++ ;
        error_sign = false ;

      } // if

      if ( !for_break && ch[0] != ' ' && 90 < ch[0] && ch[0] < 97 && ch[0] != 95 ) {
           // 不是任何東西 ex. [2

        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] ) ;

        strcpy( gToken_info.data, text ) ;
        gToken_info.lineNum = line ;
        gToken_info.token_type = UNRECOGNIZED ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text

        while ( ch[0] != EOF && ch[0] != '\n' ) {
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] ) ;
        } // while

        is_sign = false ;
        line ++ ;
        error_sign = false ;

      } // if

      if ( !for_break && ch[0] != ' ' && 122 < ch[0] && ch[0] < 128 ) {
           // 不是任何東西 ex. {A

        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] ) ;

        strcpy( gToken_info.data, text ) ;
        gToken_info.lineNum = line ;
        gToken_info.token_type = UNRECOGNIZED ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text

        while ( ch[0] != EOF && ch[0] != '\n' ) {
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] ) ;
        } // while

        is_sign = false ;
        line ++ ;
        error_sign = false ;

      } // if

      if ( !for_break && ch[0] != ' ' && 62 < ch[0] && ch[0] < 65 ) {
        // 不是任何東西 ex. {A

        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] ) ;

        strcpy( gToken_info.data, text ) ;
        gToken_info.lineNum = line ;
        gToken_info.token_type = UNRECOGNIZED ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text

        while ( ch[0] != EOF && ch[0] != '\n' ) {
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] ) ;
        } // while

        is_sign = false ;
        line ++ ;
        error_sign = false ;

      } // if


      if ( !for_break && ch[0] != ' ' && ch[0] == 44 ) {
        // 不是任何東西 ex. {A

        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        scanf( "%c", &ch[0] ) ;

        strcpy( gToken_info.data, text ) ;
        gToken_info.lineNum = line ;
        gToken_info.token_type = UNRECOGNIZED ;
        gToken.push_back( gToken_info ) ;
        strcpy( text, "" ) ; // 清空text

        while ( ch[0] != EOF && ch[0] != '\n' ) {
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] ) ;
        } // while

        is_sign = false ;
        line ++ ;
        error_sign = false ;

      } // if

      // ********************************************************************

      // 這邊是在處理 字母 或 特殊符號開頭的 IDENT      改成老大規定的開頭才能進
      if ( !for_break && ch[0] != ' ' && temp != EOF && ch[0] != '\n' && ch[0] != ':' && ch[0] != '.'
           && ch[0] != ' ' && ch[0] != ';' && ch[0] != '=' && ch[0] != '(' && ch[0] != ')'
           && ch[0] != '+' && ch[0] != '-' && ch[0] != '*' && ch[0] != '/' && ch[0] != '\t'
           && ch[0] != '>' && ch[0] != '<' && 47 < ch[0] && ch[0] < 123 ) {

        strcat( text, ch ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
        strcpy( for_unre, temp_ch ) ;


        scanf( "%c", &ch[0] ) ;
        if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch


        while ( temp != EOF && ch[0] != '\n' && ch[0] != ':' && ch[0] != ' ' && ch[0] != ';'
                && ch[0] != '=' && 47 < ch[0] && ch[0] < 123 && ch[0] != 96 && ch[0] != '@'
                && ch[0] != 91 && ch[0] != 92 && ch[0] != 93 && ch[0] != 94 && ch[0] != '\t'
                && ch[0] != '>' && ch[0] != '<' && ch[0] != '?' ) {
          strcat( text, ch ) ;
          if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
          scanf( "%c", &ch[0] ) ;
        } // while

        if ( ch[0] == ' ' || ch[0] == '+' || ch[0] == '-' || ch[0] == '*' || ch[0] == '/'
             || ch[0] == '(' || ch[0] == ':' || ch[0] != '\n' || ch[0] != '\t'
             || ch[0] == '>' || ch[0] == '<' || ch[0] == '=' || ch[0] == ')' || temp == EOF ) { 
          // 是個正常的ident才要

          if ( !error_sign ) {
            strcpy( gToken_info.data, text );
            gToken_info.lineNum = line;
            gToken_info.token_type = IDENT;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
          } // if
          else { // ident前面是sign ex.-a
            strcpy( gToken_info.data, text ); // 存取token資訊
            gToken_info.lineNum = line; // 看他屬於哪一行
            gToken_info.token_type = UNEXPECTED;
            gToken.push_back( gToken_info );
            strcpy( text, "" ); // 清空text
            error_sign = false ;
          } // else

        } // if
        else { // 代表有接到奇怪的符號 不是ident該出現der
          strcpy( gToken_info.data, for_unre ); // 錯在第一個字
          gToken_info.lineNum = line;
          gToken_info.token_type = UNRECOGNIZED;
          gToken.push_back( gToken_info );
          strcpy( text, "" ); // 清空text

          while ( temp != EOF && ch[0] != '\n' && ch[0] != ';' ) {
            if ( ch[0] != ' ' && ch[0] != '\t' ) strcpy( temp_ch, ch ) ; // 儲存上一個 ch
            scanf( "%c", &ch[0] ) ;
          } // while

          is_sign = false ;
          line ++ ;

        } // else

      } // if


      // ********************************************************************

      if ( ch[0] == ' ' || ch[0] == '\n' || ch[0] == '\t' ) { // 把空白跟換行讀掉

        temp = scanf( "%c", &ch[0] );
        if ( ch[0] == '\n' ) line ++ ;
        while ( temp != EOF && ch[0] == ' ' && ch[0] == '\n' ) {
          if ( ch[0] == '\n' ) line ++ ;
          temp = scanf( "%c", &ch[0] );
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

  if ( temp == EOF ) {
    printf( "> ERROR (no more input) : END-OF-FILE encountered\n" ) ;
    return ;
  } // if

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
  printf( "Program starts...\n" ) ;
  GetToken();
  // 好像有除以零就會莫名其妙在這個地方卡住


  if ( gToken.size() == 2 ) { 
    // 為了輸入不到一個token的情況 但是還是要進parser裡面判斷 
    // 結束後不用初始化是因為 反正也沒有後面要跑了
    Command() ;
  } // if

  while ( gNum < gToken.size() - 1 && gToken[gNum].token_type != QUIT ) {
    // 迴圈一次run一行(到分號)   -2是因為減一個size()減一個quit
    printf( "有進喔！＾＾ 從'%s'進去的\n", gToken[gNum].data ) ;

    Command() ; // 進入parser運算

    // 退出來會在分號
    if ( gToken.size() - gNum > 1 ) {
      if ( gToken[gNum+1].token_type == SEMICOLON && !gHave_error && gToken.size() - gNum > 2 ) {
        gNum = gNum + 2 ; // 要跳過分號
      } // if
      else if ( !gHave_error && gToken.size() - gNum > 1 ) gNum ++ ;
      // 為何有error就不用 ++ 是因為error會掉過該還到下一行的一開始 直接丟就去跑就好不用加
    } // if
    
    gHave_error = false ; // 初始化
    gHave_bool = false ; // 初始化
    gFloat_operation = false ;
    gValue->clear() ; // 初始化

  } // while



  printf( "> Program exits..." ) ;

} // main()


