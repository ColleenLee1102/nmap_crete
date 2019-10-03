# Makefile for building Lua
# See ../doc/readme.html for installation and customization instructions.

# == CHANGE THE SETTINGS BELOW TO SUIT YOUR ENVIRONMENT =======================

# Your platform. See PLATS for possible values.
PLAT= none

CC= gcc -std=gnu99
#zl3
AFL_CC = /home/zheli/afl-nmap-interpreter/afl-2.52b/afl-gcc
AFL_CXX = /home/zheli/afl-nmap-interpreter/afl-2.52b/afl-g++
#zl3
CFLAGS= -g -O0 -Wall -Wextra -DLUA_COMPAT_5_2 $(SYSCFLAGS) $(MYCFLAGS)
LDFLAGS= $(SYSLDFLAGS) $(MYLDFLAGS)
LIBS= -lm -lcrete_test_case -L/home/zheli/clean_crete/crete-build/bin/boost/ -lboost_system -lboost_serialization -lstdc++ -lcrete_vm_comm $(SYSLIBS) $(MYLIBS)

#zl3
INCLUDES= -I/home/zheli/clean_crete/crete/front-end/guest/lib/include

AR= ar rcu
RANLIB= ranlib
RM= rm -f

SYSCFLAGS=
SYSLDFLAGS=
SYSLIBS=

MYCFLAGS=
MYLDFLAGS= 
MYLIBS=
MYOBJS=

# == END OF USER SETTINGS -- NO NEED TO CHANGE ANYTHING BELOW THIS LINE =======

PLATS= aix bsd c89 freebsd generic linux macosx mingw posix solaris

#zl3
AFL_CORE_O=	lapi.o lstring.o 
AFL_LIB_O=	lauxlib.o lstrlib.o
#zl3

LUA_A=	liblua.a
#CORE_O=	lapi.o lcode.o lctype.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o \
	lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o \
	ltm.o lundump.o lvm.o lzio.o

#LIB_O=	lauxlib.o lbaselib.o lbitlib.o lcorolib.o ldblib.o liolib.o \
	lmathlib.o loslib.o lstrlib.o ltablib.o lutf8lib.o loadlib.o linit.o lcretelib.o
	
#zl3
CORE_O=lcode.o lctype.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o \
	lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o \
	ltm.o lundump.o lvm.o lzio.o

LIB_O=	lbaselib.o lbitlib.o lcorolib.o ldblib.o liolib.o \
	lmathlib.o loslib.o ltablib.o lutf8lib.o loadlib.o linit.o lcretelib.o
#zl3
	
#BASE_O= $(CORE_O) $(LIB_O) $(MYOBJS)
BASE_O= $(CORE_O) $(LIB_O) $(MYOBJS) $(AFL_CORE_O) $(AFL_LIB_O)

LUA_T=	lua
LUA_O=	lua.o

LUAC_T=	luac
LUAC_O=	luac.o

ALL_O= $(BASE_O) $(LUA_O) $(LUAC_O)
ALL_T= $(LUA_A) $(LUA_T) $(LUAC_T)
ALL_A= $(LUA_A)

# Targets start here.
default: $(PLAT)

all:	$(ALL_T)

o:	$(ALL_O)

a:	$(ALL_A)

$(LUA_A): $(BASE_O)
	$(AR) $@ $(BASE_O)
	$(RANLIB) $@

$(LUA_T): $(LUA_O) $(LUA_A)
	$(CC) -o $@ $(LDFLAGS) $(LUA_O) $(LUA_A) $(LIBS)

$(LUAC_T): $(LUAC_O) $(LUA_A)
	$(CC) -o $@ $(LDFLAGS) $(LUAC_O) $(LUA_A) $(LIBS)

clean:
	$(RM) $(ALL_T) $(ALL_O)

depend:
	#$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -MM l*.c -MM
	#$(AFL_CC) $(CFLAGS) $(INCLUDES) $(LIBS)
	#@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -MM l*.c -MM

echo:
	@echo "PLAT= $(PLAT)"
	@echo "CC= $(CC)"
	@echo "CFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(SYSLDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "AR= $(AR)"
	@echo "RANLIB= $(RANLIB)"
	@echo "RM= $(RM)"

# Convenience targets for popular platforms
ALL= all

none:
	@echo "Please do 'make PLATFORM' where PLATFORM is one of these:"
	@echo "liblua platform is   $(PLATS)"

