/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001,2002 Russell L. Smith.       *
 * All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file LICENSE.TXT.                                               *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file LICENSE-BSD.TXT.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
 *                                                                       *
 *************************************************************************/

#ifndef _ODE_OBJECTS_H_
#define _ODE_OBJECTS_H_

#include <ode/common.h>
#include <ode/mass.h>
#include <ode/contact.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup world World
 *
 * The world object is a container for rigid bodies and joints. Objects in 
 * different worlds can not interact, for example rigid bodies from two 
 * different worlds can not collide.
 *
 * All the objects in a world exist at the same point in time, thus one 
 * reason to use separate worlds is to simulate systems at different rates.
 * Most applications will only need one world. 
 */


/**
 * @brief Create a new, empty world and return its ID number.
 * @ingroup world
 */
ODE_API dWorldID dWorldCreate(void);


/**
 * @brief Destroy a world and everything in it. 
 *
 * This includes all bodies, and all joints that are not part of a joint 
 * group. Joints that are part of a joint group will be deactivated, and 
 * can be destroyed by calling, for example, dJointGroupEmpty().
 * @ingroup world
 * @param dWorldID the identifier for the world the be destroyed.
 */
ODE_API void dWorldDestroy (dWorldID);


/**
 * @brief Set the world's global gravity vector. 
 *
 * The units are m/s^2, so Earth's gravity vector would be (0,0,-9.81), 
 * assuming that +z is up. The default is no gravity, i.e. (0,0,0).
 *
 * @ingroup world
 */
ODE_API void dWorldSetGravity (dWorldID, dReal x, dReal y, dReal z);


/**
 * @brief Get the gravity vector for a given world.
 * @ingroup world
 */
ODE_API void dWorldGetGravity (dWorldID, dVector3 gravity);


/**
 * @brief Set the global ERP value, that controls how much error 
 * correction is performed in each time step.
 * @ingroup world
 * @param dWorldID the identifier of the world.
 * @param erp Typical values are in the range 0.1--0.8. The default is 0.2.
 */
ODE_API void dWorldSetERP (dWorldID, dReal erp);

/**
 * @brief Get the error reduction parameter.
 * @ingroup world
 */
ODE_API dReal dWorldGetERP (dWorldID);


/**
 * @brief Set the global CFM (constraint force mixing) value.
 * @ingroup world
 * @param cfm Typical values are in the range @m{10^{-9}} -- 1.
 * The default is 10^-5 if single precision is being used, or 10^-10
 * if double precision is being used.
 */
ODE_API void dWorldSetCFM (dWorldID, dReal cfm);

/**
 * @brief Get the constraint force mixing value.
 * @ingroup world
 */
ODE_API dReal dWorldGetCFM (dWorldID);


/**
 * @brief Step the world.
 *
 * This uses a "big matrix" method that takes time on the order of m^3
 * and memory on the order of m^2, where m is the total number of constraint 
 * rows. For large systems this will use a lot of memory and can be very slow,
 * but this is currently the most accurate method.
 * @ingroup world
 * @param stepsize The number of seconds that the simulation has to advance.
 */
ODE_API void dWorldStep (dWorldID, dReal stepsize);


/**
 * @brief Converts an impulse to a force.
 * @ingroup world
 * @remarks
 * If you want to apply a linear or angular impulse to a rigid body,
 * instead of a force or a torque, then you can use this function to convert
 * the desired impulse into a force/torque vector before calling the
 * BodyAdd... function.
 * The current algorithm simply scales the impulse by 1/stepsize,
 * where stepsize is the step size for the next step that will be taken.
 * This function is given a dWorldID because, in the future, the force
 * computation may depend on integrator parameters that are set as
 * properties of the world.
 */
ODE_API void dWorldImpulseToForce 
(
  dWorldID, dReal stepsize,
  dReal ix, dReal iy, dReal iz, dVector3 force
);


/**
 * @brief Step the world.
 * @ingroup world
 * @remarks
 * This uses an iterative method that takes time on the order of m*N
 * and memory on the order of m, where m is the total number of constraint 
 * rows N is the number of iterations.
 * For large systems this is a lot faster than dWorldStep(),
 * but it is less accurate.
 * @remarks
 * QuickStep is great for stacks of objects especially when the 
 * auto-disable feature is used as well.
 * However, it has poor accuracy for near-singular systems.
 * Near-singular systems can occur when using high-friction contacts, motors,
 * or certain articulated structures. For example, a robot with multiple legs
 * sitting on the ground may be near-singular.
 * @remarks
 * There are ways to help overcome QuickStep's inaccuracy problems:
 * \li Increase CFM.
 * \li Reduce the number of contacts in your system (e.g. use the minimum
 *     number of contacts for the feet of a robot or creature).
 * \li Don't use excessive friction in the contacts. 
 * \li Use contact slip if appropriate
 * \li Avoid kinematic loops (however, kinematic loops are inevitable in
 *     legged creatures).
 * \li Don't use excessive motor strength.
 * \liUse force-based motors instead of velocity-based motors.
 *
 * Increasing the number of QuickStep iterations may help a little bit, but
 * it is not going to help much if your system is really near singular.
 */
