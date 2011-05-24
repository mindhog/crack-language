#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>

struct tm *crk_localtime(int64_t t){
   const time_t lt = (const time_t)t;
   return localtime(&lt);
}

struct tm *crk_localtime_now(struct tm *now){
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return localtime_r(&(tv.tv_sec), now);
   ;
}

struct tm *crk_gmtime_now(struct tm *now){
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return gmtime_r(&(tv.tv_sec), now);
}

struct tm *crk_epoch(void){
   return gmtime(NULL);
}

char *crk_ctime_r(int64_t t, char * buf){
   const time_t lt = (const time_t)t;
   return ctime_r(&lt, buf);
}


#include "ext/Module.h"
#include "ext/Type.h"
#include "ext/Func.h"

extern "C"
void crack_runtime_time_init(crack::ext::Module *mod) {
    crack::ext::Func *f;
    crack::ext::Type *type_Class = mod->getClassType();
    crack::ext::Type *type_void = mod->getVoidType();
    crack::ext::Type *type_voidptr = mod->getVoidptrType();
    crack::ext::Type *type_bool = mod->getBoolType();
    crack::ext::Type *type_byteptr = mod->getByteptrType();
    crack::ext::Type *type_byte = mod->getByteType();
    crack::ext::Type *type_int32 = mod->getInt32Type();
    crack::ext::Type *type_int64 = mod->getInt64Type();
    crack::ext::Type *type_uint32 = mod->getUint32Type();
    crack::ext::Type *type_uint64 = mod->getUint64Type();
    crack::ext::Type *type_int = mod->getIntType();
    crack::ext::Type *type_uint = mod->getUintType();
    crack::ext::Type *type_float32 = mod->getFloat32Type();
    crack::ext::Type *type_float64 = mod->getFloat64Type();
    crack::ext::Type *type_float = mod->getFloatType();

    crack::ext::Type *type__date = mod->addType("_date");
        type__date->addInstVar(type_int, "tm_sec");
        type__date->addInstVar(type_int, "tm_min");
        type__date->addInstVar(type_int, "tm_hour");
        type__date->addInstVar(type_int, "tm_mday");
        type__date->addInstVar(type_int, "tm_mon");
        type__date->addInstVar(type_int, "tm_year");
        type__date->addInstVar(type_int, "tm_wday");
        type__date->addInstVar(type_int, "tm_yday");
        type__date->addInstVar(type_int, "tm_isdst");
        type__date->addInstVar(type_int64, "tm_gmtoff");
        f = type__date->addConstructor("init",
                    (void *)crk_localtime
            );
            f->addArg(type_int64, "seconds");

        f = type__date->addConstructor("init",
                    (void *)crk_epoch
            );

        f = type__date->addMethod(type_int64, "mktime",
                    (void *)mktime
            );

        f = type__date->addMethod(type_bool, "setToNowLocal",
                    (void *)crk_localtime_now
            );

        f = type__date->addMethod(type_bool, "setToNowUTC",
                    (void *)crk_gmtime_now
            );

        f = type__date->addMethod(type_byteptr, "asctime_r",
                    (void *)asctime_r
            );
            f->addArg(type_byteptr, "buf");

    type__date->finish();

    f = mod->addFunc(type_byteptr, "ctime_r",
            (void *)crk_ctime_r
        );
       f->addArg(type_int64, "seconds");
       f->addArg(type_byteptr, "buf");

}
