/**
 * @file mainpage.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

/*! \mainpage Transition Simulator Main Page
 *
 * \section intro_sec Introduction
 *
 * This is a bus transition simulation, in which you can see the bus
 * moving along the routes predefined. You can set up the simulation info,
 * including total time steps to run and time steps between buses for each
 * route before you run this simulation. To see the simulation, you may
 * click on the Start button and Pause button to see the updated buses and
 * stops information.
 *
 * In this implementation, Bus, Stop, Route, and Passenger are the major
 * classes. Bus class contains many operations related to bus, such as Move,
 * Update, Report. Stop class can generate stops and load passengers to bus.
 * In Route class, you can check whether it is at the end stop, go to next
 * stop and get the previous stop information. For Passenger class, you can
 * generate a new passenger with its name and destination id. These four
 * classes are the basic classes that you can first take a look at. There are
 * also some related classes to perform complex operation, such as
 * PassengerLoader, PassengerUnloader, PassengerFactory, BusFactory, and
 * PassengerGenerator. These are the classes to perform different operations,
 * like load a passenger, unload a passenger, create a passenger, and create a
 * bus object. They all work together to make VisualizationSimulator work.
 *
 * This is my course project for CSci3081W in Spring 2020.
 * The base code comes from all the teaching staffs in this course. In this
 * documentation, I only document all the new classes or methods that I added
 * to the base code. Specificlly, the new classes and methods are
 * BusFactory, Pause method in VisualizationSimulator, SmallBus, RegularBus,
 * and LargeBus. I also documented the method I modified on, such as ToNextStop
 * method in Route, and LoadPassenger in PassengerLoader.
 *
 * \section install_sec Obtain and Install
 * To get this code, you need to go to my github repo, which is
 * https://github.umn.edu/umn-csci-3081-s20/repo-qing0002/ to download the
 * code. This simulation is in /project folder.
 *
 * \section compile_sec Compile
 * To compile this code, please follow the steps below. Please make sure you
 * have already installed cmake before you start.
 * \subsection step_1 Step 1
 * Get into src folder by typing "cd project/src" in your command.
 * \subsection step_2 Step 2
 * Compile your code by typing "make" in your command.
 *
 * \section open_sec Open Simulation
 * To open the simulation window, please follow the steps below.
 * \subsection step_11 Step 1
 * If you are in the src folder, go back to the root folder by typing "cd .."
 * \subsection step_12 Step 2
 * Type "./build/bin/vis_sim <port_num>" in your command line with your chosen
 * port number. This number should be greater than 8000.
 * \subsection step_13 Step 3
 * Go to your browser (ex. Google Chrome, Firefox, Safari), and type
 * "http://127.0.0.1:<port_num>/web_graphics/project.html" with the port number
 * that you set up in last step.
 *
 * \section run_sec Run Simulation
 * To run this simulation, you need to click on the "Start" button on the web
 * page. Before you start to run, you can change the total time steps to run
 * and time steps between buses for each route under sim info. You can also
 * click on "Pause" button to pause the simulation and see the details of the
 * buses and stops. After you click the "Pause" button again, the simulation
 * will continue.
 *
 * \section discussion_sec Discussion on Bus Factory Implementation
 * \subsection con_sec Concrete bus factory implementation detail
 * In my implementation, I create a concrete \ref BusFactory, which can
 * generate three types of buses( \ref SmallBus, \ref RegularBus, and
 * \ref LargeBus). The corresponding capacities for them are 30, 60, 90.
 *
 * The core structure for concrete factory implementation is included in the
 * UML below. Three sub-classes(SmallBus, RegularBus, LargeBus) are inherited
 * from base class(Bus class). Their constructor is inherited from Bus's with
 * corresponding capacity(30, 60, or 90). Their Report method overwrites Bus
 * factory's Report method by printing their types as well as the basic
 * information of a bus, including name, speed, distance to next stop, and
 * passengers.
 *
 * My BusFactory uses these three sub-classes to
 * implement. To generate different types of buses, concrete bus factory uses
 * a "type" parameter to determine which sub-class constructor to call. If type
 * is 1, then SmallBus constructor will be called. If type is 2, then
 * RegularBus constructor will be called. If type is 3, then LargeBus
 * constructor will be called. BusFactory is used in VisualizationSimulator to
 * generate new buses on routes. The type for buses generated in visualization
 * simulator is randomly generated by now. This may change in future version.
 * <img src="../concrete.png" width="1000" height="1000"/>
 *
 * \subsection con_pro_sec Concrete bus factory advantage
 * The advantage to use concrete bus factory is its easy-coding manner.
 * Concrete factory does not need sub-classes factory to implement. When the
 * bus types are not very complex, then implementing it in a concrete factory
 * will save much more time. If you do not need separate operation for
 * different factories, then concrete factory is a good option. In my
 * implementation, I chose concrete bus factory because three different types
 * of buses share similar operations. The only difference between them is their
 * capacity, which make it easier to implement a concrete bus factory. Only one
 * concrete factory can generate different types of buses. And it does not need
 * any other operations for a factory by now. Therefore, I chose concrete bus
 * factory to save some coding time.
 *
 * \subsection con_con_sec Concrete bus factory disadvantage
 * Concrete factory does not follow the design heuristics rigorously. Different
 * parts do not separate completely, different type of buses are all generated
 * in one bus factory. Also,
 * Concrete factory cannot build a run-time binding. Sometimes, users may
 * not sure about which kind of factory they want to use on compile time.
 * This problem may
 * be fixed by run time binding. The system should identify the proper factory
 * to call, so the user can use proper factory without knowing the
 * internal implementation about the factory. Concrete factory is easy to build
 * but it needs more effort if the factory contains complex operations.
 *
 * \subsection abs_sec Abstract bus factory implementation details
 * The core structure for abstract factory implementation is included in the
 * UML below. Three sub-classes(SmallBus, RegularBus, LargeBus) are inherited
 * from base class(Bus class). This part is same as the concrete bus factory
 * Their constructor is inherited from Bus's with
 * corresponding capacity(30, 60, or 90). Their Report method overwrites Bus
 * factory's Report method by printing their types as well as the basic
 * information of a bus, including name, speed, distance to next stop, and
 * passengers.
 *
 * Three concrete factory classes are inherited from abstract bus factory.
 * They are SmallBusFactory, RegularBusFactory, and LargeBusFactory.
 * To generate different types of buses, system identify the type that users
 * want to generate, and call different bus factory correspondingly.
 * Abstract bus factory do
 * not need "type" parameter to determine the type of bus inside the bus
 * factory. Instead, they use three sub-classes to represent differnet types.
 * So that when users try to use one of them, they can just call the
 * corresponding sub-classes without knowing the internal implementation for
 * bus factory. If type
 * is 1, then SmallBusFactory will be called. If type is 2, then
 * RegularBusFactory will be called. If type is 3, then LargeBusFactory
 * constructor will be called. BusFactory is declared in VisualizationSimulator
 * and the specific factory is determined in run-time.
 *
 * <img src="../abstract.png" width="1000" height="1000"/>
 * \subsection abs_pro_sec Abstract bus factory advantage
 * Abstract factory is useful especially for the case that users do not know
 * exactly which type to generate. It isolates the specific implementation of
 * of an object from the user. So users may use abstract factory to declare
 * without knowing the implementation details about the small types of objects.
 * Therefore, even though sometimes users do not know entirely about the 
 * object. Abstract factory can also help him generating the proper object.
 * 
 * \subsection abs_con_sec Abstract bus factory disadvantage
 * Different factories may have separate operations. If you want to extend
 * abstract bus factory, then you need to change the source code including the
 * abstract factory and sub-classes everytime. And compile them all again. This
 * may cost a lof time to implement and maintain. Like this project iteration 1
 * we do not need complex operations on sub-classes. It only need generate 
 * funtion. The main difference in sub-classes is their capacity.
 * It may cost more time to implement three more concrete factory instead of
 * only one concrete factory like the implementation method mentioned above.
 *
 * \section des Designing and Implementing the Observer Pattern
 * \subsection det_des Design and Implementation Details (include classes/methods added)
 * Observer pattern is a design pattern that useful to observe the subject changes via observers.
 * In our specific case, the subject is the bus that mouse clicks on, and the 
 * observer in Iteration2 is the only one web server which you can see it at the web page.
 * In my implementation, there are two main parts, which are front-end web design and
 * back-end observer pattern implementation. The design and implementation details are
 * included in the following UML diagram.
 * 
 * <img src="../Observer_UML.jpg" alt="Obeserver pattern implementation" width="800" height="600"/>
 * For back-end observer pattern implementation, it cantains two main parts, which are
 * IObserver and ISubject. These two are the base classes, and IObserver is a pure virtual
 * base class that BusWebObserver inherited from it. IObserver is implemented in "/src/IObserver.h"
 * ( \ref IObserver). You can see the details in this header file. UpdateObserver method is
 * implemented in our version with the name "Notify". It aims to print out the updated
 * information that the user may want to see. In our version, the information includes bus id,
 * Bus position, Passengers on bus and Bus capacity. And the details is in the file "web_code/web/BusWebObserver.cc"
 * ( \ref BusWebObserver). When observer was set up successfully, ISubject should be implemented as well so
 * that when the subject changes, it will notify its observers. ISubject is a base class that contains
 * three main member functions, RegisterObserver, ClearObserver and NotifyObservers. You can see the details
 * about them in "src/IObservable.cc" ( \ref IObservable). We use "IObservable" as the name of "ISubject".
 * RegisterObserver is called when a new observer needs to be connected with subject. ClearObservers method 
 * is called when mouse clicks on another subject(bus), we need to clear all the observers connected with the current
 * subject. NotifyObservers method calls Notify method in IObserver to notify every observer related to this subject.
 * Bus class is our subject in this project, so Bus class is inherited from IObservable class.
 * So everytime the bus is updated, which means it goes along the route in one timestemp, it will notify all
 * its observers by calling NotifyObservers method.
 * 
 * For front-end web page implementation, we first need to detect the mouse click. When mouse click on the bus, then
 * send the bus id to back end and start the observer pattern to track its update. This process is clear to show by 
 * the following Sequence Diagram.
 *
 * <img src="../UML_sequence_diag.jpeg" width="1200" height="800"/>
 * To detect the mouse clicked, there is a function called mapClick in sketch.js in web_graphics folder.
 * When detecting the mouse clicked, then it will send a request to JSON to attach observer with clicked bus. When
 * receive the request, it will call AddListenerCommand in my_web_server_command.cc in web_code/web folder to add
 * a observer. This is done by clearing listeners first, then add the busWebObserver to the corresponding bus with
 * its id. In VisualizationSimulator, ClearListeners and AddListener method are added to implement the procedure
 * above.
 * 
 * \subsection diff_tips The Most Difficult Part and Tips on Understanding them
 * The most difficult part is building the observer pattern. There are aggregation and inheritence showing
 * in the same pattern, which may make it harder to understand. You may need to see the UML above to help
 * you understand how the IObserver and Iobseravle works. More details can be found in Lab 14 description.
 * Their relationship is complex, if you still feel confused, then take a look at the additional resources.
 * https://www.geeksforgeeks.org/observer-pattern-set-1-introduction/ 
 * And some example code can be found in the below link.
 * https://sourcemaking.com/design_patterns/observer/cpp/3 
 *
 * \section dec_p Designing and Implementing the Decorator Pattern
 *
 * \subsection my_dec_p My Implementation Version
 *
 * My implementation is shown as the UML below.
 * <img src="../decorator1.png" alt="My Implementation for Decorator Pattern" width="800" height="600"/>
 * In my implementation of decorator pattern, I implement an interface(contains all pure virtual method) for bus
 * object, which calls IBus. Bus is inherited from IBus. Most of the methods in Bus are pure virtual in IBus.
 * 
 * Also, the concrete BusDecorator is inherited from IBus as well. In BusDecorator, I set up the color information based
 * on the bus information in GetBusData. When Bus is in the outgoing route, its color is set to red, and when it 
 * is in the incoming route, its color is set to yellow. The intensity of the color is determined by the number
 * of passengers in the bus. Everytime a bus is passed in as the parameter, the Update method may able to update its
 * information including its color and show it in the web server. To implement the run time decorator, I also 
 * change the code in VisualizationSimulator,
 * which may need to update the busdata every timestemp. To show the color in the web server, I update the busdata in 
 * the web server and send the information to the frontend.
 *
 * \subsection an_v Another Design Version
 *
 * Another version for designing and implementing the decorator pattern is shown as the UML below.
 * <img src="../decorator2.png" alt="Another Implementation for Decorator Pattern" width="800" height="600"/>
 * In this version, the BusDecorator is the parent class for BusColorDecorator and BusIntensityDecorator. The two
 * concrete decorator is inherited from the base class. This design seperates the two requirements for updating bus color.
 * Each child class implements one requirement. 
 * 
 * However, the IBus and other components design remain the same. 
 * 
 * \subsection ad_disad Advantages and Disadvantages for two design version
 *
 * These two design methods share a lot of similar advantages. They contain the same advantages of decorator pattern.
 * The first one is that "open for extension and closed for modification". They both can extend the decorator behavior
 * without modifying the existed code base. If in the future design, other decorate requirements are proposed, then
 * inheriting from the IBus or BusDecorator can fulfill the requirement. The second one is that they do not force
 * the users to implement any irrelevent interface. They can directly use the interface to fulfill their requirements.
 * The third advantage is that the decorator pattern is independent to the bus class. The users can expand the 
 * decorator without changing the bus code.
 *
 * The disadvantage of my implementation is that it combines the two requirements together. It does not follow
 * "single responsibility principle", which means that in the single class, it implements two separate things.
 * This violation may result in further inconvenient if the users only need one of them. However, in this iteration,
 * the implementation is okay and will not have any errors. This may be changed in the future.
 *
 * Comparing to my version, the advantage of the another version is that it follows the "single responsibility principle"
 * which means that it uses two separate concrete classes to implement the decorator requirements. This is convinient
 * for users to use the interface and expand their own version of decorator. They can only use one of the classes to
 * fulfill their requirements without changing the whole decorator base code.
 * 
 * The disadvantage of the version that I do not implement is that it requires more efforts to code and maintain. It
 * may need two more classes to code and two more classes to maintain. If the base class(BusDecorator) changes, then
 * the following two child classes also need to be cared. Also, it may be too complicated to instantiate the component.
 * When you instantiate the bus, you need to wrap with different decorators. 
 * 
 * \subsection tips Tips on Understanding the Pattern
 * 
 * The most difficult part in this implementation is that we are required to use decorator pattern. The concrete decorator
 * class is hard to understand its behavior and which method should be included in this class. I got some idea from the 
 * lecture examples. https://canvas.umn.edu/courses/157639/files/12391609?module_item_id=3804851 
 * Other useful links for implementing decorator pattern:
 * https://www.geeksforgeeks.org/the-decorator-pattern-set-2-introduction-and-design/ 
 * 
 */
#endif  // SRC_MAINPAGE_H_