ODE_API void dWorldQuickStep (dWorldID w, dReal stepsize);


/**
 * @brief Set the number of iterations that the QuickStep method performs per
 *        step.
 * @ingroup world
 * @remarks
 * More iterations will give a more accurate solution, but will take 
 * longer to compute.
 * @param num The default is 20 iterations.
 */
ODE_API void dWorldSetQuickStepNumIterations (dWorldID, int num);


/**
 * @brief Get the number of iterations that the QuickStep method performs per
 *        step.
 * @ingroup world
 */
ODE_API int dWorldGetQuickStepNumIterations (dWorldID);

/**
 * @brief Set the SOR over-relaxation parameter
 * @ingroup world
 */
ODE_API void dWorldSetQuickStepW (dWorldID, dReal param);

/**
 * @brief Get the SOR over-relaxation parameter
 * @ingroup world
 */
ODE_API dReal dWorldGetQuickStepW (dWorldID);

/* World contact parameter functions */

/**
 * @brief Set the maximum correcting velocity that contacts are allowed 
 * to generate.
 * @ingroup world
 * @param vel The default value is infinity (i.e. no limit).
 * @remarks
 * Reducing this value can help prevent "popping" of deeply embedded objects.
 */
ODE_API void dWorldSetContactMaxCorrectingVel (dWorldID, dReal vel);

/**
 * @brief Get the maximum correcting velocity that contacts are allowed
 * to generated.
 * @ingroup world
 */
ODE_API dReal dWorldGetContactMaxCorrectingVel (dWorldID);

/**
 * @brief Set the depth of the surface layer around all geometry objects.
 * @ingroup world
 * @remarks
 * Contacts are allowed to sink into the surface layer up to the given
 * depth before coming to rest.
 * @param depth The default value is zero.
 * @remarks 
 * Increasing this to some small value (e.g. 0.001) can help prevent 
 * jittering problems due to contacts being repeatedly made and broken.
 */
ODE_API void dWorldSetContactSurfaceLayer (dWorldID, dReal depth);

/**
 * @brief Get the depth of the surface layer around all geometry objects.
 * @ingroup world
 */
ODE_API dReal dWorldGetContactSurfaceLayer (dWorldID);

/* StepFast1 functions */

/**
 * @brief Step the world using the StepFast1 algorithm.
 * @param stepsize the nr of seconds to advance the simulation.
 * @param maxiterations The number of iterations to perform.
 * @ingroup world
 */
ODE_API void dWorldStepFast1(dWorldID, dReal stepsize, int maxiterations);


/**
 * @defgroup disable Automatic Enabling and Disabling
 *
 * Every body can be enabled or disabled. Enabled bodies participate in the 
 * simulation, while disabled bodies are turned off and do not get updated 
 * during a simulation step. New bodies are always created in the enabled state.
 *
 * A disabled body that is connected through a joint to an enabled body will be 
 * automatically re-enabled at the next simulation step.
 *
 * Disabled bodies do not consume CPU time, therefore to speed up the simulation 
 * bodies should be disabled when they come to rest. This can be done automatically 
 * with the auto-disable feature.
 *
 * If a body has its auto-disable flag turned on, it will automatically disable 
 * itself when
 *   @li It has been idle for a given number of simulation steps.
 *   @li It has also been idle for a given amount of simulation time. 
 *
 * A body is considered to be idle when the magnitudes of both its linear velocity 
 * and angular velocity are below given thresholds.
 *
 * Thus, every body has five auto-disable parameters: an enabled flag, a idle step 
 * count, an idle time, and linear/angular velocity thresholds. Newly created bodies 
 * get these parameters from world.
 */

/**
 * @brief Set the AutoEnableDepth parameter used by the StepFast1 algorithm.
 * @ingroup disable
 */
ODE_API void dWorldSetAutoEnableDepthSF1(dWorldID, int autoEnableDepth);

/**
 * @brief Get the AutoEnableDepth parameter used by the StepFast1 algorithm.
 * @ingroup disable
 */
ODE_API int dWorldGetAutoEnableDepthSF1(dWorldID);

/**
 * @brief Get auto disable linear threshold for newly created bodies.
 * @ingroup disable
 */
ODE_API dReal dWorldGetAutoDisableLinearThreshold (dWorldID);

/**
 * @brief Set auto disable linear threshold for newly created bodies.
 * @param linear_threshold default is 0.01
 * @ingroup disable
 */
ODE_API void  dWorldSetAutoDisableLinearThreshold (dWorldID, dReal linear_threshold);

/**
 * @brief Get auto disable angular threshold for newly created bodies.
 * @ingroup disable
 */
ODE_API dReal dWorldGetAutoDisableAngularThreshold (dWorldID);

/**
 * @brief Set auto disable angular threshold for newly created bodies.
 * @param linear_threshold default is 0.01
 * @ingroup disable
 */
ODE_API void  dWorldSetAutoDisableAngularThreshold (dWorldID, dReal angular_threshold);

