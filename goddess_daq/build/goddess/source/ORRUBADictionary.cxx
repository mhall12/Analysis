// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME ORRUBADictionary

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
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/ORRUBA.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/Detector.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/siDet.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/orrubaDet.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/superX3.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/BB10.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/QQQ5.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/IonChamber.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/LiquidScint.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_Detector(void *p);
   static void deleteArray_Detector(void *p);
   static void destruct_Detector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Detector*)
   {
      ::Detector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Detector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Detector", ::Detector::Class_Version(), "Detector.h", 7,
                  typeid(::Detector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Detector::Dictionary, isa_proxy, 4,
                  sizeof(::Detector) );
      instance.SetDelete(&delete_Detector);
      instance.SetDeleteArray(&deleteArray_Detector);
      instance.SetDestructor(&destruct_Detector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Detector*)
   {
      return GenerateInitInstanceLocal((::Detector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Detector*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_siDet(void *p = 0);
   static void *newArray_siDet(Long_t size, void *p);
   static void delete_siDet(void *p);
   static void deleteArray_siDet(void *p);
   static void destruct_siDet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::siDet*)
   {
      ::siDet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::siDet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("siDet", ::siDet::Class_Version(), "siDet.h", 12,
                  typeid(::siDet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::siDet::Dictionary, isa_proxy, 4,
                  sizeof(::siDet) );
      instance.SetNew(&new_siDet);
      instance.SetNewArray(&newArray_siDet);
      instance.SetDelete(&delete_siDet);
      instance.SetDeleteArray(&deleteArray_siDet);
      instance.SetDestructor(&destruct_siDet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::siDet*)
   {
      return GenerateInitInstanceLocal((::siDet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::siDet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_orrubaDet(void *p);
   static void deleteArray_orrubaDet(void *p);
   static void destruct_orrubaDet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::orrubaDet*)
   {
      ::orrubaDet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::orrubaDet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("orrubaDet", ::orrubaDet::Class_Version(), "orrubaDet.h", 14,
                  typeid(::orrubaDet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::orrubaDet::Dictionary, isa_proxy, 4,
                  sizeof(::orrubaDet) );
      instance.SetDelete(&delete_orrubaDet);
      instance.SetDeleteArray(&deleteArray_orrubaDet);
      instance.SetDestructor(&destruct_orrubaDet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::orrubaDet*)
   {
      return GenerateInitInstanceLocal((::orrubaDet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::orrubaDet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_superX3(void *p = 0);
   static void *newArray_superX3(Long_t size, void *p);
   static void delete_superX3(void *p);
   static void deleteArray_superX3(void *p);
   static void destruct_superX3(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::superX3*)
   {
      ::superX3 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::superX3 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("superX3", ::superX3::Class_Version(), "superX3.h", 16,
                  typeid(::superX3), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::superX3::Dictionary, isa_proxy, 4,
                  sizeof(::superX3) );
      instance.SetNew(&new_superX3);
      instance.SetNewArray(&newArray_superX3);
      instance.SetDelete(&delete_superX3);
      instance.SetDeleteArray(&deleteArray_superX3);
      instance.SetDestructor(&destruct_superX3);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::superX3*)
   {
      return GenerateInitInstanceLocal((::superX3*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::superX3*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_BB10(void *p = 0);
   static void *newArray_BB10(Long_t size, void *p);
   static void delete_BB10(void *p);
   static void deleteArray_BB10(void *p);
   static void destruct_BB10(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BB10*)
   {
      ::BB10 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::BB10 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("BB10", ::BB10::Class_Version(), "BB10.h", 14,
                  typeid(::BB10), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::BB10::Dictionary, isa_proxy, 4,
                  sizeof(::BB10) );
      instance.SetNew(&new_BB10);
      instance.SetNewArray(&newArray_BB10);
      instance.SetDelete(&delete_BB10);
      instance.SetDeleteArray(&deleteArray_BB10);
      instance.SetDestructor(&destruct_BB10);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BB10*)
   {
      return GenerateInitInstanceLocal((::BB10*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::BB10*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_QQQ5(void *p = 0);
   static void *newArray_QQQ5(Long_t size, void *p);
   static void delete_QQQ5(void *p);
   static void deleteArray_QQQ5(void *p);
   static void destruct_QQQ5(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::QQQ5*)
   {
      ::QQQ5 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::QQQ5 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("QQQ5", ::QQQ5::Class_Version(), "QQQ5.h", 13,
                  typeid(::QQQ5), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::QQQ5::Dictionary, isa_proxy, 4,
                  sizeof(::QQQ5) );
      instance.SetNew(&new_QQQ5);
      instance.SetNewArray(&newArray_QQQ5);
      instance.SetDelete(&delete_QQQ5);
      instance.SetDeleteArray(&deleteArray_QQQ5);
      instance.SetDestructor(&destruct_QQQ5);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::QQQ5*)
   {
      return GenerateInitInstanceLocal((::QQQ5*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::QQQ5*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_IonChamber(void *p);
   static void deleteArray_IonChamber(void *p);
   static void destruct_IonChamber(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::IonChamber*)
   {
      ::IonChamber *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::IonChamber >(0);
      static ::ROOT::TGenericClassInfo 
         instance("IonChamber", ::IonChamber::Class_Version(), "IonChamber.h", 7,
                  typeid(::IonChamber), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::IonChamber::Dictionary, isa_proxy, 4,
                  sizeof(::IonChamber) );
      instance.SetDelete(&delete_IonChamber);
      instance.SetDeleteArray(&deleteArray_IonChamber);
      instance.SetDestructor(&destruct_IonChamber);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::IonChamber*)
   {
      return GenerateInitInstanceLocal((::IonChamber*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::IonChamber*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LiquidScint(void *p = 0);
   static void *newArray_LiquidScint(Long_t size, void *p);
   static void delete_LiquidScint(void *p);
   static void deleteArray_LiquidScint(void *p);
   static void destruct_LiquidScint(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LiquidScint*)
   {
      ::LiquidScint *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LiquidScint >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LiquidScint", ::LiquidScint::Class_Version(), "LiquidScint.h", 6,
                  typeid(::LiquidScint), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LiquidScint::Dictionary, isa_proxy, 4,
                  sizeof(::LiquidScint) );
      instance.SetNew(&new_LiquidScint);
      instance.SetNewArray(&newArray_LiquidScint);
      instance.SetDelete(&delete_LiquidScint);
      instance.SetDeleteArray(&deleteArray_LiquidScint);
      instance.SetDestructor(&destruct_LiquidScint);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LiquidScint*)
   {
      return GenerateInitInstanceLocal((::LiquidScint*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::LiquidScint*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_ORRUBA(void *p = 0);
   static void *newArray_ORRUBA(Long_t size, void *p);
   static void delete_ORRUBA(void *p);
   static void deleteArray_ORRUBA(void *p);
   static void destruct_ORRUBA(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ORRUBA*)
   {
      ::ORRUBA *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ORRUBA >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ORRUBA", ::ORRUBA::Class_Version(), "ORRUBA.h", 7,
                  typeid(::ORRUBA), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ORRUBA::Dictionary, isa_proxy, 4,
                  sizeof(::ORRUBA) );
      instance.SetNew(&new_ORRUBA);
      instance.SetNewArray(&newArray_ORRUBA);
      instance.SetDelete(&delete_ORRUBA);
      instance.SetDeleteArray(&deleteArray_ORRUBA);
      instance.SetDestructor(&destruct_ORRUBA);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ORRUBA*)
   {
      return GenerateInitInstanceLocal((::ORRUBA*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::ORRUBA*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Detector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Detector::Class_Name()
{
   return "Detector";
}

//______________________________________________________________________________
const char *Detector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Detector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Detector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Detector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Detector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Detector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Detector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Detector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr siDet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *siDet::Class_Name()
{
   return "siDet";
}

//______________________________________________________________________________
const char *siDet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::siDet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int siDet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::siDet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *siDet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::siDet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *siDet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::siDet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr orrubaDet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *orrubaDet::Class_Name()
{
   return "orrubaDet";
}

//______________________________________________________________________________
const char *orrubaDet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::orrubaDet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int orrubaDet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::orrubaDet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *orrubaDet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::orrubaDet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *orrubaDet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::orrubaDet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr superX3::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *superX3::Class_Name()
{
   return "superX3";
}

//______________________________________________________________________________
const char *superX3::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::superX3*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int superX3::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::superX3*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *superX3::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::superX3*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *superX3::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::superX3*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr BB10::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *BB10::Class_Name()
{
   return "BB10";
}

//______________________________________________________________________________
const char *BB10::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BB10*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int BB10::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BB10*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BB10::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BB10*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BB10::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BB10*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr QQQ5::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *QQQ5::Class_Name()
{
   return "QQQ5";
}

//______________________________________________________________________________
const char *QQQ5::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::QQQ5*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int QQQ5::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::QQQ5*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *QQQ5::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::QQQ5*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *QQQ5::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::QQQ5*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr IonChamber::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *IonChamber::Class_Name()
{
   return "IonChamber";
}

//______________________________________________________________________________
const char *IonChamber::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::IonChamber*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int IonChamber::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::IonChamber*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *IonChamber::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::IonChamber*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *IonChamber::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::IonChamber*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LiquidScint::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LiquidScint::Class_Name()
{
   return "LiquidScint";
}

//______________________________________________________________________________
const char *LiquidScint::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiquidScint*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LiquidScint::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiquidScint*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LiquidScint::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiquidScint*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LiquidScint::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiquidScint*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr ORRUBA::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ORRUBA::Class_Name()
{
   return "ORRUBA";
}

//______________________________________________________________________________
const char *ORRUBA::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ORRUBA*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ORRUBA::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ORRUBA*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ORRUBA::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ORRUBA*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ORRUBA::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ORRUBA*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Detector::Streamer(TBuffer &R__b)
{
   // Stream an object of class Detector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Detector::Class(),this);
   } else {
      R__b.WriteClassBuffer(Detector::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Detector(void *p) {
      delete ((::Detector*)p);
   }
   static void deleteArray_Detector(void *p) {
      delete [] ((::Detector*)p);
   }
   static void destruct_Detector(void *p) {
      typedef ::Detector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Detector

//______________________________________________________________________________
void siDet::Streamer(TBuffer &R__b)
{
   // Stream an object of class siDet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(siDet::Class(),this);
   } else {
      R__b.WriteClassBuffer(siDet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_siDet(void *p) {
      return  p ? new(p) ::siDet : new ::siDet;
   }
   static void *newArray_siDet(Long_t nElements, void *p) {
      return p ? new(p) ::siDet[nElements] : new ::siDet[nElements];
   }
   // Wrapper around operator delete
   static void delete_siDet(void *p) {
      delete ((::siDet*)p);
   }
   static void deleteArray_siDet(void *p) {
      delete [] ((::siDet*)p);
   }
   static void destruct_siDet(void *p) {
      typedef ::siDet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::siDet

//______________________________________________________________________________
void orrubaDet::Streamer(TBuffer &R__b)
{
   // Stream an object of class orrubaDet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(orrubaDet::Class(),this);
   } else {
      R__b.WriteClassBuffer(orrubaDet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_orrubaDet(void *p) {
      delete ((::orrubaDet*)p);
   }
   static void deleteArray_orrubaDet(void *p) {
      delete [] ((::orrubaDet*)p);
   }
   static void destruct_orrubaDet(void *p) {
      typedef ::orrubaDet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::orrubaDet

//______________________________________________________________________________
void superX3::Streamer(TBuffer &R__b)
{
   // Stream an object of class superX3.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(superX3::Class(),this);
   } else {
      R__b.WriteClassBuffer(superX3::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_superX3(void *p) {
      return  p ? new(p) ::superX3 : new ::superX3;
   }
   static void *newArray_superX3(Long_t nElements, void *p) {
      return p ? new(p) ::superX3[nElements] : new ::superX3[nElements];
   }
   // Wrapper around operator delete
   static void delete_superX3(void *p) {
      delete ((::superX3*)p);
   }
   static void deleteArray_superX3(void *p) {
      delete [] ((::superX3*)p);
   }
   static void destruct_superX3(void *p) {
      typedef ::superX3 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::superX3

//______________________________________________________________________________
void BB10::Streamer(TBuffer &R__b)
{
   // Stream an object of class BB10.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(BB10::Class(),this);
   } else {
      R__b.WriteClassBuffer(BB10::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_BB10(void *p) {
      return  p ? new(p) ::BB10 : new ::BB10;
   }
   static void *newArray_BB10(Long_t nElements, void *p) {
      return p ? new(p) ::BB10[nElements] : new ::BB10[nElements];
   }
   // Wrapper around operator delete
   static void delete_BB10(void *p) {
      delete ((::BB10*)p);
   }
   static void deleteArray_BB10(void *p) {
      delete [] ((::BB10*)p);
   }
   static void destruct_BB10(void *p) {
      typedef ::BB10 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::BB10

//______________________________________________________________________________
void QQQ5::Streamer(TBuffer &R__b)
{
   // Stream an object of class QQQ5.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(QQQ5::Class(),this);
   } else {
      R__b.WriteClassBuffer(QQQ5::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_QQQ5(void *p) {
      return  p ? new(p) ::QQQ5 : new ::QQQ5;
   }
   static void *newArray_QQQ5(Long_t nElements, void *p) {
      return p ? new(p) ::QQQ5[nElements] : new ::QQQ5[nElements];
   }
   // Wrapper around operator delete
   static void delete_QQQ5(void *p) {
      delete ((::QQQ5*)p);
   }
   static void deleteArray_QQQ5(void *p) {
      delete [] ((::QQQ5*)p);
   }
   static void destruct_QQQ5(void *p) {
      typedef ::QQQ5 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::QQQ5

//______________________________________________________________________________
void IonChamber::Streamer(TBuffer &R__b)
{
   // Stream an object of class IonChamber.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(IonChamber::Class(),this);
   } else {
      R__b.WriteClassBuffer(IonChamber::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_IonChamber(void *p) {
      delete ((::IonChamber*)p);
   }
   static void deleteArray_IonChamber(void *p) {
      delete [] ((::IonChamber*)p);
   }
   static void destruct_IonChamber(void *p) {
      typedef ::IonChamber current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::IonChamber

//______________________________________________________________________________
void LiquidScint::Streamer(TBuffer &R__b)
{
   // Stream an object of class LiquidScint.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LiquidScint::Class(),this);
   } else {
      R__b.WriteClassBuffer(LiquidScint::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LiquidScint(void *p) {
      return  p ? new(p) ::LiquidScint : new ::LiquidScint;
   }
   static void *newArray_LiquidScint(Long_t nElements, void *p) {
      return p ? new(p) ::LiquidScint[nElements] : new ::LiquidScint[nElements];
   }
   // Wrapper around operator delete
   static void delete_LiquidScint(void *p) {
      delete ((::LiquidScint*)p);
   }
   static void deleteArray_LiquidScint(void *p) {
      delete [] ((::LiquidScint*)p);
   }
   static void destruct_LiquidScint(void *p) {
      typedef ::LiquidScint current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LiquidScint

//______________________________________________________________________________
void ORRUBA::Streamer(TBuffer &R__b)
{
   // Stream an object of class ORRUBA.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(ORRUBA::Class(),this);
   } else {
      R__b.WriteClassBuffer(ORRUBA::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ORRUBA(void *p) {
      return  p ? new(p) ::ORRUBA : new ::ORRUBA;
   }
   static void *newArray_ORRUBA(Long_t nElements, void *p) {
      return p ? new(p) ::ORRUBA[nElements] : new ::ORRUBA[nElements];
   }
   // Wrapper around operator delete
   static void delete_ORRUBA(void *p) {
      delete ((::ORRUBA*)p);
   }
   static void deleteArray_ORRUBA(void *p) {
      delete [] ((::ORRUBA*)p);
   }
   static void destruct_ORRUBA(void *p) {
      typedef ::ORRUBA current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ORRUBA

namespace ROOT {
   static TClass *vectorlEorrubaDetmUgR_Dictionary();
   static void vectorlEorrubaDetmUgR_TClassManip(TClass*);
   static void *new_vectorlEorrubaDetmUgR(void *p = 0);
   static void *newArray_vectorlEorrubaDetmUgR(Long_t size, void *p);
   static void delete_vectorlEorrubaDetmUgR(void *p);
   static void deleteArray_vectorlEorrubaDetmUgR(void *p);
   static void destruct_vectorlEorrubaDetmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<orrubaDet*>*)
   {
      vector<orrubaDet*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<orrubaDet*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<orrubaDet*>", -2, "vector", 210,
                  typeid(vector<orrubaDet*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEorrubaDetmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<orrubaDet*>) );
      instance.SetNew(&new_vectorlEorrubaDetmUgR);
      instance.SetNewArray(&newArray_vectorlEorrubaDetmUgR);
      instance.SetDelete(&delete_vectorlEorrubaDetmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEorrubaDetmUgR);
      instance.SetDestructor(&destruct_vectorlEorrubaDetmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<orrubaDet*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<orrubaDet*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEorrubaDetmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<orrubaDet*>*)0x0)->GetClass();
      vectorlEorrubaDetmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEorrubaDetmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEorrubaDetmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<orrubaDet*> : new vector<orrubaDet*>;
   }
   static void *newArray_vectorlEorrubaDetmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<orrubaDet*>[nElements] : new vector<orrubaDet*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEorrubaDetmUgR(void *p) {
      delete ((vector<orrubaDet*>*)p);
   }
   static void deleteArray_vectorlEorrubaDetmUgR(void *p) {
      delete [] ((vector<orrubaDet*>*)p);
   }
   static void destruct_vectorlEorrubaDetmUgR(void *p) {
      typedef vector<orrubaDet*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<orrubaDet*>

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 210,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = 0);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 210,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<float>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)0x0)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEDetectormUgR_Dictionary();
   static void vectorlEDetectormUgR_TClassManip(TClass*);
   static void *new_vectorlEDetectormUgR(void *p = 0);
   static void *newArray_vectorlEDetectormUgR(Long_t size, void *p);
   static void delete_vectorlEDetectormUgR(void *p);
   static void deleteArray_vectorlEDetectormUgR(void *p);
   static void destruct_vectorlEDetectormUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Detector*>*)
   {
      vector<Detector*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Detector*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Detector*>", -2, "vector", 210,
                  typeid(vector<Detector*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEDetectormUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<Detector*>) );
      instance.SetNew(&new_vectorlEDetectormUgR);
      instance.SetNewArray(&newArray_vectorlEDetectormUgR);
      instance.SetDelete(&delete_vectorlEDetectormUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEDetectormUgR);
      instance.SetDestructor(&destruct_vectorlEDetectormUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Detector*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Detector*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEDetectormUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Detector*>*)0x0)->GetClass();
      vectorlEDetectormUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEDetectormUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEDetectormUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Detector*> : new vector<Detector*>;
   }
   static void *newArray_vectorlEDetectormUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Detector*>[nElements] : new vector<Detector*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEDetectormUgR(void *p) {
      delete ((vector<Detector*>*)p);
   }
   static void deleteArray_vectorlEDetectormUgR(void *p) {
      delete [] ((vector<Detector*>*)p);
   }
   static void destruct_vectorlEDetectormUgR(void *p) {
      typedef vector<Detector*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Detector*>

namespace ROOT {
   static TClass *maplEshortcOfloatgR_Dictionary();
   static void maplEshortcOfloatgR_TClassManip(TClass*);
   static void *new_maplEshortcOfloatgR(void *p = 0);
   static void *newArray_maplEshortcOfloatgR(Long_t size, void *p);
   static void delete_maplEshortcOfloatgR(void *p);
   static void deleteArray_maplEshortcOfloatgR(void *p);
   static void destruct_maplEshortcOfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<short,float>*)
   {
      map<short,float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<short,float>));
      static ::ROOT::TGenericClassInfo 
         instance("map<short,float>", -2, "map", 96,
                  typeid(map<short,float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEshortcOfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(map<short,float>) );
      instance.SetNew(&new_maplEshortcOfloatgR);
      instance.SetNewArray(&newArray_maplEshortcOfloatgR);
      instance.SetDelete(&delete_maplEshortcOfloatgR);
      instance.SetDeleteArray(&deleteArray_maplEshortcOfloatgR);
      instance.SetDestructor(&destruct_maplEshortcOfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<short,float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<short,float>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEshortcOfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<short,float>*)0x0)->GetClass();
      maplEshortcOfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEshortcOfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEshortcOfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<short,float> : new map<short,float>;
   }
   static void *newArray_maplEshortcOfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<short,float>[nElements] : new map<short,float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEshortcOfloatgR(void *p) {
      delete ((map<short,float>*)p);
   }
   static void deleteArray_maplEshortcOfloatgR(void *p) {
      delete [] ((map<short,float>*)p);
   }
   static void destruct_maplEshortcOfloatgR(void *p) {
      typedef map<short,float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<short,float>

namespace ROOT {
   static TClass *maplEshortcOULong64_tgR_Dictionary();
   static void maplEshortcOULong64_tgR_TClassManip(TClass*);
   static void *new_maplEshortcOULong64_tgR(void *p = 0);
   static void *newArray_maplEshortcOULong64_tgR(Long_t size, void *p);
   static void delete_maplEshortcOULong64_tgR(void *p);
   static void deleteArray_maplEshortcOULong64_tgR(void *p);
   static void destruct_maplEshortcOULong64_tgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<short,ULong64_t>*)
   {
      map<short,ULong64_t> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<short,ULong64_t>));
      static ::ROOT::TGenericClassInfo 
         instance("map<short,ULong64_t>", -2, "map", 96,
                  typeid(map<short,ULong64_t>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEshortcOULong64_tgR_Dictionary, isa_proxy, 0,
                  sizeof(map<short,ULong64_t>) );
      instance.SetNew(&new_maplEshortcOULong64_tgR);
      instance.SetNewArray(&newArray_maplEshortcOULong64_tgR);
      instance.SetDelete(&delete_maplEshortcOULong64_tgR);
      instance.SetDeleteArray(&deleteArray_maplEshortcOULong64_tgR);
      instance.SetDestructor(&destruct_maplEshortcOULong64_tgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<short,ULong64_t> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<short,ULong64_t>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEshortcOULong64_tgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<short,ULong64_t>*)0x0)->GetClass();
      maplEshortcOULong64_tgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEshortcOULong64_tgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEshortcOULong64_tgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<short,ULong64_t> : new map<short,ULong64_t>;
   }
   static void *newArray_maplEshortcOULong64_tgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<short,ULong64_t>[nElements] : new map<short,ULong64_t>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEshortcOULong64_tgR(void *p) {
      delete ((map<short,ULong64_t>*)p);
   }
   static void deleteArray_maplEshortcOULong64_tgR(void *p) {
      delete [] ((map<short,ULong64_t>*)p);
   }
   static void destruct_maplEshortcOULong64_tgR(void *p) {
      typedef map<short,ULong64_t> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<short,ULong64_t>

namespace {
  void TriggerDictionaryInitialization_ORRUBADictionary_Impl() {
    static const char* headers[] = {
"/media/mhall12/Zeus/goddess_daq/goddess/include/ORRUBA.h",
"/media/mhall12/Zeus/goddess_daq/goddess/include/Detector.h",
"/media/mhall12/Zeus/goddess_daq/goddess/include/siDet.h",
"/media/mhall12/Zeus/goddess_daq/goddess/include/orrubaDet.h",
"/media/mhall12/Zeus/goddess_daq/goddess/include/superX3.h",
"/media/mhall12/Zeus/goddess_daq/goddess/include/BB10.h",
"/media/mhall12/Zeus/goddess_daq/goddess/include/QQQ5.h",
"/media/mhall12/Zeus/goddess_daq/goddess/include/IonChamber.h",
"/media/mhall12/Zeus/goddess_daq/goddess/include/LiquidScint.h",
0
    };
    static const char* includePaths[] = {
"/home/mhall12/root/include",
"/media/mhall12/Zeus/goddess_daq/include",
"/media/mhall12/Zeus/goddess_daq/goddess/include",
"/home/mhall12/root/include",
"/media/mhall12/Zeus/goddess_daq/build/goddess/source/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "ORRUBADictionary dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$/media/mhall12/Zeus/goddess_daq/goddess/include/Detector.h")))  Detector;
class __attribute__((annotate("$clingAutoload$/media/mhall12/Zeus/goddess_daq/goddess/include/siDet.h")))  siDet;
class __attribute__((annotate("$clingAutoload$/media/mhall12/Zeus/goddess_daq/goddess/include/orrubaDet.h")))  orrubaDet;
class __attribute__((annotate("$clingAutoload$/media/mhall12/Zeus/goddess_daq/goddess/include/superX3.h")))  superX3;
class __attribute__((annotate("$clingAutoload$/media/mhall12/Zeus/goddess_daq/goddess/include/BB10.h")))  BB10;
class __attribute__((annotate("$clingAutoload$/media/mhall12/Zeus/goddess_daq/goddess/include/QQQ5.h")))  QQQ5;
class __attribute__((annotate("$clingAutoload$/media/mhall12/Zeus/goddess_daq/goddess/include/IonChamber.h")))  IonChamber;
class __attribute__((annotate("$clingAutoload$/media/mhall12/Zeus/goddess_daq/goddess/include/LiquidScint.h")))  LiquidScint;
class __attribute__((annotate("$clingAutoload$/media/mhall12/Zeus/goddess_daq/goddess/include/ORRUBA.h")))  ORRUBA;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$string")))  allocator;
}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "ORRUBADictionary dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/ORRUBA.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/Detector.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/siDet.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/orrubaDet.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/superX3.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/BB10.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/QQQ5.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/IonChamber.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/LiquidScint.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"BB10", payloadCode, "@",
"Detector", payloadCode, "@",
"IonChamber", payloadCode, "@",
"LiquidScint", payloadCode, "@",
"ORRUBA", payloadCode, "@",
"QQQ5", payloadCode, "@",
"orrubaDet", payloadCode, "@",
"siDet", payloadCode, "@",
"superX3", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("ORRUBADictionary",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_ORRUBADictionary_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_ORRUBADictionary_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_ORRUBADictionary() {
  TriggerDictionaryInitialization_ORRUBADictionary_Impl();
}
