/* XMRig
 * Copyright (c) 2016      Ivan Vizir  <define-true-false@yandex.com>
 * Copyright (c) 2016      The Qt Company Ltd.
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

#ifndef XMRIG_TASKBAR_H
#define XMRIG_TASKBAR_H


#include "base/tools/Object.h"


namespace xmrig {


class Taskbar
{
public:
    XMRIG_DISABLE_COPY_MOVE(Taskbar)

    Taskbar();
    ~Taskbar();

    inline void hide()      { setVisible(false); }
    inline void pause()     { setPaused(true); }
    inline void reset()     { setValue(minimum()); };
    inline void show()      { setVisible(true); }

    bool isPaused() const;
    bool isStopped() const;
    bool isVisible() const;
    int maximum() const;
    int minimum() const;
    int value() const;
    void resume();
    void setMaximum(int maximum);
    void setMinimum(int minimum);
    void setPaused(bool paused);
    void setRange(int minimum, int maximum);
    void setValue(int value);
    void setVisible(bool visible);
    void stop();

private:
    XMRIG_DECL_PRIVATE()
};


} // namespace xmrig


#endif // XMRIG_TASKBAR_H