/**
 * @brief Get auto disable steps for newly created bodies.
 * @ingroup disable
 */
ODE_API int   dWorldGetAutoDisableSteps (dWorldID);

/**
 * @brief Set auto disable steps for newly created bodies.
 * @ingroup disable
 * @param steps default is 10
 */
ODE_API void  dWorldSetAutoDisableSteps (dWorldID, int steps);

/**
 * @brief Get auto disable time for newly created bodies.
 * @ingroup disable
 */
ODE_API dReal dWorldGetAutoDisableTime (dWorldID);

/**
 * @brief Set auto disable time for newly created bodies.
 * @ingroup disable
 * @param time default is 0 seconds
 */
ODE_API void  dWorldSetAutoDisableTime (dWorldID, dReal time);

/**
 * @brief Get auto disable flag for newly created bodies.
 * @ingroup disable
 */
ODE_API int   dWorldGetAutoDisableFlag (dWorldID);

/**
 * @brief Set auto disable flag for newly created bodies.
 * @ingroup disable
 * @param do_auto_disable default is false.
 */
ODE_API void  dWorldSetAutoDisableFlag (dWorldID, int do_auto_disable);



/**
 * @defgroup bodies Rigid Bodies
 *
 * A rigid body has various properties from the point of view of the 
 * simulation. Some properties change over time:
 *
 *  @li Position vector (x,y,z) of the body's point of reference. 
 *      Currently the point of reference must correspond to the body's center of mass.
 *  @li Linear velocity of the point of reference, a vector (vx,vy,vz).
 *  @li Orientation of a body, represented by a quaternion (qs,qx,qy,qz) or 
 *      a 3x3 rotation matrix.
 *  @li Angular velocity vector (wx,wy,wz) which describes how the orientation 
 *      changes over time. 
 *
 * Other body properties are usually constant over time:
 *
 *  @li Mass of the body.
 *  @li Position of the center of mass with respect to the point of reference. 
 *      In the current implementation the center of mass and the point of 
 *      reference must coincide.
 *  @li Inertia matrix. This is a 3x3 matrix that describes how the body's mass 
 *      is distributed around the center of mass. Conceptually each body has an 
 *      x-y-z coordinate frame embedded in it that moves and rotates with the body.
 *
 * The origin of this coordinate frame is the body's point of reference. Some values 
 * in ODE (vectors, matrices etc) are relative to the body coordinate frame, and others 
 * are relative to the global coordinate frame.
 *
 * Note that the shape of a rigid body is not a dynamical property (except insofar as 
 * it influences the various mass properties). It is only collision detection that cares 
 * about the detailed shape of the body. 
 */


/**
 * @brief Get auto disable linear threshold.
 * @ingroup bodies
 */
ODE_API dReal dBodyGetAutoDisableLinearThreshold (dBodyID);

/**
 * @brief Set auto disable linear threshold.
 * @ingroup bodies
 */
ODE_API void  dBodySetAutoDisableLinearThreshold (dBodyID, dReal linear_threshold);

/**
 * @brief Get auto disable angular threshold.
 * @ingroup bodies
 */
ODE_API dReal dBodyGetAutoDisableAngularThreshold (dBodyID);

/**
 * @brief Set auto disable angular threshold.
 * @ingroup bodies
 */
ODE_API void  dBodySetAutoDisableAngularThreshold (dBodyID, dReal angular_threshold);

/**
 * @brief Get auto disable steps.
 * @ingroup bodies
 */
ODE_API int   dBodyGetAutoDisableSteps (dBodyID);

/**
 * @brief Set auto disable steps.
 * @ingroup bodies
 */
ODE_API void  dBodySetAutoDisableSteps (dBodyID, int steps);

/**
 * @brief Get auto disable time.
 * @ingroup bodies
 */
ODE_API dReal dBodyGetAutoDisableTime (dBodyID);

/**
 * @brief Set auto disable time.
 * @ingroup bodies
 */
ODE_API void  dBodySetAutoDisableTime (dBodyID, dReal time);

/**
 * @brief Get auto disable flag.
 * @ingroup bodies
 */
ODE_API int   dBodyGetAutoDisableFlag (dBodyID);

/**
 * @brief Set auto disable flag.
 * @ingroup bodies
 */
ODE_API void  dBodySetAutoDisableFlag (dBodyID, int do_auto_disable);

/**
 * @brief Set auto disable defaults.
 * @ingroup bodies
 */
ODE_API void  dBodySetAutoDisableDefaults (dBodyID);



/**
 * @brief Create a body in given world.
 * @remarks
 * Default mass parameters are at position (0,0,0).
 * @ingroup bodies
 */
ODE_API dBodyID dBodyCreate (dWorldID);

/**
 * @brief Destroy a body.
 * @remarks
 * All joints that are attached to this body will be put into limbo:
 * i.e. unattached and not affecting the simulation, but they will NOT be
 * deleted.
 * @ingroup bodies
 */
ODE_API void dBodyDestroy (dBodyID);

/**
 * @brief Set the body's user-data pointer.
 * @ingroup bodies
 */
