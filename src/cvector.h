/*container library for managing dynamic storage
 *supported storage types include
 *char
 *unsigned char
 *int
 *unsigned int
 *long
 *unsigned long
 *long long
 *unsigned long long
 *float
 *double
 *long double
 *others(structs or type defined arrays)
 */
#ifndef CVECTOR_H
#define CVECTOR_H
#pragma once

#ifdef __cplusplus
extern "C"
#endif


/*This defined variable types _other_element and _other_container are to be
 *redefined by the end programmer to use this library to suit his or her needs
 *concerning what type of data that needs to be stored on the container.
 *if a string data of length 6 is stored on the container and the container is
 *to be sorted then the _other_element and _other_container have to be both
 *undefined and redefined to represent a string  as well as the pointer to the
 *container housing the strings respectively
 *i.e:	#ifdef _other_element
 *		#undef _other_element
 *		#endif
 *		#define _other_element char[6]
 *
 *		#ifdef _other_container
 *		#undef _other_container
 *		#endif
 *		#define _other_container char**
 */
#define _other_element void*
#define _other_container void**


/*supported types of container
 *by the library
 */
enum variable
{
	_CHAR,_UCHAR,_SHORT,_USHORT,
	_INT,_UINT,_LONG,_ULONG,
	_LONGLONG,_ULONGLONG,_FLOAT,
	_DOUBLE,__LONGDOUBLE,_OTHER
};

extern void _init_container_(int);
extern void _clear_container_();
extern void* _delete_(void*);
extern void** _delete_other_(void**);
extern void* _create_new_(int,int,enum variable);

extern void* _append_char_(void*,char); //char 0
extern void* _append_uchar_(void*,unsigned char);	//unsigned char 1
extern void* _append_short_(void*,short);	//short 2
extern void* _append_ushort_(void*,unsigned short);	//unsigned short 3
extern void* _append_int_(void*,int);	//int	4
extern void* _append_uint_(void*,unsigned int);	//unsigned int	5
extern void* _append_long_(void*,long);		//long	6
extern void* _append_ulong_(void*,unsigned long); //unsigned long	7
extern void* _append_longlong_(void*,long long);		//long long	8
extern void* _append_ulonglong_(void*,unsigned long long);	//unsigned long long	9
extern void* _append_float_(void*,float);	//float	10
extern void* _append_double_(void*,double);	//double	11
extern void* _append_longdouble_(void*,long double);	//long double	12
extern void* _append_other_(void**,void*);		//others 13

extern void* _remove_(void*,int);
extern void* _remove_other_(void**,int);

extern int _size_(const void* const);
extern int _size_other(const void** const);


extern void _sort_(void*);

/*The compare function to be passed to this _sort_other function should be
 *able to compare two elements of the same data type and return a
 *	0 for both elements being equal
 *	1 for first element greater than the second element
 *	-1 for first element less than the second element
 */
extern void _sort_other_(void**,short compare(_other_element,_other_element));


extern int _lsearch_(const void* const,const void* const);

/*The check_equality function to be passed to this _lsearch_other function
 *should be able to compare to elements of the same data type and return a
 *	1 for both elements being equal
 *	0 for both elements being unequal
 */
extern int _lsearch_other_(const void** const,const void* const,short check_equality(_other_element,_other_element));


extern int _bsearch_(const void* const, const void* const);

/*The compare function to be passed to this _bsearch_other function should be
 *able to compare two elements of the same data type and return a
 *	0 for both elements being equal
 *	1 for first element greater than the second element
 *	-1 for first element less than the second element
 */
extern int _bsearch_other_(const void** const, const void* const,short compare(_other_element,_other_element));

#endif //CVECTOR_H
