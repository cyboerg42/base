/* XMRig
 * Copyright (c) 2018-2021 SChernykh   <https://github.com/SChernykh>
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

#ifndef XMRIG_PROCESS_H
#define XMRIG_PROCESS_H


#include "base/tools/String.h"
#include "base/tools/Object.h"


#ifdef WIN32
#   define XMRIG_DIR_SEPARATOR "\\"
#else
#   define XMRIG_DIR_SEPARATOR "/"
#endif


namespace xmrig {


class Arguments;
class ProcessPrivate;
class Versions;


class Process
{
public:
    XMRIG_DISABLE_COPY_MOVE_DEFAULT(Process)

    enum Location {
        ExePathLocation,
        ExeLocation,
        CwdLocation,
        DataLocation,
        HomeLocation,
        TempLocation
    };

    Process(int argc, char **argv);
    ~Process();

    static const Arguments &arguments();
    static const char *version();
    static const Versions &versions();
    static int pid();
    static int ppid();
    static String locate(Location location, const char *fileName);
    static String locate(Location location);

private:
    static ProcessPrivate *d_ptr;
};


} // namespace xmrig


#endif // XMRIG_PROCESS_H