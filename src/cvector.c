#include "cvector.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>


#define TRUE 0b0
#define FALSE 0b1
#define _newsize 5
#define _MAX_ALL_ 32700


/*contains the necessary types to control and maintain a
 *dynamic container(array)
 */
struct data
{
	int max_size;
	int size;
	int offset;
	enum variable type;
	void* content;	//for handling normal c variable types like char
	void** other;	//for use in handling c data structures like struct
};


static int TABLE_MAX;
static int TABLE_SIZE=0;
static struct data** _Table;


static inline void* grow_(struct data*);	//increase the size of the container
static inline void* _grow_(struct data*,int);	//decrease the size of the container
static inline short _monitor_self_();

#define sort_element void*
static void sort_self(sort_element,int);


/*initializes the table of containers to be used in a project
 *written in c
 */
void _init_container_(int size)
{
	_Table=calloc(size,sizeof(struct data*));
	TABLE_MAX=size;
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		_Table[i]=0;
	return;
}


//cleanup stored containers in memory before program exit
void _clear_container_()
{
	register int i;
	for(i=0; i<TABLE_SIZE; ++i)
	{
		if(_Table[i]->content!=0)
			free(_Table[i]->content);
		if(_Table[i]->other!=0)
		{
			int j;
			for(j=0; j<_Table[i]->size; ++j)
				if(_Table[i]->other[j]!=0)
					free(_Table[i]->other[j]);
			free(_Table[i]->other);
		}
		free(_Table[i]);
		_Table[i]=0;
	}
	TABLE_SIZE=0;
	return;
}


//delete a container from the table
void* _delete_(void* _ptr)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			free(_Table[i]->content);
			free(_Table[i]);
			_Table[i]=0;
			--TABLE_SIZE;
			return 0;
		}
	return _ptr;
}


void** _delete_other_(void** _ptr)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->other)
		{
			int j;
			for(j=0; j<_Table[i]->size; ++j)
				free(_Table[i]->other[j]);
			free(_Table[i]->other);
			free(_Table[i]);
			_Table[i]=0;
			--TABLE_SIZE;
			return 0;
		}
	return _ptr;
}


//create new container
void* _create_new_(int _size,int _offset,enum variable _type)
{
	assert(_size>0 && _size<=32700 && _offset>0 && _offset<=64 && 0<=_type && _type<=11);
	if(FALSE==_monitor_self_())return 0;
	int i;
	void* _temp=0;
	for(i=0; i<TABLE_MAX; ++i)
		if(_Table[i]==0)
		{
			struct data* temp=calloc(1,sizeof(struct data));
			temp->max_size=_size;
			temp->size=0;
			temp->offset=_offset;
			temp->type=_type;
			if(_type==_OTHER)
			{
				_temp=temp->other=calloc(_size,_offset);
				temp->content=0;
			}
			else
			{
				_temp=temp->content=calloc(_size,_offset);
				temp->other=0;
			}
			_Table[i]=temp;
			++TABLE_SIZE;
			break;
		}
	return _temp;
}


