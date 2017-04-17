/*
 * Vsys.c
 *
 *  Created on: 2016-8-16
 *      Author: wenrenjinjun
 */
#include <stdio.h>
#include <windows.h>
#include <stdint.h>
#include <winnt.h>


typedef  struct sysinfo_s  sysinfo_t ;
struct sysinfo_s
{
    OSVERSIONINFOEX os;
    SYSTEM_INFO info;
}sysinfo;

//  1.0         Interface Manager       Windows 1.0         1985-11-20
//  2.0         /                       Windows 2.0         1987-11-1
//  3.0         /                       Windows 3.0         1990-5-22
//  3.1         Janus                   Windows 3.1         1992-3-18
//  NT 3.1      NTOS/2                  Windows NT 3.1      1993-7-27
//  3.2         Janus                   Windows 3.2         1994-4-14
//  4.0         Chicago                 Windows 95          1995-8-24
//  NT 3.5      Daytona                 Windows NT 3.5      1995-11-20
//  NT 4.0      Cairo                   Windows NT 4.0      1996-7-29
//  4.00.950B   Detroit                 Windows 95 OSR2     1996-8-24
//  4.1         Memphis                 Windows 98          1998-6-25
//  4.10.2222A  Memphis                 Windows 98 SE       1999-5-5
//  NT 5.0      Windows NT 5.0          Windows 2000        2000-2-17
//  4.9         Millennium              Windows ME          2000-9-14
//  NT 5.1(32b)
//  NT 5.2(64b) Whistler                Windows XP          2001-10-25
//  NT 5.2      Whistler Server         Windows Server 2003 2003-4-24
//  NT 6.0      Longhorn                Windows Vista       2005-7-27
//  NT 5.2      Quattro                 Windows Home Server 2007-1-7
//  NT 6.0      Longhorn Server         Windows Server 2008 2008-2-27
//  NT 6.1      Blackcomb,Vienna,       Windows 7           2009-10-22
//  NT 6.1      Windows Server 7        Windows Server 2008 R2      2009-10-22
//  NT 6.1      Vail                    Windows Home Server 2011    2011-04-05
//  NT 6.1      /                       Windows Thin PC     2011-07-11
//  NT 6.2      Windows 8               Windows 8           2012-10-25
//  NT 6.2      Windows Server 8        Windows Server 2012 2012-9-4
//  NT 6.3      Windows Blue            Windows 8.1         2013-10-18
//  NT 6.3      /                       Windows Server 2012 R2      2013-10-18
//  NT 6.3.9600.17031       Windows 8.1 Spring Update
//                                      Windows 8.1 with Update     2014-04-08
//  NT 10.0     Windows Threshold       Windows 10          2015-7-29
//  NT10.1      Windows10 Autumn Update Windows10 Update 1  2015-10-29
//  NT10.2      Windows10 redstone                          2016-1


void
show_SystemInfo(SYSTEM_INFO *pSystem_Info)
{
    printf("\n");
    printf("wProcessorArchitecture = %d\n",         pSystem_Info->wProcessorArchitecture);
    printf("dwPageSize = %ld\n",                    pSystem_Info->dwPageSize);
    printf("lpMinimumApplicationAddress = 0x%p\n",  pSystem_Info->lpMinimumApplicationAddress);
    printf("lpMaximumApplicationAddress = 0x%p\n",  pSystem_Info->lpMaximumApplicationAddress);
    printf("dwActiveProcessorMask = %ld\n",         pSystem_Info->dwActiveProcessorMask);
    printf("dwNumberOfProcessors = %ld\n",          pSystem_Info->dwNumberOfProcessors);
    printf("dwProcessorType = %ld\n",               pSystem_Info->dwProcessorType);        //废弃使用
    printf("dwAllocationGranularity = %ld\n",       pSystem_Info->dwAllocationGranularity);
    printf("wProcessorLevel = %d\n",                pSystem_Info->wProcessorLevel);
    printf("wProcessorRevision = %d\n",             pSystem_Info->wProcessorRevision);
}

void
show_OSVersionInfoEx(OSVERSIONINFOEX *pOSVersionInfoEx)
{
    printf("\n");
    printf("dwOSVersionInfoSize = %ld\n",       pOSVersionInfoEx->dwOSVersionInfoSize);
    printf("dwMajorVersion = %ld\n",            pOSVersionInfoEx->dwMajorVersion);     //系统主版本号
    printf("dwMinorVersion = %ld\n",            pOSVersionInfoEx->dwMinorVersion);     //系统次版本号
    printf("dwBuildNumber = %ld\n",             pOSVersionInfoEx->dwBuildNumber);      //系统构建号
    printf("dwPlatformId = %ld\n",              pOSVersionInfoEx->dwPlatformId);       //系统支持的平台
    printf("szCSDVersion = %s\n",               pOSVersionInfoEx->szCSDVersion);       //系统补丁包的名称
    printf("wServicePackMajor = %d\n",          pOSVersionInfoEx->wServicePackMajor);  //系统补丁包的主版本
    printf("wServicePackMinor = %d\n",          pOSVersionInfoEx->wServicePackMinor);  //系统补丁包的次版本
    printf("wSuiteMask = %d\n",                 pOSVersionInfoEx->wSuiteMask);         //标识系统上的程序组
    printf("wProductType = %d\n",               pOSVersionInfoEx->wProductType);       //标识系统类型
    printf("wReserved = %d\n",                  pOSVersionInfoEx->wReserved);          //保留,未使用
}

//_osver
//_winmajor
//_winminor
//_winver
//__argc
//__wargv
//_environ
//_wenviron
//_pgmptr
//_wpgmptr
//_onexit
//  printf( "GetCommandLine = %s\n" ,GetCommandLine());
//  printf( "GetEnvironmentStrings = %s\n" ,GetEnvironmentStrings());
//  printf( "GetEnvironmentStrings = %s\n" ,GetEnvironmentVariable());

//  char moduleFileName[100];
//  GetModuleFileName(0, moduleFileName, 100);
//  printf( "GetModuleFileName = %s\n" ,moduleFileName);
//
#if 0
    DWORD dwVersion = 0;
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0;
    DWORD dwBuild = 0;

    dwVersion = GetVersion(); // Get the Windows version.已经废弃
    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

    if (dwVersion < 0x80000000)// Get the build number.
    {
        dwBuild = (DWORD)(HIWORD(dwVersion));
    }
    printf("Version is %ld.%ld (%ld)", dwMajorVersion, dwMinorVersion, dwBuild);
#endif

#include <test.h>
#ifdef __WHITEBOX_TEST

__INIT_SUITE(sysinfo)   {return 0;}
__CLEAN_SUITE(sysinfo)  {return 0;}

__IMPLEMENT_TEST(GetSystemInfo)
{
    SYSTEM_INFO info;
    GetSystemInfo(&info);
//    show_SystemInfo(&info);
//    CU_PASS(GetSystemInfo);
}

__IMPLEMENT_TEST(GetVersionEx)
{
    OSVERSIONINFOEX os;

    os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    CU_ASSERT_TRUE(GetVersionEx((OSVERSIONINFO *)&os));

//    show_OSVersionInfoEx(&os);
    os.dwOSVersionInfoSize = 0;
    CU_ASSERT_FALSE(GetVersionEx((OSVERSIONINFO *)&os));
}

__BEGIN_TESTMAP_OF_SUITE(sysinfo)
    __REG_TEST(GetSystemInfo)
    __REG_TEST(GetVersionEx)
__END_TESTMAP()

#endif
/*-------------------------------- sys.c ------------------------------------*/
