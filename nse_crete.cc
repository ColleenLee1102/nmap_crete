#include <stddef.h>
#include <crete/custom_instr.h>

extern "C" {
  #include "lua.h"
  #include "lauxlib.h"
}

#include "nse_crete.h"

static int l_crete_make_concolic(lua_State *L)     /** md5(string s) */
{
  size_t len;
  const unsigned char *s = (unsigned char *) luaL_checklstring( L, 1, &len );
  unsigned char digest[16];

  lua_pushlstring( L, (char *) MD5( s, len, digest ), 16 );
  return 1;
}