//append to a char type container
void* _append_char_(void* _ptr, char _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size>=_MAX_ALL_)
				return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->content=_ptr;
			}
			char* temp=(char*)_ptr;
			temp[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//append to an unsigned char type container
void* _append_uchar_(void* _ptr, unsigned char _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size>=_MAX_ALL_)
				return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->content=_ptr;
			}
			unsigned char* temp=(unsigned char*)_ptr;
			temp[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//append to a short integer type container
void* _append_short_(void* _ptr, short _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size>=_MAX_ALL_)
				return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->content=_ptr;
			}
			short* temp=(short*)_ptr;
			temp[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//append to a short integer type container
void* _append_ushort_(void* _ptr, unsigned short _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size>=_MAX_ALL_)
				return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->content=_ptr;
			}
			unsigned short* temp=(unsigned short*)_ptr;
			temp[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//append to an integer type container
void* _append_int_(void* _ptr, int _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size>=_MAX_ALL_)
				return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->content=_ptr;
			}
			int* temp=(int*)_ptr;
			temp[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//append to an unsigned integer container
void* _append_uint_(void* _ptr, unsigned int _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size==_MAX_ALL_)
				return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->content=_ptr;
			}
			unsigned int* temp=(unsigned int*)_ptr;
			temp[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//append to a long container
void* _append_long_(void* _ptr, long _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size==_MAX_ALL_)
				return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->content=_ptr;
			}
			long* temp=(long*)_ptr;
			temp[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//append to an unsigned long container
void* _append_ulong_(void* _ptr, unsigned long _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size==_MAX_ALL_)return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->content=_ptr;
			}
			unsigned long* temp=(unsigned long*)_ptr;
			temp[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//append to a long long container
void* _append_longlong_(void* _ptr, long long _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size==_MAX_ALL_)return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->content=_ptr;
			}
			long long* temp=(long long*)_ptr;
			temp[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//append to an unsigned long long container
void* _append_ulonglong_(void* _ptr, unsigned long long _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size==_MAX_ALL_)
				return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->content=_ptr;
			}
			unsigned long long* temp=(unsigned long long*)_ptr;
			temp[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//append to a float container
void* _append_float_(void* _ptr, float _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size==_MAX_ALL_)
				return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->content=_ptr;
			}
			float* temp=(float*)_ptr;
			temp[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//append to a double container
void* _append_double_(void* _ptr, double _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size==_MAX_ALL_)
				return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->content=_ptr;
			}
			double* temp=(double*)_ptr;
			temp[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//append to a long double container
void* _append_longdouble_(void* _ptr, long double _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size==_MAX_ALL_)
				return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->content=_ptr;
			}
			long double* temp=(long double*)_ptr;
			temp[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//append to other types of container
void* _append_other_(void** _ptr, void* _new)
{
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->other)
		{
			if(_Table[i]->size==_MAX_ALL_)
				return _ptr;
			if((_Table[i]->max_size-_Table[i]->size)==1)
			{
				void* temp=grow_(_Table[i]);
				if(temp!=0)
					_ptr=temp;
				else
					return _ptr;
				_Table[i]->other=_ptr;
			}
			_ptr[_Table[i]->size]=_new;
			++_Table[i]->size;
			break;
		}
	return _ptr;
}


