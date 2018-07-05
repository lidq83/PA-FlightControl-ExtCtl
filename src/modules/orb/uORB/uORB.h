/*
 * gorb.h
 *
 *  Created on: May 16, 2018
 *      Author: lidq
 */

#ifndef SRC_GORB_GORB_H_
#define SRC_GORB_GORB_H_

/**
 * Object metadata.
 */
struct orb_metadata
{
	const char *o_name; /**< unique object name */
	const size_t o_size; /**< object size */
	const size_t o_size_no_padding; /**< object size w/o padding at the end (for logger) */
	const char *o_fields; /**< semicolon separated list of fields (with type) */
};

typedef const struct orb_metadata *orb_id_t;

/**
 * Maximum number of multi topic instances
 */
#define ORB_MULTI_MAX_INSTANCES	4 // This must be < 10 (because it's the last char of the node path)

/**
 * Topic priority.
 * Relevant for multi-topics / topic groups
 */
enum ORB_PRIO
{
	ORB_PRIO_MIN = 1, // leave 0 free for other purposes, eg. marking an uninitialized value
	ORB_PRIO_VERY_LOW = 25,
	ORB_PRIO_LOW = 50,
	ORB_PRIO_DEFAULT = 75,
	ORB_PRIO_HIGH = 100,
	ORB_PRIO_VERY_HIGH = 125,
	ORB_PRIO_MAX = 255
};

/**
 * Generates a pointer to the uORB metadata structure for
 * a given topic.
 *
 * The topic must have been declared previously in scope
 * with ORB_DECLARE().
 *
 * @param _name		The name of the topic.
 */
#define ORB_ID(_name)		&__orb_##_name

/**
 * Declare (prototype) the uORB metadata for a topic (used by code generators).
 *
 * @param _name		The name of the topic.
 */
#if defined(__cplusplus)
# define ORB_DECLARE(_name)		extern "C" const struct orb_metadata __orb_##_name
#else
# define ORB_DECLARE(_name)		extern const struct orb_metadata __orb_##_name
#endif

/**
 * Define (instantiate) the uORB metadata for a topic.
 *
 * The uORB metadata is used to help ensure that updates and
 * copies are accessing the right data.
 *
 * Note that there must be no more than one instance of this macro
 * for each topic.
 *
 * @param _name		The name of the topic.
 * @param _struct	The structure the topic provides.
 * @param _size_no_padding	Struct size w/o padding at the end
 * @param _fields	All fields in a semicolon separated list e.g: "float[3] position;bool armed"
 */
#define ORB_DEFINE(_name, _struct, _size_no_padding, _fields)		\
	const struct orb_metadata __orb_##_name = {	\
		#_name,					\
		sizeof(_struct),		\
		_size_no_padding,			\
		_fields					\
	}; struct hack

#endif /* SRC_GORB_GORB_H_ */
