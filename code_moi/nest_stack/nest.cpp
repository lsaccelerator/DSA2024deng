/*DSA*/#include "nest.h"

bool paren ( const char exp[], Rank lo, Rank hi ) { 
   Stack<char> S; 
   for ( Rank i = lo; i <= hi; i++ ) {
      switch ( exp[i] ) { 
         case '(': case '[': case '{': S.push ( exp[i] ); break;
         case ')': if ( ( S.empty() ) || ( '(' != S.pop() ) ) return false; break;
         case ']': if ( ( S.empty() ) || ( '[' != S.pop() ) ) return false; break;
         case '}': if ( ( S.empty() ) || ( '{' != S.pop() ) ) return false; break;
         default: break; 
      /*DSA*/} 
   }
   return S.empty();  
 }

bool parenHTML ( const char exp[], Rank lo, Rank hi ) { 
   Stack<char> S; 
   Stack<std::string> S1; 
   for ( Rank i = lo; i <= hi; i++ ) {
      switch ( exp[i] ) { 
         case '(': case '[': case '{': S.push ( exp[i] ); break;
         case ')': if ( ( S.empty() ) || ( '(' != S.pop() ) ) return false; break;
         case ']': if ( ( S.empty() ) || ( '[' != S.pop() ) ) return false; break;
         case '}': if ( ( S.empty() ) || ( '{' != S.pop() ) ) return false; break;
         case  '<':  
            {
               bool find= false; string tmp;
               if (exp[++i] == '/') {find =true; i++;}
               while (exp[i]!= '>') {tmp += exp[i++];} 
               if (find){
                  if (tmp!=S1.pop()) {return false;break;}
                  else S1.push(tmp);}
            }
            break;
         default: break; 
      /*DSA*/} 
   }
   return S.empty();  
 }