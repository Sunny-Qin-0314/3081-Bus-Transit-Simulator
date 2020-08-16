/**
 * @file IObservable.cc
 *
 * @copyright Yuqing Qin, All rights reserved.
 */
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>

#include "src/IObservable.h"
#include "src/data_structs.h"

// template <typename Tp>
// void IObservable<Tp>::RegisterObserver(IObserver<Tp>* observer) {
//     // add the observer into the observer list
//     observer_.push_back(observer);
// }

// template <typename Tp>
// void IObservable<Tp>::ClearObservers() {
//     // clear the observer list
//     observer_.erase(observer_.begin(), observer_.end());
// }

// template <typename Tp>
// void IObservable<Tp>::NotifyObservers(Tp info) {
//     // Go through the observer list, and notify each of them by
//     // using Notify method in IObserver.
//     for (typename std::vector<IObserver<Tp>*>::const_iterator
//           iter = observer_.begin();
//         iter != observer_.end(); ++iter) {
//         if (*iter != 0) {
//             (*iter) -> Notify(info);
//         }
//     }
// }