//remove an element from the specified container
void* _remove_(void* _ptr, int index)
{
	assert(index>=0);
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size==0)
				break;
			assert(_Table[i]->size>index);
			if(_Table[i]->size==(index+1))
			{
				//non portable and inefficient algorithm which can lead to
				//memory leaks in machines with small heap size memory(RAM)
				--_Table[i]->size;
				register int newsize=_Table[i]->max_size-_Table[i]->size;
				if(newsize>=7)
					_ptr=_grow_(_Table[i],newsize);
				break;
			}
			switch(_Table[i]->type)
			{
				case _CHAR:
				{
					char* temp=(char*)_ptr;
					int j;
					for(j=index; j< (_Table[i]->size-1); ++j)
						temp[j]=temp[j+1];
					break;
				}

				case _UCHAR:
				{
					unsigned char* temp=(unsigned char*)_ptr;
					int j;
					for(j=index; j< (_Table[i]->size-1); ++j)
						temp[j]=temp[j+1];
					break;
				}

				case _SHORT:
				{
					short* temp=(short*)_ptr;
					int j;
					for(j=index; j< (_Table[i]->size-1); ++j)
						temp[j]=temp[j+1];
					break;
				}

				case _USHORT:
				{
					unsigned short* temp=(unsigned short*)_ptr;
					int j;
					for(j=index; j< (_Table[i]->size-1); ++j)
						temp[j]=temp[j+1];
					break;
				}

				case _INT:
				{
					int* temp=(int*)_ptr;
					int j;
					for(j=index; j< (_Table[i]->size-1); ++j)
						temp[j]=temp[j+1];
					break;
				}

				case _UINT:
				{
					unsigned int* temp=(unsigned int*)_ptr;
					int j;
					for(j=index; j< (_Table[i]->size-1); ++j)
						temp[j]=temp[j+1];
					break;
				}

				case _LONG:
				{
					long* temp=(long*)_ptr;
					int j;
					for(j=index; j< (_Table[i]->size-1); ++j)
						temp[j]=temp[j+1];
					break;
				}

				case _ULONG:
				{
					unsigned long* temp=(unsigned long*)_ptr;
					int j;
					for(j=index; j< (_Table[i]->size-1); ++j)
						temp[j]=temp[j+1];
					break;
				}

				case _LONGLONG:
				{
					long long* temp=(long long*)_ptr;
					int j;
					for(j=index; j< (_Table[i]->size-1); ++j)
						temp[j]=temp[j+1];
					break;
				}

				case _ULONGLONG:
				{
					unsigned long long* temp=(unsigned long long*)_ptr;
					int j;
					for(j=index; j< (_Table[i]->size-1); ++j)
						temp[j]=temp[j+1];
					break;
				}

				case _FLOAT:
				{
					float* temp=(float*)_ptr;
					int j;
					for(j=index; j< (_Table[i]->size-1); ++j)
						temp[j]=temp[j+1];
					break;
				}

				case _DOUBLE:
				{
					double* temp=(double*)_ptr;
					int j;
					for(j=index; j< (_Table[i]->size-1); ++j)
						temp[j]=temp[j+1];
					break;
				}

				case __LONGDOUBLE:
				{
					long double* temp=(long double*)_ptr;
					int j;
					for(j=index; j< (_Table[i]->size-1); ++j)
						temp[j]=temp[j+1];
					break;
				}

				default:
					break;
			}
			--_Table[i]->size;
			register int newsize=_Table[i]->max_size-_Table[i]->size;
			if(newsize>=7)
				_ptr=_grow_(_Table[i],newsize);
			break;
		}
	return _ptr;
}


//remove an element from the the specified other type container
void* _remove_other_(void** _ptr, int index)
{
	assert(index>=0);
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->other)
		{
			if(_Table[i]->size==0)
				break;
			assert(_Table[i]->size>index);
			if(_Table[i]->size==(index+1))
			{
				//non portable and inefficient algorithm which can lead to
				//memory leaks in machines with small heap size memory(RAM)
				--_Table[i]->size;
				register int newsize=_Table[i]->max_size-_Table[i]->size;
				if(newsize>=7)
					_ptr=_grow_(_Table[i],newsize);
				break;
			}
			int k;
			for(k=index; k< (_Table[i]->size-1); ++k)
				_ptr[k]=_ptr[k+1];
			--_Table[i]->size;
			register int newsize=_Table[i]->max_size-_Table[i]->size;
			if(newsize>=7)
				_ptr=_grow_(_Table[i],newsize);
			break;
		}
	return _ptr;
}


//returns the size of the specified container
int _size_(const void* const _ptr)
{
	int i,index=0;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			index=_Table[i]->size;
			break;
		}
	return index;
}


//returns the size of the container of type other
int _size_other(const void** const _ptr)
{
	int i,index=0;
	for(i=0; i<TABLE_MAX; ++i)
		if((void**)_ptr==_Table[i]->other)
		{
			index=_Table[i]->size;
			break;
		}
	return index;
}


//expands the container been specified
static inline void* grow_(struct data* _ptr)
{
	void* temp;
	if(_ptr->type==_OTHER)
	{
		_ptr->max_size+=_newsize;
		temp=realloc(_ptr->other,_ptr->max_size*_ptr->offset);
		if(temp==0)
		{
			perror("append operation unsuccessful\n");
			_ptr->max_size-=_newsize;
			return temp;
		}
		else
			_ptr->other=temp;
		return temp;
	}
	_ptr->max_size+=_newsize;
	temp=realloc(_ptr->content,_ptr->max_size*_ptr->offset);
	if(temp==0)
	{
		perror("append operation unsuccessful\n");
		_ptr->max_size-=_newsize;
		return temp;
	}
	else
		_ptr->content=temp;
	return temp;
}


