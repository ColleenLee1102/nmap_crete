/**zl3 adding crete lua lib**/

#define lcretelib_c
#define LUA_LIB


#include "lauxlib.h"
#include "lualib.h"

#include "lua.h"

#include <stddef.h>
#include <crete/custom_instr.h>

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

static const luaL_Reg crete_funcs[] = {
  {"mconcolic", mconcolic},
  {NULL, NULL}
};


LUAMOD_API int luaopen_crete (lua_State *L) {
  luaL_newlib(L, crete_funcs);
  return 1;
}
