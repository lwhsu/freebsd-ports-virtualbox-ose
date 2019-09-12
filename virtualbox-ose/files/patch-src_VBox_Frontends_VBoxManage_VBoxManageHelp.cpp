--- src/VBox/Frontends/VBoxManage/VBoxManageHelp.cpp.orig	2019-01-25 18:19:18 UTC
+++ src/VBox/Frontends/VBoxManage/VBoxManageHelp.cpp
@@ -610,7 +610,7 @@ void printUsage(USAGECATEGORY fCategory, uint32_t fSub
                      "                                             file <file>|\n"
                      "                                             <devicename>]\n"
                      "                            [--uarttype<1-N> 16450|16550A|16750\n"
-#if defined(RT_OS_LINUX) || defined(RT_OS_WINDOWS)
+#if defined(RT_OS_FREEBSD) || defined(RT_OS_LINUX) || defined(RT_OS_WINDOWS)
                      "                            [--lpt<1-N> off|<I/O base> <IRQ>]\n"
                      "                            [--lptmode<1-N> <devicename>]\n"
 #endif
@@ -624,7 +624,7 @@ void printUsage(USAGECATEGORY fCategory, uint32_t fSub
             RTStrmPrintf(pStrm, "|dsound");
 #endif
         }
-        if (fLinux || fSolaris)
+        if (fLinux || fFreeBSD || fSolaris)
         {
             RTStrmPrintf(pStrm, ""
 #ifdef VBOX_WITH_AUDIO_OSS
@@ -637,22 +637,6 @@ void printUsage(USAGECATEGORY fCategory, uint32_t fSub
                                 "|pulse"
 #endif
                         );
-        }
-        if (fFreeBSD)
-        {
-#ifdef VBOX_WITH_AUDIO_OSS
-            /* Get the line break sorted when dumping all option variants. */
-            if (fDumpOpts)
-            {
-                RTStrmPrintf(pStrm, "|\n"
-                     "                                     oss");
-            }
-            else
-                RTStrmPrintf(pStrm, "|oss");
-#endif
-#ifdef VBOX_WITH_AUDIO_PULSE
-            RTStrmPrintf(pStrm, "|pulse");
-#endif
         }
         if (fDarwin)
         {