//reduces the size of the container been specified
static inline void* _grow_(struct data* _ptr, int newsize)
{
	void* temp;
	if(_ptr->type==_OTHER)
	{
		_ptr->max_size-=newsize;
		temp=realloc(_ptr->other,_ptr->max_size*_ptr->offset);
		if(temp==0)
		{
			//perror("remove operation unsuccessful\n");
			temp=_ptr->other;
		}
		else
			_ptr->other=temp;
		return temp;
	}
	_ptr->max_size-=newsize;
	temp=realloc(_ptr->content,_ptr->max_size*_ptr->offset);
	if(temp==0)
	{
		//perror("remove operation unsuccessful\n");
		temp=_ptr->content;
	}
	else
		_ptr->content=temp;
	return temp;
}


//monitors the state of the table of containers
static inline short _monitor_self_()
{
	short state=TRUE;
	if(TABLE_SIZE==TABLE_MAX)
		state=FALSE;
	return state;
}


//sub sorting function to improve code readability to be used with normal C data
//variable types
void sort_self(sort_element container, int size)
{
    return;
}


//sorts the given container to enable faster searches like binary searches
void _sort_(void* _ptr)
{
    int i;
    for(i=0; i<TABLE_MAX; ++i)
        if(_ptr==_Table[i]->content)
        {
            switch(_Table[i]->type)
            {
            case _CHAR:
                {
                    #undef sort_element
                    #define sort_element char*
                    sort_element temp=(sort_element)_ptr;
                    sort_self(temp,_Table[i]->size);
                    break;
                }

            case _UCHAR:
                {
                    #undef sort_element
                    #define sort_element unsigned char*
                    sort_element temp=(sort_element)_ptr;
                    sort_self(temp,_Table[i]->size);
                    break;
                }

            case _SHORT:
                {
                    #undef sort_element
                    #define sort_element short*
                    sort_element temp=(sort_element)_ptr;
                    sort_self(temp,_Table[i]->size);
                    break;
                }

            case _USHORT:
                {
                    #undef sort_element
                    #define sort_element unsigned short*
                    sort_element temp=(sort_element)_ptr;
                    sort_self(temp,_Table[i]->size);
                    break;
                }

            case _INT:
                {
                    #undef sort_element
                    #define sort_element int*
                    sort_element temp=(sort_element)_ptr;
                    sort_self(temp,_Table[i]->size);
                    break;
                }

            case _UINT:
                {
                    #undef sort_element
                    #define sort_element unsigned int*
                    sort_element temp=(sort_element)_ptr;
                    sort_self(temp,_Table[i]->size);
                    break;
                }

            case _LONG:
                {
                    #undef sort_element
                    #define sort_element long*
                    sort_element temp=(sort_element)_ptr;
                    sort_self(temp,_Table[i]->size);
                    break;
                }

            case _ULONG:
                {
                    #undef sort_element
                    #define sort_element unsigned long*
                    sort_element temp=(sort_element)_ptr;
                    sort_self(temp,_Table[i]->size);
                    break;
                }

            case _LONGLONG:
                {
                    #undef sort_element
                    #define sort_element long long*
                    sort_element temp=(sort_element)_ptr;
                    sort_self(temp,_Table[i]->size);
                    break;
                }

            case _ULONGLONG:
                {
                    #undef sort_element
                    #define sort_element unsigned long long*
                    sort_element temp=(sort_element)_ptr;
                    sort_self(temp,_Table[i]->size);
                    break;
                }

            case _FLOAT:
                {
                    #undef sort_element
                    #define sort_element float*
                    sort_element temp=(sort_element)_ptr;
                    sort_self(temp,_Table[i]->size);
                    break;
                }

            case _DOUBLE:
                {
                    #undef sort_element
                    #define sort_element double*
                    sort_element temp=(sort_element)_ptr;
                    sort_self(temp,_Table[i]->size);
                    break;
                }

            case __LONGDOUBLE:
                {
                    #undef sort_element
                    #define sort_element long double*
                    sort_element temp=(sort_element)_ptr;
                    sort_self(temp,_Table[i]->size);
                    break;
                }

            default: break;
            }
            break;
        }
	return;
}


