using System;

namespace MelonLoader
{
    internal static class Core
    {
        static Core()
        {
            try { MelonUtils.Setup(); } catch (Exception ex) { MelonLogger.Error("MelonUtils.Setup Exception: " + ex.ToString()); throw ex; }

            AppDomain curDomain = AppDomain.CurrentDomain;

            Fixes.UnhandledException.Run(curDomain);
            Fixes.InvariantCurrentCulture.Install();

            Fixes.ApplicationBase.Run(curDomain);
            Fixes.ExtraCleanup.Run();

#if PORT_DISABLE
            MelonCommandLine.Load();
#endif
            MelonCompatibilityLayer.Setup(curDomain);

            if (MelonUtils.IsGameIl2Cpp())
                HarmonyLib.Public.Patching.PatchManager.ResolvePatcher += HarmonyIl2CppMethodPatcher.TryResolve;

            PatchShield.Install();
        }

        private static int Initialize()
        {
#if PORT_DISABLE
            try { bHaptics_NativeLibrary.Load(); } 
            catch (Exception ex) { MelonLogger.Warning("bHaptics_NativeLibrary.Load Exception: " + ex.ToString()); bHaptics.WasError = true; }
#endif

            MelonPreferences.Load();

            if (MelonUtils.IsGameIl2Cpp() && !Il2CppAssemblyGenerator.Run())
                return 1;

            MelonHandler.LoadPlugins();
            MelonHandler.OnPreInitialization();

            return 0;
        }

        private static int Start()
        {
            MelonDebug.Msg(MelonUtils.GetMainAssemblyLoc());
            if (!SupportModule.Initialize())
                return 1;

#if PORT_DISABLE
            AddUnityDebugLog();
#endif
            try { bHaptics.Start(); } 
            catch (Exception ex) { MelonLogger.Warning("bHaptics.Start Exception: " + ex.ToString()); bHaptics.WasError = true; }

            if (MelonUtils.StaticSettings.safeMode)
                MelonLogger.Warning("Safe Mode is enabled. MelonLoader will have reduced functionality.");
            
            MelonHandler.OnApplicationStart_Plugins();

            MelonHandler.LoadMods();
            MelonHandler.OnApplicationStart_Mods();

            MelonHandler.OnApplicationLateStart_Plugins();
            MelonHandler.OnApplicationLateStart_Mods();

            return 0;
        }

        internal static void Quit()
        {
            MelonHandler.OnApplicationQuit();
            MelonPreferences.Save();

            //Harmony.HarmonyInstance.UnpatchAllInstances();

            try { bHaptics.Quit(); } 
            catch (Exception ex) { MelonLogger.Warning("bHaptics.Quit Exception: " + ex.ToString()); bHaptics.WasError = true; }

            MelonLogger.Flush();
            Fixes.QuitFix.Run();
        }

        private static void AddUnityDebugLog()
        {
            SupportModule.Interface.UnityDebugLog("--------------------------------------------------------------------------------------------------");
            SupportModule.Interface.UnityDebugLog("~   This Game has been MODIFIED using MelonLoader. DO NOT report any issues to the Developers!   ~");
            SupportModule.Interface.UnityDebugLog("--------------------------------------------------------------------------------------------------");
        }
    }
}