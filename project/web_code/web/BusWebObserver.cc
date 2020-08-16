/**
 * @file my_web_server_command.h
 *
 * @Copyright Sunny Qin and 3081 Staff, All rights reserved.
 */
#include <sstream>

#include "web_code/web/BusWebObserver.h"
#include "src/config_manager.h"
#include "web_code/web/my_web_server_session.h"
#include "web_code/web/my_web_server_session_state.h"
#include "web_code/web/my_web_server.h"

void BusWebObserver::Notify(BusData* info) {
        // This normally called update, but we call it Notify
        picojson::object data;
        data["command"] = picojson::value("observe");
        std::stringstream ss;
        ss << "Bus " << info->id << "\n";
        ss << "-----------------------------\n";
        ss << "  * Position: (" << info->position.x << ","
                << info->position.y << ")\n";
        ss << "  * Passnegers: " << info->num_passengers << "\n";
        ss << "  * Capacity: " << info->capacity << "\n";
        data["text"] = picojson::value(ss.str());
        picojson::value ret(data);
        session->sendJSON(ret);
}