//sorts the given container of type other to enable faster searches like binary searches
void _sort_other_(void** _ptr,short compare(_other_element,_other_element))
{
	return;
}




//searches the given container linearly which should be slow if the container size is large
int _lsearch_(const void* const _ptr,const void* const _element)
{
	int index=-1;
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			if(_Table[i]->size==0)
				break;
			switch(_Table[i]->type)
			{
				case _CHAR:
				{
					char* temp=(char*)_ptr;
					int j;
					for(j=0; j<_Table[i]->size; ++j)
						if(temp[j]==*(char*)_element)
						{
							index=j;
							break;
						}
					break;
				}

				case _UCHAR:
				{
					unsigned char* temp=(unsigned char*)_ptr;
					int j;
					for(j=0; j<_Table[i]->size; ++j)
						if(temp[j]==*(unsigned char*)_element)
						{
							index=j;
							break;
						}
					break;
				}

				case _SHORT:
				{
					short* temp=(short*)_ptr;
					int j;
					for(j=0; j<_Table[i]->size; ++j)
						if(temp[j]==*(short*)_element)
						{
							index=j;
							break;
						}
					break;
				}

				case _USHORT:
				{
					unsigned short* temp=(unsigned short*)_ptr;
					int j;
					for(j=0; j<_Table[i]->size; ++j)
						if(temp[j]==*(unsigned short*)_element)
						{
							index=j;
							break;
						}
					break;
				}

				case _INT:
				{
					int* temp=(int*)_ptr;
					int j;
					for(j=0; j<_Table[i]->size; ++j)
						if(temp[j]==*(int*)_element)
						{
							index=j;
							break;
						}
					break;
				}

				case _UINT:
				{
					unsigned int* temp=(unsigned int*)_ptr;
					int j;
					for(j=0; j<_Table[i]->size; ++j)
						if(temp[j]==*(unsigned int*)_element)
						{
							index=j;
							break;
						}
					break;
				}

				case _LONG:
				{
					long* temp=(long*)_ptr;
					int j;
					for(j=0; j<_Table[i]->size; ++j)
						if(temp[j]==*(long*)_element)
						{
							index=j;
							break;
						}
					break;
				}

				case _ULONG:
				{
					unsigned long* temp=(unsigned long*)_ptr;
					int j;
					for(j=0; j<_Table[i]->size; ++j)
						if(temp[j]==*(unsigned long*)_element)
						{
							index=j;
							break;
						}
					break;
				}

				case _LONGLONG:
				{
					long long* temp=(long long*)_ptr;
					int j;
					for(j=0; j<_Table[i]->size; ++j)
						if(temp[j]==*(long long*)_element)
						{
							index=j;
							break;
						}
					break;
				}

				case _ULONGLONG:
				{
					unsigned long long* temp=(unsigned long long*)_ptr;
					int j;
					for(j=0; j<_Table[i]->size; ++j)
						if(temp[j]==*(unsigned long long*)_element)
						{
							index=j;
							break;
						}
					break;
				}

				case _FLOAT:
				{
					float* temp=(float*)_ptr;
					int j;
					for(j=0; j<_Table[i]->size; ++j)
						if(temp[j]==*(float*)_element)
						{
							index=j;
							break;
						}
					break;
				}

				case _DOUBLE:
				{
					double* temp=(double*)_ptr;
					int j;
					for(j=0; j<_Table[i]->size; ++j)
						if(temp[j]==*(double*)_element)
						{
							index=j;
							break;
						}
					break;
				}

				case __LONGDOUBLE:
				{
					long double* temp=(long double*)_ptr;
					int j;
					for(j=0; j<_Table[i]->size; ++j)
						if(temp[j]==*(long double*)_element)
						{
							index=j;
							break;
						}
					break;
				}

				default:
					break;
			}
			break;
		}
	return index;
}