ODE_API void  dBodySetData (dBodyID, void *data);

/**
 * @brief Get the body's user-data pointer.
 * @ingroup bodies
 */
ODE_API void *dBodyGetData (dBodyID);

/**
 * @brief Set position of a body.
 * @remarks 
 * After setting, the outcome of the simulation is undefined
 * if the new configuration is inconsistent with the joints/constraints 
 * that are present.
 * @ingroup bodies
 */
ODE_API void dBodySetPosition   (dBodyID, dReal x, dReal y, dReal z);

/**
 * @brief Set the orientation of a body.
 * @ingroup bodies
 * @remarks 
 * After setting, the outcome of the simulation is undefined
 * if the new configuration is inconsistent with the joints/constraints 
 * that are present.
 */
ODE_API void dBodySetRotation   (dBodyID, const dMatrix3 R);

/**
 * @brief Set the orientation of a body.
 * @ingroup bodies
 * @remarks 
 * After setting, the outcome of the simulation is undefined
 * if the new configuration is inconsistent with the joints/constraints 
 * that are present.
 */
ODE_API void dBodySetQuaternion (dBodyID, const dQuaternion q);

/**
 * @brief Set the linear velocity of a body.
 * @ingroup bodies
 */
ODE_API void dBodySetLinearVel  (dBodyID, dReal x, dReal y, dReal z);

/**
 * @brief Set the angular velocity of a body.
 * @ingroup bodies
 */
ODE_API void dBodySetAngularVel (dBodyID, dReal x, dReal y, dReal z);

/**
 * @brief Get the position of a body.
 * @ingroup bodies
 * @remarks
 * When getting, the returned values are pointers to internal data structures,
 * so the vectors are valid until any changes are made to the rigid body 
 * system structure.
 */
ODE_API const dReal * dBodyGetPosition   (dBodyID);

/**
 * @brief Get the rotation of a body.
 * @ingroup bodies
 * @return pointer to a 4x3 rotation matrix.
 */
ODE_API const dReal * dBodyGetRotation   (dBodyID);

/**
 * @brief Get the rotation of a body.
 * @ingroup bodies
 * @return pointer to 4 scalars that represent the quaternion.
 */
ODE_API const dReal * dBodyGetQuaternion (dBodyID);

/**
 * @brief Get the linear velocity of a body.
 * @ingroup bodies
 */
ODE_API const dReal * dBodyGetLinearVel  (dBodyID);

/**
 * @brief Get the angular velocity of a body.
 * @ingroup bodies
 */
ODE_API const dReal * dBodyGetAngularVel (dBodyID);

/**
 * @brief Set the mass of a body.
 * @ingroup bodies
 */
ODE_API void dBodySetMass (dBodyID, const dMass *mass);

/**
 * @brief Get the mass of a body.
 * @ingroup bodies
 */
ODE_API void dBodyGetMass (dBodyID, dMass *mass);

/**
 * @brief Add force at centre of mass of body in absolute coordinates.
 * @ingroup bodies
 */
ODE_API void dBodyAddForce            (dBodyID, dReal fx, dReal fy, dReal fz);

/**
 * @brief Add torque at centre of mass of body in absolute coordinates.
 * @ingroup bodies
 */
ODE_API void dBodyAddTorque           (dBodyID, dReal fx, dReal fy, dReal fz);

/**
 * @brief Add force at centre of mass of body in coordinates relative to body.
 * @ingroup bodies
 */
ODE_API void dBodyAddRelForce         (dBodyID, dReal fx, dReal fy, dReal fz);

/**
 * @brief Add torque at centre of mass of body in coordinates relative to body.
 * @ingroup bodies
 */
ODE_API void dBodyAddRelTorque        (dBodyID, dReal fx, dReal fy, dReal fz);

/**
 * @brief Add force at specified point in body in global coordinates.
 * @ingroup bodies
 */
ODE_API void dBodyAddForceAtPos       (dBodyID, dReal fx, dReal fy, dReal fz,
			                dReal px, dReal py, dReal pz);
/**
 * @brief Add force at specified point in body in local coordinates.
 * @ingroup bodies
 */
ODE_API void dBodyAddForceAtRelPos    (dBodyID, dReal fx, dReal fy, dReal fz,
			                dReal px, dReal py, dReal pz);
/**
 * @brief Add force at specified point in body in global coordinates.
 * @ingroup bodies
 */
ODE_API void dBodyAddRelForceAtPos    (dBodyID, dReal fx, dReal fy, dReal fz,
			                dReal px, dReal py, dReal pz);
/**
 * @brief Add force at specified point in body in local coordinates.
 * @ingroup bodies
 */
ODE_API void dBodyAddRelForceAtRelPos (dBodyID, dReal fx, dReal fy, dReal fz,
			                dReal px, dReal py, dReal pz);

/**
 * @brief Return the current accumulated force vector.
 * @return points to an array of 3 reals.
 * @remarks 
 * The returned values are pointers to internal data structures, so 
 * the vectors are only valid until any changes are made to the rigid 
 * body system.
 * @ingroup bodies
 */
