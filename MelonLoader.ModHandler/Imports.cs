﻿using System;
using System.Runtime.InteropServices;

namespace MelonLoader
{
    public class Imports
    {
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern bool SetDllDirectory(string lpPathName);

        [DllImport("MelonLoader\\MelonLoader", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static IntPtr melonloader_get_il2cpp_domain();
        [DllImport("MelonLoader\\MelonLoader", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static bool melonloader_is_il2cpp_game();
        [DllImport("MelonLoader\\MelonLoader", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public extern static bool melonloader_is_debug_mode();
    }
}