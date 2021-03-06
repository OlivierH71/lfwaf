/*
 *  Helper functions (mainly text manipulation) FOR LFAWF
 *
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
 */
#ifndef lfwaf_helpers_h
#define lfwaf_helpers_h

// inplace uppercasing 0 based character string
static char * UpperStr( char * str ) {
    while( *str = toupper( *str ) )
      str++;
    return str;
}

// uppcase 0 based character string to destination
static char * strtoupper( char * dest, const char * src ) {
    char * result = dest;
    while( *dest++ = toupper( *src++ ) );
    return result;
}

#endif