ODE_API const dReal * dBodyGetForce   (dBodyID);

/**
 * @brief Return the current accumulated torque vector.
 * @return points to an array of 3 reals.
 * @remarks 
 * The returned values are pointers to internal data structures, so 
 * the vectors are only valid until any changes are made to the rigid 
 * body system.
 * @ingroup bodies
 */
ODE_API const dReal * dBodyGetTorque  (dBodyID);

/**
 * @brief Set the body force accumulation vector.
 * @remarks 
 * This is mostly useful to zero the force and torque for deactivated bodies
 * before they are reactivated, in the case where the force-adding functions
 * were called on them while they were deactivated.
 * @ingroup bodies
 */
ODE_API void dBodySetForce  (dBodyID b, dReal x, dReal y, dReal z);

/**
 * @brief Set the body torque accumulation vector.
 * @remarks 
 * This is mostly useful to zero the force and torque for deactivated bodies
 * before they are reactivated, in the case where the force-adding functions
 * were called on them while they were deactivated.
 * @ingroup bodies
 */
ODE_API void dBodySetTorque (dBodyID b, dReal x, dReal y, dReal z);

/**
 * @brief Get world position of a relative point on body.
 * @ingroup bodies
 * @param result will contain the result.
 */
ODE_API void dBodyGetRelPointPos 
(
  dBodyID, dReal px, dReal py, dReal pz,
  dVector3 result
);

/**
 * @brief Get velocity vector in global coords of a relative point on body.
 * @ingroup bodies
 * @param result will contain the result.
 */
ODE_API void dBodyGetRelPointVel
(
  dBodyID, dReal px, dReal py, dReal pz,
  dVector3 result
);

/**
 * @brief Get velocity vector in global coords of a globally 
 * specified point on a body.
 * @ingroup bodies
 * @param result will contain the result.
 */
ODE_API void dBodyGetPointVel
(
  dBodyID, dReal px, dReal py, dReal pz,
  dVector3 result
);

/**
 * @brief takes a point in global coordinates and returns
 * the point's position in body-relative coordinates.
 * @remarks
 * This is the inverse of dBodyGetRelPointPos()
 * @ingroup bodies
 * @param result will contain the result.
 */
ODE_API void dBodyGetPosRelPoint 
(
  dBodyID, dReal px, dReal py, dReal pz,
  dVector3 result
);

/**
 * @brief Convert from local to world coordinates.
 * @ingroup bodies
 * @param result will contain the result.
 */
ODE_API void dBodyVectorToWorld
(
  dBodyID, dReal px, dReal py, dReal pz,
  dVector3 result
);

/**
 * @brief Convert from world to local coordinates.
 * @ingroup bodies
 * @param result will contain the result.
 */
ODE_API void dBodyVectorFromWorld 
(
  dBodyID, dReal px, dReal py, dReal pz,
  dVector3 result
);

/**
 * @brief controls the way a body's orientation is updated at each timestep.
 * @ingroup bodies
 * @param mode can be 0 or 1:
 * \li 0: An ``infinitesimal'' orientation update is used.
 * This is fast to compute, but it can occasionally cause inaccuracies
 * for bodies that are rotating at high speed, especially when those
 * bodies are joined to other bodies.
 * This is the default for every new body that is created.
 * \li 1: A ``finite'' orientation update is used.
 * This is more costly to compute, but will be more accurate for high
 * speed rotations.
 * @remarks
 * Note however that high speed rotations can result in many types of
 * error in a simulation, and the finite mode will only fix one of those
 * sources of error.
 */
ODE_API void dBodySetFiniteRotationMode (dBodyID, int mode);

/**
 * @brief sets the finite rotation axis for a body.
 * @ingroup bodies
 * @remarks
 * This is axis only has meaning when the finite rotation mode is set
 * If this axis is zero (0,0,0), full finite rotations are performed on 
 * the body.
 * If this axis is nonzero, the body is rotated by performing a partial finite
 * rotation along the axis direction followed by an infinitesimal rotation 
 * along an orthogonal direction.
 * @remarks
 * This can be useful to alleviate certain sources of error caused by quickly
 * spinning bodies. For example, if a car wheel is rotating at high speed
 * you can call this function with the wheel's hinge axis as the argument to
 * try and improve its behavior.
 */
ODE_API void dBodySetFiniteRotationAxis (dBodyID, dReal x, dReal y, dReal z);

/**
 * @brief Get the way a body's orientation is updated each timestep.
 * @ingroup bodies
 * @return the mode 0 (infitesimal) or 1 (finite).
 */
ODE_API int dBodyGetFiniteRotationMode (dBodyID);

/**
 * @brief Get the finite rotation axis.
 * @param result will contain the axis.
 * @ingroup bodies
 */
ODE_API void dBodyGetFiniteRotationAxis (dBodyID, dVector3 result);

/**
 * @brief Get the number of joints that are attached to this body.
 * @ingroup bodies
 * @return nr of joints
 */
ODE_API int dBodyGetNumJoints (dBodyID b);