aix:
	$(MAKE) $(ALL) CC="xlc" CFLAGS="-O2 -DLUA_USE_POSIX -DLUA_USE_DLOPEN" SYSLIBS="-ldl" SYSLDFLAGS="-brtl -bexpall"

bsd:
	$(MAKE) $(ALL) SYSCFLAGS="-DLUA_USE_POSIX -DLUA_USE_DLOPEN" SYSLIBS="-Wl,-E"

c89:
	$(MAKE) $(ALL) SYSCFLAGS="-DLUA_USE_C89" CC="gcc -std=c89"
	@echo ''
	@echo '*** C89 does not guarantee 64-bit integers for Lua.'
	@echo ''


freebsd:
	$(MAKE) $(ALL) SYSCFLAGS="-DLUA_USE_LINUX" SYSLIBS="-Wl,-E -lreadline"

generic: $(ALL)
#zl3 adding debug info
linux:
	$(MAKE) $(ALL) MYCFLAGS="-g -O0" $(CFLAGS) SYSCFLAGS="-DLUA_USE_LINUX" SYSLIBS="-Wl,-E -lreadline -ldl" 

macosx:
	$(MAKE) $(ALL) SYSCFLAGS="-DLUA_USE_MACOSX" SYSLIBS="-lreadline" CC=cc

mingw:
	$(MAKE) "LUA_A=lua53.dll" "LUA_T=lua.exe" \
	"AR=$(CC) -shared -o" "RANLIB=strip --strip-unneeded" \
	"SYSCFLAGS=-DLUA_BUILD_AS_DLL" "SYSLIBS=" "SYSLDFLAGS=-s" lua.exe
	$(MAKE) "LUAC_T=luac.exe" luac.exe

posix:
	$(MAKE) $(ALL) SYSCFLAGS="-DLUA_USE_POSIX"

solaris:
	$(MAKE) $(ALL) SYSCFLAGS="-DLUA_USE_POSIX -DLUA_USE_DLOPEN -D_REENTRANT" SYSLIBS="-ldl"

# list targets that do not create files (but not all makes understand .PHONY)
.PHONY: all $(PLATS) default o a clean depend echo none

# DO NOT DELETE

