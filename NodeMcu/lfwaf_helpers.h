
#ifndef lfwaf_helpers_h
#define lfwaf_helpers_h


static char * UpperStr( char * str ) {
    while( *str = toupper( *str ) )
      str++;
    return str;
}


static char * strtoupper( char * dest, const char * src ) {
    char * result = dest;
    while( *dest++ = toupper( *src++ ) );
    return result;
}

#endif
