#include "cvector.h"
#include <stdio.h>

int main()
{
	_init_container_(5);
	short* test=_create_new_(1,sizeof(short),_SHORT);
	if(test==0)
		printf("couldn't create the container\n");
	else
		printf("container creation successful and pointer to new container is %p\n",(void*)test);
	test=(short*)_append_short_(test,9);
	test=(short*)_append_short_(test,18);
	test=(short*)_append_short_(test,36);
	printf("size of container is %d and contains the element %d & %d & %d\n",_size_(test),test[0],test[1],test[2]);
	short _18=18;
	printf("searching for number 18 in the test array. -1 for not found. Index(18): %d\n",_bsearch_(test,&_18));
	test=_remove_(test,1);
	printf("size of container is %d and contains the element %d & %d\n",_size_(test),test[0],test[1]);
	test=_delete_(test);
	if(test==0)
		printf("delete operation successful\n");
	else
		printf("delete operation unsuccessful and pointer still remains %p\n",(void*)test);
	_clear_container_();
	return 0;
}