/**
 * @brief Return a joint attached to this body, given by index.
 * @ingroup bodies
 * @param index valid range is  0 to n-1 where n is the value returned by
 * dBodyGetNumJoints().
 */
ODE_API dJointID dBodyGetJoint (dBodyID, int index);

/**
 * @brief Manually enable a body.
 * @param dBodyID identification of body.
 * @ingroup bodies
 */
ODE_API void dBodyEnable (dBodyID);

/**
 * @brief Manually disable a body.
 * @ingroup bodies
 * @remarks
 * A disabled body that is connected through a joint to an enabled body will
 * be automatically re-enabled at the next simulation step.
 */
ODE_API void dBodyDisable (dBodyID);

/**
 * @brief Check wether a body is enabled.
 * @ingroup bodies
 * @return 1 if a body is currently enabled or 0 if it is disabled.
 */
ODE_API int dBodyIsEnabled (dBodyID);

/**
 * @brief Set whether the body is influenced by the world's gravity or not.
 * @ingroup bodies
 * @param mode when nonzero gravity affects this body.
 * @remarks
 * Newly created bodies are always influenced by the world's gravity.
 */
ODE_API void dBodySetGravityMode (dBodyID b, int mode);

/**
 * @brief Get whether the body is influenced by the world's gravity or not.
 * @ingroup bodies
 * @return nonzero means gravity affects this body.
 */
ODE_API int dBodyGetGravityMode (dBodyID b);




/**
 * @defgroup joints Joints
 *
 * In real life a joint is something like a hinge, that is used to connect two
 * objects.
 * In ODE a joint is very similar: It is a relationship that is enforced between
 * two bodies so that they can only have certain positions and orientations
 * relative to each other.
 * This relationship is called a constraint -- the words joint and
 * constraint are often used interchangeably.
 */


/**
 * @brief Create a new joint of the ball type.
 * @ingroup joints
 * @remarks
 * The joint is initially in "limbo" (i.e. it has no effect on the simulation)
 * because it does not connect to any bodies.
 * @param dJointGroupID set to 0 to allocate the joint normally.
 * If it is nonzero the joint is allocated in the given joint group.
 */
ODE_API dJointID dJointCreateBall (dWorldID, dJointGroupID);

/**
 * @brief Create a new joint of the hinge type.
 * @ingroup joints
 * @param dJointGroupID set to 0 to allocate the joint normally.
 * If it is nonzero the joint is allocated in the given joint group.
 */
ODE_API dJointID dJointCreateHinge (dWorldID, dJointGroupID);

/**
 * @brief Create a new joint of the slider type.
 * @ingroup joints
 * @param dJointGroupID set to 0 to allocate the joint normally.
 * If it is nonzero the joint is allocated in the given joint group.
 */
ODE_API dJointID dJointCreateSlider (dWorldID, dJointGroupID);

/**
 * @brief Create a new joint of the contact type.
 * @ingroup joints
 * @param dJointGroupID set to 0 to allocate the joint normally.
 * If it is nonzero the joint is allocated in the given joint group.
 */
ODE_API dJointID dJointCreateContact (dWorldID, dJointGroupID, const dContact *);

/**
 * @brief Create a new joint of the hinge2 type.
 * @ingroup joints
 * @param dJointGroupID set to 0 to allocate the joint normally.
 * If it is nonzero the joint is allocated in the given joint group.
 */
ODE_API dJointID dJointCreateHinge2 (dWorldID, dJointGroupID);

/**
 * @brief Create a new joint of the universal type.
 * @ingroup joints
 * @param dJointGroupID set to 0 to allocate the joint normally.
 * If it is nonzero the joint is allocated in the given joint group.
 */
ODE_API dJointID dJointCreateUniversal (dWorldID, dJointGroupID);

/**
 * @brief Create a new joint of the fixed type.
 * @ingroup joints
 * @param dJointGroupID set to 0 to allocate the joint normally.
 * If it is nonzero the joint is allocated in the given joint group.
 */
ODE_API dJointID dJointCreateFixed (dWorldID, dJointGroupID);

ODE_API dJointID dJointCreateNull (dWorldID, dJointGroupID);

/**
 * @brief Create a new joint of the A-motor type.
 * @ingroup joints
 * @param dJointGroupID set to 0 to allocate the joint normally.
 * If it is nonzero the joint is allocated in the given joint group.
 */
ODE_API dJointID dJointCreateAMotor (dWorldID, dJointGroupID);

/**
 * @brief Create a new joint of the L-motor type.
 * @ingroup joints
 * @param dJointGroupID set to 0 to allocate the joint normally.
 * If it is nonzero the joint is allocated in the given joint group.
 */
ODE_API dJointID dJointCreateLMotor (dWorldID, dJointGroupID);


/**
 * @brief Destroy a joint.
 * @ingroup joints
 *
 * disconnects it from its attached bodies and removing it from the world.
 * However, if the joint is a member of a group then this function has no
 * effect - to destroy that joint the group must be emptied or destroyed.
 */
ODE_API void dJointDestroy (dJointID);


/**
 * @brief Create a joint group
 * @ingroup joints
 * @param max_size deprecated. Set to 0.
 */