//searches the given container of type other linearly which should be slow if the size of the container is large
int _lsearch_other_(const void** const _ptr,const void* const _element,short check_equality(_other_element,_other_element))
{
	int index=-1;
	int i;
	for(i=0; i<TABLE_SIZE; ++i)
		if((void**)_ptr==_Table[i]->other)
		{
			_other_container temp=(_other_container)_ptr;
			int j;
			for(j=0; j<_Table[j]->size; ++j)
				if(check_equality(temp[j],(_other_element)_element))
				{
					index=j;
					break;
				}
			break;
		}
	return index;
}


//searches the given container using binary algorithm which is more faster than linear search
int _bsearch_(const void* const _ptr,const void* const _element)
{
	int index=-1;
	int low=0,high=0;

	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if(_ptr==_Table[i]->content)
		{
			switch(_Table[i]->type)
			{
				case _CHAR:
				{
					char* temp=(char*)_ptr;
					high=_Table[i]->size-1;
					while(low<=high)
					{
						int midpoint=(low+high)/2;
						if(temp[midpoint]==*(char*)_element)
						{
							index=midpoint;
							break;
						}
						else if(temp[midpoint]>*(char*)_element)
							high=midpoint-1;
						else
							low=midpoint+1;
					}
					break;
				}

				case _UCHAR:
				{
					unsigned char* temp=(unsigned char*)_ptr;
					high=_Table[i]->size-1;
					while(low<=high)
					{
						int midpoint=(low+high)/2;
						if(temp[midpoint]==*(unsigned char*)_element)
						{
							index=midpoint;
							break;
						}
						else if(temp[midpoint]>*(unsigned char*)_element)
							high=midpoint-1;
						else
							low=midpoint+1;
					}
					break;
				}

				case _SHORT:
				{
					short* temp=(short*)_ptr;
					high=_Table[i]->size-1;
					while(low<=high)
					{
						int midpoint=(low+high)/2;
						if(temp[midpoint]==*(short*)_element)
						{
							index=midpoint;
							break;
						}
						else if(temp[midpoint]>*(short*)_element)
							high=midpoint-1;
						else
							low=midpoint+1;
					}
					break;
				}

				case _USHORT:
				{
					unsigned short* temp=(unsigned short*)_ptr;
					high=_Table[i]->size-1;
					while(low<=high)
					{
						int midpoint=(low+high)/2;
						if(temp[midpoint]==*(unsigned short*)_element)
						{
							index=midpoint;
							break;
						}
						else if(temp[midpoint]>*(unsigned short*)_element)
							high=midpoint-1;
						else
							low=midpoint+1;
					}
					break;
				}

				case _INT:
				{
					int* temp=(int*)_ptr;
					high=_Table[i]->size-1;
					while(low<=high)
					{
						int midpoint=(low+high)/2;
						if(temp[midpoint]==*(int*)_element)
						{
							index=midpoint;
							break;
						}
						else if(temp[midpoint]>*(int*)_element)
							high=midpoint-1;
						else
							low=midpoint+1;
					}
					break;
				}

				case _UINT:
				{
					unsigned int* temp=(unsigned int*)_ptr;
					high=_Table[i]->size-1;
					while(low<=high)
					{
						int midpoint=(low+high)/2;
						if(temp[midpoint]==*(unsigned int*)_element)
						{
							index=midpoint;
							break;
						}
						else if(temp[midpoint]>*(unsigned int*)_element)
							high=midpoint-1;
						else
							low=midpoint+1;
					}
					break;
				}

				case _LONG:
				{
					long* temp=(long*)_ptr;
					high=_Table[i]->size-1;
					while(low<=high)
					{
						int midpoint=(low+high)/2;
						if(temp[midpoint]==*(long*)_element)
						{
							index=midpoint;
							break;
						}
						else if(temp[midpoint]>*(long*)_element)
							high=midpoint-1;
						else
							low=midpoint+1;
					}
					break;
				}

				case _ULONG:
				{
					unsigned long* temp=(unsigned long*)_ptr;
					high=_Table[i]->size-1;
					while(low<=high)
					{
						int midpoint=(low+high)/2;
						if(temp[midpoint]==*(unsigned long*)_element)
						{
							index=midpoint;
							break;
						}
						else if(temp[midpoint]>*(unsigned long*)_element)
							high=midpoint-1;
						else
							low=midpoint+1;
					}
					break;
				}

				case _LONGLONG:
				{
					long long* temp=(long long*)_ptr;
					high=_Table[i]->size-1;
					while(low<=high)
					{
						int midpoint=(low+high)/2;
						if(temp[midpoint]==*(long long*)_element)
						{
							index=midpoint;
							break;
						}
						else if(temp[midpoint]>*(long long*)_element)
							high=midpoint-1;
						else
							low=midpoint+1;
					}
					break;
				}

				case _ULONGLONG:
				{
					unsigned long long* temp=(unsigned long long*)_ptr;
					high=_Table[i]->size-1;
					while(low<=high)
					{
						int midpoint=(low+high)/2;
						if(temp[midpoint]==*(unsigned long long*)_element)
						{
							index=midpoint;
							break;
						}
						else if(temp[midpoint]>*(unsigned long long*)_element)
							high=midpoint-1;
						else
							low=midpoint+1;
					}
					break;
				}

				case _FLOAT:
				{
					float* temp=(float*)_ptr;
					high=_Table[i]->size-1;
					while(low<=high)
					{
						int midpoint=(low+high)/2;
						if(temp[midpoint]==*(float*)_element)
						{
							index=midpoint;
							break;
						}
						else if(temp[midpoint]>*(float*)_element)
							high=midpoint-1;
						else
							low=midpoint+1;
					}
					break;
				}

				case _DOUBLE:
				{
					double* temp=(double*)_ptr;
					high=_Table[i]->size-1;
					while(low<=high)
					{
						int midpoint=(low+high)/2;
						if(temp[midpoint]==*(double*)_element)
						{
							index=midpoint;
							break;
						}
						else if(temp[midpoint]>*(double*)_element)
							high=midpoint-1;
						else
							low=midpoint+1;
					}
					break;
				}

				case __LONGDOUBLE:
				{
					long double* temp=(long double*)_ptr;
					high=_Table[i]->size-1;
					while(low<=high)
					{
						int midpoint=(low+high)/2;
						if(temp[midpoint]==*(long double*)_element)
						{
							index=midpoint;
							break;
						}
						else if(temp[midpoint]>*(long double*)_element)
							high=midpoint-1;
						else
							low=midpoint+1;
					}
					break;
				}

				default:
					break;
			}
			break;
		}
	return index;
}

//searches the given container of type other using binary algorithm which is more faster than linear search
int _bsearch_other(const void** const _ptr,const void* const _element,short compare(_other_element,_other_element))
{
	int index=-1;
	int low=0,high=0;
	int i;
	for(i=0; i<TABLE_MAX; ++i)
		if((void**)_ptr==_Table[i]->other)
		{
			_other_container temp=(_other_container)_ptr;
			high=_Table[i]->size-1;
			while(low<=high)
			{
				int midpoint=(low+high)/2;
				if(compare(temp[midpoint],(_other_element)_element)==0)
				{
					index=midpoint;
					break;
				}
				else if(compare(temp[midpoint],(_other_element)_element)==1)
					high=midpoint-1;
				else
					low=midpoint+1;
			}
			break;
		}
	return index;
}