lapi.o: lapi.c lprefix.h lua.h luaconf.h lapi.h llimits.h lstate.h \
 lobject.h ltm.h lzio.h lmem.h ldebug.h ldo.h lfunc.h lgc.h lstring.h \
 ltable.h lundump.h lvm.h
	$(AFL_CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lapi.c -o lapi.o
lauxlib.o: lauxlib.c lprefix.h lua.h luaconf.h lauxlib.h
	$(AFL_CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lauxlib.c -o lauxlib.o
lbaselib.o: lbaselib.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lbaselib.c -o lbaselib.o
lbitlib.o: lbitlib.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lbitlib.c -o lbitlib.o
lcode.o: lcode.c lprefix.h lua.h luaconf.h lcode.h llex.h lobject.h \
 llimits.h lzio.h lmem.h lopcodes.h lparser.h ldebug.h lstate.h ltm.h \
 ldo.h lgc.h lstring.h ltable.h lvm.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lcode.c -o lcode.o
lcorolib.o: lcorolib.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lcorolib.c -o lcorolib.o
lctype.o: lctype.c lprefix.h lctype.h lua.h luaconf.h llimits.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lctype.c -o lctype.o
ldblib.o: ldblib.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c ldblib.c -o ldblib.o
ldebug.o: ldebug.c lprefix.h lua.h luaconf.h lapi.h llimits.h lstate.h \
 lobject.h ltm.h lzio.h lmem.h lcode.h llex.h lopcodes.h lparser.h \
 ldebug.h ldo.h lfunc.h lstring.h lgc.h ltable.h lvm.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c ldebug.c -o ldebug.o
	
ldo.o: ldo.c lprefix.h lua.h luaconf.h lapi.h llimits.h lstate.h \
 lobject.h ltm.h lzio.h lmem.h ldebug.h ldo.h lfunc.h lgc.h lopcodes.h \
 lparser.h lstring.h ltable.h lundump.h lvm.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c ldo.c -o ldo.o
ldump.o: ldump.c lprefix.h lua.h luaconf.h lobject.h llimits.h lstate.h \
 ltm.h lzio.h lmem.h lundump.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c ldump.c -o ldump.o
lfunc.o: lfunc.c lprefix.h lua.h luaconf.h lfunc.h lobject.h llimits.h \
 lgc.h lstate.h ltm.h lzio.h lmem.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lfunc.c -o lfunc.o
lgc.o: lgc.c lprefix.h lua.h luaconf.h ldebug.h lstate.h lobject.h \
 llimits.h ltm.h lzio.h lmem.h ldo.h lfunc.h lgc.h lstring.h ltable.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lgc.c -o lgc.o
linit.o: linit.c lprefix.h lua.h luaconf.h lualib.h lauxlib.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c linit.c -o linit.o
liolib.o: liolib.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c liolib.c -o liolib.o
llex.o: llex.c lprefix.h lua.h luaconf.h lctype.h llimits.h ldebug.h \
 lstate.h lobject.h ltm.h lzio.h lmem.h ldo.h lgc.h llex.h lparser.h \
 lstring.h ltable.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c llex.c -o llex.o
lmathlib.o: lmathlib.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lmathlib.c -o lmathlib.o
lmem.o: lmem.c lprefix.h lua.h luaconf.h ldebug.h lstate.h lobject.h \
 llimits.h ltm.h lzio.h lmem.h ldo.h lgc.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lmem.c -o lmem.o
loadlib.o: loadlib.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c loadlib.c -o loadlib.o
lobject.o: lobject.c lprefix.h lua.h luaconf.h lctype.h llimits.h \
 ldebug.h lstate.h lobject.h ltm.h lzio.h lmem.h ldo.h lstring.h lgc.h \
 lvm.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lobject.c -o lobject.o
lopcodes.o: lopcodes.c lprefix.h lopcodes.h llimits.h lua.h luaconf.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lopcodes.c -o lopcodes.o
loslib.o: loslib.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c loslib.c -o loslib.o
lparser.o: lparser.c lprefix.h lua.h luaconf.h lcode.h llex.h lobject.h \
 llimits.h lzio.h lmem.h lopcodes.h lparser.h ldebug.h lstate.h ltm.h \
 ldo.h lfunc.h lstring.h lgc.h ltable.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lparser.c -o lparser.o
lstate.o: lstate.c lprefix.h lua.h luaconf.h lapi.h llimits.h lstate.h \
 lobject.h ltm.h lzio.h lmem.h ldebug.h ldo.h lfunc.h lgc.h llex.h \
 lstring.h ltable.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lstate.c -o lstate.o 
lstring.o: lstring.c lprefix.h lua.h luaconf.h ldebug.h lstate.h \
 lobject.h llimits.h ltm.h lzio.h lmem.h ldo.h lstring.h lgc.h
	$(AFL_CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lstring.c -o lstring.o 
lstrlib.o: lstrlib.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	$(AFL_CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lstrlib.c -o lstrlib.o
ltable.o: ltable.c lprefix.h lua.h luaconf.h ldebug.h lstate.h lobject.h \
 llimits.h ltm.h lzio.h lmem.h ldo.h lgc.h lstring.h ltable.h lvm.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c ltable.c -o ltable.o
ltablib.o: ltablib.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c ltablib.c -o ltablib.o
ltm.o: ltm.c lprefix.h lua.h luaconf.h ldebug.h lstate.h lobject.h \
 llimits.h ltm.h lzio.h lmem.h ldo.h lstring.h lgc.h ltable.h lvm.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c ltm.c -o ltm.o
lua.o: lua.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lua.c -o lua.o
luac.o: luac.c lprefix.h lua.h luaconf.h lauxlib.h lobject.h llimits.h \
 lstate.h ltm.h lzio.h lmem.h lundump.h ldebug.h lopcodes.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c luac.c -o luac.o
lundump.o: lundump.c lprefix.h lua.h luaconf.h ldebug.h lstate.h \
 lobject.h llimits.h ltm.h lzio.h lmem.h ldo.h lfunc.h lstring.h lgc.h \
 lundump.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lundump.c -o lundump.o
lutf8lib.o: lutf8lib.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lutf8lib.c -o lutf8lib.o
lvm.o: lvm.c lprefix.h lua.h luaconf.h ldebug.h lstate.h lobject.h \
 llimits.h ltm.h lzio.h lmem.h ldo.h lfunc.h lgc.h lopcodes.h lstring.h \
 ltable.h lvm.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lvm.c -o lvm.o
lzio.o: lzio.c lprefix.h lua.h luaconf.h llimits.h lmem.h lstate.h \
 lobject.h ltm.h lzio.h
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lzio.c -o lzio.o
 
lcretelib.o: lcretelib.c lua.h lualib.h lauxlib.h
	$(AFL_CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c lcretelib.c -o lcretelib.o

# (end of Makefile)