ODE_API dJointGroupID dJointGroupCreate (int max_size);

/**
 * @brief Destroy a joint group.
 * @ingroup joints
 * 
 * All joints in the joint group will be destroyed.
 */
ODE_API void dJointGroupDestroy (dJointGroupID);

/**
 * @brief Empty a joint group.
 * @ingroup joints
 *
 * All joints in the joint group will be destroyed,
 * but the joint group itself will not be destroyed.
 */
ODE_API void dJointGroupEmpty (dJointGroupID);

/**
 * @brief Attach the joint to some new bodies.
 * @ingroup joints
 *
 * If the joint is already attached, it will be detached from the old bodies
 * first.
 * To attach this joint to only one body, set body1 or body2 to zero - a zero
 * body refers to the static environment.
 * Setting both bodies to zero puts the joint into "limbo", i.e. it will
 * have no effect on the simulation.
 * @remarks
 * Some joints, like hinge-2 need to be attached to two bodies to work.
 */
ODE_API void dJointAttach (dJointID, dBodyID body1, dBodyID body2);

/**
 * @brief Set the user-data pointer
 * @ingroup joints
 */
ODE_API void dJointSetData (dJointID, void *data);

/**
 * @brief Get the user-data pointer
 * @ingroup joints
 */
ODE_API void *dJointGetData (dJointID);

/**
 * @brief Get the type of the joint
 * @ingroup joints
 * @return the type, being one of these:
 * \li JointTypeBall
 * \li JointTypeHinge
 * \li JointTypeSlider
 * \li JointTypeContact
 * \li JointTypeUniversal
 * \li JointTypeHinge2
 * \li JointTypeFixed
 * \li JointTypeAMotor
 * \li JointTypeLMotor
 */
ODE_API int dJointGetType (dJointID);

/**
 * @brief Return the bodies that this joint connects.
 * @ingroup joints
 * @param index return the first (0) or second (1) body.
 * @remarks
 * If one of these returned body IDs is zero, the joint connects the other body
 * to the static environment.
 * If both body IDs are zero, the joint is in ``limbo'' and has no effect on
 * the simulation.
 */
ODE_API dBodyID dJointGetBody (dJointID, int index);

/**
 * @brief Sets the datastructure that is to receive the feedback.
 *
 * The feedback can be used by the user, so that it is known how
 * much force an individual joint exerts. 
 * @ingroup joints
 */
ODE_API void dJointSetFeedback (dJointID, dJointFeedback *);

/**
 * @brief Gets the datastructure that is to receive the feedback.
 * @ingroup joints
 */
ODE_API dJointFeedback *dJointGetFeedback (dJointID);

/** 
 * @brief Set the joint anchor point. 
 * @ingroup joints
 *
 * The joint will try to keep this point on each body
 * together. The input is specified in world coordinates.
 */
ODE_API void dJointSetBallAnchor (dJointID, dReal x, dReal y, dReal z);

ODE_API void dJointSetBallAnchor2 (dJointID, dReal x, dReal y, dReal z);

/**
 * @brief Set hinge anchor parameter.
 * @ingroup joints
 */
ODE_API void dJointSetHingeAnchor (dJointID, dReal x, dReal y, dReal z);

ODE_API void dJointSetHingeAnchorDelta (dJointID, dReal x, dReal y, dReal z, dReal ax, dReal ay, dReal az);

/**
 * @brief Set hinge axis parameter.
 * @ingroup joints
 */
ODE_API void dJointSetHingeAxis (dJointID, dReal x, dReal y, dReal z);

ODE_API void dJointSetHingeParam (dJointID, int parameter, dReal value);

ODE_API void dJointAddHingeTorque(dJointID joint, dReal torque);

ODE_API void dJointSetSliderAxis (dJointID, dReal x, dReal y, dReal z);

ODE_API void dJointSetSliderAxisDelta (dJointID, dReal x, dReal y, dReal z, dReal ax, dReal ay, dReal az);

ODE_API void dJointSetSliderParam (dJointID, int parameter, dReal value);

ODE_API void dJointAddSliderForce(dJointID joint, dReal force);

ODE_API void dJointSetHinge2Anchor (dJointID, dReal x, dReal y, dReal z);

ODE_API void dJointSetHinge2Axis1 (dJointID, dReal x, dReal y, dReal z);

ODE_API void dJointSetHinge2Axis2 (dJointID, dReal x, dReal y, dReal z);

ODE_API void dJointSetHinge2Param (dJointID, int parameter, dReal value);

ODE_API void dJointAddHinge2Torques(dJointID joint, dReal torque1, dReal torque2);
ODE_API void dJointSetUniversalAnchor (dJointID, dReal x, dReal y, dReal z);

ODE_API void dJointSetUniversalAxis1 (dJointID, dReal x, dReal y, dReal z);

ODE_API void dJointSetUniversalAxis2 (dJointID, dReal x, dReal y, dReal z);

ODE_API void dJointSetUniversalParam (dJointID, int parameter, dReal value);

