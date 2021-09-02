/* XMRig
 * Copyright (c) 2016-2021 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2021 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <uv.h>


#ifdef XMRIG_FEATURE_TLS
#   include <openssl/opensslv.h>
#endif

#ifdef XMRIG_FEATURE_HWLOC
#   include <hwloc.h>
#endif

#ifdef XMRIG_FEATURE_OPENCL
#   include "backend/opencl/wrappers/OclLib.h"
#   include "backend/opencl/wrappers/OclPlatform.h"
#endif

#include "base/kernel/Entry.h"
#include "../version.h"
#include "base/kernel/Process.h"
#include "base/tools/Arguments.h"
#include "core/config/usage.h"


namespace xmrig {


static int showVersion()
{
    printf(APP_NAME " " APP_VERSION "\n built on " __DATE__

#   if defined(__clang__)
    " with clang " __clang_version__);
#   elif defined(__GNUC__)
    " with GCC");
    printf(" %d.%d.%d", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#   elif defined(_MSC_VER)
    " with MSVC");
    printf(" %d", MSVC_VERSION);
#   else
    );
#   endif

    printf("\n features:"
#   if defined(__i386__) || defined(_M_IX86)
    " 32-bit"
#   elif defined(__x86_64__) || defined(_M_AMD64)
    " 64-bit"
#   endif

#   if defined(__AES__) || defined(_MSC_VER)
    " AES"
#   endif
    "\n");

    printf("\nlibuv/%s\n", uv_version_string());

#   if defined(XMRIG_FEATURE_TLS)
    {
#       if defined(LIBRESSL_VERSION_TEXT)
        printf("LibreSSL/%s\n", LIBRESSL_VERSION_TEXT + 9);
#       elif defined(OPENSSL_VERSION_TEXT)
        constexpr const char *v = &OPENSSL_VERSION_TEXT[8];
        printf("OpenSSL/%.*s\n", static_cast<int>(strchr(v, ' ') - v), v);
#       endif
    }
#   endif

#   if defined(XMRIG_FEATURE_HWLOC)
#   if defined(HWLOC_VERSION)
    printf("hwloc/%s\n", HWLOC_VERSION);
#   elif HWLOC_API_VERSION >= 0x20000
    printf("hwloc/2\n");
#   else
    printf("hwloc/1\n");
#   endif
#   endif

    return 0;
}


#ifdef XMRIG_FEATURE_HWLOC
static int exportTopology()
{
    const String path = Process::locate(Process::ExeLocation, "topology.xml");

    hwloc_topology_t topology = nullptr;
    hwloc_topology_init(&topology);
    hwloc_topology_load(topology);

#   if HWLOC_API_VERSION >= 0x20000
    if (hwloc_topology_export_xml(topology, path, 0) == -1) {
#   else
    if (hwloc_topology_export_xml(topology, path) == -1) {
#   endif
        printf("failed to export hwloc topology.\n");
    }
    else {
        printf("hwloc topology successfully exported to \"%s\"\n", path.data());
    }

    hwloc_topology_destroy(topology);

    return 0;
}
#endif


} // namespace xmrig


xmrig::Entry::Id xmrig::Entry::get()
{
    const auto &args = Process::arguments();
    if (args.contains("-h") || args.contains("--help")) {
         return Usage;
    }

    if (args.contains("-V") || args.contains("--version")) {
         return Version;
    }

#   ifdef XMRIG_FEATURE_HWLOC
    if (args.contains("--export-topology")) {
        return Topo;
    }
#   endif

#   ifdef XMRIG_FEATURE_OPENCL // FIXME
    if (args.contains("--print-platforms")) {
        return Platforms;
    }
#   endif

    return Default;
}


int xmrig::Entry::exec(Id id)
{
    switch (id) {
    case Usage:
        printf("%s\n", usage().c_str());
        return 0;

    case Version:
        return showVersion();

#   ifdef XMRIG_FEATURE_HWLOC
    case Topo:
        return exportTopology();
#   endif

#   ifdef XMRIG_FEATURE_OPENCL
    case Platforms:
        if (OclLib::init()) {
            OclPlatform::print();
        }
        return 0;
#   endif

    default:
        break;
    }

    return 1;
}
