// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME GoddessStructDictionary

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/media/mhall12/Zeus/Analysis/goddess_daq/goddess/include/GoddessStruct.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *GamData_Dictionary();
   static void GamData_TClassManip(TClass*);
   static void *new_GamData(void *p = 0);
   static void *newArray_GamData(Long_t size, void *p);
   static void delete_GamData(void *p);
   static void deleteArray_GamData(void *p);
   static void destruct_GamData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamData*)
   {
      ::GamData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamData));
      static ::ROOT::TGenericClassInfo 
         instance("GamData", "GoddessStruct.h", 7,
                  typeid(::GamData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamData_Dictionary, isa_proxy, 4,
                  sizeof(::GamData) );
      instance.SetNew(&new_GamData);
      instance.SetNewArray(&newArray_GamData);
      instance.SetDelete(&delete_GamData);
      instance.SetDeleteArray(&deleteArray_GamData);
      instance.SetDestructor(&destruct_GamData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamData*)
   {
      return GenerateInitInstanceLocal((::GamData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::GamData*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamData_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamData*)0x0)->GetClass();
      GamData_TClassManip(theClass);
   return theClass;
   }

   static void GamData_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *SiData_Dictionary();
   static void SiData_TClassManip(TClass*);
   static void *new_SiData(void *p = 0);
   static void *newArray_SiData(Long_t size, void *p);
   static void delete_SiData(void *p);
   static void deleteArray_SiData(void *p);
   static void destruct_SiData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SiData*)
   {
      ::SiData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::SiData));
      static ::ROOT::TGenericClassInfo 
         instance("SiData", "GoddessStruct.h", 19,
                  typeid(::SiData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &SiData_Dictionary, isa_proxy, 4,
                  sizeof(::SiData) );
      instance.SetNew(&new_SiData);
      instance.SetNewArray(&newArray_SiData);
      instance.SetDelete(&delete_SiData);
      instance.SetDeleteArray(&deleteArray_SiData);
      instance.SetDestructor(&destruct_SiData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SiData*)
   {
      return GenerateInitInstanceLocal((::SiData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::SiData*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *SiData_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::SiData*)0x0)->GetClass();
      SiData_TClassManip(theClass);
   return theClass;
   }

   static void SiData_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *IonData_Dictionary();
   static void IonData_TClassManip(TClass*);
   static void *new_IonData(void *p = 0);
   static void *newArray_IonData(Long_t size, void *p);
   static void delete_IonData(void *p);
   static void deleteArray_IonData(void *p);
   static void destruct_IonData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::IonData*)
   {
      ::IonData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::IonData));
      static ::ROOT::TGenericClassInfo 
         instance("IonData", "GoddessStruct.h", 53,
                  typeid(::IonData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &IonData_Dictionary, isa_proxy, 4,
                  sizeof(::IonData) );
      instance.SetNew(&new_IonData);
      instance.SetNewArray(&newArray_IonData);
      instance.SetDelete(&delete_IonData);
      instance.SetDeleteArray(&deleteArray_IonData);
      instance.SetDestructor(&destruct_IonData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::IonData*)
   {
      return GenerateInitInstanceLocal((::IonData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::IonData*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *IonData_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::IonData*)0x0)->GetClass();
      IonData_TClassManip(theClass);
   return theClass;
   }

   static void IonData_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamData(void *p) {
      return  p ? new(p) ::GamData : new ::GamData;
   }
   static void *newArray_GamData(Long_t nElements, void *p) {
      return p ? new(p) ::GamData[nElements] : new ::GamData[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamData(void *p) {
      delete ((::GamData*)p);
   }
   static void deleteArray_GamData(void *p) {
      delete [] ((::GamData*)p);
   }
   static void destruct_GamData(void *p) {
      typedef ::GamData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamData

namespace ROOT {
   // Wrappers around operator new
   static void *new_SiData(void *p) {
      return  p ? new(p) ::SiData : new ::SiData;
   }
   static void *newArray_SiData(Long_t nElements, void *p) {
      return p ? new(p) ::SiData[nElements] : new ::SiData[nElements];
   }
   // Wrapper around operator delete
   static void delete_SiData(void *p) {
      delete ((::SiData*)p);
   }
   static void deleteArray_SiData(void *p) {
      delete [] ((::SiData*)p);
   }
   static void destruct_SiData(void *p) {
      typedef ::SiData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::SiData

namespace ROOT {
   // Wrappers around operator new
   static void *new_IonData(void *p) {
      return  p ? new(p) ::IonData : new ::IonData;
   }
   static void *newArray_IonData(Long_t nElements, void *p) {
      return p ? new(p) ::IonData[nElements] : new ::IonData[nElements];
   }
   // Wrapper around operator delete
   static void delete_IonData(void *p) {
      delete ((::IonData*)p);
   }
   static void deleteArray_IonData(void *p) {
      delete [] ((::IonData*)p);
   }
   static void destruct_IonData(void *p) {
      typedef ::IonData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::IonData

namespace ROOT {
   static TClass *vectorlESiDatagR_Dictionary();
   static void vectorlESiDatagR_TClassManip(TClass*);
   static void *new_vectorlESiDatagR(void *p = 0);
   static void *newArray_vectorlESiDatagR(Long_t size, void *p);
   static void delete_vectorlESiDatagR(void *p);
   static void deleteArray_vectorlESiDatagR(void *p);
   static void destruct_vectorlESiDatagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<SiData>*)
   {
      vector<SiData> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<SiData>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<SiData>", -2, "vector", 210,
                  typeid(vector<SiData>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlESiDatagR_Dictionary, isa_proxy, 4,
                  sizeof(vector<SiData>) );
      instance.SetNew(&new_vectorlESiDatagR);
      instance.SetNewArray(&newArray_vectorlESiDatagR);
      instance.SetDelete(&delete_vectorlESiDatagR);
      instance.SetDeleteArray(&deleteArray_vectorlESiDatagR);
      instance.SetDestructor(&destruct_vectorlESiDatagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<SiData> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<SiData>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlESiDatagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<SiData>*)0x0)->GetClass();
      vectorlESiDatagR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlESiDatagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlESiDatagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<SiData> : new vector<SiData>;
   }
   static void *newArray_vectorlESiDatagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<SiData>[nElements] : new vector<SiData>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlESiDatagR(void *p) {
      delete ((vector<SiData>*)p);
   }
   static void deleteArray_vectorlESiDatagR(void *p) {
      delete [] ((vector<SiData>*)p);
   }
   static void destruct_vectorlESiDatagR(void *p) {
      typedef vector<SiData> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<SiData>

namespace ROOT {
   static TClass *vectorlEIonDatagR_Dictionary();
   static void vectorlEIonDatagR_TClassManip(TClass*);
   static void *new_vectorlEIonDatagR(void *p = 0);
   static void *newArray_vectorlEIonDatagR(Long_t size, void *p);
   static void delete_vectorlEIonDatagR(void *p);
   static void deleteArray_vectorlEIonDatagR(void *p);
   static void destruct_vectorlEIonDatagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<IonData>*)
   {
      vector<IonData> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<IonData>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<IonData>", -2, "vector", 210,
                  typeid(vector<IonData>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEIonDatagR_Dictionary, isa_proxy, 4,
                  sizeof(vector<IonData>) );
      instance.SetNew(&new_vectorlEIonDatagR);
      instance.SetNewArray(&newArray_vectorlEIonDatagR);
      instance.SetDelete(&delete_vectorlEIonDatagR);
      instance.SetDeleteArray(&deleteArray_vectorlEIonDatagR);
      instance.SetDestructor(&destruct_vectorlEIonDatagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<IonData> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<IonData>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEIonDatagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<IonData>*)0x0)->GetClass();
      vectorlEIonDatagR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEIonDatagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEIonDatagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<IonData> : new vector<IonData>;
   }
   static void *newArray_vectorlEIonDatagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<IonData>[nElements] : new vector<IonData>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEIonDatagR(void *p) {
      delete ((vector<IonData>*)p);
   }
   static void deleteArray_vectorlEIonDatagR(void *p) {
      delete [] ((vector<IonData>*)p);
   }
   static void destruct_vectorlEIonDatagR(void *p) {
      typedef vector<IonData> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<IonData>

namespace ROOT {
   static TClass *vectorlEGamDatagR_Dictionary();
   static void vectorlEGamDatagR_TClassManip(TClass*);
   static void *new_vectorlEGamDatagR(void *p = 0);
   static void *newArray_vectorlEGamDatagR(Long_t size, void *p);
   static void delete_vectorlEGamDatagR(void *p);
   static void deleteArray_vectorlEGamDatagR(void *p);
   static void destruct_vectorlEGamDatagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GamData>*)
   {
      vector<GamData> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GamData>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GamData>", -2, "vector", 210,
                  typeid(vector<GamData>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGamDatagR_Dictionary, isa_proxy, 4,
                  sizeof(vector<GamData>) );
      instance.SetNew(&new_vectorlEGamDatagR);
      instance.SetNewArray(&newArray_vectorlEGamDatagR);
      instance.SetDelete(&delete_vectorlEGamDatagR);
      instance.SetDeleteArray(&deleteArray_vectorlEGamDatagR);
      instance.SetDestructor(&destruct_vectorlEGamDatagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GamData> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<GamData>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGamDatagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GamData>*)0x0)->GetClass();
      vectorlEGamDatagR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGamDatagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGamDatagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GamData> : new vector<GamData>;
   }
   static void *newArray_vectorlEGamDatagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GamData>[nElements] : new vector<GamData>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGamDatagR(void *p) {
      delete ((vector<GamData>*)p);
   }
   static void deleteArray_vectorlEGamDatagR(void *p) {
      delete [] ((vector<GamData>*)p);
   }
   static void destruct_vectorlEGamDatagR(void *p) {
      typedef vector<GamData> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GamData>

namespace {
  void TriggerDictionaryInitialization_GoddessStructDictionary_Impl() {
    static const char* headers[] = {
"/media/mhall12/Zeus/Analysis/goddess_daq/goddess/include/GoddessStruct.h",
0
    };
    static const char* includePaths[] = {
"/home/mhall12/root/include",
"/media/mhall12/Zeus/Analysis/goddess_daq/include",
"/media/mhall12/Zeus/Analysis/goddess_daq/goddess/include",
"/home/mhall12/root/include",
"/media/mhall12/Zeus/Analysis/goddess_daq/build/goddess/source/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "GoddessStructDictionary dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
struct __attribute__((annotate("$clingAutoload$/media/mhall12/Zeus/Analysis/goddess_daq/goddess/include/GoddessStruct.h")))  GamData;
struct __attribute__((annotate("$clingAutoload$/media/mhall12/Zeus/Analysis/goddess_daq/goddess/include/GoddessStruct.h")))  SiData;
struct __attribute__((annotate("$clingAutoload$/media/mhall12/Zeus/Analysis/goddess_daq/goddess/include/GoddessStruct.h")))  IonData;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$string")))  allocator;
}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "GoddessStructDictionary dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/media/mhall12/Zeus/Analysis/goddess_daq/goddess/include/GoddessStruct.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"GamData", payloadCode, "@",
"IonData", payloadCode, "@",
"SiData", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("GoddessStructDictionary",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_GoddessStructDictionary_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_GoddessStructDictionary_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_GoddessStructDictionary() {
  TriggerDictionaryInitialization_GoddessStructDictionary_Impl();
}
