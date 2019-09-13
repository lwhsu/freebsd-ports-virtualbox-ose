--- include/VBox/com/array.h.orig	2019-01-25 18:10:05 UTC
+++ include/VBox/com/array.h
@@ -171,7 +171,7 @@
 
 #include "VBox/com/defs.h"
 
-#if RT_GNUC_PREREQ(4, 6) || (defined(_MSC_VER) && (_MSC_VER >= 1600))
+#if RT_GNUC_PREREQ(4, 6) || (defined(_MSC_VER) && (_MSC_VER >= 1600)) || defined(_LIBCPP_VERSION)
 /** @def VBOX_WITH_TYPE_TRAITS
  * Type traits are a C++ 11 feature, so not available everywhere (yet).
  * Only GCC 4.6 or newer and MSVC++ 16.0 (Visual Studio 2010) or newer.
@@ -943,12 +943,12 @@ class SafeArray : public Traits (public)
      */
     T &operator[] (size_t aIdx)
     {
-        AssertReturn(m.arr != NULL,  *((T *)NULL));
-        AssertReturn(aIdx < size(), *((T *)NULL));
+        AssertReturn(m.arr != NULL,  *((T *)1));
+        AssertReturn(aIdx < size(), *((T *)1));
 #ifdef VBOX_WITH_XPCOM
         return m.arr[aIdx];
 #else
-        AssertReturn(m.raw != NULL,  *((T *)NULL));
+        AssertReturn(m.raw != NULL,  *((T *)1));
         return m.raw[aIdx];
 #endif
     }
@@ -963,7 +963,7 @@ class SafeArray : public Traits (public)
 #ifdef VBOX_WITH_XPCOM
         return m.arr[aIdx];
 #else
-        AssertReturn(m.raw != NULL,  *((T *)NULL));
+        AssertReturn(m.raw != NULL,  *((T *)1));
         return m.raw[aIdx];
 #endif
     }
