/**
 * @file IObservable.h
 *
 * @copyright Yuqing Qin, All rights reserved.
 */
#ifndef SRC_IOBSERVABLE_H_
#define SRC_IOBSERVABLE_H_

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>

#include "src/IObserver.h"
#include "src/data_structs.h"

/******************************************************************************
 * Class Definitions
 *****************************************************************************/

/**
 * @brief The class for creating the subject in the observer pattern
 *
 * Calls to \ref RegisterObserver method to attach an observer to the subject.
 * \ref ClearObservers method can help detach the observers registered before.
 * \ref NotifyObservers may be called by subject to notify all the observers 
 * with the updated information. Implement the IObserver using template. It can be used 
 * for different type of data.
 */
template <typename Tp>
class IObservable{
    std::vector<IObserver<Tp>*> observer_;

 public:
  /**
  * @brief Register the observer to connect with the subject.
  * It will attach the specified observer to the subject's observer list.
  * This function will be used for getting the updates from the subject, and
  * notifying all the users.
  *
  * @param[in] observer observer that wants to attach to the subject
  *
  */
    void RegisterObserver(IObserver<Tp>* observer);

  /**
  * @brief Clear the observers that connected with the subject.
  * It will detach all the observers in the subject's observer list. The
  * subjects can be a bus or a stop in this iteration.
  *
  */
    void ClearObservers();

  /**
  * @brief Notify all the observers that connected with the subject.
  * It will notify the observers with the updated information 
  *
  * @param[in] info the busdata that need to be updated and notify to the
  * observer
  *
  */
    void NotifyObservers(Tp info);
};


template <typename Tp>
void IObservable<Tp>::RegisterObserver(IObserver<Tp>* observer) {
    // add the observer into the observer list
    observer_.push_back(observer);
}

template <typename Tp>
void IObservable<Tp>::ClearObservers() {
    // clear the observer list
    observer_.erase(observer_.begin(), observer_.end());
}

template <typename Tp>
void IObservable<Tp>::NotifyObservers(Tp info) {
    // Go through the observer list, and notify each of them by
    // using Notify method in IObserver.
    for (typename std::vector<IObserver<Tp>*>::const_iterator
        iter = observer_.begin();
        iter != observer_.end(); ++iter) {
        if (*iter != 0) {
            (*iter) -> Notify(info);
        }
    }
}

#endif  // SRC_IOBSERVABLE_H_
