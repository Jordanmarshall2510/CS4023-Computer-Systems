char flipChar(char c){
    if ('a' <= c && c <= 'z' ){
      c = 'a'- c +'z';
    }
    if ('A' <= c && c <= 'Z'){
      c = 'A'-c + 'Z';
    }
    if ('0'<= c && c <= '9'){
      c= '0' - c + '9';
    }
    return c;
}
