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

#ifndef XMRIG_EVENTS_H
#define XMRIG_EVENTS_H


#include "base/tools/Object.h"


#include <memory>


namespace xmrig {


class IEvent;
class IEventListener;


class Events
{
public:
    XMRIG_DISABLE_COPY_MOVE(Events)

    Events();
    ~Events();

    template<typename T, typename... Args>
    inline void post(Args&&... args)
    {
        post(std::make_shared<T>(std::forward<Args>(args)...));
    }

    template<typename T, typename... Args>
    inline void send(Args&&... args)
    {
        T event(std::forward<Args>(args)...);
        send(event);
    }

    static void send(IEventListener *listener, IEvent &event);

    void addListener(IEventListener *listener);
    void post(std::shared_ptr<IEvent> &&event);
    void removeListener(IEventListener *listener);
    void send(IEvent &event);

private:
    XMRIG_DECL_PRIVATE()
};


} // namespace xmrig


#endif // XMRIG_EVENTS_H
