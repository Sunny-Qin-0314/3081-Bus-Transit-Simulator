/**
 * @file BusWebObserver.h
 *
 * @Copyright Sunny Qin and 3081 Staff, All rights reserved.
 */
#ifndef WEB_CODE_WEB_BUSWEBOBSERVER_H_
#define WEB_CODE_WEB_BUSWEBOBSERVER_H_

#include "src/IObserver.h"
#include "web_code/web/my_web_server_session.h"
#include "web_code/web/my_web_server_session_state.h"
#include "src/data_structs.h"

/**
 * @brief The class for creating bus web observer
 *
 * Implement \ref Notify method in observer pattern
 */
class BusWebObserver : public IObserver<BusData*> {
 public:
   /**
   * @brief Bus web observer creation
   *
   * This constructor will create a observer for bus
   *
   * @param[in] session web server session
   */
    explicit BusWebObserver(MyWebServerSession* session) : session(session) {}

   /**
   * @brief Notify the observer with the info
   *
   * This method overrides the one in \ref IObserver
   *
   * @param[in] info BusData need to be informed
   */
    void Notify(BusData* info);
 private:
    MyWebServerSession* session;
};

#endif  // WEB_CODE_WEB_BUSWEBOBSERVER_H_
