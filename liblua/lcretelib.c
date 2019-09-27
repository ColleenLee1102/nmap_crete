/**zl3 adding crete lua lib**/

#define lcretelib_c
#define LUA_LIB


#include "lauxlib.h"
#include "lualib.h"

#include "lua.h"

#include <stddef.h>
#include <crete/custom_instr.h>

#include <stdio.h>
#include <stdlib.h>

//zl3 add afl flag
#include "afl_input.h"
extern char *aflinputfile = "";

static int mconcolic (lua_State *L) {
  lua_Integer len;  /* concolic string length */
  len = luaL_checkinteger(L, 2);
  char *str = luaL_checkstring(L, 1);
  printf("api make concolic enter\n");
  str[len+1]='\0';
  //crete_make_concolic(str, len, "lua_api_string");
  printf("api make concolic finished\n");
  //printf("lua api calling, integer is %d, str is %s\n", len, str);
  return 0;
}

static int aflreadfile (lua_State *L) {
  luaL_Buffer b;
  FILE *aflfile;

  lua_Integer len;
  len = luaL_checkinteger(L,1);
  char *buffer = (char *) malloc(len);

  //aflfile = fopen("/home/zheli/test/afl-nmap/testcase_dir_1/1.txt", "r");
  printf("afl input file path is %s\n", aflinputfile);
  aflfile = fopen(aflinputfile, "r");

  if(aflfile == NULL){
	  printf("aflreadfile failed to read file\n");
	  exit(EXIT_FAILURE);
  }
  size_t t = fread(buffer, len, 1,  aflfile);
  printf("t is %d\n",t);
  if(t > 0){
	  luaL_buffinit(L, &b);
	  luaL_addlstring(&b, buffer, len);
  }
  fclose(aflfile);
  printf("afl buffer read is %s\n", buffer);
  luaL_pushresult(&b);
  return 1;
}

static const luaL_Reg crete_funcs[] = {
  {"mconcolic", mconcolic},
  {"aflreadfile", aflreadfile},
  {NULL, NULL}
};


LUAMOD_API int luaopen_crete (lua_State *L) {
  luaL_newlib(L, crete_funcs);
  return 1;
}