ODE_API void dJointAddUniversalTorques(dJointID joint, dReal torque1, dReal torque2);
ODE_API void dJointSetFixed (dJointID);

ODE_API void dJointSetAMotorNumAxes (dJointID, int num);

ODE_API void dJointSetAMotorAxis (dJointID, int anum, int rel,
			  dReal x, dReal y, dReal z);

ODE_API void dJointSetAMotorAngle (dJointID, int anum, dReal angle);

ODE_API void dJointSetAMotorParam (dJointID, int parameter, dReal value);

ODE_API void dJointSetAMotorMode (dJointID, int mode);

ODE_API void dJointAddAMotorTorques (dJointID, dReal torque1, dReal torque2, dReal torque3);

ODE_API void dJointSetLMotorNumAxes (dJointID, int num);

ODE_API void dJointSetLMotorAxis (dJointID, int anum, int rel, dReal x, dReal y, dReal z);

ODE_API void dJointSetLMotorParam (dJointID, int parameter, dReal value);

/**
 * @brief Get the joint anchor point, in world coordinates.
 *
 * This returns the point on body 1. If the joint is perfectly satisfied, 
 * this will be the same as the point on body 2.
 */
ODE_API void dJointGetBallAnchor (dJointID, dVector3 result);

/**
 * @brief Get the joint anchor point, in world coordinates.
 *
 * This returns the point on body 2. You can think of a ball and socket 
 * joint as trying to keep the result of dJointGetBallAnchor() and 
 * dJointGetBallAnchor2() the same.  If the joint is perfectly satisfied,
 * this function will return the same value as dJointGetBallAnchor() to
 * within roundoff errors. dJointGetBallAnchor2() can be used, along with 
 * dJointGetBallAnchor(), to see how far the joint has come apart.
 */
ODE_API void dJointGetBallAnchor2 (dJointID, dVector3 result);

ODE_API void dJointGetHingeAnchor (dJointID, dVector3 result);
ODE_API void dJointGetHingeAnchor2 (dJointID, dVector3 result);
ODE_API void dJointGetHingeAxis (dJointID, dVector3 result);
ODE_API dReal dJointGetHingeParam (dJointID, int parameter);
ODE_API dReal dJointGetHingeAngle (dJointID);
ODE_API dReal dJointGetHingeAngleRate (dJointID);
ODE_API dReal dJointGetSliderPosition (dJointID);
ODE_API dReal dJointGetSliderPositionRate (dJointID);
ODE_API void dJointGetSliderAxis (dJointID, dVector3 result);
ODE_API dReal dJointGetSliderParam (dJointID, int parameter);
ODE_API void dJointGetHinge2Anchor (dJointID, dVector3 result);
ODE_API void dJointGetHinge2Anchor2 (dJointID, dVector3 result);
ODE_API void dJointGetHinge2Axis1 (dJointID, dVector3 result);
ODE_API void dJointGetHinge2Axis2 (dJointID, dVector3 result);
ODE_API dReal dJointGetHinge2Param (dJointID, int parameter);
ODE_API dReal dJointGetHinge2Angle1 (dJointID);
ODE_API dReal dJointGetHinge2Angle1Rate (dJointID);
ODE_API dReal dJointGetHinge2Angle2Rate (dJointID);
ODE_API void dJointGetUniversalAnchor (dJointID, dVector3 result);
ODE_API void dJointGetUniversalAnchor2 (dJointID, dVector3 result);
ODE_API void dJointGetUniversalAxis1 (dJointID, dVector3 result);
ODE_API void dJointGetUniversalAxis2 (dJointID, dVector3 result);
ODE_API dReal dJointGetUniversalParam (dJointID, int parameter);
ODE_API dReal dJointGetUniversalAngle1 (dJointID);
ODE_API dReal dJointGetUniversalAngle2 (dJointID);
ODE_API dReal dJointGetUniversalAngle1Rate (dJointID);
ODE_API dReal dJointGetUniversalAngle2Rate (dJointID);
ODE_API int dJointGetAMotorNumAxes (dJointID);
ODE_API void dJointGetAMotorAxis (dJointID, int anum, dVector3 result);
ODE_API int dJointGetAMotorAxisRel (dJointID, int anum);
ODE_API dReal dJointGetAMotorAngle (dJointID, int anum);
ODE_API dReal dJointGetAMotorAngleRate (dJointID, int anum);
ODE_API dReal dJointGetAMotorParam (dJointID, int parameter);
ODE_API int dJointGetAMotorMode (dJointID);
ODE_API int dJointGetLMotorNumAxes (dJointID);
ODE_API void dJointGetLMotorAxis (dJointID, int anum, dVector3 result);
ODE_API dReal dJointGetLMotorParam (dJointID, int parameter);

ODE_API dJointID dConnectingJoint (dBodyID, dBodyID);
ODE_API int dConnectingJointList (dBodyID, dBodyID, dJointID*);
ODE_API int dAreConnected (dBodyID, dBodyID);
ODE_API int dAreConnectedExcluding (dBodyID, dBodyID, int joint_type);


#ifdef __cplusplus
}
#endif

#endif

